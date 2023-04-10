#pragma once



inline void RECV_M2_BD_VOICE_CHAT_REQ(HisUtil::CMsg& msgRecv, stM2_BD_VOICE_CHAT_REQ& st)
{
	msgRecv
		>> st.chat
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_BD_VOICE_CHAT_REQ"));
}


inline void RECV_M2_BD_VOICE_CHAT_ACK(HisUtil::CMsg& msgRecv, stM2_BD_VOICE_CHAT_ACK& st)
{
	msgRecv
		>> st.chat
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_BD_VOICE_CHAT_ACK"));
}


inline void RECV_M2_AC_LOGIN_REQ(HisUtil::CMsg& msgRecv, stM2_AC_LOGIN_REQ& st)
{
	msgRecv
		>> st.account
		>> st.password
		>> st.remoteX
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_LOGIN_REQ"));
}


inline void RECV_M2_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv, stM2_AC_LOGIN_ACK& st)
{
	msgRecv
		>> st.result
		>> st.remoteX
		>> st.accountpk
		>> st.account
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_AC_LOGIN_ACK"));
}


inline void RECV_M2_IN_EQUIP_LOAD_REQ(HisUtil::CMsg& msgRecv, stM2_IN_EQUIP_LOAD_REQ& st)
{
	msgRecv
		>> st.remoteX
		>> st.accountpk
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_IN_EQUIP_LOAD_REQ"));
}


inline void RECV_M2_IN_EQUIP_LOAD_ACK(HisUtil::CMsg& msgRecv, stM2_IN_EQUIP_LOAD_ACK& st)
{
	msgRecv
		>> st.remoteX
		>> st.inven
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_IN_EQUIP_LOAD_ACK"));
}


inline void RECV_M2_IN_EQUIP_UPDATE_REQ(HisUtil::CMsg& msgRecv, stM2_IN_EQUIP_UPDATE_REQ& st)
{
	msgRecv
		>> st.remoteX
		>> st.accountpk
		>> st.inven
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_IN_EQUIP_UPDATE_REQ"));
}


inline void RECV_M2_IN_EQUIP_UPDATE_ACK(HisUtil::CMsg& msgRecv, stM2_IN_EQUIP_UPDATE_ACK& st)
{
	msgRecv
		>> st.remoteX
		>> st.result
		>> st.inven
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv M2_IN_EQUIP_UPDATE_ACK"));
}
