#pragma once



inline void RECV_C2M_MT_SERVER_LIST_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_SERVER_LIST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_SERVER_LIST_REQ"));
}


inline void RECV_C2M_MT_SERVER_LIST_ACK(HisUtil::CMsg& msgRecv, stC2M_MT_SERVER_LIST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_SERVER_LIST_ACK"));
}


inline void RECV_C2M_MT_ADD_SERVER_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_ADD_SERVER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_ADD_SERVER_REQ"));
}


inline void RECV_C2M_MT_ADD_SERVER_ACK(HisUtil::CMsg& msgRecv, stC2M_MT_ADD_SERVER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_ADD_SERVER_ACK"));
}


inline void RECV_C2M_MT_DELETE_SERVER_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_DELETE_SERVER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_DELETE_SERVER_REQ"));
}


inline void RECV_C2M_MT_DELETE_SERVER_ACK(HisUtil::CMsg& msgRecv, stC2M_MT_DELETE_SERVER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_DELETE_SERVER_ACK"));
}


inline void RECV_C2M_MT_GAME_SERVER_INFO_NTF(HisUtil::CMsg& msgRecv, stC2M_MT_GAME_SERVER_INFO_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.gameinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_GAME_SERVER_INFO_NTF"));
}


inline void RECV_C2M_MT_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_CHANGE_SERVER_STATUS_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		>> st.status
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_CHANGE_SERVER_STATUS_REQ"));
}


inline void RECV_C2M_MT_CHANGE_SERVER_STATUS_ACK(HisUtil::CMsg& msgRecv, stC2M_MT_CHANGE_SERVER_STATUS_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.remote
		>> st.status
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_CHANGE_SERVER_STATUS_ACK"));
}


inline void RECV_C2M_MT_SERVER_LAUNCH_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_SERVER_LAUNCH_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_SERVER_LAUNCH_REQ"));
}


inline void RECV_C2M_MT_SERVER_SHUTDOWN_REQ(HisUtil::CMsg& msgRecv, stC2M_MT_SERVER_SHUTDOWN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.serverinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_SERVER_SHUTDOWN_REQ"));
}


inline void RECV_C2M_MT_CLEAR_SERVER_LIST_NTF(HisUtil::CMsg& msgRecv, stC2M_MT_CLEAR_SERVER_LIST_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv C2M_MT_CLEAR_SERVER_LIST_NTF"));
}
