#pragma once



class NetC2C_SEND : public NetCore::INetCore
{
public:
	NetC2C_SEND() {}
	virtual ~NetC2C_SEND() {}

	inline void SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(HOSTID remote, stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::UNRELIABLE);
		msgSend.ID(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ)
			<< st.remoteFrom
			<< st.remoteTo
			<< st.bpublic
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ to peer(0x%p)"), remote);
	};


	inline void SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(HOSTID remote, stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK& st)
	{
		NetCore::IRemote* peer = FindRemote(remote);
		if(NULL == peer)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK not found peer(0x%p)"), remote);
			return;
		}

		NetCore::CPacketSession* session = FindPacketSession(peer,true);
		if(NULL == session)
		{
			LOGEVENT("Session_Base_Error", _T("Fail send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK not found session(0x%p)"), remote);
			return;
		}

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::UNRELIABLE);
		msgSend.ID(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK)
			<< st.remoteFrom
			<< st.remoteTo
			<< st.bpublic
			;
		HisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);

		SendUdpPacket(peer, session, msgSend);
		msgSend.Clear();
		LOGEVENT("Session_Base_Packet", _T("==> send NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK to peer(0x%p)"), remote);
	};


};
