#pragma once



inline void RECV_X2B_AC_LOGIN_REQ(HisUtil::CMsg& msgRecv, stX2B_AC_LOGIN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.account
		>> st.authkey
		>> st.version
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_AC_LOGIN_REQ"));
}


inline void RECV_X2B_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv, stX2B_AC_LOGIN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.result_noti
		>> st.masterkey
		>> st.game
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_AC_LOGIN_ACK"));
}


inline void RECV_X2B_CH_JOIN_GROUP_REQ(HisUtil::CMsg& msgRecv, stX2B_CH_JOIN_GROUP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_CH_JOIN_GROUP_REQ"));
}


inline void RECV_X2B_CH_LEAVE_GROUP_REQ(HisUtil::CMsg& msgRecv, stX2B_CH_LEAVE_GROUP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.group
		>> st.remote
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_CH_LEAVE_GROUP_REQ"));
}


inline void RECV_X2B_CH_UDP_HELLO_PEER_REQ(HisUtil::CMsg& msgRecv, stX2B_CH_UDP_HELLO_PEER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_CH_UDP_HELLO_PEER_REQ"));
}


inline void RECV_X2B_CH_UDP_FINE_THANKS_PEER_ACK(HisUtil::CMsg& msgRecv, stX2B_CH_UDP_FINE_THANKS_PEER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2B_CH_UDP_FINE_THANKS_PEER_ACK"));
}
