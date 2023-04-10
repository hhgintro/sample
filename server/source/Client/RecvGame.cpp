#include "StdAfx.h"


//void CGameClient::OnX2G_AC_CERTIFY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AC_CERTIFY_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_RED", _T("fail OnX2G_AC_CERTIFY_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_WHITE", _T("게임 서버 인증 성공") );
//
//	//GetOwner()->GetBalanceClient().GetTcpSession()->End();
//	GetOwner()->GetBalanceClient().End();
//	LOGEVENT("HG_GRAY", _T("Balance 서버 접속을 종료합니다.") );
//
//
//	LoadAllChar();
//}
//
//void CGameClient::OnX2G_CH_LOAD_ALL_CHAR_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LOAD_ALL_CHAR_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_RED", _T("fail OnX2G_CH_LOAD_ALL_CHAR_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Load All Char") );
//
//	//캐릭터 생성
//	if(0 == st.chardata.size())
//	{
//		CreateChar();
//		return;
//	}
//	//입장
//	for(int i=0; i<(int)st.chardata.size(); ++i)
//	{
//		WorldEnter(1, st.chardata[0].id_);
//		objectindex_ = st.chardata[0].id_;
//		break;
//	}
//}
//
//void CGameClient::OnX2G_CH_LOAD_CHAR_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LOAD_CHAR_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_LOAD_CHAR_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Load Char") );
//
//	for(int i=0; i<(int)st.chardata.size(); ++i)
//	{
//		WorldEnter(1, st.chardata[0].id_);
//		objectindex_ = st.chardata[0].id_;
//		break;
//	}
//}
//
//void CGameClient::OnX2G_CH_CREATE_CHAR_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_CREATE_CHAR_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_RED", _T("fail OnX2G_CH_CREATE_CHAR_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Create Char") );
//}
//
//void CGameClient::OnX2G_CH_DELETE_CHAR_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_DELETE_CHAR_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_DELETE_CHAR_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Delete Char") );
//}
//
//void CGameClient::OnX2G_CH_CHECK_NICK_DUPLICATE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_CHECK_NICK_DUPLICATE_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_CHECK_NICK_DUPLICATE_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Check Nick Duplicate") );
//}
//
//void CGameClient::OnX2G_CH_OBJECT_EXP_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_OBJECT_EXP_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_OBJECT_EXP_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success object exp ack") );
//}
//
//void CGameClient::OnX2G_CH_LEVEL_UP_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LEVEL_UP_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_LEVEL_UP_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success level up ack") );
//}
//
//void CGameClient::OnX2G_CH_LEVEL_UP_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LEVEL_UP_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_LEVEL_UP_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success level up ntf") );
//}
//
//void CGameClient::OnX2G_CH_MONEY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_MONEY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_MONEY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success money ntf") );
//}
//
//void CGameClient::OnX2G_CH_SETUP_NO_RIVAL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_SETUP_NO_RIVAL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_SETUP_NO_RIVAL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success setup no rival") );
//}
//
//void CGameClient::OnX2G_CH_RELEASE_NO_RIVAL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_RELEASE_NO_RIVAL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_RELEASE_NO_RIVAL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success release no rival") );
//}
//
//void CGameClient::OnX2G_CH_RESET_ABILITY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_RESET_ABILITY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_RESET_ABILITY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success reset ability ntf") );
//}
//
//void CGameClient::OnX2G_CH_COMPLETED_TUTORIAL_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_COMPLETED_TUTORIAL_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_COMPLETED_TUTORIAL_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success completed tutorial") );
//}
//
//void CGameClient::OnX2G_CH_BATTLE_FORMATION_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_BATTLE_FORMATION_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_BATTLE_FORMATION_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success battle formation ack") );
//}
//
//void CGameClient::OnX2G_CH_LOAD_ALL_SOLDIER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LOAD_ALL_SOLDIER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_RED", _T("fail OnX2G_CH_LOAD_ALL_SOLDIER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Load All SOLDIER") );
//}
//
//void CGameClient::OnX2G_CH_LOAD_SOLDIER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_LOAD_SOLDIER_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_LOAD_SOLDIER_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Load SOLDIER") );
//}
//
//void CGameClient::OnX2G_CH_CREATE_SOLDIER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_CREATE_SOLDIER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_RED", _T("fail OnX2G_CH_CREATE_SOLDIER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Create SOLDIER") );
//}
//
//void CGameClient::OnX2G_CH_DELETE_SOLDIER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_DELETE_SOLDIER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_DELETE_SOLDIER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Delete SOLDIER") );
//}
//
//void CGameClient::OnX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success pay salary SOLDIER") );
//}
//
//void CGameClient::OnX2G_WD_WORLD_ENTER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_WORLD_ENTER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_WORLD_ENTER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	for(int i=0; i<(int)st.enterdata.size(); ++i)
//	{
//		_stEnterObjectData& enterobject = st.enterdata[i];
//		if(objectindex_ == enterobject.id_)
//		{
//			//SetIsEnterWorld(TRUE);
//			patrolpos_ = enterobject.currentpos_;
//		}
//	}
//	LOGEVENT("HG_GRAY", _T("Success World Enter") );
//
//	//Chat(1, _T(""));
//}
//
//void CGameClient::OnX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_WORLD_CHANGE_FOR_QUEST_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success World Change For Quest") );
//}
//
//void CGameClient::OnX2G_WD_ENTER_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_ENTER_OBJECT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_ENTER_OBJECT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success World Enter Ntf") );
//}
//
//void CGameClient::OnX2G_WD_ALL_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_ALL_OBJECT_NTF);
//
//	LOGEVENT("HG_GRAY", _T("Success World All Object Ntf") );
//}
//
//void CGameClient::OnX2G_WD_LEAVE_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_LEAVE_OBJECT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_LEAVE_OBJECT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success World Leave Ntf") );
//}
//
//void CGameClient::OnX2G_WD_MOVE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_MOVE_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_MOVE_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success World Move") );
//}
//
//void CGameClient::OnX2G_WD_MOVE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_MOVE_NTF);
//	LOGEVENT("HG_GRAY", _T("Success World Move Ntf") );
//}
//
//void CGameClient::OnX2G_WD_STOP_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_STOP_NTF);
//	LOGEVENT("HG_GRAY", _T("Success World Stop Ntf") );
//}
//
//void CGameClient::OnX2G_WD_MOTION_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_MOTION_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_WD_MOTION_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success World motion ") );
//}
//
//void CGameClient::OnX2G_WD_MOTION_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_MOTION_NTF);
//	LOGEVENT("HG_GRAY", _T("Success World motion Ntf") );
//}
//
//void CGameClient::OnX2G_WD_WORLD_PUZZLE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_WORLD_PUZZLE_NTF);
//	LOGEVENT("HG_GRAY", _T("Success World puzzle Ntf") );
//}
//
//void CGameClient::OnX2G_WD_WORLD_MAP_OPEN_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_WD_WORLD_MAP_OPEN_ACK);
//	LOGEVENT("HG_GRAY", _T("Success World map open Ack") );
//}
//
//void CGameClient::OnX2G_BD_CHAT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BD_CHAT_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BD_CHAT_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	//Chat(1, _T(""));
//}
//
//void CGameClient::OnX2G_BD_CHAT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BD_CHAT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BD_CHAT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	for(int i=0; i<(int)st.chatdata.size(); ++i)
//	{
//		_stChattingData& chat = st.chatdata[i];
//
//		LOGEVENT("HG_GRAY", _T("type : %d/%d, chat : %s"), ++chatcount_, chat.type_, chat.chatmsg_.c_str());
//	}
//
//	//Chat(1, _T(""));
//}
//
//void CGameClient::OnX2G_BD_NOTICE_CHAT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BD_NOTICE_CHAT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BD_NOTICE_CHAT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	for(int i=0; i<(int)st.noticedata.size(); ++i)
//	{
//		_stNoticeChattingData& notice = st.noticedata[i];
//
//		LOGEVENT("HG_GRAY", _T("notice : %s"), notice.chatmsg_.c_str());
//	}
//}
//
//void CGameClient::OnX2G_OB_REGEN_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_OB_REGEN_NTF);
//}
//
//void CGameClient::OnX2G_OB_DEATH_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_OB_DEATH_NTF);
//}
//
//void CGameClient::OnX2G_OB_REVIVAL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_OB_REVIVAL_NTF);
//}
//
//void CGameClient::OnX2G_SK_LOAD_CHAR_SKILL_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_LOAD_CHAR_SKILL_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_LOAD_CHAR_SKILL_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success load char skill Ack") );
//}
//
//void CGameClient::OnX2G_SK_SKILL_LEARN_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_SKILL_LEARN_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_SKILL_LEARN_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//}
//
//void CGameClient::OnX2G_SK_SKILL_LEARN_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_SKILL_LEARN_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_SKILL_LEARN_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//}
//
//void CGameClient::OnX2G_SK_SKILL_LEVELUP_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_SKILL_LEVELUP_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_SKILL_LEVELUP_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//}
//
//void CGameClient::OnX2G_SK_SKILL_LEVELUP_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_SKILL_LEVELUP_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_SKILL_LEVELUP_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//}
//
//void CGameClient::OnX2G_SK_SKILL_QUICK_SLOT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_SKILL_QUICK_SLOT_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_SKILL_QUICK_SLOT_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//}
//
//void CGameClient::OnX2G_SK_ATTACK_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_ATTACK_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_ATTACK_ACK(0x%04x)"), st.result);
//		return;
//	}
//}
//
//void CGameClient::OnX2G_SK_ATTACK_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_ATTACK_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_ATTACK_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Attack Ntf") );
//}
//
//void CGameClient::OnX2G_SK_INSERT_BUFF_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_INSERT_BUFF_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_INSERT_BUFF_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Insert Buff Ntf") );
//}
//
//void CGameClient::OnX2G_SK_DELETE_BUFF_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_DELETE_BUFF_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_DELETE_BUFF_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Delete Buff Ntf") );
//}
//
//void CGameClient::OnX2G_SK_HEAL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_SK_HEAL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_SK_HEAL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Heal Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_OBJECT_NTF);
//	LOGEVENT("HG_GRAY", _T("Success Battle object Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_OPEN_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_OPEN_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_OPEN_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle open ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_INTRUDE_CHAR_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_INTRUDE_CHAR_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_INTRUDE_CHAR_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle intrude char ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_INTRUDE_CHAR_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_INTRUDE_CHAR_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_INTRUDE_CHAR_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle intrude char ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_INTRUDE_MONSTER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_INTRUDE_MONSTER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_INTRUDE_MONSTER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle intrude monster ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_ENTER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_ENTER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_ENTER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Enter") );
//}
//
//void CGameClient::OnX2G_BF_ENTER_BATTLE_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_ENTER_BATTLE_OBJECT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_ENTER_BATTLE_OBJECT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Enter Ntf") );
//}
//
//void CGameClient::OnX2G_BF_ALL_BATTLE_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_ALL_BATTLE_OBJECT_NTF);
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field All Object Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_LEAVE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_LEAVE_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_LEAVE_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Leave") );
//}
//
//void CGameClient::OnX2G_BF_LEAVE_BATTLE_OBJECT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_LEAVE_BATTLE_OBJECT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_LEAVE_BATTLE_OBJECT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Leave Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_MOVE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_MOVE_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_MOVE_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Move") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_MOVE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_MOVE_NTF);
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Move Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_STOP_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_STOP_NTF);
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Stop Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_NEXT_STATUS_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_NEXT_STATUS_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_NEXT_STATUS_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Move") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_STATUS_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_STATUS_NTF);
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Status Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_TURN_WAITING_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_TURN_WAITING_NTF);
//	LOGEVENT("HG_GRAY", _T("Success Battle Field Waiting List Ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_PVP_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_PVP_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_PVP_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle find path") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_PVP_RESULT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_PVP_RESULT_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_PVP_RESULT_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle find path") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_SKIP_ENTER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_SKIP_ENTER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_SKIP_ENTER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle skip enter ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_SKIP_LEAVE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_SKIP_LEAVE_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_SKIP_LEAVE_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle skip leave ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle skip skill casting ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle skip skill casting ntf") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_TOGGLE_SOLDIER_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle toggle soldier ack") );
//}
//
//void CGameClient::OnX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_BF_BATTLE_TOGGLE_SOLDIER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Battle toggle soldier ntf") );
//}
//
//void CGameClient::OnX2G_IT_LOAD_INVENTORY_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_LOAD_INVENTORY_ITEM_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_LOAD_INVENTORY_ITEM_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Load Inventory Item") );
//}
//
//void CGameClient::OnX2G_IT_QUICK_SLOT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_QUICK_SLOT_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_QUICK_SLOT_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success Load quick slot") );
//}
//
//void CGameClient::OnX2G_IT_BUY_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_BUY_ITEM_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_BUY_ITEM_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success buy item") );
//}
//
//
//void CGameClient::OnX2G_IT_SELL_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_SELL_ITEM_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_SELL_ITEM_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success sell item") );
//}
//
//void CGameClient::OnX2G_IT_PICKUP_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_PICKUP_ITEM_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_PICKUP_ITEM_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success pickup item") );
//}
//
//void CGameClient::OnX2G_IT_PICKUP_ITEM_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_PICKUP_ITEM_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_PICKUP_ITEM_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success pickup item ntf") );
//}
//
//void CGameClient::OnX2G_IT_DESTROY_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_DESTROY_ITEM_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_DESTROY_ITEM_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success destroy item") );
//}
//
//void CGameClient::OnX2G_IT_INVENTORY_CHANGE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_INVENTORY_CHANGE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_INVENTORY_CHANGE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success inventory change") );
//}
//
//void CGameClient::OnX2G_IT_EQUIP_CHANGE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_EQUIP_CHANGE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_EQUIP_CHANGE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success equip change Ack") );
//}
//
//void CGameClient::OnX2G_IT_EQUIP_CHANGE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_EQUIP_CHANGE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_EQUIP_CHANGE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success equip change Ntf") );
//}
//
//void CGameClient::OnX2G_IT_GIFT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_GIFT_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_GIFT_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success gift inventory") );
//}
//
//void CGameClient::OnX2G_IT_GIFT_EQUIP_CHANGE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_GIFT_EQUIP_CHANGE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_GIFT_EQUIP_CHANGE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success equip change Ack") );
//}
//
//void CGameClient::OnX2G_IT_GIFT_EQUIP_CHANGE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_GIFT_EQUIP_CHANGE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_GIFT_EQUIP_CHANGE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success equip change Ntf") );
//}
//
////void CGameClient::OnX2G_IT_NPC_DROP_ITEM_ACK(CMsg& msgRecv)
////{
////	READ_PACKET(X2G_IT_NPC_DROP_ITEM_ACK);
////
////	//if(st.result)
////	//{
////	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_NPC_DROP_ITEM_ACK(0x%04x)"), st.result);
////	//	return;
////	//}
////
////	LOGEVENT("HG_GRAY", _T("Success npc drop item ack") );
////}
////
////void CGameClient::OnX2G_IT_NPC_DROP_ITEM_NTF(CMsg& msgRecv)
////{
////	READ_PACKET(X2G_IT_NPC_DROP_ITEM_NTF);
////
////	//if(st.result)
////	//{
////	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_NPC_DROP_ITEM_NTF(0x%04x)"), st.result);
////	//	return;
////	//}
////
////	LOGEVENT("HG_GRAY", _T("Success npc drop item ntf") );
////}
//
//void CGameClient::OnX2G_IT_USE_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_USE_ITEM_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_USE_ITEM_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success use item Ack") );
//}
//
//void CGameClient::OnX2G_IT_USE_ITEM_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_USE_ITEM_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_USE_ITEM_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success use item ntf") );
//}
//
//void CGameClient::OnX2G_IT_UPDATE_ITEM_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_UPDATE_ITEM_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_UPDATE_ITEM_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success update item ntf") );
//}
//
//void CGameClient::OnX2G_IT_SPLITE_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_SPLITE_ITEM_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_SPLITE_ITEM_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success splite item Ack") );
//}
//
//void CGameClient::OnX2G_IT_COMBINE_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_IT_COMBINE_ITEM_ACK);
//
//	if(st.result)
//	{
//		LOGEVENT("HG_GRAY", _T("fail OnX2G_IT_COMBINE_ITEM_ACK(0x%04x)"), st.result);
//		return;
//	}
//
//	LOGEVENT("HG_GRAY", _T("Success combine item Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_LIST_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_LIST_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_LIST_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success quest list Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_INSERT_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_INSERT_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_INSERT_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success new quest ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_HELLO_NPC_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_HELLO_NPC_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_HELLO_NPC_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success hello npc Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_TALK_NPC_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_TALK_NPC_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_TALK_NPC_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success talk quest npc Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_UPDATE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_UPDATE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_UPDATE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success quest update Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success quest progress update Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_REWARD_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_REWARD_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_REWARD_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success reward quest Ack") );
//}
//
//void CGameClient::OnX2G_QT_CHAR_QUEST_DELETE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_QT_CHAR_QUEST_DELETE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_QT_CHAR_QUEST_DELETE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success quest delete ack") );
//}
//
//void CGameClient::OnX2G_ML_MAIL_LIST_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_ML_MAIL_LIST_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_ML_MAIL_LIST_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success mail list ack") );
//}
//
//void CGameClient::OnX2G_ML_SEND_MAIL_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_ML_SEND_MAIL_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_ML_SEND_MAIL_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success send mail ack") );
//}
//
//void CGameClient::OnX2G_ML_RECIEVE_MAIL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_ML_RECIEVE_MAIL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_ML_RECIEVE_MAIL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success recieve mail ack") );
//}
//
//void CGameClient::OnX2G_ML_CHANGE_MAIL_STATUS_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_ML_CHANGE_MAIL_STATUS_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_ML_CHANGE_MAIL_STATUS_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success send mail ack") );
//}
//
//void CGameClient::OnX2G_PT_CREATE_PARTY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CREATE_PARTY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CREATE_PARTY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success create party ack") );
//}
//
//void CGameClient::OnX2G_PT_CREATE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CREATE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CREATE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success create party ntf") );
//}
//
//void CGameClient::OnX2G_PT_DELETE_PARTY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_DELETE_PARTY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_DELETE_PARTY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success delete party ack") );
//}
//
//void CGameClient::OnX2G_PT_DELETE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_DELETE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_DELETE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party delete ack") );
//}
//
//void CGameClient::OnX2G_PT_INVITE_PARTY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_INVITE_PARTY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_INVITE_PARTY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success invite party ack") );
//}
//
//void CGameClient::OnX2G_PT_INVITE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_INVITE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_INVITE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success invite party ntf") );
//}
//
//void CGameClient::OnX2G_PT_ENTER_PARTY_MEMBER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_ENTER_PARTY_MEMBER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_ENTER_PARTY_MEMBER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success enter party member ntf") );
//}
//
//void CGameClient::OnX2G_PT_ALL_PARTY_MEMBER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_ALL_PARTY_MEMBER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_ALL_PARTY_MEMBER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success all party member ntf") );
//}
//
//void CGameClient::OnX2G_PT_LEAVE_PARTY_MEMBER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_LEAVE_PARTY_MEMBER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_LEAVE_PARTY_MEMBER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success leave party member ntf") );
//}
//
//void CGameClient::OnX2G_PT_ENTER_PARTY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_ENTER_PARTY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_ENTER_PARTY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success enter party ack") );
//}
//
//void CGameClient::OnX2G_PT_ENTER_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_ENTER_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_ENTER_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success enter party ntf") );
//}
//
//void CGameClient::OnX2G_PT_LEAVE_PARTY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_LEAVE_PARTY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_LEAVE_PARTY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success leave party ack") );
//}
//
//void CGameClient::OnX2G_PT_LEAVE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_LEAVE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_LEAVE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success leave party ntf") );
//}
//
//void CGameClient::OnX2G_PT_BANISH_PARTY_MEMBER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_BANISH_PARTY_MEMBER_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_BANISH_PARTY_MEMBER_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success banish part member ack") );
//}
//
//void CGameClient::OnX2G_PT_BANISH_PARTY_MEMBER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_BANISH_PARTY_MEMBER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_BANISH_PARTY_MEMBER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success banish party member ntf") );
//}
//
//void CGameClient::OnX2G_PT_CHANGE_MASTER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CHANGE_MASTER_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CHANGE_MASTER_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ack") );
//}
//
//void CGameClient::OnX2G_PT_CHANGE_MASTER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CHANGE_MASTER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CHANGE_MASTER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_PT_ONLINE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_ONLINE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_ONLINE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success online party ntf") );
//}
//
//void CGameClient::OnX2G_PT_OFFLINE_PARTY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_OFFLINE_PARTY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_OFFLINE_PARTY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success offline party ntf") );
//}
//
//void CGameClient::OnX2G_PT_CHANGE_DISTRIBUTE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CHANGE_DISTRIBUTE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CHANGE_DISTRIBUTE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change distribute ack") );
//}
//
//void CGameClient::OnX2G_PT_CHANGE_DISTRIBUTE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_CHANGE_DISTRIBUTE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_CHANGE_DISTRIBUTE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change distribute ntf") );
//}
//
//void CGameClient::OnX2G_PT_PARTY_MEMBER_MOVE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_PARTY_MEMBER_MOVE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_PARTY_MEMBER_MOVE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party member move ntf") );
//}
//
//void CGameClient::OnX2G_PT_PARTY_MEMBER_REGEN_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_PARTY_MEMBER_REGEN_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_PARTY_MEMBER_REGEN_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party member regen ntf") );
//}
//
//void CGameClient::OnX2G_PT_PARTY_MEMBER_DAMAGE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_PARTY_MEMBER_DAMAGE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_PARTY_MEMBER_DAMAGE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party member damage ntf") );
//}
//
//void CGameClient::OnX2G_PT_PARTY_MEMBER_REVIVAL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_PARTY_MEMBER_REVIVAL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_PARTY_MEMBER_REVIVAL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party member revival ntf") );
//}
//
//void CGameClient::OnX2G_PT_PARTY_MEMBER_DEAD_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_PT_PARTY_MEMBER_DEAD_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_PT_PARTY_MEMBER_DEAD_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success party member dead ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_CANCEL_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_CANCEL_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_CANCEL_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_UPLOAD_MONEY_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_UPLOAD_MONEY_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_UPLOAD_MONEY_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_UPLOAD_MONEY_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_UPLOAD_MONEY_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_UPLOAD_MONEY_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_UPLOAD_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_UPLOAD_ITEM_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_UPLOAD_ITEM_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_UPLOAD_ITEM_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_UPLOAD_ITEM_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_UPLOAD_ITEM_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_DOWNLOAD_ITEM_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_DOWNLOAD_ITEM_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_DOWNLOAD_ITEM_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_DOWNLOAD_ITEM_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_DOWNLOAD_ITEM_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_DOWNLOAD_ITEM_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_CHAT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_CHAT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_CHAT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_ACCEPT_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_ACCEPT_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_ACCEPT_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_COMPLETE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_COMPLETE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_COMPLETE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_COMPLETE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_COMPLETE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_COMPLETE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_TD_TRADE_LIST_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_TD_TRADE_LIST_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_TD_TRADE_LIST_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success change master ntf") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_LIST_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_LIST_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_LIST_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction list ack") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_LIST_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_LIST_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_LIST_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction list ntf") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_CREATE_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_CREATE_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_CREATE_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction register ack") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_CREATE_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_CREATE_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_CREATE_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction register ntf") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_TENDER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_TENDER_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_TENDER_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction tender ack") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_TENDER_NTF(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_TENDER_NTF);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_TENDER_NTF(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction tender ntf") );
//}
//
//void CGameClient::OnX2G_AU_AUCTION_RETURN_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2G_AU_AUCTION_RETURN_ACK);
//
//	//if(st.result)
//	//{
//	//	LOGEVENT("HG_GRAY", _T("fail OnX2G_AU_AUCTION_RETURN_ACK(0x%04x)"), st.result);
//	//	return;
//	//}
//
//	LOGEVENT("HG_GRAY", _T("Success auction return ack") );
//}