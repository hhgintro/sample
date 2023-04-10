#pragma once



inline void RECV_C2_UDP_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv, stC2_UDP_CHANGE_SERVER_STATUS_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteFrom
		>> st.remoteTo
		>> st.status
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2_UDP_CHANGE_SERVER_STATUS_REQ"));
}


inline void RECV_C2_UDP_CHANGE_SERVER_STATUS_ACK(HisUtil::CMsg& msgRecv, stC2_UDP_CHANGE_SERVER_STATUS_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remoteTo
		>> st.status
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2_UDP_CHANGE_SERVER_STATUS_ACK"));
}


inline void RECV_C2_UDP_GAME_SERVER_INFO_NTF(HisUtil::CMsg& msgRecv, stC2_UDP_GAME_SERVER_INFO_NTF& st)
{
	msgRecv
		>> st.gameinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2_UDP_GAME_SERVER_INFO_NTF"));
}
