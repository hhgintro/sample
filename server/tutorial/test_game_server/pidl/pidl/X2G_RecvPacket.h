#pragma once



inline void RECV_X2G_AC_LOGIN_REQ(HisUtil::CMsg& msgRecv, stX2G_AC_LOGIN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.account
		>> st.password
		>> st.protocol
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AC_LOGIN_REQ"));
}


inline void RECV_X2G_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv, stX2G_AC_LOGIN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.accountpk
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AC_LOGIN_ACK"));
}


inline void RECV_X2G_IN_EQUIP_LOAD_REQ(HisUtil::CMsg& msgRecv, stX2G_IN_EQUIP_LOAD_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IN_EQUIP_LOAD_REQ"));
}


inline void RECV_X2G_IN_EQUIP_LOAD_ACK(HisUtil::CMsg& msgRecv, stX2G_IN_EQUIP_LOAD_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.inven
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IN_EQUIP_LOAD_ACK"));
}


inline void RECV_X2G_IN_EQUIP_UPDATE_REQ(HisUtil::CMsg& msgRecv, stX2G_IN_EQUIP_UPDATE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.inven
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IN_EQUIP_UPDATE_REQ"));
}


inline void RECV_X2G_IN_EQUIP_UPDATE_ACK(HisUtil::CMsg& msgRecv, stX2G_IN_EQUIP_UPDATE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IN_EQUIP_UPDATE_ACK"));
}


inline void RECV_X2G_RM_ENTER_SQUARE_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_SQUARE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_SQUARE_REQ"));
}


inline void RECV_X2G_RM_ENTER_ROOM_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_ROOM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_ROOM_REQ"));
}


inline void RECV_X2G_RM_ENTER_ROOM_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_ROOM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.players
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_ROOM_ACK"));
}


inline void RECV_X2G_RM_ENTER_ROOM_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_ROOM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.player
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_ROOM_NTF"));
}


inline void RECV_X2G_RM_LEAVE_SQUARE_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_SQUARE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_SQUARE_REQ"));
}


inline void RECV_X2G_RM_LEAVE_ROOM_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_ROOM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_ROOM_REQ"));
}


inline void RECV_X2G_RM_LEAVE_ROOM_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_ROOM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_ROOM_ACK"));
}


inline void RECV_X2G_RM_LEAVE_ROOM_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_ROOM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.accountpk
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_ROOM_NTF"));
}


inline void RECV_X2G_RM_PARTY_LIST_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_PARTY_LIST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.type
		>> st.page
		>> st.cnt
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_PARTY_LIST_REQ"));
}


inline void RECV_X2G_RM_PARTY_LIST_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_PARTY_LIST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.parties
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_PARTY_LIST_ACK"));
}


inline void RECV_X2G_RM_CREATE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_CREATE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.type
		>> st.maxplayer
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_CREATE_PARTY_REQ"));
}


inline void RECV_X2G_RM_CREATE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_CREATE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.info
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_CREATE_PARTY_ACK"));
}


inline void RECV_X2G_RM_ENTER_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.index
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_PARTY_REQ"));
}


inline void RECV_X2G_RM_ENTER_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.info
		>> st.players
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_PARTY_ACK"));
}


inline void RECV_X2G_RM_ENTER_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_ENTER_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.player
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_ENTER_PARTY_NTF"));
}


inline void RECV_X2G_RM_LEAVE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_PARTY_REQ"));
}


inline void RECV_X2G_RM_LEAVE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_PARTY_ACK"));
}


inline void RECV_X2G_RM_LEAVE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_LEAVE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.accountpk
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_LEAVE_PARTY_NTF"));
}


inline void RECV_X2G_RM_CLOSED_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_CLOSED_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_CLOSED_PARTY_NTF"));
}


inline void RECV_X2G_RM_MOVE_REQ(HisUtil::CMsg& msgRecv, stX2G_RM_MOVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.pos
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_MOVE_REQ"));
}


inline void RECV_X2G_RM_MOVE_ACK(HisUtil::CMsg& msgRecv, stX2G_RM_MOVE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.pos
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_MOVE_ACK"));
}


inline void RECV_X2G_RM_MOVE_NTF(HisUtil::CMsg& msgRecv, stX2G_RM_MOVE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.accountpk
		>> st.pos
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_RM_MOVE_NTF"));
}
