#pragma once



class B2L_SEND : public NetCore::INetCore
{
public:
	B2L_SEND() {}
	virtual ~B2L_SEND() {}

	inline void SEND_B2L_AC_LOGIN_REQ(HOSTID remote, PACKET_CONTEXT context, stB2L_AC_LOGIN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send B2L_AC_LOGIN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send B2L_AC_LOGIN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(B2L_AC_LOGIN_REQ)
			<< st.account
			<< st.authkey
			<< st.remoteBalance
			<< st.remoteX
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		switch (peer->GetHolePunchingStep())
		{
		//hole punching 체크
		case NetCore::enAttempt:
		case NetCore::enSuccess:
			session->SendToPacket(context, msgSend, peer->GetRemoteIP(), peer->GetRemoteUdpPort());
			break;

		//hole punching 실패한 경우는 서버를 경유한다.
		case NetCore::enFailed:
			SEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);
			break;

		default:
			session->SendPacket(msgSend);
			break;
		}

		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send B2L_AC_LOGIN_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_B2L_AC_LOGIN_ACK(HOSTID remote, PACKET_CONTEXT context, stB2L_AC_LOGIN_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send B2L_AC_LOGIN_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send B2L_AC_LOGIN_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(B2L_AC_LOGIN_ACK)
			<< st.result
			<< st.result_noti
			<< st.remoteX
			<< st.accountpk
			<< st.account
			<< st.masterkey
			<< st.gameserverno
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		switch (peer->GetHolePunchingStep())
		{
		//hole punching 체크
		case NetCore::enAttempt:
		case NetCore::enSuccess:
			session->SendToPacket(context, msgSend, peer->GetRemoteIP(), peer->GetRemoteUdpPort());
			break;

		//hole punching 실패한 경우는 서버를 경유한다.
		case NetCore::enFailed:
			SEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);
			break;

		default:
			session->SendPacket(msgSend);
			break;
		}

		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send B2L_AC_LOGIN_ACK to peer(0x%08x)"), remote);
	};


};
