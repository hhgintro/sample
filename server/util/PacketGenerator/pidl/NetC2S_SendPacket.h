#pragma once



class NetC2S_SEND : public NetCore::INetCore
{
public:
	NetC2S_SEND() {}
	virtual ~NetC2S_SEND() {}

	inline void SEND_NetC2S_CORE_CONNECT_COMPLETED_NTF(HOSTID remote, stNetC2S_CORE_CONNECT_COMPLETED_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_CONNECT_COMPLETED_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_CONNECT_COMPLETED_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_CONNECT_COMPLETED_NTF)
			<< st.remote
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_CONNECT_COMPLETED_NTF to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_SIGN_UP_REQ(HOSTID remote, stNetC2S_CORE_SIGN_UP_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_SIGN_UP_REQ not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_SIGN_UP_REQ not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_SIGN_UP_REQ)
			<< st.version
			<< st.entry
			<< st.serverTcpPort
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_SIGN_UP_REQ to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_SIGN_UP_ACK(HOSTID remote, stNetC2S_CORE_SIGN_UP_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_SIGN_UP_ACK not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_SIGN_UP_ACK not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_SIGN_UP_ACK)
			<< st.result
			<< st.servertime
			<< st.udpport
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_SIGN_UP_ACK to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_HEART_BEAT_REQ(HOSTID remote, stNetC2S_CORE_HEART_BEAT_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HEART_BEAT_REQ not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HEART_BEAT_REQ not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_HEART_BEAT_REQ)
			<< st.servertime
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_HEART_BEAT_REQ to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_HEART_BEAT_ACK(HOSTID remote, stNetC2S_CORE_HEART_BEAT_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HEART_BEAT_ACK not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HEART_BEAT_ACK not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_HEART_BEAT_ACK)
			<< st.servertime
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_HEART_BEAT_ACK to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_JOIN_GROUP_NTF(HOSTID remote, stNetC2S_CORE_JOIN_GROUP_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_JOIN_GROUP_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_JOIN_GROUP_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_JOIN_GROUP_NTF)
			<< st.group
			<< st.peerinfo
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_JOIN_GROUP_NTF to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_ENTER_GROUP_NTF(HOSTID remote, stNetC2S_CORE_ENTER_GROUP_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_ENTER_GROUP_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_ENTER_GROUP_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_ENTER_GROUP_NTF)
			<< st.group
			<< st.peerinfo
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_ENTER_GROUP_NTF to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_LEAVE_GROUP_NTF(HOSTID remote, stNetC2S_CORE_LEAVE_GROUP_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_LEAVE_GROUP_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_LEAVE_GROUP_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_LEAVE_GROUP_NTF)
			<< st.group
			<< st.remote
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_LEAVE_GROUP_NTF to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HOSTID remote, stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ)
			<< st.remote
			<< st.privateIP
			<< st.privatePort
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(HOSTID remote, stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK)
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(HOSTID remote, stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ)
			<< st.remoteTos
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF(HOSTID remote, stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF)
			<< st.remoteFrom
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(HOSTID remote, stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,false);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF)
			<< st.result
			<< st.remoteFrom
			<< st.remoteTo
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		session->SendPacket(msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF to peer(0x%p)"), remote);
	};


};
