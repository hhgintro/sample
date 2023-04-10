#pragma once



inline void RECV_B2L_AC_LOGIN_REQ(HisUtil::CMsg& msgRecv, stB2L_AC_LOGIN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.account
		>> st.authkey
		>> st.remoteBalance
		>> st.remoteX
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv B2L_AC_LOGIN_REQ"));
}


inline void RECV_B2L_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv, stB2L_AC_LOGIN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.result_noti
		>> st.remoteX
		>> st.accountpk
		>> st.account
		>> st.masterkey
		>> st.gameserverno
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv B2L_AC_LOGIN_ACK"));
}
