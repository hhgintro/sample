#pragma once



//GAME 서버 접속 승인 요청
//	account : 계정명
//	masterkey : master서버 접속 인증키 ( balance서버를 통해 받았다.)
struct stX2G_AC_CERTIFY_REQ
{
	stX2G_AC_CERTIFY_REQ()
	{
		memset(temp, 0, sizeof(temp));
		memset(test, 0, sizeof(test));
	}

	std::string account;
	std::string masterkey;
	char temp[100];
	char test[50];
};


//GAME 서버 접속 승인 요청에 대한 응답
//	result : 응답 결과값
//	servertime : 서버의 현재시간
struct stX2G_AC_CERTIFY_ACK
{
	stX2G_AC_CERTIFY_ACK()
		: result(0), servertime(0)
	{
	}

	RESULT_T result;
	TIME_T servertime;
};


//케릭터 list 요청
struct stX2G_CH_LOAD_ALL_CHAR_REQ
{
	stX2G_CH_LOAD_ALL_CHAR_REQ()
	{
	}

};


//케릭터 list 요청에 대한 응답
//	result : 응답 결과값
//	_stCharData : 케릭터 정보를 담은 구조체
//	_stItemData : 캐릭터 item 정보
// _stSkillData : 케릭터 skill 정보
struct stX2G_CH_LOAD_ALL_CHAR_ACK
{
	stX2G_CH_LOAD_ALL_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stCharData> chardata;
};


//케릭터 list 요청(사용안함)
//[encrypt] CH_LOAD_CHAR_REQ()
//케릭터 list 요청에 대한 응답
//	_stCharData : 케릭터 정보를 담은 구조체
// _stSkillData : 케릭터 skill 정보
struct stX2G_CH_LOAD_CHAR_ACK
{
	stX2G_CH_LOAD_CHAR_ACK()
	{
	}

	std::vector<_stCharData> chardata;
	std::vector<_stSkillData> skilldata;
};


//케릭터 생성 요청
//	_stCreateCharInfo : 생성할 캐릭터 정보
struct stX2G_CH_CREATE_CHAR_REQ
{
	stX2G_CH_CREATE_CHAR_REQ()
	{
	}

	std::vector<_stCreateCharInfo> charinfo;
};


//케릭터 생성 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_CH_CREATE_CHAR_ACK
{
	stX2G_CH_CREATE_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//케릭터 삭제 요청
//	objectindex : 삭제할 캐릭터 index
struct stX2G_CH_DELETE_CHAR_REQ
{
	stX2G_CH_DELETE_CHAR_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//케릭터 삭제 요청에 대한 응답
//	result : 응답 결과값
//	objectindex : 삭제할 캐릭터 index
struct stX2G_CH_DELETE_CHAR_ACK
{
	stX2G_CH_DELETE_CHAR_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
};


//soldier list 요청
// objectindex : soldier 를 소유한 케릭터 정보
struct stX2G_CH_LOAD_ALL_SOLDIER_REQ
{
	stX2G_CH_LOAD_ALL_SOLDIER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//soldier list 요청에 대한 응답
//	result : 응답 결과값
//	_stHiredSoldierData : soldier 정보를 담은 구조체
//	_stItemData : soldier item 정보
// _stSkillData : soldier skill 정보
struct stX2G_CH_LOAD_ALL_SOLDIER_ACK
{
	stX2G_CH_LOAD_ALL_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stHiredSoldierData> soldierdata;
};


//soldier list 요청(사용안함)
//[encrypt] CH_LOAD_CHAR_REQ()
//케릭터 list 요청에 대한 응답
//	_stHiredSoldierData : soldier 정보를 담은 구조체
struct stX2G_CH_LOAD_SOLDIER_ACK
{
	stX2G_CH_LOAD_SOLDIER_ACK()
	{
	}

	std::vector<_stHiredSoldierData> soldierdata;
};


//soldier 생성 요청(사용안함)
//	_stCreateSoldierInfo : 생성할 soldier 정보
//[encrypt] CH_CREATE_SOLDIER_REQ(std::vector<_stCreateSoldierInfo> soldierinfo)
//soldier 생성 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_CH_CREATE_SOLDIER_ACK
{
	stX2G_CH_CREATE_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//soldier 삭제 요청
//	objectindex : 삭제할 soldier index
struct stX2G_CH_DELETE_SOLDIER_REQ
{
	stX2G_CH_DELETE_SOLDIER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//soldier 삭제 요청에 대한 응답
//	result : 응답 결과값
//	objectindex : 삭제할 soldier index
struct stX2G_CH_DELETE_SOLDIER_ACK
{
	stX2G_CH_DELETE_SOLDIER_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
};


//soldier 월급 지급 통보
//	money : 지급후 money
struct stX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF
{
	stX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//케릭터 nick 중복 체크 요청
//	nickname :
struct stX2G_CH_CHECK_NICK_DUPLICATE_REQ
{
	stX2G_CH_CHECK_NICK_DUPLICATE_REQ()
	{
	}

	tstring nickname;
};


//케릭터 nick 중복 체크 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_CH_CHECK_NICK_DUPLICATE_ACK
{
	stX2G_CH_CHECK_NICK_DUPLICATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//케릭터 획득 경험치 통보(자신에게만)
//	_stObjectExp : 캐릭터 획득 경험치 정보 구조체
struct stX2G_CH_OBJECT_EXP_ACK
{
	stX2G_CH_OBJECT_EXP_ACK()
	{
	}

	std::vector<_stObjectExp> objectexp;
};


//케릭터 level up 통보(자신에게만)
//	_stLevelupObject : 캐릭터 level up 정보 구조체
struct stX2G_CH_LEVEL_UP_ACK
{
	stX2G_CH_LEVEL_UP_ACK()
	{
	}

	std::vector<_stLevelupObject> levelupobject;
};


//케릭터 level up 통보(주변에만)
//	_stLevelupObjectNtf : 캐릭터 level up 정보 구조체
struct stX2G_CH_LEVEL_UP_NTF
{
	stX2G_CH_LEVEL_UP_NTF()
	{
	}

	std::vector<_stLevelupObjectNtf> levelupobject;
};


//케릭터 현재 소지금 통보
//	money : 캐릭터 소지금
struct stX2G_CH_MONEY_NTF
{
	stX2G_CH_MONEY_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//object의 무적 상태 설정 통보
//	objectindex : 무적 상태 설정 개체 index
struct stX2G_CH_SETUP_NO_RIVAL_NTF
{
	stX2G_CH_SETUP_NO_RIVAL_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//object의 무적 상태 해제 통보
//	objectindex : 무적 상태 해제 개체 index
struct stX2G_CH_RELEASE_NO_RIVAL_NTF
{
	stX2G_CH_RELEASE_NO_RIVAL_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//object의 능력치 변경 통보
// objectindex : 능력치 변경된 개체
//	_stStateAbility : state
//	_stBasicAbility : basic
//	_stBattleAbility : battle
struct stX2G_CH_RESET_ABILITY_NTF
{
	stX2G_CH_RESET_ABILITY_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stStateAbility> state;
	std::vector<_stBasicAbility> basic;
	std::vector<_stBattleAbility> battle;
};


//튜터리얼 진행 요청
//	tutorial : 튜터리얼 진행여부(0:진행중, 1:포기, 2:완료)
struct stX2G_CH_COMPLETED_TUTORIAL_REQ
{
	stX2G_CH_COMPLETED_TUTORIAL_REQ()
		: tutorial(0)
	{
	}

	TUTORIAL_TYPE_T tutorial;
};


//튜터리얼 진행 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_CH_COMPLETED_TUTORIAL_ACK
{
	stX2G_CH_COMPLETED_TUTORIAL_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//게임 옵션 수정 요청
//	gameoption : //게임내 옵션(CHAR_GAME_OPTION : 거래거절,파티거절)
struct stX2G_CH_CHAR_GAME_OPTION_REQ
{
	stX2G_CH_CHAR_GAME_OPTION_REQ()
		: gameoption(0)
	{
	}

	CHAR_GAME_OPTION_T gameoption;
};


//Battle Formation 수정 요청
//	battletype : 일반전투, 파티전투
//	_stObjectBattleo : 전투시의 용병의 대형(char를 기준(0)으로 용병의 위치를 상대적으로 설정한다.) -- char 위치는 포함하지 않음
//	bestfriendsoldierindex : best friend 용병
//	_stBattleToggleSoldier : toggle 용병
struct stX2G_CH_BATTLE_FORMATION_REQ
{
	stX2G_CH_BATTLE_FORMATION_REQ()
		: battletype(0), bestfriendsoldierindex(0)
	{
	}

	BATTLE_TYPE_T battletype;
	std::vector<_stObjectBattleFormation> objectformation;
	GAMEOBJECTID bestfriendsoldierindex;
	std::vector<_stBattleToggleSoldier> toggle;
};


//Battle Formation 수정 요청에 대한 응답
//	_stBattleFormation : 전투시의 용병의 대형(char를 기준(0)으로 용병의 위치를 상대적으로 설정한다.) -- char 위치는 포함하지 않음
//	bestfriendsoldierindex : best friend 용병
struct stX2G_CH_BATTLE_FORMATION_ACK
{
	stX2G_CH_BATTLE_FORMATION_ACK()
		: bestfriendsoldierindex(0)
	{
	}

	std::vector<_stBattleFormation> formation;
	GAMEOBJECTID bestfriendsoldierindex;
};


//world에 진입 요청(캐릭터 선택해서 처음 world 진입할 때)
//	zonecode : 입장하고자 하는 zone code --사용되지 않는다. 추후 삭제할 것
//	objectindex : 입장할 캐릭터 index
struct stX2G_WD_WORLD_ENTER_REQ
{
	stX2G_WD_WORLD_ENTER_REQ()
		: zonecode(0), objectindex(0)
	{
	}

	ZONECODE zonecode;
	GAMEOBJECTID objectindex;
};


//portal 사용 요청
//	objectindex : 사용할 portal index
struct stX2G_WD_USE_PORTAL_REQ
{
	stX2G_WD_USE_PORTAL_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//world에 진입 요청에 대한 응답(자신에게 통보한다.)
//	result : 응답 결과값
//	_stEnterObjectData : zone 입장한 개체의 정보
struct stX2G_WD_WORLD_ENTER_ACK
{
	stX2G_WD_WORLD_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stEnterObjectData> enterdata;
};


//npc 대화중 Quest에 의해 world 이동 요청
//	_stWorldChangeForQuest : 맵이동 실패한 Quest 정보
struct stX2G_WD_WORLD_CHANGE_FOR_QUEST_REQ
{
	stX2G_WD_WORLD_CHANGE_FOR_QUEST_REQ()
	{
	}

	std::vector<_stWorldChangeForQuest> questinfo;
};


//world에 진입 요청에 대한 응답(자신에게 통보한다.)
//	result : 응답 결과값
struct stX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK
{
	stX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//world에 진입한 유저의 정보 통보(타인에게만 전송)
//	_stZoneCharData : 케릭터 정보를 담은 구조체
//	_stZoneHiredSoldierData : 용병 정보를 담은 구조체
//	_stMonsterData : 몬스터 정보를 담은 구조체
//	_stTownNpcData : town NPC 정보를 담은 구조체
//	_stPortalData : portal 정보를 담은 구조체
struct stX2G_WD_ENTER_OBJECT_NTF
{
	stX2G_WD_ENTER_OBJECT_NTF()
	{
	}

	std::vector<_stZoneCharData> zonechardata;
	std::vector<_stZoneHiredSoldierData> zonehiredsoldierdata;
	std::vector<_stMonsterData> monsterdata;
	std::vector<_stTownNpcData> townnpcdata;
	std::vector<_stPortalData> portaldata;
};


//world에 존재하는 개체의 정보 통보(입장한 케릭터에게 전송)
//	_stZoneCharData : 케릭터 정보를 담은 구조체
//	_stZoneHiredSoldierData : 용병 정보를 담은 구조체
//	_stMonsterData : 몬스터 정보를 담은 구조체
//	_stTownNpcData : town NPC 정보를 담은 구조체
//	_stPortalData : portal 정보를 담은 구조체
struct stX2G_WD_ALL_OBJECT_NTF
{
	stX2G_WD_ALL_OBJECT_NTF()
	{
	}

	std::vector<_stZoneCharData> zonechardata;
	std::vector<_stZoneHiredSoldierData> zonehiredsoldierdata;
	std::vector<_stMonsterData> monsterdata;
	std::vector<_stTownNpcData> townnpcdata;
	std::vector<_stPortalData> portaldata;
};


//world에 퇴장 요청
struct stX2G_WD_WORLD_LEAVE_REQ
{
	stX2G_WD_WORLD_LEAVE_REQ()
	{
	}

};


//world에서 퇴장한 object(유저/npc)의 정보 통보(타인에게 전송)
//	_stLeaveObjectData : 퇴장할 캐릭터 index
struct stX2G_WD_LEAVE_OBJECT_NTF
{
	stX2G_WD_LEAVE_OBJECT_NTF()
	{
	}

	std::vector<_stLeaveObjectData> leaveobject;
};


//world에 이동 요청
//	x, y, z : 이동할 위치(구조체는 vector로 전달한다.)
struct stX2G_WD_MOVE_REQ
{
	stX2G_WD_MOVE_REQ()
		: x(0), y(0), z(0)
	{
	}

	float x;
	float y;
	float z;
};


//world에 이동 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_WD_MOVE_ACK
{
	stX2G_WD_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//world에 이동한 object의 정보 통보
//	_stMoveObjectData : zone 이동 개체 정보
//	servertime : 서버의 현재시간
struct stX2G_WD_MOVE_NTF
{
	stX2G_WD_MOVE_NTF()
		: servertime(0)
	{
	}

	std::vector<_stMoveObjectData> moveobject;
	TIME_T servertime;
};


//world에 멈춤 요청
//	x, y, z : 멈춘 위치(구조체는 vector로 전달한다.)
struct stX2G_WD_STOP_REQ
{
	stX2G_WD_STOP_REQ()
		: x(0), y(0), z(0)
	{
	}

	float x;
	float y;
	float z;
};


//world에 멈춘 object의 정보 통보
//	_stStopObjectData : zone 멈춘 개체 정보
struct stX2G_WD_STOP_NTF
{
	stX2G_WD_STOP_NTF()
	{
	}

	std::vector<_stStopObjectData> stopobject;
};


//케릭터 motion 요청
//	motion : 캐릭터 motion
struct stX2G_WD_MOTION_REQ
{
	stX2G_WD_MOTION_REQ()
		: motion(0)
	{
	}

	MOTION_T motion;
};


//케릭터 motion 요청청에 대한 응답
//	result : 응답 결과값
struct stX2G_WD_MOTION_ACK
{
	stX2G_WD_MOTION_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//케릭터 motion 통보
//	_stObjectMotion : 캐릭터 motion 정보 구조체
struct stX2G_WD_MOTION_NTF
{
	stX2G_WD_MOTION_NTF()
	{
	}

	std::vector<_stObjectMotion> motion;
};


//zone puzzle 정보 갱신 요청
//	puzzle : 변경된 zone puzzle정보
struct stX2G_WD_WORLD_PUZZLE_REQ
{
	stX2G_WD_WORLD_PUZZLE_REQ()
	{
	}

	ZONEPUZZLE puzzle;
};


//zone puzzle 정보 갱신 통보
//	puzzle : 변경된 zone puzzle정보
struct stX2G_WD_WORLD_PUZZLE_NTF
{
	stX2G_WD_WORLD_PUZZLE_NTF()
	{
	}

	ZONEPUZZLE puzzle;
};


//월드맵 open 요청
//	worldmap : open된 맵 정보
struct stX2G_WD_WORLD_MAP_OPEN_REQ
{
	stX2G_WD_WORLD_MAP_OPEN_REQ()
		: worldmap(0)
	{
	}

	WORLD_MAP_T worldmap;
};


//월드맵 open 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_WD_WORLD_MAP_OPEN_ACK
{
	stX2G_WD_WORLD_MAP_OPEN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//체팅(전체 체팅)
//	type : 체팅 종류(normal, notice)
//	chatmsg : 체팅 메시지
struct stX2G_BD_CHAT_REQ
{
	stX2G_BD_CHAT_REQ()
		: type(0)
	{
	}

	CHAT_TYPE_T type;
	tstring chatmsg;
};


//체팅 귓말 요청(귓말 처럼 받는 대상을 지정할때 사용된다)
//	toid : 받는 사람 GAMEOBJECTID
//	tonick : 받는 사람 nick(보통은 설정안하는데, 귓말시 toid를 모를경우 설정한다)
//	type : 체팅 종류
//	chatmsg: 체팅메시지
struct stX2G_BD_TARGET_CHAT_REQ
{
	stX2G_BD_TARGET_CHAT_REQ()
		: toid(0), type(0)
	{
	}

	UINT32 toid;
	tstring tonick;
	CHAT_TYPE_T type;
	tstring chatmsg;
};


//chat 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BD_CHAT_ACK
{
	stX2G_BD_CHAT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//chat 주변 통보
//	_stChattingData : 체팅 구조체 정보
struct stX2G_BD_CHAT_NTF
{
	stX2G_BD_CHAT_NTF()
	{
	}

	std::vector<_stChattingData> chatdata;
};


//공지 메시지 통보
//	_stNoticeChattingData : 공지 정보
struct stX2G_BD_NOTICE_CHAT_NTF
{
	stX2G_BD_NOTICE_CHAT_NTF()
	{
	}

	std::vector<_stNoticeChattingData> noticedata;
};


//개체의 hp/mp 변경됨
//	_stRegenObjectData : regen 개체 정보
struct stX2G_OB_REGEN_NTF
{
	stX2G_OB_REGEN_NTF()
	{
	}

	std::vector<_stRegenObjectData> regenobject;
};


//개체의 사망
//	objectindex : 사망한 캐릭터 index
struct stX2G_OB_DEATH_NTF
{
	stX2G_OB_DEATH_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//개체의 부활
//	_stRevivalObjectData : revival 개체 정보
struct stX2G_OB_REVIVAL_NTF
{
	stX2G_OB_REVIVAL_NTF()
	{
	}

	std::vector<_stRevivalObjectData> revivalobject;
};


//케릭터 skill 정보
//	objectindex : object index(용병일 수 있기에 index를 받는다.)
//	_stSkillData : 케릭터 skill 정보
struct stX2G_SK_LOAD_CHAR_SKILL_ACK
{
	stX2G_SK_LOAD_CHAR_SKILL_ACK()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stSkillData> skilldata;
};


//learn skill 요청
//	objectindex : object index(용병일 수 있기에 index를 받는다.)
//	skillcode : skill table id
struct stX2G_SK_SKILL_LEARN_REQ
{
	stX2G_SK_SKILL_LEARN_REQ()
		: objectindex(0), skillcode(0)
	{
	}

	GAMEOBJECTID objectindex;
	SKILLCODE skillcode;
};


//learn skill 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_SK_SKILL_LEARN_ACK
{
	stX2G_SK_SKILL_LEARN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//learn skill 통보
//	_stLearnSkill : 취득 스킬 정보
struct stX2G_SK_SKILL_LEARN_NTF
{
	stX2G_SK_SKILL_LEARN_NTF()
	{
	}

	std::vector<_stLearnSkill> learnskill;
};


//level up skill 요청
//	objectindex : object index(용병일 수 있기에 index를 받는다.)
//	skillcode : skill table id
struct stX2G_SK_SKILL_LEVELUP_REQ
{
	stX2G_SK_SKILL_LEVELUP_REQ()
		: objectindex(0), skillcode(0)
	{
	}

	GAMEOBJECTID objectindex;
	SKILLCODE skillcode;
};


//level up skill 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_SK_SKILL_LEVELUP_ACK
{
	stX2G_SK_SKILL_LEVELUP_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//level up skill 통보
//	_stLevelupSkill : level up 스킬 정보
struct stX2G_SK_SKILL_LEVELUP_NTF
{
	stX2G_SK_SKILL_LEVELUP_NTF()
	{
	}

	std::vector<_stLevelupSkill> levelupskill;
};


//케릭터 skill quick slot 정보 변경 요청
struct stX2G_SK_SKILL_QUICK_SLOT_REQ
{
	stX2G_SK_SKILL_QUICK_SLOT_REQ()
	{
	}

	std::vector<_stSkillQuickSlot> quickslot;
};


//케릭터 skill quick slot 정보
//	_stSkillQuickSlot : skill quick slot 정보
struct stX2G_SK_SKILL_QUICK_SLOT_ACK
{
	stX2G_SK_SKILL_QUICK_SLOT_ACK()
	{
	}

	std::vector<_stSkillQuickSlot> quickslot;
};


//attack 요청
//	objectindex : 공격할 캐릭터 index(용병일 수 있기에 index를 받는다.)
//	targetboard : battle field의 target seat id (설 위치)
//	skillcode : skill table id
struct stX2G_SK_ATTACK_REQ
{
	stX2G_SK_ATTACK_REQ()
		: objectindex(0), targetboard(0), skillcode(0)
	{
	}

	GAMEOBJECTID objectindex;
	BOARDINDEX targetboard;
	SKILLCODE skillcode;
};


//attack 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_SK_ATTACK_ACK
{
	stX2G_SK_ATTACK_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//attack 통보
//	_stAttackObjectData : 공격하는 개체 정보
//	_stTargetObjectData : 공격받는 개체 정보
//	servertime : 서버의 현재시간
struct stX2G_SK_ATTACK_NTF
{
	stX2G_SK_ATTACK_NTF()
		: servertime(0)
	{
	}

	std::vector<_stAttackObjectData> attackobject;
	std::vector<_stTargetObjectData> targetobject;
	TIME_T servertime;
};


//버프 생성 통보
//	_stBuffDebuff : 추가된 버프 정보
struct stX2G_SK_INSERT_BUFF_NTF
{
	stX2G_SK_INSERT_BUFF_NTF()
	{
	}

	std::vector<_stBuffDebuff> buffdata;
};


//버프 소멸 통보
//	_stBuffDebuff : 소멸된 버프 정보
struct stX2G_SK_DELETE_BUFF_NTF
{
	stX2G_SK_DELETE_BUFF_NTF()
	{
	}

	std::vector<_stBuffDebuff> buffdata;
};


//개체의 hp/mp 변경됨
//	_stAttackObjectData : 공격하는 개체 정보
//	_stRegenObjectData : regen 개체 정보
struct stX2G_SK_HEAL_NTF
{
	stX2G_SK_HEAL_NTF()
		: servertime(0)
	{
	}

	std::vector<_stAttackObjectData> attackobject;
	std::vector<_stRegenObjectData> regenobject;
	TIME_T servertime;
};


//몬스터와 battle 요청(성공시 BF_BATTLE_STATUS_NTF 을 받는다.)
//	objectindex : 전투 대상 몬스터 object index
//	formation : 전투 상황(정공,기습)
struct stX2G_BF_BATTLE_OPEN_REQ
{
	stX2G_BF_BATTLE_OPEN_REQ()
		: objectindex(0), formation(0)
	{
	}

	GAMEOBJECTID objectindex;
	BATTLE_FORMATION_T formation;
};


//몬스터와 battle 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_OPEN_ACK
{
	stX2G_BF_BATTLE_OPEN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//캐릭터 battle 난입 요청(성공시 BF_BATTLE_STATUS_NTF 을 받는다.)
//	objectindex : 전투중인 대상 몬스터 object index
struct stX2G_BF_BATTLE_INTRUDE_CHAR_REQ
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//캐릭터 battle 난입 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_INTRUDE_CHAR_ACK
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle 에 참여하는 인원정보 통보
//	chardata : battle char 정보
//	monsterdata : battle monster 정보
struct stX2G_BF_BATTLE_INTRUDE_CHAR_NTF
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_NTF()
	{
	}

	std::vector<_stOpenBattleObjectData> chardata;
	std::vector<_stOpenBattleObjectData> monsterdata;
};


//Monster battle 난입 요청(성공시 BF_BATTLE_STATUS_NTF 을 받는다.)
//	objectindex : 난입 몬스터 object index(전투중인 char가 주변 monster를 끌어들인다.)
struct stX2G_BF_BATTLE_INTRUDE_MONSTER_REQ
{
	stX2G_BF_BATTLE_INTRUDE_MONSTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Monster battle 난입 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_INTRUDE_MONSTER_ACK
{
	stX2G_BF_BATTLE_INTRUDE_MONSTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle 에 참여하는 인원정보 통보
//	chardata : battle char 정보
//	monsterdata : battle monster 정보
struct stX2G_BF_BATTLE_OBJECT_NTF
{
	stX2G_BF_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stOpenBattleObjectData> chardata;
	std::vector<_stOpenBattleObjectData> monsterdata;
};


//battle field 에 진입 요청
//	board : battle field seat id (설 위치)
//[encrypt] BF_BATTLE_ENTER_REQ(BOARDINDEX board)
//battle field 에 진입 요청에 대한 응답
//	result : 응답 결과값
//	_stEnterBattleObjectData : battle 입장한 개체의 정보
struct stX2G_BF_BATTLE_ENTER_ACK
{
	stX2G_BF_BATTLE_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stEnterBattleObjectData> enterdata;
};


//battle field 에 진입한 유저의 정보 통보(타인/자신에게 전송)
//	_stBattleChar : 케릭터의 전투 정보를 담은 구조체( _stCharData 와 구분됨 )
//	_stBattleHiredSoldier : 용병 정보를 담은 구조체( __stHiredSoldierData와 구분됨)
//	_stBattleMonster : 몬스터의 전투 정보를 담은 구조체
//	servertime : 서버의 현재시간
struct stX2G_BF_ENTER_BATTLE_OBJECT_NTF
{
	stX2G_BF_ENTER_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stBattleChar> battlechar;
	std::vector<_stBattleHiredSoldier> battlehiredsoldier;
	std::vector<_stBattleMonster> battlemonster;
};


//battle field 에 존재하는 개체의 정보 통보(타인에게 전송)
//	_stBattleChar : 케릭터의 전투 정보를 담은 구조체( _stCharData 와 구분됨 )
//	_stBattleHiredSoldier : 용병 정보를 담은 구조체( __stHiredSoldierData와 구분됨)
//	_stBattleMonster : 몬스터 정보를 담은 구조체
//	servertime : 서버의 현재시간
struct stX2G_BF_ALL_BATTLE_OBJECT_NTF
{
	stX2G_BF_ALL_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stBattleChar> battlechar;
	std::vector<_stBattleHiredSoldier> battlehiredsoldier;
	std::vector<_stBattleMonster> battlemonster;
};


//battle field 에 퇴장 요청
struct stX2G_BF_BATTLE_LEAVE_REQ
{
	stX2G_BF_BATTLE_LEAVE_REQ()
	{
	}

};


//battle field 에 퇴장 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_LEAVE_ACK
{
	stX2G_BF_BATTLE_LEAVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field 에서 퇴장한 object(유저/npc)의 정보 통보(타인에게 전송)
//	_stLeaveBattleObjectData : battle 퇴장한 object 정보를 담은 구조체
//	servertime : 서버의 현재시간
struct stX2G_BF_LEAVE_BATTLE_OBJECT_NTF
{
	stX2G_BF_LEAVE_BATTLE_OBJECT_NTF()
		: servertime(0)
	{
	}

	std::vector<_stLeaveBattleObjectData> leaveobject;
	TIME_T servertime;
};


//battle field 에 이동 요청
//	objectindex : 움직일 캐릭터 index(용병일 수 있기에 index를 받는다.)
//	board : 이동할 battle 위치 index
struct stX2G_BF_BATTLE_MOVE_REQ
{
	stX2G_BF_BATTLE_MOVE_REQ()
		: objectindex(0), board(0)
	{
	}

	GAMEOBJECTID objectindex;
	BOARDINDEX board;
};


//battle field 에 이동 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_MOVE_ACK
{
	stX2G_BF_BATTLE_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field 에 이동한 object의 정보 통보
//	_stMoveBattleObjectData : battle field 이동 개체 정보
//	servertime : 서버의 현재시간
struct stX2G_BF_BATTLE_MOVE_NTF
{
	stX2G_BF_BATTLE_MOVE_NTF()
		: servertime(0)
	{
	}

	std::vector<_stMoveBattleObjectData> moveobject;
	TIME_T servertime;
};


//battle field 에 멈춘 object의 정보 통보
//	_stStopObjectData : zone 멈춘 개체 정보
struct stX2G_BF_BATTLE_STOP_NTF
{
	stX2G_BF_BATTLE_STOP_NTF()
	{
	}

	std::vector<_stStopObjectData> stopobject;
};


//battle status 변경 요청
struct stX2G_BF_BATTLE_NEXT_STATUS_REQ
{
	stX2G_BF_BATTLE_NEXT_STATUS_REQ()
	{
	}

};


//battle status 변경 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_NEXT_STATUS_ACK
{
	stX2G_BF_BATTLE_NEXT_STATUS_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field 에 status 정보 통보
//	status : 현재의 battle field 상태
//	servertime : 서버의 현재시간
struct stX2G_BF_BATTLE_STATUS_NTF
{
	stX2G_BF_BATTLE_STATUS_NTF()
		: status(0), servertime(0)
	{
	}

	BATTLE_STATUS_T status;
	TIME_T servertime;
};


//battle field 에 waiting list(대기자명단) 통보
//	currentturn : 현재 turn 번호(TURN_T) -- 보내야 할지 고민좀 해 보자.
//	servertime : 서버의 현재시간
//	movepower : 현재 turn object의 movepower
//	_stBattleTurnWaitingObject : battle 공격 대기자 목록
//	_stBattleTurnBonusCard : battle bonus card 목록
struct stX2G_BF_BATTLE_TURN_WAITING_NTF
{
	stX2G_BF_BATTLE_TURN_WAITING_NTF()
		: currentturn(0), servertime(0), movepower(0)
	{
	}

	TURN_T currentturn;
	TIME_T servertime;
	float movepower;
	std::vector<_stBattleTurnWaitingObject> objectlist;
	std::vector<_stBattleTurnBonusCard> bonuslist;
};


//사용안함
//battle 이동 경로 요청
//	objectindex : 공격할 캐릭터 index(용병일 수 있기에 index를 받는다.)
//	destboard : 목표 위치
//	skillcode : skill table id
//[encrypt] BF_FIND_PATH_REQ(GAMEOBJECTID objectindex, BOARDINDEX destboard, SKILLCODE skillcode)
//사용안함
//battle 이동 경로 요청에 대한 응답
//	result : 응답 결과값
//	board : 이동 경로
//[encrypt] BF_FIND_PATH_ACK(RESULT_T result, std::vector<_stBoardIndex> board)
//battle PvP 요청
//	objectindex : PvP 상대 캐릭터 index
//	bisparty : 0.개인전, 그외는 pvp party전
struct stX2G_BF_BATTLE_PVP_REQ
{
	stX2G_BF_BATTLE_PVP_REQ()
		: objectindex(0), bisparty(0)
	{
	}

	GAMEOBJECTID objectindex;
	UINT8 bisparty;
};


//battle PvP 요청을 전달한다.(상대에게 통보한다.)
//	_stPvPRequestObjectData : PvP 요청한 개체의 정보
struct stX2G_BF_BATTLE_PVP_ACK
{
	stX2G_BF_BATTLE_PVP_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stPvPRequestObjectData> enterdata;
};


//battle PvP 요청에 대한 응답(요청자-철회가능, 응답자-수락및 거절가능)
//	pvpindex : pvp 정보 index
//	result : 응답 결과값(0 이외의 값은 거절처리됨)
struct stX2G_BF_BATTLE_PVP_RESULT_REQ
{
	stX2G_BF_BATTLE_PVP_RESULT_REQ()
		: pvpindex(0), result(0)
	{
	}

	BATTLEPVPINDEX pvpindex;
	RESULT_T result;
};


//battle PvP 응답을 상대에게 통보
//	result : 응답 결과값
struct stX2G_BF_BATTLE_PVP_RESULT_ACK
{
	stX2G_BF_BATTLE_PVP_RESULT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//monster entertime skip 요청
//	objectindex : skip 개체 정보
struct stX2G_BF_BATTLE_SKIP_ENTER_REQ
{
	stX2G_BF_BATTLE_SKIP_ENTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//monster entertime skip 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_SKIP_ENTER_ACK
{
	stX2G_BF_BATTLE_SKIP_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//monster leavetime skip 요청
//	objectindex : skip 개체 정보
struct stX2G_BF_BATTLE_SKIP_LEAVE_REQ
{
	stX2G_BF_BATTLE_SKIP_LEAVE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//monster leavetime skip 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_SKIP_LEAVE_ACK
{
	stX2G_BF_BATTLE_SKIP_LEAVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//char skill casting skip 요청
//	objectindex : skip 개체 정보
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//char skill casting skip 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//char skill casting skip 통보
//	result : 응답 결과값
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF()
	{
	}

};


//용병 toggle 요청
//	objectindex : 현재 turn object
//	leaveobjectindex : leave object
//	enterobjectindex : enter object
struct stX2G_BF_BATTLE_TOGGLE_SOLDIER_REQ
{
	stX2G_BF_BATTLE_TOGGLE_SOLDIER_REQ()
		: objectindex(0), leaveobjectindex(0), enterobjectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	GAMEOBJECTID leaveobjectindex;
	GAMEOBJECTID enterobjectindex;
};


//용병 toggle 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK
{
	stX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//용병 toggle 요청에 대한 응답
//	_stBattleHiredSoldier : 교체 투입된 개체 정보
struct stX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF
{
	stX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF()
	{
	}

	std::vector<_stBattleHiredSoldier> togglehiredsoldier;
};


//케릭터 inventory 정보 요청(사용안함)
//[encrypt] IT_LOAD_INVENTORY_ITEM_REQ()
//케릭터 inventory 정보
//	objectindex : 개체 정보
//	_stItemData : 보유한 item 정보
struct stX2G_IT_LOAD_INVENTORY_ITEM_ACK
{
	stX2G_IT_LOAD_INVENTORY_ITEM_ACK()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stItemData> itemdata;
};


//케릭터 item quick slot 정보 변경 요청
struct stX2G_IT_QUICK_SLOT_REQ
{
	stX2G_IT_QUICK_SLOT_REQ()
	{
	}

	std::vector<_stItemQuickSlot> quickslot;
};


//케릭터 item quick slot 정보
//	objectindex : 개체 정보
//	_stItemQuickSlot : item quick slot 정보
struct stX2G_IT_QUICK_SLOT_ACK
{
	stX2G_IT_QUICK_SLOT_ACK()
	{
	}

	std::vector<_stItemQuickSlot> quickslot;
};


//아이템 구매 요청
//	_stBuyItem : 구매 정보
struct stX2G_IT_BUY_ITEM_REQ
{
	stX2G_IT_BUY_ITEM_REQ()
	{
	}

	std::vector<_stBuyItem> buyitem;
};


//아이템 구매 요청에 대한 응답
//	result : 응답 결과값
//	objectindex : 개체 정보
//	money : 구매후 소지한 money
//	_stItemData : 구매한 item 정보
struct stX2G_IT_BUY_ITEM_ACK
{
	stX2G_IT_BUY_ITEM_ACK()
		: result(0), objectindex(0), money(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
	INT32 money;
	std::vector<_stItemData> itemdata;
};


//아이템 판매 요청
//	objectindex : 개체 정보
//	itemindex : 판매 아이템 index
struct stX2G_IT_SELL_ITEM_REQ
{
	stX2G_IT_SELL_ITEM_REQ()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//아이템 판매 요청에 대한 응답
//	result : 응답 결과값
//	_stSellItem : 판매정보
struct stX2G_IT_SELL_ITEM_ACK
{
	stX2G_IT_SELL_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stSellItem> sellitem;
};


//사냥한 monster로 부터 아이템 줍기(사용안함)
//	objectindex : 사망 몬스터 object index
//	_stPickupItem : 획득 item 정보(item code)
//[encrypt] IT_PICKUP_ITEM_REQ(GAMEOBJECTID objectindex, std::vector<_stPickupItem> pickupitem)
//사냥한 monster로 부터 아이템 줍기에 대한 응답
//	result : 응답 결과값
//	objectindex : 아이템  object index
//	_stItemData : 획득 item 정보(item 상세 정보)
struct stX2G_IT_PICKUP_ITEM_ACK
{
	stX2G_IT_PICKUP_ITEM_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
	std::vector<_stItemData> itemdata;
};


//사냥한 monster로 부터 아이템 지급 통보
//	objectindex : 아이템 지급 대상자 object index
//	_stPickupItem : 획득 item 정보
//	_stPickupObject : 지급 경쟁자들 정보
struct stX2G_IT_PICKUP_ITEM_NTF
{
	stX2G_IT_PICKUP_ITEM_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stPickupItem> pickupitem;
	std::vector<_stPickupObject> pickupobject;
};


//아이템 파괴(버리기) 요청
//	objectindex : 개체 정보
//	itemindex : 파괴 아이템 index
struct stX2G_IT_DESTROY_ITEM_REQ
{
	stX2G_IT_DESTROY_ITEM_REQ()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//아이템 파괴(버리기) 요청에 대한 응답
//	result : 응답 결과값
//	_stDestroyItem : 파괴정보
struct stX2G_IT_DESTROY_ITEM_ACK
{
	stX2G_IT_DESTROY_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stDestroyItem> destroyitem;
};


//아이템 inventory 위치 변경 요청
//	objectindex : 개체 정보
//	_stInventorySlot : 변경된 item 정보
struct stX2G_IT_INVENTORY_CHANGE_REQ
{
	stX2G_IT_INVENTORY_CHANGE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stInventorySlot> inventorydata;
};


//아이템 inventory 위치 변경 요청에 대한 응답
//	result : 응답 결과값
//	objectindex : 개체 정보
//	_stInventorySlot : 변경된 item 정보
struct stX2G_IT_INVENTORY_CHANGE_ACK
{
	stX2G_IT_INVENTORY_CHANGE_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
	std::vector<_stInventorySlot> inventorydata;
};


//아이템 Equip 위치 변경 요청
//	objectindex : 개체 정보
//	_stEquipPart : 변경된 item 정보
struct stX2G_IT_EQUIP_CHANGE_REQ
{
	stX2G_IT_EQUIP_CHANGE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stEquipPart> equipdata;
};


//아이템 Equip 위치 변경 요청에 대한 응답(자신에게 통보)
//	result : 응답 결과값
//	objectindex : equip 변경 object index
//	_stEquipPart : 변경된 item 정보
struct stX2G_IT_EQUIP_CHANGE_ACK
{
	stX2G_IT_EQUIP_CHANGE_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
	std::vector<_stEquipPart> equipdata;
};


//아이템 장착 주변 통보(자신은 제외)
//	objectindex : equip 변경 object index
//	_stObjectItemData(equipitem) : 장착 item 정보
//	_stObjectItemData(unequipitem) : 탈착 item 정보
struct stX2G_IT_EQUIP_CHANGE_NTF
{
	stX2G_IT_EQUIP_CHANGE_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stObjectItemData> equipitem;
	std::vector<_stObjectItemData> unequipitem;
};


//아이템 다른 개체에게 선물 요청
//	_stGiftInventorySlot : 변경된 item 정보
struct stX2G_IT_GIFT_REQ
{
	stX2G_IT_GIFT_REQ()
	{
	}

	std::vector<_stGiftInventorySlot> giftdata;
};


//아이템 다른 개체에게 선물 요청에 대한 응답
//	result : 응답 결과값
//	_stGiftInventorySlot : 변경된 item 정보
struct stX2G_IT_GIFT_ACK
{
	stX2G_IT_GIFT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stGiftInventorySlot> giftdata;
};


//아이템 다른 개체에게 장착(탈착) 요청
//	fromid : 주는 개체 정보
//	toid : 받는 개체 정보
//	_stEquipPart : 변경된 item 정보(받는 개체)
struct stX2G_IT_GIFT_EQUIP_CHANGE_REQ
{
	stX2G_IT_GIFT_EQUIP_CHANGE_REQ()
		: fromid(0), toid(0)
	{
	}

	GAMEOBJECTID fromid;
	GAMEOBJECTID toid;
	std::vector<_stEquipPart> equipdata;
};


//아이템 다른 개체에게 장착(탈착) 요청에 대한 응답(자신에게 통보)
//	result : 응답 결과값
//	fromid : 주는 개체 정보
//	toid : 받는 개체 정보
//	_stEquipPart : 변경된 item 정보
struct stX2G_IT_GIFT_EQUIP_CHANGE_ACK
{
	stX2G_IT_GIFT_EQUIP_CHANGE_ACK()
		: result(0), fromid(0), toid(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID fromid;
	GAMEOBJECTID toid;
	std::vector<_stEquipPart> equipdata;
};


//아이템 다른 개체에게 장착(탈착) 주변 통보(자신은 제외)
//	_stZoneObjectItemData(equipitem) : 장착 item 정보
//	_stZoneObjectItemData(unequipitem) : 탈착 item 정보
struct stX2G_IT_GIFT_EQUIP_CHANGE_NTF
{
	stX2G_IT_GIFT_EQUIP_CHANGE_NTF()
	{
	}

	std::vector<_stZoneObjectItemData> equipitem;
	std::vector<_stZoneObjectItemData> unequipitem;
};


//보물상자의 drop 아이템 목록 요청(사용안함)
//	objectindex : 보물상자의 index
//[encrypt] IT_NPC_DROP_ITEM_REQ(GAMEOBJECTID objectindex)
//사냥한 monster의 drop 아이템 목록요청에 대한 응답(사용안함)
//	result : 응답 결과값
//[encrypt] IT_NPC_DROP_ITEM_ACK(RESULT_T result)
//사냥한 monster의 drop 아이템 / 보물상자 열었을때 아이템 목록(사용안함)
//	objectindex : 사망한 monster index
//	_stPickupItem : Drop item 정보
//[encrypt] IT_NPC_DROP_ITEM_NTF(GAMEOBJECTID objectindex, std::vector<_stPickupItem> pickupitem)
//아이템 사용 요청(field 전용)
//	_stUseItemOnField  : 아이템 사용 정보
struct stX2G_IT_USE_ITEM_REQ
{
	stX2G_IT_USE_ITEM_REQ()
	{
	}

	std::vector<_stUseItemOnField> useiteminfo;
};


//아이템 사용 요청(battle field 전용)
//	_stUseItemOnBattle : 아이템 사용 정보
struct stX2G_IT_USE_ITEM_ON_BATTLE_REQ
{
	stX2G_IT_USE_ITEM_ON_BATTLE_REQ()
	{
	}

	std::vector<_stUseItemOnBattle> useiteminfo;
};


//아이템 사용 요청에 대한 응답
//	result : 응답 결과값
//	_stUseItemChar : 사용된 아이템 정보
struct stX2G_IT_USE_ITEM_ACK
{
	stX2G_IT_USE_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stUseItemChar> useitem;
};


//아이템 사용 통보
//	_stUseItemNtf : 사용 아이템 정보
struct stX2G_IT_USE_ITEM_NTF
{
	stX2G_IT_USE_ITEM_NTF()
	{
	}

	std::vector<_stUseItemNtf> useitem;
};


//갱신된 아이템 정보 통보
//	_stUpdateItemcard : 갱신된 아이템 정보
struct stX2G_IT_UPDATE_ITEM_NTF
{
	stX2G_IT_UPDATE_ITEM_NTF()
	{
	}

	std::vector<_stUpdateItemcard> updateitem;
};


//아이템 분리 요청
//	fromid : 주는 개체 정보
//	toid : 받는 개체 정보
//	sourceitemindex : 분리할 원본 아이템 index
//	itemcount : 분리할 개수
//	slot : 분리될 인벤위치
struct stX2G_IT_SPLITE_ITEM_REQ
{
	stX2G_IT_SPLITE_ITEM_REQ()
		: fromid(0), toid(0), sourceitemindex(0), itemcount(0), slot(0)
	{
	}

	GAMEOBJECTID fromid;
	GAMEOBJECTID toid;
	ITEMINDEX sourceitemindex;
	UINT8 itemcount;
	UINT8 slot;
};


//아이템 분리 요청에 대한 응답
//	result : 응답 결과값
//	fromid : 주는 개체 정보
//	toid : 받는 개체 정보
//	_stItemSplite : 분리후 아이템 정보
//	_stItemData : 생성된 item 정보(item 상세 정보)
struct stX2G_IT_SPLITE_ITEM_ACK
{
	stX2G_IT_SPLITE_ITEM_ACK()
		: result(0), fromid(0), toid(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID fromid;
	GAMEOBJECTID toid;
	std::vector<_stItemSplite> spliteitem;
	std::vector<_stItemData> itemdata;
};


//아이템 결합 요청
//	fromid : 주는 개체 정보
//	toid : 받는 개체 정보
//	sourceitemindex : 주는 개체의 아이템 index
//	itemindex : 받는 개체의 아이템 index
struct stX2G_IT_COMBINE_ITEM_REQ
{
	stX2G_IT_COMBINE_ITEM_REQ()
		: fromid(0), toid(0), sourceitemindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID fromid;
	GAMEOBJECTID toid;
	ITEMINDEX sourceitemindex;
	ITEMINDEX itemindex;
};


//아이템 결합 요청에 대한 응답
//	result : 응답 결과값
//	_stItemCombine : 결합 아이템 정보
struct stX2G_IT_COMBINE_ITEM_ACK
{
	stX2G_IT_COMBINE_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stItemCombine> itemcombine;
};


//Quest 목록 요청
struct stX2G_QT_CHAR_QUEST_LIST_REQ
{
	stX2G_QT_CHAR_QUEST_LIST_REQ()
	{
	}

};


//Quest 목록 요청에 대한 응답
//	TQuest : Quest 정보
//	_stQuestUpdate : Quest 정보
//	_stQuestProgressUpdate : Progress 정보
struct stX2G_QT_CHAR_QUEST_LIST_ACK
{
	stX2G_QT_CHAR_QUEST_LIST_ACK()
	{
	}

	std::vector<_stQuestUpdate> questdata;
	std::vector<_stQuestProgressUpdate> progressdata;
};


//new Quest 등록 요청
//	questcode : 등록할 Quest code
struct stX2G_QT_CHAR_QUEST_INSERT_REQ
{
	stX2G_QT_CHAR_QUEST_INSERT_REQ()
		: questcode(0)
	{
	}

	QUESTCODE questcode;
};


//new Quest 등록 요청에 대한 응답
//	result : 응답 결과값
//	questcode : 생성된 Quest code
struct stX2G_QT_CHAR_QUEST_INSERT_ACK
{
	stX2G_QT_CHAR_QUEST_INSERT_ACK()
		: result(0), questcode(0)
	{
	}

	RESULT_T result;
	QUESTCODE questcode;
};


//town npc와 대화 요청
//	objectindex : 대화중인 npc 정보
struct stX2G_QT_CHAR_HELLO_NPC_REQ
{
	stX2G_QT_CHAR_HELLO_NPC_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//town npc와 대화 요청에 대한 응답(성공시엔 WD_STOP_NTF 을 보낸다.)
//	result : 응답 결과값
struct stX2G_QT_CHAR_HELLO_NPC_ACK
{
	stX2G_QT_CHAR_HELLO_NPC_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//town npc와 대화 종료 요청
//	objectindex : 대화 종료 npc 정보
struct stX2G_QT_CHAR_GOODBYE_NPC_REQ
{
	stX2G_QT_CHAR_GOODBYE_NPC_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Quest npc와 대화 요청(주로 npc와의 대화 or 전달인 경우에 처리된다)
//	_stQuestTalkNpc : Quest npc 정보
struct stX2G_QT_CHAR_QUEST_TALK_NPC_REQ
{
	stX2G_QT_CHAR_QUEST_TALK_NPC_REQ()
	{
	}

	std::vector<_stQuestTalkNpc> questnpc;
};


//Quest npc와 대화 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_QT_CHAR_QUEST_TALK_NPC_ACK
{
	stX2G_QT_CHAR_QUEST_TALK_NPC_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Quest 갱신 요청에 대한 응답
//	_stQuestUpdate : 갱신된 Quest 정보
struct stX2G_QT_CHAR_QUEST_UPDATE_ACK
{
	stX2G_QT_CHAR_QUEST_UPDATE_ACK()
	{
	}

	std::vector<_stQuestUpdate> questdata;
};


//Quest Progress 갱신 요청에 대한 응답
//	_stQuestProgressUpdate : 갱신된 Quest Progress 정보
struct stX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK
{
	stX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK()
	{
	}

	std::vector<_stQuestProgressUpdate> progressdata;
};


//Quest 보상 요청
//	questcode : 보상 받을 Quest
//	order : 보상 받을 아이템 Reward 순번(선택일 경우)
struct stX2G_QT_CHAR_QUEST_REWARD_REQ
{
	stX2G_QT_CHAR_QUEST_REWARD_REQ()
		: questcode(0), order(0)
	{
	}

	QUESTCODE questcode;
	UINT8 order;
};


//Quest 보상 요청에 대한 응답
//	result : 응답 결과값
//	objectindex : 보상 받은 objectindex
//	_stQuestRewardItem : Quest 보상 정보
struct stX2G_QT_CHAR_QUEST_REWARD_ACK
{
	stX2G_QT_CHAR_QUEST_REWARD_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
	std::vector<_stQuestRewardItem> rewarddata;
};


//Quest 삭제 요청
//	questcode : 삭제할 quest code
struct stX2G_QT_CHAR_QUEST_DELETE_REQ
{
	stX2G_QT_CHAR_QUEST_DELETE_REQ()
		: questcode(0)
	{
	}

	QUESTCODE questcode;
};


//Quest 삭제 요청에 대한 응답
//	result : 응답 결과값
//	questcode : 삭제된 Quest code
struct stX2G_QT_CHAR_QUEST_DELETE_ACK
{
	stX2G_QT_CHAR_QUEST_DELETE_ACK()
		: result(0), questcode(0)
	{
	}

	RESULT_T result;
	QUESTCODE questcode;
};


//mail list 요청
struct stX2G_ML_MAIL_LIST_REQ
{
	stX2G_ML_MAIL_LIST_REQ()
	{
	}

};


//mail list 요청에 대한 응답
//	result : 응답 결과값
//	_stMailList : mail 정보
struct stX2G_ML_MAIL_LIST_ACK
{
	stX2G_ML_MAIL_LIST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stMailList> mail;
};


//mail send 요청
//	_stSendMail : 보내는 mail 정보
struct stX2G_ML_SEND_MAIL_REQ
{
	stX2G_ML_SEND_MAIL_REQ()
	{
	}

	std::vector<_stSendMail> sendmail;
};


//mail send 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_ML_SEND_MAIL_ACK
{
	stX2G_ML_SEND_MAIL_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//받은 mail 통보
//	_stMailList : mail 정보
struct stX2G_ML_RECIEVE_MAIL_NTF
{
	stX2G_ML_RECIEVE_MAIL_NTF()
	{
	}

	std::vector<_stMailList> mail;
};


//mail 상태 변경 요청
// _stChangeMailStatus : mail 상태 변경 정보
struct stX2G_ML_CHANGE_MAIL_STATUS_REQ
{
	stX2G_ML_CHANGE_MAIL_STATUS_REQ()
	{
	}

	std::vector<_stChangeMailStatus> changemail;
};


//mail 상태 변경 요청에 대한 응답
//	result : 응답 결과값
//	_stChangeMailStatus : mail 상태 변경 정보
//	_stTakeMailItem : mail에서 회수된 money, 아이템 정보
struct stX2G_ML_CHANGE_MAIL_STATUS_ACK
{
	stX2G_ML_CHANGE_MAIL_STATUS_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stChangeMailStatus> changemail;
	std::vector<_stTakeMailItem> mailitem;
};


//받은 mail 아이템 회수 통보
//	_stChangeMailStatus : mail 정보
//	money : 현재 소지 money
//	_stItemData : 회수된 mail 아이템 정보
struct stX2G_ML_TAKE_MAIL_ITEM_NTF
{
	stX2G_ML_TAKE_MAIL_ITEM_NTF()
		: money(0)
	{
	}

	std::vector<_stChangeMailStatus> maildata;
	INT32 money;
	std::vector<_stItemData> itemdata;
};


//Party 생성 요청
//	objectindex : 파티에 초대할 대상 object index
struct stX2G_PT_CREATE_PARTY_REQ
{
	stX2G_PT_CREATE_PARTY_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 생성 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_CREATE_PARTY_ACK
{
	stX2G_PT_CREATE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 생성 정보 통보
//	_stCreatePartyBossInfo : boss 정보
struct stX2G_PT_CREATE_PARTY_NTF
{
	stX2G_PT_CREATE_PARTY_NTF()
	{
	}

	std::vector<_stCreatePartyBossInfo> bossinfo;
};


//Party 생성 참여 응답
//	_stCreatePartyAccept : 응답 결과값
struct stX2G_PT_CREATE_PARTY_ACCEPT_REQ
{
	stX2G_PT_CREATE_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stCreatePartyAccept> partyaccept;
};


//입장한 object 정보 통보(파티의 기존맴버에게 통보)
//	_stPartyChar : 입장한 개체 정보
//	_stPartyHiredSoldier : 입장한 개체의 용병 정보
struct stX2G_PT_ENTER_PARTY_MEMBER_NTF
{
	stX2G_PT_ENTER_PARTY_MEMBER_NTF()
	{
	}

	std::vector<_stPartyChar> partychar;
	std::vector<_stPartyHiredSoldier> partyhiredsoldier;
};


//Party의 기존맴버 정보 통보(입장한 유저에게 통보)
//	_stPartyInfo : Party 정보
//	_stPartyChar : Party 맴버 개체 정보
//	_stPartyHiredSoldier : Party 맴버 개체의 용병 정보
struct stX2G_PT_ALL_PARTY_MEMBER_NTF
{
	stX2G_PT_ALL_PARTY_MEMBER_NTF()
	{
	}

	std::vector<_stPartyInfo> partyinfo;
	std::vector<_stPartyChar> partychar;
	std::vector<_stPartyHiredSoldier> partyhiredsoldier;
};


//퇴장한 object 정보 통보(파티의 기존맴버에게 통보)
//	objectindex : 퇴장한 개체의 용병 정보
struct stX2G_PT_LEAVE_PARTY_MEMBER_NTF
{
	stX2G_PT_LEAVE_PARTY_MEMBER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 소멸 요청
struct stX2G_PT_DELETE_PARTY_REQ
{
	stX2G_PT_DELETE_PARTY_REQ()
	{
	}

};


//Party 소멸 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_DELETE_PARTY_ACK
{
	stX2G_PT_DELETE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 소멸 정보 통보
struct stX2G_PT_DELETE_PARTY_NTF
{
	stX2G_PT_DELETE_PARTY_NTF()
	{
	}

};


//Party 초대 요청( 방장권한 )
//	objectindex : 파티에 초대할 대상 object index
struct stX2G_PT_INVITE_PARTY_REQ
{
	stX2G_PT_INVITE_PARTY_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 초대 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_INVITE_PARTY_ACK
{
	stX2G_PT_INVITE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 초대할 대상에게 초대 요청 통보(방장 --> 초대할 대상)
//	_stInvitePartyBossInfo : boss 정보
struct stX2G_PT_INVITE_PARTY_NTF
{
	stX2G_PT_INVITE_PARTY_NTF()
	{
	}

	std::vector<_stInvitePartyBossInfo> bossinfo;
};


//Party 초대 응답
//	_stInvitePartyAccept : 응답 결과값
struct stX2G_PT_INVITE_PARTY_ACCEPT_REQ
{
	stX2G_PT_INVITE_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stInvitePartyAccept> partyaccept;
};


//Party 가입 요청( 일반 유저 권한 )
//	partyindex : 가입할 party index
struct stX2G_PT_ENTER_PARTY_REQ
{
	stX2G_PT_ENTER_PARTY_REQ()
		: partyindex(0)
	{
	}

	GAMEOBJECTID partyindex;
};


//Party 가입 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_ENTER_PARTY_ACK
{
	stX2G_PT_ENTER_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 방장에게 가입 요청 통보( 일반유저 --> 방장 )
struct stX2G_PT_ENTER_PARTY_NTF
{
	stX2G_PT_ENTER_PARTY_NTF()
	{
	}

	std::vector<_stEnterPartyCharInfo> enterobject;
};


//Party 가입 응답
//	_stEnterPartyAccept : 응답 결과값
struct stX2G_PT_ENTER_PARTY_ACCEPT_REQ
{
	stX2G_PT_ENTER_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stEnterPartyAccept> partyaccept;
};


//Party 탈퇴 요청
struct stX2G_PT_LEAVE_PARTY_REQ
{
	stX2G_PT_LEAVE_PARTY_REQ()
	{
	}

};


//Party 탈퇴 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_LEAVE_PARTY_ACK
{
	stX2G_PT_LEAVE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 탈퇴 통보
//	objectindex : 탈퇴한 개체 정보
struct stX2G_PT_LEAVE_PARTY_NTF
{
	stX2G_PT_LEAVE_PARTY_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 맴버 추방 요청
//	objectindex : 추방할 개체 정보
struct stX2G_PT_BANISH_PARTY_MEMBER_REQ
{
	stX2G_PT_BANISH_PARTY_MEMBER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 맴버 추방 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_BANISH_PARTY_MEMBER_ACK
{
	stX2G_PT_BANISH_PARTY_MEMBER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 맴버 추방 통보
//	objectindex : 추방된 개체 정보
struct stX2G_PT_BANISH_PARTY_MEMBER_NTF
{
	stX2G_PT_BANISH_PARTY_MEMBER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 권한 위임 요청
//	objectindex : 새로운 boss 개체
struct stX2G_PT_CHANGE_MASTER_REQ
{
	stX2G_PT_CHANGE_MASTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party 권한 위임 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_CHANGE_MASTER_ACK
{
	stX2G_PT_CHANGE_MASTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 권한 위임 통보
//	objectindex : 새로운 boss 개체 정보
struct stX2G_PT_CHANGE_MASTER_NTF
{
	stX2G_PT_CHANGE_MASTER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party member OM LINE 통보
//	_stPartyOnOffLine : 접속 개체 정보
struct stX2G_PT_ONLINE_PARTY_NTF
{
	stX2G_PT_ONLINE_PARTY_NTF()
	{
	}

	std::vector<_stPartyOnOffLine> onoff;
};


//Party member OFF LINE 통보
//	_stPartyOnOffLine : 접속 종료 개체 정보
struct stX2G_PT_OFFLINE_PARTY_NTF
{
	stX2G_PT_OFFLINE_PARTY_NTF()
	{
	}

	std::vector<_stPartyOnOffLine> onoff;
};


//Party 분배 Rule 요청
//	rule : 변경할 분배 Rule
struct stX2G_PT_CHANGE_DISTRIBUTE_REQ
{
	stX2G_PT_CHANGE_DISTRIBUTE_REQ()
		: rule(0)
	{
	}

	DISTRIBUTE_RULE_T rule;
};


//Party 분배 Rule 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_PT_CHANGE_DISTRIBUTE_ACK
{
	stX2G_PT_CHANGE_DISTRIBUTE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party 분배 Rule 통보
//	rule : 변경뙨 분배 Rule
struct stX2G_PT_CHANGE_DISTRIBUTE_NTF
{
	stX2G_PT_CHANGE_DISTRIBUTE_NTF()
		: rule(0)
	{
	}

	DISTRIBUTE_RULE_T rule;
};


//Party member 이동 통보
//	_stPartyMemberPosition : 개체의 이동 정보
struct stX2G_PT_PARTY_MEMBER_MOVE_NTF
{
	stX2G_PT_PARTY_MEMBER_MOVE_NTF()
	{
	}

	std::vector<_stPartyMemberPosition> moveobject;
};


//Party member regen
//	_stPartyMemberRegen : 개체 regen 정보
struct stX2G_PT_PARTY_MEMBER_REGEN_NTF
{
	stX2G_PT_PARTY_MEMBER_REGEN_NTF()
	{
	}

	std::vector<_stPartyMemberRegen> partyregen;
};


//Party member damage
//	_stPartyMemberDamage : 개체 damage 정보
struct stX2G_PT_PARTY_MEMBER_DAMAGE_NTF
{
	stX2G_PT_PARTY_MEMBER_DAMAGE_NTF()
	{
	}

	std::vector<_stPartyMemberDamage> partydamage;
};


//Party member revival
//	_stPartyMemberRevival : 개체 damage 정보
struct stX2G_PT_PARTY_MEMBER_REVIVAL_NTF
{
	stX2G_PT_PARTY_MEMBER_REVIVAL_NTF()
	{
	}

	std::vector<_stPartyMemberRevival> partyrevival;
};


//Party member dead
//	_stPartyMemberDead : 사망 개체 정보
struct stX2G_PT_PARTY_MEMBER_DEAD_NTF
{
	stX2G_PT_PARTY_MEMBER_DEAD_NTF()
	{
	}

	std::vector<_stPartyMemberDead> partydead;
};


//거래 요청
//	objectindex : 거래할 대상 object
struct stX2G_TD_TRADE_REQ
{
	stX2G_TD_TRADE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//거래 요청에 대한 응답
//	result : 응답 결과값
//	tradeindex : trade index(성공시)
struct stX2G_TD_TRADE_ACK
{
	stX2G_TD_TRADE_ACK()
		: result(0), tradeindex(0)
	{
	}

	RESULT_T result;
	TRADEINDEX tradeindex;
};


//거래 통보
//	_stTradeAsker : 거래자 정보
struct stX2G_TD_TRADE_NTF
{
	stX2G_TD_TRADE_NTF()
	{
	}

	std::vector<_stTradeAsker> traderinfo;
};


//거래 수락/거부
//	tradeindex : trade index
//	bisenter : 1:수락, 그외는 거부
struct stX2G_TD_TRADE_ENTER_REQ
{
	stX2G_TD_TRADE_ENTER_REQ()
		: tradeindex(0), bisenter(0)
	{
	}

	TRADEINDEX tradeindex;
	UINT8 bisenter;
};


//거래 취소 요청(거래완료를 선택후에는 처리가 되지 않는다.)
struct stX2G_TD_TRADE_CANCEL_REQ
{
	stX2G_TD_TRADE_CANCEL_REQ()
	{
	}

};


//거래 취소 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_TD_TRADE_CANCEL_NTF
{
	stX2G_TD_TRADE_CANCEL_NTF()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래 money 등록/해제 요청(등록 이후에는 아이템/money 등록및 해제가 불가능하다.)
//	money :
struct stX2G_TD_TRADE_UPLOAD_MONEY_REQ
{
	stX2G_TD_TRADE_UPLOAD_MONEY_REQ()
		: money(0)
	{
	}

	INT32 money;
};


//거래 money 등록/해제 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_TD_TRADE_UPLOAD_MONEY_ACK
{
	stX2G_TD_TRADE_UPLOAD_MONEY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래 money 등록/해제 통보
//	objectindex : money 등록 object
//	money :
struct stX2G_TD_TRADE_UPLOAD_MONEY_NTF
{
	stX2G_TD_TRADE_UPLOAD_MONEY_NTF()
		: objectindex(0), money(0)
	{
	}

	GAMEOBJECTID objectindex;
	INT32 money;
};


//거래 item 등록 요청(등록 이후에는 아이템/money 등록및 해제가 불가능하다.)
//	itemindex : 등록 아이템
struct stX2G_TD_TRADE_UPLOAD_ITEM_REQ
{
	stX2G_TD_TRADE_UPLOAD_ITEM_REQ()
		: itemindex(0)
	{
	}

	ITEMINDEX itemindex;
};


//거래 item 등록 요청에 대한 응답(자신에게 통보)
//	result : 응답 결과값
//	itemindex : 등록 아이템
struct stX2G_TD_TRADE_UPLOAD_ITEM_ACK
{
	stX2G_TD_TRADE_UPLOAD_ITEM_ACK()
		: result(0), itemindex(0)
	{
	}

	RESULT_T result;
	ITEMINDEX itemindex;
};


//거래 item 등록 통보(상대방에게 통보)
//	objectindex : item 등록 object
//	_stItemData : 등록 아이템
struct stX2G_TD_TRADE_UPLOAD_ITEM_NTF
{
	stX2G_TD_TRADE_UPLOAD_ITEM_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stItemData> itemdata;
};


//거래 item 해제 요청(등록 이후에는 아이템/money 등록및 해제가 불가능하다.)
//	itemindex : 해제 아이템
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_REQ
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_REQ()
		: itemindex(0)
	{
	}

	ITEMINDEX itemindex;
};


//거래 item 해제 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_ACK
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래 item 해제 통보
//	objectindex : item 해제 object
//	itemindex : 해제 아이템
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_NTF
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_NTF()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//거래 체팅 요청
//	chatmsg : 체팅
struct stX2G_TD_TRADE_CHAT_REQ
{
	stX2G_TD_TRADE_CHAT_REQ()
	{
	}

	tstring chatmsg;
};


//거래 체팅 통보
//	_stTraderChatData : 체팅 정보
struct stX2G_TD_TRADE_CHAT_NTF
{
	stX2G_TD_TRADE_CHAT_NTF()
	{
	}

	std::vector<_stTraderChatData> chatdata;
};


//거래 등록완료 요청(등록 이후에는 아이템/money 등록및 해제가 불가능하다.)
struct stX2G_TD_TRADE_ACCEPT_REQ
{
	stX2G_TD_TRADE_ACCEPT_REQ()
	{
	}

};


//거래 등록완료 통보
//	objectindex : 등록 완료 object
struct stX2G_TD_TRADE_ACCEPT_NTF
{
	stX2G_TD_TRADE_ACCEPT_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//거래완료 요청
struct stX2G_TD_TRADE_COMPLETE_REQ
{
	stX2G_TD_TRADE_COMPLETE_REQ()
	{
	}

};


//거래완료 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_TD_TRADE_COMPLETE_ACK
{
	stX2G_TD_TRADE_COMPLETE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래완료 통보
//	objectindex : 거래완료 object
//	itemindex : 거래후 삭제될 아이템
struct stX2G_TD_TRADE_COMPLETE_NTF
{
	stX2G_TD_TRADE_COMPLETE_NTF()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//거래목록 통보(거래된 목록을 각각의 소유주에게 통보한다 - 인벤저장 불가능할 때는 우편함으로 전송예정)
//	money :
//	_stItemData : 거래 아이템
struct stX2G_TD_TRADE_LIST_NTF
{
	stX2G_TD_TRADE_LIST_NTF()
		: money(0)
	{
	}

	INT32 money;
	std::vector<_stItemData> itemdata;
};


//경매목록 요청
//	_stAuctionListRequest : 경매 목록 요청 정보
struct stX2G_AU_AUCTION_LIST_REQ
{
	stX2G_AU_AUCTION_LIST_REQ()
	{
	}

	std::vector<_stAuctionListRequest> auctionrequest;
};


//경매목록 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_AU_AUCTION_LIST_ACK
{
	stX2G_AU_AUCTION_LIST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래목록 통보
//	_stAuctionList : 경매 목록
struct stX2G_AU_AUCTION_LIST_NTF
{
	stX2G_AU_AUCTION_LIST_NTF()
	{
	}

	std::vector<_stAuctionList> auctionlist;
};


//경매등록 요청
//	_stAuctionCreate : 경매 등록 정보
struct stX2G_AU_AUCTION_CREATE_REQ
{
	stX2G_AU_AUCTION_CREATE_REQ()
	{
	}

	std::vector<_stAuctionCreate> auctioncreate;
};


//경매등록 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_AU_AUCTION_CREATE_ACK
{
	stX2G_AU_AUCTION_CREATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//경매등록 통보
//	_stAuctionCreateItem : 등록된 아이템 정보
struct stX2G_AU_AUCTION_CREATE_NTF
{
	stX2G_AU_AUCTION_CREATE_NTF()
	{
	}

	std::vector<_stAuctionCreateItem> auctionitem;
};


//경매입찰 요청
//	_stAuctionTender : 입찰 정보
struct stX2G_AU_AUCTION_TENDER_REQ
{
	stX2G_AU_AUCTION_TENDER_REQ()
	{
	}

	std::vector<_stAuctionTender> auctiontender;
};


//경매입찰 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_AU_AUCTION_TENDER_ACK
{
	stX2G_AU_AUCTION_TENDER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//거래입찰 통보
//	money : 입찰후 소지 money
struct stX2G_AU_AUCTION_TENDER_NTF
{
	stX2G_AU_AUCTION_TENDER_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//경매회수 요청
//	auctionindex : 경매 정보
struct stX2G_AU_AUCTION_RETURN_REQ
{
	stX2G_AU_AUCTION_RETURN_REQ()
	{
	}

	AUCTIONINDEX auctionindex;
};


//경매회수 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_AU_AUCTION_RETURN_ACK
{
	stX2G_AU_AUCTION_RETURN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};
