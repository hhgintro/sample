#pragma once

//#define _HG_TEST_RELEASE_MODE_DEBUGING_				//release 모드로 디버깅하기(worldinfo 정보 경로때문에)
//#define _HG_TEST_NO_CHECK_WORLD_IN_CHAR_			//npc의 움직임을 제한한 유저 접속여부 체크를 하지 않는다.
//#define _HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_		//계정 중복 체크 안함( 적용시 game server 수정이 필요함 )
//#define _HG_TEST_HIRED_SOLDIER_AI_				//용병 AI 적용시킨다.
//#define _HG_TEST_USE_PORTAL_PROTOCOL_				//client에서 portal요청받아 처리한다.
//#define _HG_TEST_DUNGEON_RESTART_					//던전에서 시작
//#define _HG_TEST_SHOW_DAMAGE_VALUE_					//기획요청으로 현재의 데미지를 보고 싶단다.
//#define _HG_TEST_3x3_MONSTER_						//3x3몬스터 설정
#define _HG_TEST_TUTORIAL_DUNGEON_START_				//튜터리얼 던전에서 케릭터 생성
//#define _HT_TEST_BATTLE_START_ALL_OBJECT_				//battle이 start를 되기전엔 object 목록을 보내지 않는다.
//#define _HG_TEST_PARTY_DUNGEON_							//파티원 같은 던전 입장처리
//#define _HG_TEST_HEAL_STEEL_EXP_						//heal , steel 시 exp 획득

//typedef UINT16			RESULT_T;
//typedef UINT32			HOSTID;
//typedef UINT8			REMOTE_ENTRY_T;	
//typedef UINT32			GROUPID;
//typedef UINT32			ADDR_IP;
//typedef UINT16			ADDR_PORT;
//typedef UINT64			TIME_T;//서버시간
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
//typedef UINT8			BOARDINDEX;		//battle field seat id --꼭, 타입이 변경되면 BOARDINDEX_DB 타입도 signed형으로 꼭 변환해라.
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
//typedef UINT16			TURN_T;			//battle 턴 no
//typedef UINT8			BATTLE_STATUS_T;
//typedef UINT8			MOTION_T;		//motion id
//typedef UINT8			ATTACK_RESULT_T;
//typedef float			ORDER_T;		//battle 공격 우선순위
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
//typedef INT16			STATEPOINT;		//케릭터 능력치
//typedef INT16			SKILLPOINT;		//케릭터 스킬

