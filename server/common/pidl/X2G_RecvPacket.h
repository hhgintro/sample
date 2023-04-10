#pragma once



inline void RECV_X2G_AC_CERTIFY_REQ(HisUtil::CMsg& msgRecv, stX2G_AC_CERTIFY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.account
		>> st.masterkey
		>> HisUtil::CMsg::CMsgPack(st.temp, (int)sizeof(st.temp))
		>> HisUtil::CMsg::CMsgPack(st.test, (int)sizeof(st.test))
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AC_CERTIFY_REQ"));
}


inline void RECV_X2G_AC_CERTIFY_ACK(HisUtil::CMsg& msgRecv, stX2G_AC_CERTIFY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AC_CERTIFY_ACK"));
}


inline void RECV_X2G_CH_LOAD_ALL_CHAR_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_ALL_CHAR_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_ALL_CHAR_REQ"));
}


inline void RECV_X2G_CH_LOAD_ALL_CHAR_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_ALL_CHAR_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.chardata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_ALL_CHAR_ACK"));
}


inline void RECV_X2G_CH_LOAD_CHAR_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_CHAR_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chardata
		>> st.skilldata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_CHAR_ACK"));
}


inline void RECV_X2G_CH_CREATE_CHAR_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_CREATE_CHAR_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.charinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CREATE_CHAR_REQ"));
}


inline void RECV_X2G_CH_CREATE_CHAR_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_CREATE_CHAR_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CREATE_CHAR_ACK"));
}


inline void RECV_X2G_CH_DELETE_CHAR_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_DELETE_CHAR_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_DELETE_CHAR_REQ"));
}


inline void RECV_X2G_CH_DELETE_CHAR_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_DELETE_CHAR_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_DELETE_CHAR_ACK"));
}


inline void RECV_X2G_CH_LOAD_ALL_SOLDIER_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_ALL_SOLDIER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_ALL_SOLDIER_REQ"));
}


inline void RECV_X2G_CH_LOAD_ALL_SOLDIER_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_ALL_SOLDIER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.soldierdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_ALL_SOLDIER_ACK"));
}


inline void RECV_X2G_CH_LOAD_SOLDIER_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_LOAD_SOLDIER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.soldierdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LOAD_SOLDIER_ACK"));
}


inline void RECV_X2G_CH_CREATE_SOLDIER_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_CREATE_SOLDIER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CREATE_SOLDIER_ACK"));
}


inline void RECV_X2G_CH_DELETE_SOLDIER_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_DELETE_SOLDIER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_DELETE_SOLDIER_REQ"));
}


inline void RECV_X2G_CH_DELETE_SOLDIER_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_DELETE_SOLDIER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_DELETE_SOLDIER_ACK"));
}


inline void RECV_X2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.money
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF"));
}


inline void RECV_X2G_CH_CHECK_NICK_DUPLICATE_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_CHECK_NICK_DUPLICATE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.nickname
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CHECK_NICK_DUPLICATE_REQ"));
}


inline void RECV_X2G_CH_CHECK_NICK_DUPLICATE_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_CHECK_NICK_DUPLICATE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CHECK_NICK_DUPLICATE_ACK"));
}


inline void RECV_X2G_CH_OBJECT_EXP_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_OBJECT_EXP_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectexp
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_OBJECT_EXP_ACK"));
}


inline void RECV_X2G_CH_LEVEL_UP_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_LEVEL_UP_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.levelupobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LEVEL_UP_ACK"));
}


inline void RECV_X2G_CH_LEVEL_UP_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_LEVEL_UP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.levelupobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_LEVEL_UP_NTF"));
}


inline void RECV_X2G_CH_MONEY_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_MONEY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.money
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_MONEY_NTF"));
}


inline void RECV_X2G_CH_SETUP_NO_RIVAL_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_SETUP_NO_RIVAL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_SETUP_NO_RIVAL_NTF"));
}


inline void RECV_X2G_CH_RELEASE_NO_RIVAL_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_RELEASE_NO_RIVAL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_RELEASE_NO_RIVAL_NTF"));
}


inline void RECV_X2G_CH_RESET_ABILITY_NTF(HisUtil::CMsg& msgRecv, stX2G_CH_RESET_ABILITY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.state
		>> st.basic
		>> st.battle
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_RESET_ABILITY_NTF"));
}


inline void RECV_X2G_CH_COMPLETED_TUTORIAL_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_COMPLETED_TUTORIAL_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.tutorial
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_COMPLETED_TUTORIAL_REQ"));
}


inline void RECV_X2G_CH_COMPLETED_TUTORIAL_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_COMPLETED_TUTORIAL_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_COMPLETED_TUTORIAL_ACK"));
}


inline void RECV_X2G_CH_CHAR_GAME_OPTION_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_CHAR_GAME_OPTION_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.gameoption
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_CHAR_GAME_OPTION_REQ"));
}


inline void RECV_X2G_CH_BATTLE_FORMATION_REQ(HisUtil::CMsg& msgRecv, stX2G_CH_BATTLE_FORMATION_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.battletype
		>> st.objectformation
		>> st.bestfriendsoldierindex
		>> st.toggle
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_BATTLE_FORMATION_REQ"));
}


inline void RECV_X2G_CH_BATTLE_FORMATION_ACK(HisUtil::CMsg& msgRecv, stX2G_CH_BATTLE_FORMATION_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.formation
		>> st.bestfriendsoldierindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_CH_BATTLE_FORMATION_ACK"));
}


inline void RECV_X2G_WD_WORLD_ENTER_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_ENTER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.zonecode
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_ENTER_REQ"));
}


inline void RECV_X2G_WD_USE_PORTAL_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_USE_PORTAL_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_USE_PORTAL_REQ"));
}


inline void RECV_X2G_WD_WORLD_ENTER_ACK(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_ENTER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.enterdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_ENTER_ACK"));
}


inline void RECV_X2G_WD_WORLD_CHANGE_FOR_QUEST_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_CHANGE_FOR_QUEST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_CHANGE_FOR_QUEST_REQ"));
}


inline void RECV_X2G_WD_WORLD_CHANGE_FOR_QUEST_ACK(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_CHANGE_FOR_QUEST_ACK"));
}


inline void RECV_X2G_WD_ENTER_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_ENTER_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.zonechardata
		>> st.zonehiredsoldierdata
		>> st.monsterdata
		>> st.townnpcdata
		>> st.portaldata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_ENTER_OBJECT_NTF"));
}


inline void RECV_X2G_WD_ALL_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_ALL_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.zonechardata
		>> st.zonehiredsoldierdata
		>> st.monsterdata
		>> st.townnpcdata
		>> st.portaldata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_ALL_OBJECT_NTF"));
}


inline void RECV_X2G_WD_WORLD_LEAVE_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_LEAVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_LEAVE_REQ"));
}


inline void RECV_X2G_WD_LEAVE_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_LEAVE_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.leaveobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_LEAVE_OBJECT_NTF"));
}


inline void RECV_X2G_WD_MOVE_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_MOVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.x
		>> st.y
		>> st.z
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOVE_REQ"));
}


inline void RECV_X2G_WD_MOVE_ACK(HisUtil::CMsg& msgRecv, stX2G_WD_MOVE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOVE_ACK"));
}


inline void RECV_X2G_WD_MOVE_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_MOVE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.moveobject
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOVE_NTF"));
}


inline void RECV_X2G_WD_STOP_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_STOP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.x
		>> st.y
		>> st.z
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_STOP_REQ"));
}


inline void RECV_X2G_WD_STOP_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_STOP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.stopobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_STOP_NTF"));
}


inline void RECV_X2G_WD_MOTION_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_MOTION_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.motion
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOTION_REQ"));
}


inline void RECV_X2G_WD_MOTION_ACK(HisUtil::CMsg& msgRecv, stX2G_WD_MOTION_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOTION_ACK"));
}


inline void RECV_X2G_WD_MOTION_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_MOTION_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.motion
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_MOTION_NTF"));
}


inline void RECV_X2G_WD_WORLD_PUZZLE_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_PUZZLE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.puzzle
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_PUZZLE_REQ"));
}


inline void RECV_X2G_WD_WORLD_PUZZLE_NTF(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_PUZZLE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.puzzle
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_PUZZLE_NTF"));
}


inline void RECV_X2G_WD_WORLD_MAP_OPEN_REQ(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_MAP_OPEN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.worldmap
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_MAP_OPEN_REQ"));
}


inline void RECV_X2G_WD_WORLD_MAP_OPEN_ACK(HisUtil::CMsg& msgRecv, stX2G_WD_WORLD_MAP_OPEN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_WD_WORLD_MAP_OPEN_ACK"));
}


inline void RECV_X2G_BD_CHAT_REQ(HisUtil::CMsg& msgRecv, stX2G_BD_CHAT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.type
		>> st.chatmsg
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BD_CHAT_REQ"));
}


inline void RECV_X2G_BD_TARGET_CHAT_REQ(HisUtil::CMsg& msgRecv, stX2G_BD_TARGET_CHAT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.toid
		>> st.tonick
		>> st.type
		>> st.chatmsg
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BD_TARGET_CHAT_REQ"));
}


inline void RECV_X2G_BD_CHAT_ACK(HisUtil::CMsg& msgRecv, stX2G_BD_CHAT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BD_CHAT_ACK"));
}


inline void RECV_X2G_BD_CHAT_NTF(HisUtil::CMsg& msgRecv, stX2G_BD_CHAT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chatdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BD_CHAT_NTF"));
}


inline void RECV_X2G_BD_NOTICE_CHAT_NTF(HisUtil::CMsg& msgRecv, stX2G_BD_NOTICE_CHAT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.noticedata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BD_NOTICE_CHAT_NTF"));
}


inline void RECV_X2G_OB_REGEN_NTF(HisUtil::CMsg& msgRecv, stX2G_OB_REGEN_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.regenobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_OB_REGEN_NTF"));
}


inline void RECV_X2G_OB_DEATH_NTF(HisUtil::CMsg& msgRecv, stX2G_OB_DEATH_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_OB_DEATH_NTF"));
}


inline void RECV_X2G_OB_REVIVAL_NTF(HisUtil::CMsg& msgRecv, stX2G_OB_REVIVAL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.revivalobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_OB_REVIVAL_NTF"));
}


inline void RECV_X2G_SK_LOAD_CHAR_SKILL_ACK(HisUtil::CMsg& msgRecv, stX2G_SK_LOAD_CHAR_SKILL_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.skilldata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_LOAD_CHAR_SKILL_ACK"));
}


inline void RECV_X2G_SK_SKILL_LEARN_REQ(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEARN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.skillcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEARN_REQ"));
}


inline void RECV_X2G_SK_SKILL_LEARN_ACK(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEARN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEARN_ACK"));
}


inline void RECV_X2G_SK_SKILL_LEARN_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEARN_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.learnskill
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEARN_NTF"));
}


inline void RECV_X2G_SK_SKILL_LEVELUP_REQ(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEVELUP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.skillcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEVELUP_REQ"));
}


inline void RECV_X2G_SK_SKILL_LEVELUP_ACK(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEVELUP_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEVELUP_ACK"));
}


inline void RECV_X2G_SK_SKILL_LEVELUP_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_LEVELUP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.levelupskill
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_LEVELUP_NTF"));
}


inline void RECV_X2G_SK_SKILL_QUICK_SLOT_REQ(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_QUICK_SLOT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.quickslot
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_QUICK_SLOT_REQ"));
}


inline void RECV_X2G_SK_SKILL_QUICK_SLOT_ACK(HisUtil::CMsg& msgRecv, stX2G_SK_SKILL_QUICK_SLOT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.quickslot
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_SKILL_QUICK_SLOT_ACK"));
}


inline void RECV_X2G_SK_ATTACK_REQ(HisUtil::CMsg& msgRecv, stX2G_SK_ATTACK_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.targetboard
		>> st.skillcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_ATTACK_REQ"));
}


inline void RECV_X2G_SK_ATTACK_ACK(HisUtil::CMsg& msgRecv, stX2G_SK_ATTACK_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_ATTACK_ACK"));
}


inline void RECV_X2G_SK_ATTACK_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_ATTACK_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.attackobject
		>> st.targetobject
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_ATTACK_NTF"));
}


inline void RECV_X2G_SK_INSERT_BUFF_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_INSERT_BUFF_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.buffdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_INSERT_BUFF_NTF"));
}


inline void RECV_X2G_SK_DELETE_BUFF_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_DELETE_BUFF_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.buffdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_DELETE_BUFF_NTF"));
}


inline void RECV_X2G_SK_HEAL_NTF(HisUtil::CMsg& msgRecv, stX2G_SK_HEAL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.attackobject
		>> st.regenobject
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_SK_HEAL_NTF"));
}


inline void RECV_X2G_BF_BATTLE_OPEN_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_OPEN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.formation
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_OPEN_REQ"));
}


inline void RECV_X2G_BF_BATTLE_OPEN_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_OPEN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_OPEN_ACK"));
}


inline void RECV_X2G_BF_BATTLE_INTRUDE_CHAR_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_INTRUDE_CHAR_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_INTRUDE_CHAR_REQ"));
}


inline void RECV_X2G_BF_BATTLE_INTRUDE_CHAR_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_INTRUDE_CHAR_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_INTRUDE_CHAR_ACK"));
}


inline void RECV_X2G_BF_BATTLE_INTRUDE_CHAR_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_INTRUDE_CHAR_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chardata
		>> st.monsterdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_INTRUDE_CHAR_NTF"));
}


inline void RECV_X2G_BF_BATTLE_INTRUDE_MONSTER_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_INTRUDE_MONSTER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_INTRUDE_MONSTER_REQ"));
}


inline void RECV_X2G_BF_BATTLE_INTRUDE_MONSTER_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_INTRUDE_MONSTER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_INTRUDE_MONSTER_ACK"));
}


inline void RECV_X2G_BF_BATTLE_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chardata
		>> st.monsterdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_OBJECT_NTF"));
}


inline void RECV_X2G_BF_BATTLE_ENTER_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_ENTER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.enterdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_ENTER_ACK"));
}


inline void RECV_X2G_BF_ENTER_BATTLE_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_ENTER_BATTLE_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.battlechar
		>> st.battlehiredsoldier
		>> st.battlemonster
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_ENTER_BATTLE_OBJECT_NTF"));
}


inline void RECV_X2G_BF_ALL_BATTLE_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_ALL_BATTLE_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.battlechar
		>> st.battlehiredsoldier
		>> st.battlemonster
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_ALL_BATTLE_OBJECT_NTF"));
}


inline void RECV_X2G_BF_BATTLE_LEAVE_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_LEAVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_LEAVE_REQ"));
}


inline void RECV_X2G_BF_BATTLE_LEAVE_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_LEAVE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_LEAVE_ACK"));
}


inline void RECV_X2G_BF_LEAVE_BATTLE_OBJECT_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_LEAVE_BATTLE_OBJECT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.leaveobject
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_LEAVE_BATTLE_OBJECT_NTF"));
}


inline void RECV_X2G_BF_BATTLE_MOVE_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_MOVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.board
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_MOVE_REQ"));
}


inline void RECV_X2G_BF_BATTLE_MOVE_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_MOVE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_MOVE_ACK"));
}


inline void RECV_X2G_BF_BATTLE_MOVE_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_MOVE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.moveobject
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_MOVE_NTF"));
}


inline void RECV_X2G_BF_BATTLE_STOP_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_STOP_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.stopobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_STOP_NTF"));
}


inline void RECV_X2G_BF_BATTLE_NEXT_STATUS_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_NEXT_STATUS_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_NEXT_STATUS_REQ"));
}


inline void RECV_X2G_BF_BATTLE_NEXT_STATUS_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_NEXT_STATUS_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_NEXT_STATUS_ACK"));
}


inline void RECV_X2G_BF_BATTLE_STATUS_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_STATUS_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.status
		>> st.servertime
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_STATUS_NTF"));
}


inline void RECV_X2G_BF_BATTLE_TURN_WAITING_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_TURN_WAITING_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.currentturn
		>> st.servertime
		>> st.movepower
		>> st.objectlist
		>> st.bonuslist
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_TURN_WAITING_NTF"));
}


inline void RECV_X2G_BF_BATTLE_PVP_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_PVP_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.bisparty
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_PVP_REQ"));
}


inline void RECV_X2G_BF_BATTLE_PVP_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_PVP_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.enterdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_PVP_ACK"));
}


inline void RECV_X2G_BF_BATTLE_PVP_RESULT_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_PVP_RESULT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.pvpindex
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_PVP_RESULT_REQ"));
}


inline void RECV_X2G_BF_BATTLE_PVP_RESULT_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_PVP_RESULT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_PVP_RESULT_ACK"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_ENTER_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_ENTER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_ENTER_REQ"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_ENTER_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_ENTER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_ENTER_ACK"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_LEAVE_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_LEAVE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_LEAVE_REQ"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_LEAVE_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_LEAVE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_LEAVE_ACK"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK"));
}


inline void RECV_X2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF"));
}


inline void RECV_X2G_BF_BATTLE_TOGGLE_SOLDIER_REQ(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_TOGGLE_SOLDIER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.leaveobjectindex
		>> st.enterobjectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_TOGGLE_SOLDIER_REQ"));
}


inline void RECV_X2G_BF_BATTLE_TOGGLE_SOLDIER_ACK(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_TOGGLE_SOLDIER_ACK"));
}


inline void RECV_X2G_BF_BATTLE_TOGGLE_SOLDIER_NTF(HisUtil::CMsg& msgRecv, stX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.togglehiredsoldier
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_BF_BATTLE_TOGGLE_SOLDIER_NTF"));
}


inline void RECV_X2G_IT_LOAD_INVENTORY_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_LOAD_INVENTORY_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_LOAD_INVENTORY_ITEM_ACK"));
}


inline void RECV_X2G_IT_QUICK_SLOT_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_QUICK_SLOT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.quickslot
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_QUICK_SLOT_REQ"));
}


inline void RECV_X2G_IT_QUICK_SLOT_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_QUICK_SLOT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.quickslot
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_QUICK_SLOT_ACK"));
}


inline void RECV_X2G_IT_BUY_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_BUY_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.buyitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_BUY_ITEM_REQ"));
}


inline void RECV_X2G_IT_BUY_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_BUY_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		>> st.money
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_BUY_ITEM_ACK"));
}


inline void RECV_X2G_IT_SELL_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_SELL_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_SELL_ITEM_REQ"));
}


inline void RECV_X2G_IT_SELL_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_SELL_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.sellitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_SELL_ITEM_ACK"));
}


inline void RECV_X2G_IT_PICKUP_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_PICKUP_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_PICKUP_ITEM_ACK"));
}


inline void RECV_X2G_IT_PICKUP_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_IT_PICKUP_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.pickupitem
		>> st.pickupobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_PICKUP_ITEM_NTF"));
}


inline void RECV_X2G_IT_DESTROY_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_DESTROY_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_DESTROY_ITEM_REQ"));
}


inline void RECV_X2G_IT_DESTROY_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_DESTROY_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.destroyitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_DESTROY_ITEM_ACK"));
}


inline void RECV_X2G_IT_INVENTORY_CHANGE_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_INVENTORY_CHANGE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.inventorydata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_INVENTORY_CHANGE_REQ"));
}


inline void RECV_X2G_IT_INVENTORY_CHANGE_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_INVENTORY_CHANGE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		>> st.inventorydata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_INVENTORY_CHANGE_ACK"));
}


inline void RECV_X2G_IT_EQUIP_CHANGE_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_EQUIP_CHANGE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.equipdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_EQUIP_CHANGE_REQ"));
}


inline void RECV_X2G_IT_EQUIP_CHANGE_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_EQUIP_CHANGE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		>> st.equipdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_EQUIP_CHANGE_ACK"));
}


inline void RECV_X2G_IT_EQUIP_CHANGE_NTF(HisUtil::CMsg& msgRecv, stX2G_IT_EQUIP_CHANGE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.equipitem
		>> st.unequipitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_EQUIP_CHANGE_NTF"));
}


inline void RECV_X2G_IT_GIFT_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_GIFT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.giftdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_GIFT_REQ"));
}


inline void RECV_X2G_IT_GIFT_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_GIFT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.giftdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_GIFT_ACK"));
}


inline void RECV_X2G_IT_GIFT_EQUIP_CHANGE_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_GIFT_EQUIP_CHANGE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.fromid
		>> st.toid
		>> st.equipdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_GIFT_EQUIP_CHANGE_REQ"));
}


inline void RECV_X2G_IT_GIFT_EQUIP_CHANGE_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_GIFT_EQUIP_CHANGE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.fromid
		>> st.toid
		>> st.equipdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_GIFT_EQUIP_CHANGE_ACK"));
}


inline void RECV_X2G_IT_GIFT_EQUIP_CHANGE_NTF(HisUtil::CMsg& msgRecv, stX2G_IT_GIFT_EQUIP_CHANGE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.equipitem
		>> st.unequipitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_GIFT_EQUIP_CHANGE_NTF"));
}


inline void RECV_X2G_IT_USE_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_USE_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.useiteminfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_USE_ITEM_REQ"));
}


inline void RECV_X2G_IT_USE_ITEM_ON_BATTLE_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_USE_ITEM_ON_BATTLE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.useiteminfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_USE_ITEM_ON_BATTLE_REQ"));
}


inline void RECV_X2G_IT_USE_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_USE_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.useitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_USE_ITEM_ACK"));
}


inline void RECV_X2G_IT_USE_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_IT_USE_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.useitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_USE_ITEM_NTF"));
}


inline void RECV_X2G_IT_UPDATE_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_IT_UPDATE_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.updateitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_UPDATE_ITEM_NTF"));
}


inline void RECV_X2G_IT_SPLITE_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_SPLITE_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.fromid
		>> st.toid
		>> st.sourceitemindex
		>> st.itemcount
		>> st.slot
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_SPLITE_ITEM_REQ"));
}


inline void RECV_X2G_IT_SPLITE_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_SPLITE_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.fromid
		>> st.toid
		>> st.spliteitem
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_SPLITE_ITEM_ACK"));
}


inline void RECV_X2G_IT_COMBINE_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_IT_COMBINE_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.fromid
		>> st.toid
		>> st.sourceitemindex
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_COMBINE_ITEM_REQ"));
}


inline void RECV_X2G_IT_COMBINE_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_IT_COMBINE_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.itemcombine
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_IT_COMBINE_ITEM_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_LIST_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_LIST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_LIST_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_LIST_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_LIST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questdata
		>> st.progressdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_LIST_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_INSERT_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_INSERT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_INSERT_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_INSERT_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_INSERT_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.questcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_INSERT_ACK"));
}


inline void RECV_X2G_QT_CHAR_HELLO_NPC_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_HELLO_NPC_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_HELLO_NPC_REQ"));
}


inline void RECV_X2G_QT_CHAR_HELLO_NPC_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_HELLO_NPC_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_HELLO_NPC_ACK"));
}


inline void RECV_X2G_QT_CHAR_GOODBYE_NPC_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_GOODBYE_NPC_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_GOODBYE_NPC_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_TALK_NPC_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_TALK_NPC_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questnpc
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_TALK_NPC_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_TALK_NPC_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_TALK_NPC_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_TALK_NPC_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_UPDATE_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_UPDATE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_UPDATE_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.progressdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_REWARD_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_REWARD_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questcode
		>> st.order
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_REWARD_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_REWARD_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_REWARD_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.objectindex
		>> st.rewarddata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_REWARD_ACK"));
}


inline void RECV_X2G_QT_CHAR_QUEST_DELETE_REQ(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_DELETE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.questcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_DELETE_REQ"));
}


inline void RECV_X2G_QT_CHAR_QUEST_DELETE_ACK(HisUtil::CMsg& msgRecv, stX2G_QT_CHAR_QUEST_DELETE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.questcode
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_QT_CHAR_QUEST_DELETE_ACK"));
}


inline void RECV_X2G_ML_MAIL_LIST_REQ(HisUtil::CMsg& msgRecv, stX2G_ML_MAIL_LIST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_MAIL_LIST_REQ"));
}


inline void RECV_X2G_ML_MAIL_LIST_ACK(HisUtil::CMsg& msgRecv, stX2G_ML_MAIL_LIST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.mail
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_MAIL_LIST_ACK"));
}


inline void RECV_X2G_ML_SEND_MAIL_REQ(HisUtil::CMsg& msgRecv, stX2G_ML_SEND_MAIL_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.sendmail
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_SEND_MAIL_REQ"));
}


inline void RECV_X2G_ML_SEND_MAIL_ACK(HisUtil::CMsg& msgRecv, stX2G_ML_SEND_MAIL_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_SEND_MAIL_ACK"));
}


inline void RECV_X2G_ML_RECIEVE_MAIL_NTF(HisUtil::CMsg& msgRecv, stX2G_ML_RECIEVE_MAIL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.mail
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_RECIEVE_MAIL_NTF"));
}


inline void RECV_X2G_ML_CHANGE_MAIL_STATUS_REQ(HisUtil::CMsg& msgRecv, stX2G_ML_CHANGE_MAIL_STATUS_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.changemail
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_CHANGE_MAIL_STATUS_REQ"));
}


inline void RECV_X2G_ML_CHANGE_MAIL_STATUS_ACK(HisUtil::CMsg& msgRecv, stX2G_ML_CHANGE_MAIL_STATUS_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.changemail
		>> st.mailitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_CHANGE_MAIL_STATUS_ACK"));
}


inline void RECV_X2G_ML_TAKE_MAIL_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_ML_TAKE_MAIL_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.maildata
		>> st.money
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_ML_TAKE_MAIL_ITEM_NTF"));
}


inline void RECV_X2G_PT_CREATE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_CREATE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CREATE_PARTY_REQ"));
}


inline void RECV_X2G_PT_CREATE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_CREATE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CREATE_PARTY_ACK"));
}


inline void RECV_X2G_PT_CREATE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_CREATE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.bossinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CREATE_PARTY_NTF"));
}


inline void RECV_X2G_PT_CREATE_PARTY_ACCEPT_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_CREATE_PARTY_ACCEPT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyaccept
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CREATE_PARTY_ACCEPT_REQ"));
}


inline void RECV_X2G_PT_ENTER_PARTY_MEMBER_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_ENTER_PARTY_MEMBER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partychar
		>> st.partyhiredsoldier
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ENTER_PARTY_MEMBER_NTF"));
}


inline void RECV_X2G_PT_ALL_PARTY_MEMBER_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_ALL_PARTY_MEMBER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyinfo
		>> st.partychar
		>> st.partyhiredsoldier
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ALL_PARTY_MEMBER_NTF"));
}


inline void RECV_X2G_PT_LEAVE_PARTY_MEMBER_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_LEAVE_PARTY_MEMBER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_LEAVE_PARTY_MEMBER_NTF"));
}


inline void RECV_X2G_PT_DELETE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_DELETE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_DELETE_PARTY_REQ"));
}


inline void RECV_X2G_PT_DELETE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_DELETE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_DELETE_PARTY_ACK"));
}


inline void RECV_X2G_PT_DELETE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_DELETE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_DELETE_PARTY_NTF"));
}


inline void RECV_X2G_PT_INVITE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_INVITE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_INVITE_PARTY_REQ"));
}


inline void RECV_X2G_PT_INVITE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_INVITE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_INVITE_PARTY_ACK"));
}


inline void RECV_X2G_PT_INVITE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_INVITE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.bossinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_INVITE_PARTY_NTF"));
}


inline void RECV_X2G_PT_INVITE_PARTY_ACCEPT_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_INVITE_PARTY_ACCEPT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyaccept
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_INVITE_PARTY_ACCEPT_REQ"));
}


inline void RECV_X2G_PT_ENTER_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_ENTER_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ENTER_PARTY_REQ"));
}


inline void RECV_X2G_PT_ENTER_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_ENTER_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ENTER_PARTY_ACK"));
}


inline void RECV_X2G_PT_ENTER_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_ENTER_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.enterobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ENTER_PARTY_NTF"));
}


inline void RECV_X2G_PT_ENTER_PARTY_ACCEPT_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_ENTER_PARTY_ACCEPT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyaccept
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ENTER_PARTY_ACCEPT_REQ"));
}


inline void RECV_X2G_PT_LEAVE_PARTY_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_LEAVE_PARTY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_LEAVE_PARTY_REQ"));
}


inline void RECV_X2G_PT_LEAVE_PARTY_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_LEAVE_PARTY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_LEAVE_PARTY_ACK"));
}


inline void RECV_X2G_PT_LEAVE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_LEAVE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_LEAVE_PARTY_NTF"));
}


inline void RECV_X2G_PT_BANISH_PARTY_MEMBER_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_BANISH_PARTY_MEMBER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_BANISH_PARTY_MEMBER_REQ"));
}


inline void RECV_X2G_PT_BANISH_PARTY_MEMBER_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_BANISH_PARTY_MEMBER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_BANISH_PARTY_MEMBER_ACK"));
}


inline void RECV_X2G_PT_BANISH_PARTY_MEMBER_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_BANISH_PARTY_MEMBER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_BANISH_PARTY_MEMBER_NTF"));
}


inline void RECV_X2G_PT_CHANGE_MASTER_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_MASTER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_MASTER_REQ"));
}


inline void RECV_X2G_PT_CHANGE_MASTER_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_MASTER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_MASTER_ACK"));
}


inline void RECV_X2G_PT_CHANGE_MASTER_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_MASTER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_MASTER_NTF"));
}


inline void RECV_X2G_PT_ONLINE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_ONLINE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.onoff
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_ONLINE_PARTY_NTF"));
}


inline void RECV_X2G_PT_OFFLINE_PARTY_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_OFFLINE_PARTY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.onoff
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_OFFLINE_PARTY_NTF"));
}


inline void RECV_X2G_PT_CHANGE_DISTRIBUTE_REQ(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_DISTRIBUTE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.rule
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_DISTRIBUTE_REQ"));
}


inline void RECV_X2G_PT_CHANGE_DISTRIBUTE_ACK(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_DISTRIBUTE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_DISTRIBUTE_ACK"));
}


inline void RECV_X2G_PT_CHANGE_DISTRIBUTE_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_CHANGE_DISTRIBUTE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.rule
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_CHANGE_DISTRIBUTE_NTF"));
}


inline void RECV_X2G_PT_PARTY_MEMBER_MOVE_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_PARTY_MEMBER_MOVE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.moveobject
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_PARTY_MEMBER_MOVE_NTF"));
}


inline void RECV_X2G_PT_PARTY_MEMBER_REGEN_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_PARTY_MEMBER_REGEN_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyregen
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_PARTY_MEMBER_REGEN_NTF"));
}


inline void RECV_X2G_PT_PARTY_MEMBER_DAMAGE_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_PARTY_MEMBER_DAMAGE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partydamage
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_PARTY_MEMBER_DAMAGE_NTF"));
}


inline void RECV_X2G_PT_PARTY_MEMBER_REVIVAL_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_PARTY_MEMBER_REVIVAL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partyrevival
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_PARTY_MEMBER_REVIVAL_NTF"));
}


inline void RECV_X2G_PT_PARTY_MEMBER_DEAD_NTF(HisUtil::CMsg& msgRecv, stX2G_PT_PARTY_MEMBER_DEAD_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.partydead
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_PT_PARTY_MEMBER_DEAD_NTF"));
}


inline void RECV_X2G_TD_TRADE_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_REQ"));
}


inline void RECV_X2G_TD_TRADE_ACK(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.tradeindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_ACK"));
}


inline void RECV_X2G_TD_TRADE_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.traderinfo
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_NTF"));
}


inline void RECV_X2G_TD_TRADE_ENTER_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_ENTER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.tradeindex
		>> st.bisenter
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_ENTER_REQ"));
}


inline void RECV_X2G_TD_TRADE_CANCEL_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_CANCEL_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_CANCEL_REQ"));
}


inline void RECV_X2G_TD_TRADE_CANCEL_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_CANCEL_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_CANCEL_NTF"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_MONEY_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_MONEY_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.money
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_MONEY_REQ"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_MONEY_ACK(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_MONEY_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_MONEY_ACK"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_MONEY_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_MONEY_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.money
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_MONEY_NTF"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_ITEM_REQ"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_ITEM_ACK"));
}


inline void RECV_X2G_TD_TRADE_UPLOAD_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_UPLOAD_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_UPLOAD_ITEM_NTF"));
}


inline void RECV_X2G_TD_TRADE_DOWNLOAD_ITEM_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_DOWNLOAD_ITEM_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_DOWNLOAD_ITEM_REQ"));
}


inline void RECV_X2G_TD_TRADE_DOWNLOAD_ITEM_ACK(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_DOWNLOAD_ITEM_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_DOWNLOAD_ITEM_ACK"));
}


inline void RECV_X2G_TD_TRADE_DOWNLOAD_ITEM_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_DOWNLOAD_ITEM_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_DOWNLOAD_ITEM_NTF"));
}


inline void RECV_X2G_TD_TRADE_CHAT_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_CHAT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chatmsg
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_CHAT_REQ"));
}


inline void RECV_X2G_TD_TRADE_CHAT_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_CHAT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.chatdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_CHAT_NTF"));
}


inline void RECV_X2G_TD_TRADE_ACCEPT_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_ACCEPT_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_ACCEPT_REQ"));
}


inline void RECV_X2G_TD_TRADE_ACCEPT_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_ACCEPT_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_ACCEPT_NTF"));
}


inline void RECV_X2G_TD_TRADE_COMPLETE_REQ(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_COMPLETE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_COMPLETE_REQ"));
}


inline void RECV_X2G_TD_TRADE_COMPLETE_ACK(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_COMPLETE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_COMPLETE_ACK"));
}


inline void RECV_X2G_TD_TRADE_COMPLETE_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_COMPLETE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.objectindex
		>> st.itemindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_COMPLETE_NTF"));
}


inline void RECV_X2G_TD_TRADE_LIST_NTF(HisUtil::CMsg& msgRecv, stX2G_TD_TRADE_LIST_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.money
		>> st.itemdata
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_TD_TRADE_LIST_NTF"));
}


inline void RECV_X2G_AU_AUCTION_LIST_REQ(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_LIST_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctionrequest
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_LIST_REQ"));
}


inline void RECV_X2G_AU_AUCTION_LIST_ACK(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_LIST_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_LIST_ACK"));
}


inline void RECV_X2G_AU_AUCTION_LIST_NTF(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_LIST_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctionlist
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_LIST_NTF"));
}


inline void RECV_X2G_AU_AUCTION_CREATE_REQ(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_CREATE_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctioncreate
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_CREATE_REQ"));
}


inline void RECV_X2G_AU_AUCTION_CREATE_ACK(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_CREATE_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_CREATE_ACK"));
}


inline void RECV_X2G_AU_AUCTION_CREATE_NTF(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_CREATE_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctionitem
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_CREATE_NTF"));
}


inline void RECV_X2G_AU_AUCTION_TENDER_REQ(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_TENDER_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctiontender
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_TENDER_REQ"));
}


inline void RECV_X2G_AU_AUCTION_TENDER_ACK(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_TENDER_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_TENDER_ACK"));
}


inline void RECV_X2G_AU_AUCTION_TENDER_NTF(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_TENDER_NTF& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.money
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_TENDER_NTF"));
}


inline void RECV_X2G_AU_AUCTION_RETURN_REQ(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_RETURN_REQ& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.auctionindex
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_RETURN_REQ"));
}


inline void RECV_X2G_AU_AUCTION_RETURN_ACK(HisUtil::CMsg& msgRecv, stX2G_AU_AUCTION_RETURN_ACK& st)
{
	HisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);
	msgRecv
		>> st.result
		;

	LOGEVENT("Session_Base_Packet", _T("<== recv X2G_AU_AUCTION_RETURN_ACK"));
}
