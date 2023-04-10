#pragma once

class CClientWorld;

//사용자에 의해 선언되어지는 class 이다
class CGameClient : public NetCore::CNetClient//, public X2B_SEND, public X2G_SEND
{
public:
	CGameClient(void);
	virtual ~CGameClient(void);

	VOID OnIoConnected(VOID);
	VOID OnIoDisconnected(VOID);
	VOID OnIoRecv(HisUtil::CMsg& msgRecv);
	VOID OnIoSend(VOID);

	VOID OnIoServerHolePunchingCompleted();

	VOID OnJoinGroup(HOSTID remote);
	VOID OnLeaveGroup(HOSTID remote);

	void Update();

	////void Disconnect();
	////void JoinGroup();
	////void LeaveGroup();
	////void SayHelloPeer();
	//void Certify();
	//void LoadAllChar();
	//void CreateChar();
	//void DeleteChar();

	//void WorldEnter(ZONECODE zonecode, GAMEOBJECTID objectindex);
	//void WorldLeave();
	//void WorldMove(float x, float y);

	//void Chat(BYTE type, TCHAR* chatmsg);


	NetCore::IRemote* FindRemote(HOSTID remote) { return CNetClient::FindRemote(remote); }
	NetCore::CPacketSession* FindPacketSession(NetCore::IRemote* peer, bool bIsUdp) { return CNetClient::FindPacketSession(peer, bIsUdp); }

	//std::string GetAccount() { return account_;}
	//void SetAccount(std::string account) { account_ = account; }

	//std::string GetMasterKey() { return masterkey_;}
	//void SetMasterKey(std::string key) { masterkey_ = key; }

	CClientWorld* GetOwner() { return owner_; }
	void SetOwner(CClientWorld* owner) { owner_ = owner; }

	//BOOL GetIsEnterWorld() { return bIsEnterWorld_; }
	//void SetIsEnterWorld(BOOL bEnter) { bIsEnterWorld_ = bEnter; }

	//GAMEOBJECTID GetObjectID() { return objectindex_; }
	//Vector3D& GetPatrolPos() { return patrolpos_; }

private:

	//void OnX2G_AC_CERTIFY_ACK(CMsg& msgRecv);

	//void OnX2G_CH_LOAD_ALL_CHAR_ACK(CMsg& msgRecv);
	//void OnX2G_CH_LOAD_CHAR_ACK(CMsg& msgRecv);
	//void OnX2G_CH_CREATE_CHAR_ACK(CMsg& msgRecv);
	//void OnX2G_CH_DELETE_CHAR_ACK(CMsg& msgRecv);
	//void OnX2G_CH_CHECK_NICK_DUPLICATE_ACK(CMsg& msgRecv);
	//void OnX2G_CH_OBJECT_EXP_ACK(CMsg& msgRecv);
	//void OnX2G_CH_LEVEL_UP_ACK(CMsg& msgRecv);
	//void OnX2G_CH_LEVEL_UP_NTF(CMsg& msgRecv);
	//void OnX2G_CH_MONEY_NTF(CMsg& msgRecv);
	//void OnX2G_CH_SETUP_NO_RIVAL_NTF(CMsg& msgRecv);
	//void OnX2G_CH_RELEASE_NO_RIVAL_NTF(CMsg& msgRecv);
	//void OnX2G_CH_RESET_ABILITY_NTF(CMsg& msgRecv);
	//void OnX2G_CH_COMPLETED_TUTORIAL_ACK(CMsg& msgRecv);
	//void OnX2G_CH_BATTLE_FORMATION_ACK(CMsg& msgRecv);

	//void OnX2G_CH_LOAD_ALL_SOLDIER_ACK(CMsg& msgRecv);
	//void OnX2G_CH_LOAD_SOLDIER_ACK(CMsg& msgRecv);
	//void OnX2G_CH_CREATE_SOLDIER_ACK(CMsg& msgRecv);
	//void OnX2G_CH_DELETE_SOLDIER_ACK(CMsg& msgRecv);
	//void OnX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF(CMsg& msgRecv);

	//void OnX2G_WD_WORLD_ENTER_ACK(CMsg& msgRecv);
	//void OnX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK(CMsg& msgRecv);
	//void OnX2G_WD_ENTER_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_WD_ALL_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_WD_LEAVE_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_WD_MOVE_ACK(CMsg& msgRecv);
	//void OnX2G_WD_MOVE_NTF(CMsg& msgRecv);
	//void OnX2G_WD_STOP_NTF(CMsg& msgRecv);
	//void OnX2G_WD_MOTION_ACK(CMsg& msgRecv);
	//void OnX2G_WD_MOTION_NTF(CMsg& msgRecv);
	//void OnX2G_WD_WORLD_PUZZLE_NTF(CMsg& msgRecv);
	//void OnX2G_WD_WORLD_MAP_OPEN_ACK(CMsg& msgRecv);

	//void OnX2G_BD_CHAT_ACK(CMsg& msgRecv);
	//void OnX2G_BD_CHAT_NTF(CMsg& msgRecv);
	//void OnX2G_BD_NOTICE_CHAT_NTF(CMsg& msgRecv);

	//void OnX2G_OB_REGEN_NTF(CMsg& msgRecv);
	//void OnX2G_OB_DEATH_NTF(CMsg& msgRecv);
	//void OnX2G_OB_REVIVAL_NTF(CMsg& msgRecv);

	//void OnX2G_SK_LOAD_CHAR_SKILL_ACK(CMsg& msgRecv);
	//void OnX2G_SK_SKILL_LEARN_ACK(CMsg& msgRecv);
	//void OnX2G_SK_SKILL_LEARN_NTF(CMsg& msgRecv);
	//void OnX2G_SK_SKILL_LEVELUP_ACK(CMsg& msgRecv);
	//void OnX2G_SK_SKILL_LEVELUP_NTF(CMsg& msgRecv);
	//void OnX2G_SK_SKILL_QUICK_SLOT_ACK(CMsg& msgRecv);
	//void OnX2G_SK_ATTACK_ACK(CMsg& msgRecv);
	//void OnX2G_SK_ATTACK_NTF(CMsg& msgRecv);
	//void OnX2G_SK_INSERT_BUFF_NTF(CMsg& msgRecv);
	//void OnX2G_SK_DELETE_BUFF_NTF(CMsg& msgRecv);
	//void OnX2G_SK_HEAL_NTF(CMsg& msgRecv);


	//void OnX2G_BF_BATTLE_OPEN_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_INTRUDE_CHAR_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_INTRUDE_CHAR_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_INTRUDE_MONSTER_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_ENTER_ACK(CMsg& msgRecv);
	//void OnX2G_BF_ENTER_BATTLE_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_BF_ALL_BATTLE_OBJECT_NTF(CMsg& msgRecv);

	//void OnX2G_BF_BATTLE_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_LEAVE_ACK(CMsg& msgRecv);
	//void OnX2G_BF_LEAVE_BATTLE_OBJECT_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_MOVE_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_MOVE_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_STOP_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_NEXT_STATUS_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_STATUS_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_TURN_WAITING_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_PVP_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_PVP_RESULT_ACK(CMsg& msgRecv);

	//void OnX2G_BF_BATTLE_SKIP_ENTER_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_SKIP_LEAVE_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK(CMsg& msgRecv);
	//void OnX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF(CMsg& msgRecv);

	//void OnX2G_IT_LOAD_INVENTORY_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_QUICK_SLOT_ACK(CMsg& msgRecv);
	//void OnX2G_IT_BUY_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_SELL_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_PICKUP_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_PICKUP_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_IT_DESTROY_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_INVENTORY_CHANGE_ACK(CMsg& msgRecv);
	//void OnX2G_IT_EQUIP_CHANGE_ACK(CMsg& msgRecv);
	//void OnX2G_IT_EQUIP_CHANGE_NTF(CMsg& msgRecv);
	//void OnX2G_IT_GIFT_ACK(CMsg& msgRecv);
	//void OnX2G_IT_GIFT_EQUIP_CHANGE_ACK(CMsg& msgRecv);
	//void OnX2G_IT_GIFT_EQUIP_CHANGE_NTF(CMsg& msgRecv);
	////void OnX2G_IT_NPC_DROP_ITEM_ACK(CMsg& msgRecv);
	////void OnX2G_IT_NPC_DROP_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_IT_USE_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_USE_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_IT_UPDATE_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_IT_SPLITE_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_IT_COMBINE_ITEM_ACK(CMsg& msgRecv);

	//void OnX2G_QT_CHAR_QUEST_LIST_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_INSERT_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_HELLO_NPC_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_TALK_NPC_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_UPDATE_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_REWARD_ACK(CMsg& msgRecv);
	//void OnX2G_QT_CHAR_QUEST_DELETE_ACK(CMsg& msgRecv);


	//void OnX2G_ML_MAIL_LIST_ACK(CMsg& msgRecv);
	//void OnX2G_ML_SEND_MAIL_ACK(CMsg& msgRecv);
	//void OnX2G_ML_RECIEVE_MAIL_NTF(CMsg& msgRecv);
	//void OnX2G_ML_CHANGE_MAIL_STATUS_ACK(CMsg& msgRecv);


	//void OnX2G_PT_CREATE_PARTY_ACK(CMsg& msgRecv);
	//void OnX2G_PT_CREATE_PARTY_NTF(CMsg& msgRecv);
	//void OnX2G_PT_DELETE_PARTY_ACK(CMsg& msgRecv);
	//void OnX2G_PT_DELETE_PARTY_NTF(CMsg& msgRecv);

	//void OnX2G_PT_INVITE_PARTY_ACK(CMsg& msgRecv);
	//void OnX2G_PT_INVITE_PARTY_NTF(CMsg& msgRecv);
	//void OnX2G_PT_ENTER_PARTY_MEMBER_NTF(CMsg& msgRecv);
	//void OnX2G_PT_ALL_PARTY_MEMBER_NTF(CMsg& msgRecv);
	//void OnX2G_PT_LEAVE_PARTY_MEMBER_NTF(CMsg& msgRecv);
	//void OnX2G_PT_ENTER_PARTY_ACK(CMsg& msgRecv);
	//void OnX2G_PT_ENTER_PARTY_NTF(CMsg& msgRecv);
	//void OnX2G_PT_LEAVE_PARTY_ACK(CMsg& msgRecv);
	//void OnX2G_PT_LEAVE_PARTY_NTF(CMsg& msgRecv);

	//void OnX2G_PT_BANISH_PARTY_MEMBER_ACK(CMsg& msgRecv);
	//void OnX2G_PT_BANISH_PARTY_MEMBER_NTF(CMsg& msgRecv);
	//void OnX2G_PT_CHANGE_MASTER_ACK(CMsg& msgRecv);
	//void OnX2G_PT_CHANGE_MASTER_NTF(CMsg& msgRecv);
	//void OnX2G_PT_ONLINE_PARTY_NTF(CMsg& msgRecv);
	//void OnX2G_PT_OFFLINE_PARTY_NTF(CMsg& msgRecv);
	//void OnX2G_PT_CHANGE_DISTRIBUTE_ACK(CMsg& msgRecv);
	//void OnX2G_PT_CHANGE_DISTRIBUTE_NTF(CMsg& msgRecv);
	//void OnX2G_PT_PARTY_MEMBER_MOVE_NTF(CMsg& msgRecv);
	//void OnX2G_PT_PARTY_MEMBER_REGEN_NTF(CMsg& msgRecv);
	//void OnX2G_PT_PARTY_MEMBER_DAMAGE_NTF(CMsg& msgRecv);
	//void OnX2G_PT_PARTY_MEMBER_REVIVAL_NTF(CMsg& msgRecv);
	//void OnX2G_PT_PARTY_MEMBER_DEAD_NTF(CMsg& msgRecv);

	//void OnX2G_TD_TRADE_ACK(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_CANCEL_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_UPLOAD_MONEY_ACK(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_UPLOAD_MONEY_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_UPLOAD_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_UPLOAD_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_DOWNLOAD_ITEM_ACK(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_DOWNLOAD_ITEM_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_CHAT_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_ACCEPT_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_COMPLETE_ACK(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_COMPLETE_NTF(CMsg& msgRecv);
	//void OnX2G_TD_TRADE_LIST_NTF(CMsg& msgRecv);

	//void OnX2G_AU_AUCTION_LIST_ACK(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_LIST_NTF(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_CREATE_ACK(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_CREATE_NTF(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_TENDER_ACK(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_TENDER_NTF(CMsg& msgRecv);
	//void OnX2G_AU_AUCTION_RETURN_ACK(CMsg& msgRecv);


private:
	//std::string account_;
	//std::string masterkey_;

	//int chatcount_;

	CClientWorld* owner_;

	//BOOL bIsEnterWorld_;
	//GAMEOBJECTID objectindex_;
	//Vector3D patrolpos_;	//현재 위치

};
