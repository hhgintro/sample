#pragma once



class C2M_SEND : public NetCore::INetCore
{
public:
	C2M_SEND() {}
	virtual ~C2M_SEND() {}

	inline void SEND_C2M_MT_SERVER_LIST_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_SERVER_LIST_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LIST_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LIST_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_SERVER_LIST_REQ)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_SERVER_LIST_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_SERVER_LIST_ACK(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_SERVER_LIST_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LIST_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LIST_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_SERVER_LIST_ACK)
			<< st.serverinfo
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_SERVER_LIST_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_ADD_SERVER_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_ADD_SERVER_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_ADD_SERVER_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_ADD_SERVER_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_ADD_SERVER_REQ)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_ADD_SERVER_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_ADD_SERVER_ACK(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_ADD_SERVER_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_ADD_SERVER_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_ADD_SERVER_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_ADD_SERVER_ACK)
			<< st.serverinfo
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_ADD_SERVER_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_DELETE_SERVER_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_DELETE_SERVER_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_DELETE_SERVER_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_DELETE_SERVER_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_DELETE_SERVER_REQ)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_DELETE_SERVER_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_DELETE_SERVER_ACK(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_DELETE_SERVER_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_DELETE_SERVER_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_DELETE_SERVER_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_DELETE_SERVER_ACK)
			<< st.remote
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_DELETE_SERVER_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_GAME_SERVER_INFO_NTF(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_GAME_SERVER_INFO_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_GAME_SERVER_INFO_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_GAME_SERVER_INFO_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_GAME_SERVER_INFO_NTF)
			<< st.gameinfo
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_GAME_SERVER_INFO_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_CHANGE_SERVER_STATUS_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_CHANGE_SERVER_STATUS_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CHANGE_SERVER_STATUS_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CHANGE_SERVER_STATUS_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_CHANGE_SERVER_STATUS_REQ)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_CHANGE_SERVER_STATUS_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_CHANGE_SERVER_STATUS_ACK(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_CHANGE_SERVER_STATUS_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CHANGE_SERVER_STATUS_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CHANGE_SERVER_STATUS_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_CHANGE_SERVER_STATUS_ACK)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_CHANGE_SERVER_STATUS_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_SERVER_LAUNCH_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_SERVER_LAUNCH_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LAUNCH_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_LAUNCH_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_SERVER_LAUNCH_REQ)
			<< st.serverinfo
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_SERVER_LAUNCH_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_SERVER_SHUTDOWN_REQ(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_SERVER_SHUTDOWN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_SHUTDOWN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_SERVER_SHUTDOWN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_SERVER_SHUTDOWN_REQ)
			<< st.serverinfo
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_SERVER_SHUTDOWN_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_C2M_MT_CLEAR_SERVER_LIST_NTF(HOSTID remote, PACKET_CONTEXT context, stC2M_MT_CLEAR_SERVER_LIST_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CLEAR_SERVER_LIST_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send C2M_MT_CLEAR_SERVER_LIST_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(C2M_MT_CLEAR_SERVER_LIST_NTF)
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
		LOGEVENT("Session_Base_Packet", _T("==> send C2M_MT_CLEAR_SERVER_LIST_NTF to peer(0x%08x)"), remote);
	};


};
