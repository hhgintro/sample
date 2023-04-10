#pragma once



inline void RECV_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(HisUtil::CMsg& msgRecv, stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		>> st.bpublic
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ"));
}


inline void RECV_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(HisUtil::CMsg& msgRecv, stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		>> st.bpublic
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK"));
}
