#include "StdAfx.h"
#include "GameClient.h"


CGameClient::CGameClient(void)
{
}

CGameClient::~CGameClient(void)
{
}


VOID CGameClient::OnIoConnected(VOID)
{
	//bIsEnterWorld_ = FALSE;
	CNetClient::OnIoConnected();
	LOGEVENT("HG_WHITE", _T("game에 접속되었습니다."));
}

VOID CGameClient::OnIoDisconnected(VOID)
{
	CNetClient::OnIoDisconnected();
	LOGEVENT("HG_WHITE", _T("game와 접속이 종료 되었습니다."));
}

VOID CGameClient::OnIoRecv(HisUtil::CMsg& msgRecv)
{
	// 프로토콜에 따른 switch 문
	switch (msgRecv.ID())
	{
		////tcp
		//ON_RECEIVE_ON_CLIENT(X2G_AC_CERTIFY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_LOAD_ALL_CHAR_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_LOAD_CHAR_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_CREATE_CHAR_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_DELETE_CHAR_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_CHECK_NICK_DUPLICATE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_OBJECT_EXP_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_LEVEL_UP_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_LEVEL_UP_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_MONEY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_SETUP_NO_RIVAL_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_RELEASE_NO_RIVAL_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_RESET_ABILITY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_COMPLETED_TUTORIAL_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_BATTLE_FORMATION_ACK);

		//ON_RECEIVE_ON_CLIENT(X2G_CH_LOAD_ALL_SOLDIER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_LOAD_SOLDIER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_CREATE_SOLDIER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_DELETE_SOLDIER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_WD_WORLD_ENTER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_WORLD_CHANGE_FOR_QUEST_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_ENTER_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_ALL_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_LEAVE_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_MOVE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_MOVE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_STOP_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_MOTION_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_MOTION_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_WORLD_PUZZLE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_WD_WORLD_MAP_OPEN_ACK);


		//ON_RECEIVE_ON_CLIENT(X2G_BD_CHAT_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BD_CHAT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BD_NOTICE_CHAT_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_OB_REGEN_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_OB_DEATH_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_OB_REVIVAL_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_SK_LOAD_CHAR_SKILL_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_SKILL_LEARN_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_SKILL_LEARN_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_SKILL_LEVELUP_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_SKILL_LEVELUP_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_SKILL_QUICK_SLOT_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_ATTACK_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_ATTACK_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_INSERT_BUFF_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_DELETE_BUFF_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_SK_HEAL_NTF);


		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_OPEN_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_INTRUDE_CHAR_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_INTRUDE_CHAR_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_INTRUDE_MONSTER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_ENTER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_LEAVE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_MOVE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_ENTER_BATTLE_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_ALL_BATTLE_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_LEAVE_BATTLE_OBJECT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_MOVE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_STOP_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_NEXT_STATUS_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_STATUS_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_TURN_WAITING_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_PVP_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_PVP_RESULT_ACK);

		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_SKIP_ENTER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_SKIP_LEAVE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_TOGGLE_SOLDIER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_BF_BATTLE_TOGGLE_SOLDIER_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_IT_LOAD_INVENTORY_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_QUICK_SLOT_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_BUY_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_SELL_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_PICKUP_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_PICKUP_ITEM_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_DESTROY_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_INVENTORY_CHANGE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_EQUIP_CHANGE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_EQUIP_CHANGE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_GIFT_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_GIFT_EQUIP_CHANGE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_GIFT_EQUIP_CHANGE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_USE_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_USE_ITEM_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_UPDATE_ITEM_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_SPLITE_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_IT_COMBINE_ITEM_ACK);

		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_LIST_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_INSERT_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_HELLO_NPC_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_TALK_NPC_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_UPDATE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_REWARD_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_QT_CHAR_QUEST_DELETE_ACK);


		//ON_RECEIVE_ON_CLIENT(X2G_ML_MAIL_LIST_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_ML_SEND_MAIL_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_ML_RECIEVE_MAIL_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_ML_CHANGE_MAIL_STATUS_ACK);


		//ON_RECEIVE_ON_CLIENT(X2G_PT_CREATE_PARTY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_CREATE_PARTY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_DELETE_PARTY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_DELETE_PARTY_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_PT_INVITE_PARTY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_INVITE_PARTY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_ENTER_PARTY_MEMBER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_ALL_PARTY_MEMBER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_LEAVE_PARTY_MEMBER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_ENTER_PARTY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_ENTER_PARTY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_LEAVE_PARTY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_LEAVE_PARTY_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_PT_BANISH_PARTY_MEMBER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_BANISH_PARTY_MEMBER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_CHANGE_MASTER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_CHANGE_MASTER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_ONLINE_PARTY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_OFFLINE_PARTY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_CHANGE_DISTRIBUTE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_CHANGE_DISTRIBUTE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_PARTY_MEMBER_MOVE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_PARTY_MEMBER_REGEN_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_PARTY_MEMBER_DAMAGE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_PARTY_MEMBER_REVIVAL_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_PT_PARTY_MEMBER_DEAD_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_CANCEL_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_UPLOAD_MONEY_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_UPLOAD_MONEY_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_UPLOAD_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_UPLOAD_ITEM_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_DOWNLOAD_ITEM_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_DOWNLOAD_ITEM_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_CHAT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_ACCEPT_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_COMPLETE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_COMPLETE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_TD_TRADE_LIST_NTF);

		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_LIST_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_LIST_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_CREATE_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_CREATE_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_TENDER_ACK);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_TENDER_NTF);
		//ON_RECEIVE_ON_CLIENT(X2G_AU_AUCTION_RETURN_ACK);


		////udp
		////ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_HELLO_PEER_REQ);
		////ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_FINE_THANKS_PEER_ACK);

		case 0:
		default:
		{
			LOGEVENT("Session_Base_Error", _T("Not Support Protocol(0x%04x)"), msgRecv.ID());

			// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_GRAY", _T("접속을 해제합니다."));

		} break;
	}

}

VOID CGameClient::OnIoSend(VOID)
{
	//LOGEVENT("HG_GRAY", _T("데이타 보낸 후처리는 여기에서 하세요"));

}

VOID CGameClient::OnIoServerHolePunchingCompleted()
{
	LOGEVENT("HG_WHITE", _T("서버와의 준비(홀펀칭)가 완료되었습니다."));

	//Certify();
}

VOID CGameClient::OnJoinGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Join Group 처리는 여기에서 하세요 Host id(0x%08x)"), remote);

}

VOID CGameClient::OnLeaveGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group 처리는 여기에서 하세요 Host id(0x%08x)"), remote);

}

void CGameClient::Update()
{
	CNetClient::Update();
}

//////remoteIP : 서버 ip
//////remotePort : 서버 port
////void CGameClient::Disconnect()
////{
////	//stX2L_CH_DISCONNECT_REQ st;
////	//SEND_X2L_CH_DISCONNECT_REQ(Host_Server, RELIABLE, st);
////}
////
////void CGameClient::JoinGroup()
////{
////	//stX2L_CH_JOIN_GROUP_REQ st;
////	//st.remote = remoteClient_.GetHostID();
////	//SEND_X2L_CH_JOIN_GROUP_REQ(Host_Server, RELIABLE, st);
////}
////
////void CGameClient::LeaveGroup()
////{
////	//stX2L_CH_LEAVE_GROUP_REQ st;
////	//st.remote = remoteClient_.GetHostID();
////	//SEND_X2L_CH_LEAVE_GROUP_REQ(Host_Server, RELIABLE, st);
////}
//void CGameClient::Certify()
//{
//	stX2G_AC_CERTIFY_REQ st;
//	st.account = account_;
//	st.masterkey = masterkey_;
//	SEND_X2G_AC_CERTIFY_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::LoadAllChar()
//{
//	stX2G_CH_LOAD_ALL_CHAR_REQ st;
//	SEND_X2G_CH_LOAD_ALL_CHAR_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::CreateChar()
//{
//	TCHAR nick[NICK_NAME_LENGTH] = _T("");
//	_stprintf(nick, _T("Dummy_%x"), this);
//
//	_stCreateCharInfo info;
//	info.slot_ = 0;
//	info.nickname_ = nick;
//	info.charcode_ = (UINT32)this % 3 + 1;
//	info.hearstyle_ = 21;
//	info.hearcolor_= 22;
//	info.face_ = 23;
//	info.dress_ = 1;
//	info.sstr_ = 11;
//	info.ddex_ = 12;
//	info.iint_ = 13;
//	info.ccon_ = 14;
//
//	stX2G_CH_CREATE_CHAR_REQ st;
//	st.charinfo.push_back(info);
//	SEND_X2G_CH_CREATE_CHAR_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::DeleteChar()
//{
//	stX2G_CH_DELETE_CHAR_REQ st;
//	st.objectindex = 0;
//	SEND_X2G_CH_DELETE_CHAR_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::WorldEnter(ZONECODE zonecode, GAMEOBJECTID objectindex)
//{
//	stX2G_WD_WORLD_ENTER_REQ st;
//	st.zonecode = zonecode;
//	st.objectindex = objectindex;
//	SEND_X2G_WD_WORLD_ENTER_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::WorldLeave()
//{
//	stX2G_WD_WORLD_LEAVE_REQ st;
//	SEND_X2G_WD_WORLD_LEAVE_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::WorldMove(float x, float y)
//{
//	stX2G_WD_MOVE_REQ st;
//	st.x = x;
//	st.y = y;
//	st.z = 0.f;
//	SEND_X2G_WD_MOVE_REQ(Host_Server, RELIABLE, st);
//}
//
//void CGameClient::Chat(BYTE type, TCHAR* chatmsg)
//{
//	stX2G_BD_CHAT_REQ st;
//	st.type = type;
//	st.chatmsg = chatmsg;
////	st.chatmsg = 
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
////L"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//	SEND_X2G_BD_CHAT_REQ(Host_Server, RELIABLE, st);
//	chatcount_ = 0;
//}
//

