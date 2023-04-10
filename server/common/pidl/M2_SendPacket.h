#pragma once



class M2_SEND : public NetCore::INetCore
{
public:
	M2_SEND() {}
	virtual ~M2_SEND() {}

	inline void SEND_M2_JOIN_GROUP_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_JOIN_GROUP_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_JOIN_GROUP_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_JOIN_GROUP_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_JOIN_GROUP_REQ)
			<< st.remote
			<< st.serverinfo
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_JOIN_GROUP_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_CH_UDP_HELLO_PEER_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_CH_UDP_HELLO_PEER_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_HELLO_PEER_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_HELLO_PEER_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_CH_UDP_HELLO_PEER_REQ)
			<< st.remoteFrom
			<< st.remoteTo
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_CH_UDP_HELLO_PEER_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_CH_UDP_FINE_THANKS_PEER_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_CH_UDP_FINE_THANKS_PEER_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_FINE_THANKS_PEER_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_FINE_THANKS_PEER_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_CH_UDP_FINE_THANKS_PEER_ACK)
			<< st.remoteFrom
			<< st.remoteTo
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_CH_UDP_FINE_THANKS_PEER_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_CH_UDP_CURRENT_USER_NTF(HOSTID remote, PACKET_CONTEXT context, stM2_CH_UDP_CURRENT_USER_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_CURRENT_USER_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_CH_UDP_CURRENT_USER_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_CH_UDP_CURRENT_USER_NTF)
			<< st.serverinfo
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_CH_UDP_CURRENT_USER_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_LOGIN_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_AC_LOGIN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_AC_LOGIN_REQ)
			<< st.accountpk
			<< st.account
			<< st.gameserverno
			<< st.remoteBalance
			<< st.remoteX
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_LOGIN_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_LOGIN_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_AC_LOGIN_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_AC_LOGIN_ACK)
			<< st.result
			<< st.result_noti
			<< st.remoteBalance
			<< st.remoteX
			<< st.accountpk
			<< st.account
			<< st.masterkey
			<< st.gameserverno
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_LOGIN_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_LOGOUT_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_AC_LOGOUT_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGOUT_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGOUT_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_AC_LOGOUT_REQ)
			<< st.accountpk
			<< st.entry
			<< st.remoteServer
			<< st.remoteX
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_LOGOUT_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_UDP_CHANGE_SERVER_STATUS_NTF(HOSTID remote, PACKET_CONTEXT context, stM2_UDP_CHANGE_SERVER_STATUS_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_UDP_CHANGE_SERVER_STATUS_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_UDP_CHANGE_SERVER_STATUS_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_UDP_CHANGE_SERVER_STATUS_NTF)
			<< st.remote
			<< st.status
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_UDP_CHANGE_SERVER_STATUS_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_CERTIFY_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_AC_CERTIFY_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_CERTIFY_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_CERTIFY_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_AC_CERTIFY_REQ)
			<< st.account
			<< st.masterkey
			<< st.remoteGame
			<< st.remoteX
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_CERTIFY_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_CERTIFY_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_AC_CERTIFY_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_CERTIFY_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_CERTIFY_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(M2_AC_CERTIFY_ACK)
			<< st.result
			<< st.remoteX
			<< st.accountpk
			<< st.account
			;
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
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_CERTIFY_ACK to peer(0x%08x)"), remote);
	};


};
