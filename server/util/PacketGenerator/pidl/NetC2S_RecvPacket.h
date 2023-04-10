#pragma once



inline void RECV_NetC2S_CORE_CONNECT_COMPLETED_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_CONNECT_COMPLETED_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_CONNECT_COMPLETED_NTF"));
}


inline void RECV_NetC2S_CORE_SIGN_UP_REQ(HisUtil::CMsg& msgRecv, stNetC2S_CORE_SIGN_UP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.version
		>> st.entry
		>> st.serverTcpPort
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_SIGN_UP_REQ"));
}


inline void RECV_NetC2S_CORE_SIGN_UP_ACK(HisUtil::CMsg& msgRecv, stNetC2S_CORE_SIGN_UP_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.servertime
		>> st.udpport
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_SIGN_UP_ACK"));
}


inline void RECV_NetC2S_CORE_HEART_BEAT_REQ(HisUtil::CMsg& msgRecv, stNetC2S_CORE_HEART_BEAT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.servertime
		;

	LOGEVENT("Heart_Beat_Packet", _T("<== recv NetC2S_CORE_HEART_BEAT_REQ"));
}


inline void RECV_NetC2S_CORE_HEART_BEAT_ACK(HisUtil::CMsg& msgRecv, stNetC2S_CORE_HEART_BEAT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.servertime
		;

	LOGEVENT("Heart_Beat_Packet", _T("<== recv NetC2S_CORE_HEART_BEAT_ACK"));
}


inline void RECV_NetC2S_CORE_JOIN_GROUP_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_JOIN_GROUP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.group
		>> st.peerinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_JOIN_GROUP_NTF"));
}


inline void RECV_NetC2S_CORE_ENTER_GROUP_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_ENTER_GROUP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.group
		>> st.peerinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_ENTER_GROUP_NTF"));
}


inline void RECV_NetC2S_CORE_LEAVE_GROUP_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_LEAVE_GROUP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.group
		>> st.remote
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_LEAVE_GROUP_NTF"));
}


inline void RECV_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HisUtil::CMsg& msgRecv, stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		>> st.privateIP
		>> st.privatePort
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ"));
}


inline void RECV_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(HisUtil::CMsg& msgRecv, stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK"));
}


inline void RECV_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(HisUtil::CMsg& msgRecv, stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteTos
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ"));
}


inline void RECV_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF"));
}


inline void RECV_NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(HisUtil::CMsg& msgRecv, stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.remoteFrom
		>> st.remoteTo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF"));
}
