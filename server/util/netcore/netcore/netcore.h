#pragma once

namespace NetCore {


	struct stCORE_UDP_RELAY_SERVER_TO_PEER_NTF
	{
		stCORE_UDP_RELAY_SERVER_TO_PEER_NTF()
			: remoteTo(0)
		{
		}

		HOSTID remoteTo;
		//PACKET_CONTEXT context;
		HisUtil::CMsg msg;
	};


	class INetCore
	{
	protected:
		virtual IRemote* FindRemote(HOSTID remote) = 0;
		virtual CPacketSession* FindPacketSession(IRemote* peer, bool bIsUdp) = 0;

	public:
		INetCore() {}
		virtual ~INetCore() {}

		inline void SEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HOSTID remoteTo, HisUtil::CMsg& msg)
		{
			LOGEVENT("Network_Packet_Number_Info", _T("send udp relay data...remoteTo(0x%p) packet id(0x%04x) packet num(%d)"), remoteTo, msg.ID(), msg.GetNum());

			IRemote* peer = FindRemote(Host_Server);
			if (NULL == peer)
				return;

			//Server에서 선언되었다면
			//	bUdp 이면 GetUdpSession() 리턴
			//	bTcp 이면 peer 리턴
			//Client에서 선언되었다면
			//	bUdp 이면 GetUdpSession() 리턴
			//	bTcp 이면 GetTcpSession() 리턴
			CPacketSession* session = FindPacketSession(peer,true);
			if (NULL == session)
				return;

			HisUtil::CMsg msgSend;
			msgSend.SetContext(msg.GetContext());
			msgSend.ID(CORE_UDP_RELAY_SERVER_TO_PEER_NTF)
				<< remoteTo
				//<< context
				<< msg
				;
			//HG_TODO : 위에서 Encrypt되었을텐데...또 Encrypt ?? 왜???
			HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

			session->SendToPacket(msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicUdpPort());
			msgSend.Clear();
		}

		inline void RECV_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HisUtil::CMsg& msgRecv, stCORE_UDP_RELAY_SERVER_TO_PEER_NTF& st)
		{
			HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
			msgRecv
				>> st.remoteTo
				//>> st.context
				>> st.msg
				;

			LOGEVENT("Network_Packet_Number_Info", _T("recv udp relay data...remoteTo(0x%p) packet id(0x%04x) packet num(%d)"), st.remoteTo, st.msg.ID(), st.msg.GetNum());
		}


		inline void SendUdpPacket(IRemote* peer, CPacketSession* session, HisUtil::CMsg& msgSend)
		{
			if (NULL == peer || NULL == session)
				return;

			switch (peer->GetHolePunchingStep())
			{
				//hole punching(public) 체크
			case NetCore::enPublicAttempt:
			case NetCore::enPublicSuccess:
				session->SendToPacket(msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicUdpPort());
				break;

				//hole punching(private) 체크
			case NetCore::enPrivateAttempt:
			case NetCore::enPrivateSuccess:
				session->SendToPacket(msgSend, peer->GetRemotePrivateIP(), peer->GetRemotePrivateUdpPort());
				break;

				//hole punching 실패(public실패/private실패)한 경우는 서버를 경유한다.
			case NetCore::enPrivateFailed:
				SEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), msgSend);
				break;

			default:
				session->SendPacket(msgSend);
				break;
			}
		}

	};//..class INetCore

};//..namespace NetCore {