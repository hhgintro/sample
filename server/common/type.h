#pragma once

//#define _HG_TEST_RELEASE_MODE_DEBUGING_				//release ���� ������ϱ�(worldinfo ���� ��ζ�����)
//#define _HG_TEST_NO_CHECK_WORLD_IN_CHAR_			//npc�� �������� ������ ���� ���ӿ��� üũ�� ���� �ʴ´�.
//#define _HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_		//���� �ߺ� üũ ����( ����� game server ������ �ʿ��� )
//#define _HG_TEST_HIRED_SOLDIER_AI_				//�뺴 AI �����Ų��.
//#define _HG_TEST_USE_PORTAL_PROTOCOL_				//client���� portal��û�޾� ó���Ѵ�.
//#define _HG_TEST_DUNGEON_RESTART_					//�������� ����
//#define _HG_TEST_SHOW_DAMAGE_VALUE_					//��ȹ��û���� ������ �������� ���� �ʹܴ�.
//#define _HG_TEST_3x3_MONSTER_						//3x3���� ����
#define _HG_TEST_TUTORIAL_DUNGEON_START_				//Ʃ�͸��� �������� �ɸ��� ����
//#define _HT_TEST_BATTLE_START_ALL_OBJECT_				//battle�� start�� �Ǳ����� object ����� ������ �ʴ´�.
//#define _HG_TEST_PARTY_DUNGEON_							//��Ƽ�� ���� ���� ����ó��
//#define _HG_TEST_HEAL_STEEL_EXP_						//heal , steel �� exp ȹ��

//typedef UINT16			RESULT_T;
//typedef UINT32			HOSTID;
//typedef UINT8			REMOTE_ENTRY_T;	
//typedef UINT32			GROUPID;
//typedef UINT32			ADDR_IP;
//typedef UINT16			ADDR_PORT;
//typedef UINT64			TIME_T;//�����ð�
typedef UINT32			PROTOCOL_T ;
//typedef UINT8			PACKET_CONTEXT;
//typedef UINT32			CONNECTCODE;
typedef UINT32			ACCOUNTPK;	//unique id
//typedef UINT32			CHARPK;		//unique id
//typedef UINT32			SOLDIERPK;
//typedef UINT16			ZONEINDEX;
//typedef UINT16			ZONECODE;
//typedef UINT32			ZONEPUZZLE;
//typedef INT32			SECTORINDEX;
typedef	INT16			PARTYINDEX;	//party id
typedef INT64			ROOMINDEX;	//room id
//typedef INT32			BATTLEINDEX;	//battle field id
//typedef UINT8			BOARDINDEX;		//battle field seat id --��, Ÿ���� ����Ǹ� BOARDINDEX_DB Ÿ�Ե� signed������ �� ��ȯ�ض�.
//typedef INT8			BOARDINDEX_DB;
//typedef UINT32			GAMEOBJECTID;	//world unique id
//typedef UINT32			ANIINDEX;		//ani unique id
//typedef UINT8			ACTION_T;
//typedef UINT8			CHARCODE;
//typedef UINT8			SOLDIERCODE;
//typedef UINT16			NPCCODE;
//typedef UINT16			SKILLCODE;
//typedef UINT32			SKILLINDEX;		//unique id(App)
//typedef UINT32			SKILLPK;		//unique id(DB)
//typedef UINT16			SHOPCODE;
//typedef UINT32			ITEMINDEX;		//unique id(app)
//typedef UINT16			ITEMCODE;
//typedef UINT32			ITEMPK;			//unique id(DB)
//typedef UINT16			TURN_T;			//battle �� no
//typedef UINT8			BATTLE_STATUS_T;
//typedef UINT8			MOTION_T;		//motion id
//typedef UINT8			ATTACK_RESULT_T;
//typedef float			ORDER_T;		//battle ���� �켱����
//typedef UINT8			LEVELCODE;
//typedef UINT8			ITEM_GROUP_T;
//typedef UINT8			ITEM_CATEGORY_T;
//typedef UINT8			EQUIP_SEX_T;
//typedef UINT32			BUFFINDEX;
//typedef UINT16			BUFFCODE;
//typedef UINT16			BATTLEBONUSCODE;
//typedef UINT8			BATTLE_TEAM_T;
//typedef UINT32			QUESTPK;		//unique id(DB)
//typedef UINT16			QUESTCODE;
//typedef UINT8			QUEST_STATUS_T;
//typedef UINT8			CHAT_TYPE_T;
//typedef UINT8			S_STATUS_T;
//typedef UINT32			MAILPK;
//typedef UINT8			MAIL_STATUS_T;
//typedef UINT8			PARTY_ACCEPT_T;
//typedef UINT32			BATTLEPVPINDEX;
//typedef UINT32			PARTYINDEX;
//typedef UINT32			TRADEINDEX;
//typedef UINT32			TRADEPK;
//typedef UINT32			AUCTIONINDEX;
//typedef UINT32			AUCTIONPK;
//typedef UINT8			AUCTION_STATUS_T;
//typedef UINT8			BATTLE_FORMATION_T;
//typedef UINT8			TUTORIAL_TYPE_T;
//typedef UINT8			DISTRIBUTE_RULE_T;
//typedef UINT8			WORLD_MAP_T;
//typedef UINT32			CHAR_GAME_OPTION_T;
//typedef UINT8			BATTLE_TYPE_T;
//typedef UINT32			TELEGRAMINDEX;
//typedef UINT8			ITEM_GIFT_TYPE_T;
//typedef UINT8			ITEM_INVENTORY_TYPE_T;
//typedef INT16			STATEPOINT;		//�ɸ��� �ɷ�ġ
//typedef INT16			SKILLPOINT;		//�ɸ��� ��ų

