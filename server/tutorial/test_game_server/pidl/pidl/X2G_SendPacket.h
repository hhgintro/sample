#pragma once



class X2G_SEND : public NetCore::INetCore
{
public:
	X2G_SEND() {}
	virtual ~X2G_SEND() {}

	inline void SEND_X2G_AC_LOGIN_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_AC_LOGIN_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_AC_LOGIN_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_AC_LOGIN_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_AC_LOGIN_REQ)
			<< st.account
			<< st.password
			<< st.protocol
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_AC_LOGIN_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_AC_LOGIN_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_AC_LOGIN_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_AC_LOGIN_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_AC_LOGIN_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_AC_LOGIN_ACK)
			<< st.result
			<< st.accountpk
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_AC_LOGIN_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_IN_EQUIP_LOAD_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_IN_EQUIP_LOAD_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_LOAD_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_LOAD_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_IN_EQUIP_LOAD_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_IN_EQUIP_LOAD_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_IN_EQUIP_LOAD_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_IN_EQUIP_LOAD_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_LOAD_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_LOAD_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_IN_EQUIP_LOAD_ACK)
			<< st.inven
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_IN_EQUIP_LOAD_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_IN_EQUIP_UPDATE_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_IN_EQUIP_UPDATE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_UPDATE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_UPDATE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_IN_EQUIP_UPDATE_REQ)
			<< st.inven
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_IN_EQUIP_UPDATE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_IN_EQUIP_UPDATE_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_IN_EQUIP_UPDATE_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_UPDATE_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_IN_EQUIP_UPDATE_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_IN_EQUIP_UPDATE_ACK)
			<< st.result
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_IN_EQUIP_UPDATE_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_SQUARE_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_SQUARE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_SQUARE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_SQUARE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_SQUARE_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_SQUARE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_ROOM_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_ROOM_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_ROOM_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_ROOM_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_ROOM_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_ROOM_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_ROOM_ACK)
			<< st.result
			<< st.players
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_ROOM_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_ROOM_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_ROOM_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_ROOM_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_ROOM_NTF)
			<< st.player
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_ROOM_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_SQUARE_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_SQUARE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_SQUARE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_SQUARE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_SQUARE_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_SQUARE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_ROOM_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_ROOM_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_ROOM_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_ROOM_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_ROOM_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_ROOM_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_ROOM_ACK)
			<< st.result
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_ROOM_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_ROOM_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_ROOM_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_ROOM_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_ROOM_NTF)
			<< st.accountpk
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_ROOM_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_PARTY_LIST_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_PARTY_LIST_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_PARTY_LIST_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_PARTY_LIST_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_PARTY_LIST_REQ)
			<< st.type
			<< st.page
			<< st.cnt
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_PARTY_LIST_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_PARTY_LIST_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_PARTY_LIST_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_PARTY_LIST_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_PARTY_LIST_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_PARTY_LIST_ACK)
			<< st.parties
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_PARTY_LIST_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_CREATE_PARTY_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_CREATE_PARTY_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CREATE_PARTY_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CREATE_PARTY_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_CREATE_PARTY_REQ)
			<< st.type
			<< st.maxplayer
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_CREATE_PARTY_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_CREATE_PARTY_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_CREATE_PARTY_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CREATE_PARTY_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CREATE_PARTY_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_CREATE_PARTY_ACK)
			<< st.result
			<< st.info
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_CREATE_PARTY_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_PARTY_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_PARTY_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_PARTY_REQ)
			<< st.index
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_PARTY_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_PARTY_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_PARTY_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_PARTY_ACK)
			<< st.result
			<< st.info
			<< st.players
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_PARTY_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_ENTER_PARTY_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_ENTER_PARTY_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_ENTER_PARTY_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_ENTER_PARTY_NTF)
			<< st.player
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_ENTER_PARTY_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_PARTY_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_PARTY_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_PARTY_REQ)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_PARTY_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_PARTY_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_PARTY_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_PARTY_ACK)
			<< st.result
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_PARTY_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_LEAVE_PARTY_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_LEAVE_PARTY_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_LEAVE_PARTY_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_LEAVE_PARTY_NTF)
			<< st.accountpk
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_LEAVE_PARTY_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_CLOSED_PARTY_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_CLOSED_PARTY_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CLOSED_PARTY_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_CLOSED_PARTY_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_CLOSED_PARTY_NTF)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_CLOSED_PARTY_NTF to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_MOVE_REQ(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_MOVE_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_REQ not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_REQ not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_MOVE_REQ)
			<< st.pos
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_MOVE_REQ to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_MOVE_ACK(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_MOVE_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_ACK not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_ACK not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_MOVE_ACK)
			<< st.result
			<< st.pos
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_MOVE_ACK to peer(0x%08x)"), remote);
	};


	inline void SEND_X2G_RM_MOVE_NTF(HOSTID remote, PACKET_CONTEXT context, stX2G_RM_MOVE_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_NTF not found peer(0x%08x)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send X2G_RM_MOVE_NTF not found session(0x%08x)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(context);
		msgSend.ID(X2G_RM_MOVE_NTF)
			<< st.accountpk
			<< st.pos
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send X2G_RM_MOVE_NTF to peer(0x%08x)"), remote);
	};


};
