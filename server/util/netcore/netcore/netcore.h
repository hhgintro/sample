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

			//Server���� ����Ǿ��ٸ�
			//	bUdp �̸� GetUdpSession() ����
			//	bTcp �̸� peer ����
			//Client���� ����Ǿ��ٸ�
			//	bUdp �̸� GetUdpSession() ����
			//	bTcp �̸� GetTcpSession() ����
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
			//HG_TODO : ������ Encrypt�Ǿ����ٵ�...�� Encrypt ?? ��???
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
				//hole punching(public) üũ
			case NetCore::enPublicAttempt:
			case NetCore::enPublicSuccess:
				session->SendToPacket(msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicUdpPort());
				break;

				//hole punching(private) üũ
			case NetCore::enPrivateAttempt:
			case NetCore::enPrivateSuccess:
				session->SendToPacket(msgSend, peer->GetRemotePrivateIP(), peer->GetRemotePrivateUdpPort());
				break;

				//hole punching ����(public����/private����)�� ���� ������ �����Ѵ�.
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