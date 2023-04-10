#pragma once



class G2DB_SEND : public NetCore::INetCore
{
public:
	G2DB_SEND() {}
	virtual ~G2DB_SEND() {}

	inline void SEND_G2DB_AC_LOGIN_REQ(HOSTID remote, PACKET_CONTEXT context, stG2DB_AC_LOGIN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_AC_LOGIN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_AC_LOGIN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_AC_LOGIN_REQ)
			<< st.account
			<< st.password
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_AC_LOGIN_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_G2DB_AC_LOGIN_ACK(HOSTID remote, PACKET_CONTEXT context, stG2DB_AC_LOGIN_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_AC_LOGIN_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_AC_LOGIN_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_AC_LOGIN_ACK)
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_AC_LOGIN_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_G2DB_IN_EQUIP_LOAD_REQ(HOSTID remote, PACKET_CONTEXT context, stG2DB_IN_EQUIP_LOAD_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_LOAD_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_LOAD_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_IN_EQUIP_LOAD_REQ)
			<< st.remoteX
			<< st.accountpk
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_IN_EQUIP_LOAD_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_G2DB_IN_EQUIP_LOAD_ACK(HOSTID remote, PACKET_CONTEXT context, stG2DB_IN_EQUIP_LOAD_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_LOAD_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_LOAD_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_IN_EQUIP_LOAD_ACK)
			<< st.remoteX
			<< st.inven
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_IN_EQUIP_LOAD_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_G2DB_IN_EQUIP_UPDATE_REQ(HOSTID remote, PACKET_CONTEXT context, stG2DB_IN_EQUIP_UPDATE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_UPDATE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_UPDATE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_IN_EQUIP_UPDATE_REQ)
			<< st.remoteX
			<< st.accountpk
			<< st.inven
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_IN_EQUIP_UPDATE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_G2DB_IN_EQUIP_UPDATE_ACK(HOSTID remote, PACKET_CONTEXT context, stG2DB_IN_EQUIP_UPDATE_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_UPDATE_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send G2DB_IN_EQUIP_UPDATE_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.ID(G2DB_IN_EQUIP_UPDATE_ACK)
			<< st.remoteX
			<< st.result
			<< st.inven
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
		LOGEVENT("Session_Base_Packet", _T("==> send G2DB_IN_EQUIP_UPDATE_ACK to peer(0x%08x)"), remote);
	};


};
