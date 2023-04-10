#pragma once



class M2_SEND : public NetCore::INetCore
{
public:
	M2_SEND() {}
	virtual ~M2_SEND() {}

	inline void SEND_M2_BD_VOICE_CHAT_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_BD_VOICE_CHAT_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_BD_VOICE_CHAT_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_BD_VOICE_CHAT_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_BD_VOICE_CHAT_REQ)
			<< st.chat
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_BD_VOICE_CHAT_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_BD_VOICE_CHAT_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_BD_VOICE_CHAT_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_BD_VOICE_CHAT_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_BD_VOICE_CHAT_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_BD_VOICE_CHAT_ACK)
			<< st.chat
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_BD_VOICE_CHAT_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_AC_LOGIN_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_AC_LOGIN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_AC_LOGIN_REQ)
			<< st.account
			<< st.password
			<< st.remoteX
			;
		session->SendPacket(msgSend);
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

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_AC_LOGIN_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_AC_LOGIN_ACK)
			<< st.result
			<< st.remoteX
			<< st.accountpk
			<< st.account
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_AC_LOGIN_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_IN_EQUIP_LOAD_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_IN_EQUIP_LOAD_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_LOAD_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_LOAD_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_IN_EQUIP_LOAD_REQ)
			<< st.remoteX
			<< st.accountpk
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_IN_EQUIP_LOAD_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_IN_EQUIP_LOAD_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_IN_EQUIP_LOAD_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_LOAD_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_LOAD_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_IN_EQUIP_LOAD_ACK)
			<< st.remoteX
			<< st.inven
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_IN_EQUIP_LOAD_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_IN_EQUIP_UPDATE_REQ(HOSTID remote, PACKET_CONTEXT context, stM2_IN_EQUIP_UPDATE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_UPDATE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_UPDATE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_IN_EQUIP_UPDATE_REQ)
			<< st.remoteX
			<< st.accountpk
			<< st.inven
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_IN_EQUIP_UPDATE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_M2_IN_EQUIP_UPDATE_ACK(HOSTID remote, PACKET_CONTEXT context, stM2_IN_EQUIP_UPDATE_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_UPDATE_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send M2_IN_EQUIP_UPDATE_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(M2_IN_EQUIP_UPDATE_ACK)
			<< st.remoteX
			<< st.result
			<< st.inven
			;
		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send M2_IN_EQUIP_UPDATE_ACK to peer(0x%08x)"), remote);
	};


};
