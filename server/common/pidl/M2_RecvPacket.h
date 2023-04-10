#pragma once



inline void RECV_M2_JOIN_GROUP_REQ(HisUtil::CMsg& msgRecv, stM2_JOIN_GROUP_REQ& st)
{
	msgRecv
		>> st.remote
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_JOIN_GROUP_REQ"));
}


inline void RECV_M2_CH_UDP_HELLO_PEER_REQ(HisUtil::CMsg& msgRecv, stM2_CH_UDP_HELLO_PEER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_CH_UDP_HELLO_PEER_REQ"));
}


inline void RECV_M2_CH_UDP_FINE_THANKS_PEER_ACK(HisUtil::CMsg& msgRecv, stM2_CH_UDP_FINE_THANKS_PEER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_CH_UDP_FINE_THANKS_PEER_ACK"));
}


inline void RECV_M2_CH_UDP_CURRENT_USER_NTF(HisUtil::CMsg& msgRecv, stM2_CH_UDP_CURRENT_USER_NTF& st)
{
	msgRecv
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_CH_UDP_CURRENT_USER_NTF"));
}


inline void RECV_M2_AC_LOGIN_REQ(HisUtil::CMsg& msgRecv, stM2_AC_LOGIN_REQ& st)
{
	msgRecv
		>> st.accountpk
		>> st.account
		>> st.gameserverno
		>> st.remoteBalance
		>> st.remoteX
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_LOGIN_REQ"));
}


inline void RECV_M2_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv, stM2_AC_LOGIN_ACK& st)
{
	msgRecv
		>> st.result
		>> st.result_noti
		>> st.remoteBalance
		>> st.remoteX
		>> st.accountpk
		>> st.account
		>> st.masterkey
		>> st.gameserverno
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_LOGIN_ACK"));
}


inline void RECV_M2_AC_LOGOUT_REQ(HisUtil::CMsg& msgRecv, stM2_AC_LOGOUT_REQ& st)
{
	msgRecv
		>> st.accountpk
		>> st.entry
		>> st.remoteServer
		>> st.remoteX
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_LOGOUT_REQ"));
}


inline void RECV_M2_UDP_CHANGE_SERVER_STATUS_NTF(HisUtil::CMsg& msgRecv, stM2_UDP_CHANGE_SERVER_STATUS_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		>> st.status
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_UDP_CHANGE_SERVER_STATUS_NTF"));
}


inline void RECV_M2_AC_CERTIFY_REQ(HisUtil::CMsg& msgRecv, stM2_AC_CERTIFY_REQ& st)
{
	msgRecv
		>> st.account
		>> st.masterkey
		>> st.remoteGame
		>> st.remoteX
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_CERTIFY_REQ"));
}


inline void RECV_M2_AC_CERTIFY_ACK(HisUtil::CMsg& msgRecv, stM2_AC_CERTIFY_ACK& st)
{
	msgRecv
		>> st.result
		>> st.remoteX
		>> st.accountpk
		>> st.account
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_CERTIFY_ACK"));
}
