#pragma once



//GAME ���� ���� ���� ��û
//	account : ������
//	masterkey : master���� ���� ����Ű ( balance������ ���� �޾Ҵ�.)
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


//GAME ���� ���� ���� ��û�� ���� ����
//	result : ���� �����
//	servertime : ������ ����ð�
struct stX2G_AC_CERTIFY_ACK
{
	stX2G_AC_CERTIFY_ACK()
		: result(0), servertime(0)
	{
	}

	RESULT_T result;
	TIME_T servertime;
};


//�ɸ��� list ��û
struct stX2G_CH_LOAD_ALL_CHAR_REQ
{
	stX2G_CH_LOAD_ALL_CHAR_REQ()
	{
	}

};


//�ɸ��� list ��û�� ���� ����
//	result : ���� �����
//	_stCharData : �ɸ��� ������ ���� ����ü
//	_stItemData : ĳ���� item ����
// _stSkillData : �ɸ��� skill ����
struct stX2G_CH_LOAD_ALL_CHAR_ACK
{
	stX2G_CH_LOAD_ALL_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stCharData> chardata;
};


//�ɸ��� list ��û(������)
//[encrypt] CH_LOAD_CHAR_REQ()
//�ɸ��� list ��û�� ���� ����
//	_stCharData : �ɸ��� ������ ���� ����ü
// _stSkillData : �ɸ��� skill ����
struct stX2G_CH_LOAD_CHAR_ACK
{
	stX2G_CH_LOAD_CHAR_ACK()
	{
	}

	std::vector<_stCharData> chardata;
	std::vector<_stSkillData> skilldata;
};


//�ɸ��� ���� ��û
//	_stCreateCharInfo : ������ ĳ���� ����
struct stX2G_CH_CREATE_CHAR_REQ
{
	stX2G_CH_CREATE_CHAR_REQ()
	{
	}

	std::vector<_stCreateCharInfo> charinfo;
};


//�ɸ��� ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_CH_CREATE_CHAR_ACK
{
	stX2G_CH_CREATE_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ɸ��� ���� ��û
//	objectindex : ������ ĳ���� index
struct stX2G_CH_DELETE_CHAR_REQ
{
	stX2G_CH_DELETE_CHAR_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//�ɸ��� ���� ��û�� ���� ����
//	result : ���� �����
//	objectindex : ������ ĳ���� index
struct stX2G_CH_DELETE_CHAR_ACK
{
	stX2G_CH_DELETE_CHAR_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
};


//soldier list ��û
// objectindex : soldier �� ������ �ɸ��� ����
struct stX2G_CH_LOAD_ALL_SOLDIER_REQ
{
	stX2G_CH_LOAD_ALL_SOLDIER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//soldier list ��û�� ���� ����
//	result : ���� �����
//	_stHiredSoldierData : soldier ������ ���� ����ü
//	_stItemData : soldier item ����
// _stSkillData : soldier skill ����
struct stX2G_CH_LOAD_ALL_SOLDIER_ACK
{
	stX2G_CH_LOAD_ALL_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stHiredSoldierData> soldierdata;
};


//soldier list ��û(������)
//[encrypt] CH_LOAD_CHAR_REQ()
//�ɸ��� list ��û�� ���� ����
//	_stHiredSoldierData : soldier ������ ���� ����ü
struct stX2G_CH_LOAD_SOLDIER_ACK
{
	stX2G_CH_LOAD_SOLDIER_ACK()
	{
	}

	std::vector<_stHiredSoldierData> soldierdata;
};


//soldier ���� ��û(������)
//	_stCreateSoldierInfo : ������ soldier ����
//[encrypt] CH_CREATE_SOLDIER_REQ(std::vector<_stCreateSoldierInfo> soldierinfo)
//soldier ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_CH_CREATE_SOLDIER_ACK
{
	stX2G_CH_CREATE_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//soldier ���� ��û
//	objectindex : ������ soldier index
struct stX2G_CH_DELETE_SOLDIER_REQ
{
	stX2G_CH_DELETE_SOLDIER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//soldier ���� ��û�� ���� ����
//	result : ���� �����
//	objectindex : ������ soldier index
struct stX2G_CH_DELETE_SOLDIER_ACK
{
	stX2G_CH_DELETE_SOLDIER_ACK()
		: result(0), objectindex(0)
	{
	}

	RESULT_T result;
	GAMEOBJECTID objectindex;
};


//soldier ���� ���� �뺸
//	money : ������ money
struct stX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF
{
	stX2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//�ɸ��� nick �ߺ� üũ ��û
//	nickname :
struct stX2G_CH_CHECK_NICK_DUPLICATE_REQ
{
	stX2G_CH_CHECK_NICK_DUPLICATE_REQ()
	{
	}

	tstring nickname;
};


//�ɸ��� nick �ߺ� üũ ��û�� ���� ����
//	result : ���� �����
struct stX2G_CH_CHECK_NICK_DUPLICATE_ACK
{
	stX2G_CH_CHECK_NICK_DUPLICATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ɸ��� ȹ�� ����ġ �뺸(�ڽſ��Ը�)
//	_stObjectExp : ĳ���� ȹ�� ����ġ ���� ����ü
struct stX2G_CH_OBJECT_EXP_ACK
{
	stX2G_CH_OBJECT_EXP_ACK()
	{
	}

	std::vector<_stObjectExp> objectexp;
};


//�ɸ��� level up �뺸(�ڽſ��Ը�)
//	_stLevelupObject : ĳ���� level up ���� ����ü
struct stX2G_CH_LEVEL_UP_ACK
{
	stX2G_CH_LEVEL_UP_ACK()
	{
	}

	std::vector<_stLevelupObject> levelupobject;
};


//�ɸ��� level up �뺸(�ֺ�����)
//	_stLevelupObjectNtf : ĳ���� level up ���� ����ü
struct stX2G_CH_LEVEL_UP_NTF
{
	stX2G_CH_LEVEL_UP_NTF()
	{
	}

	std::vector<_stLevelupObjectNtf> levelupobject;
};


//�ɸ��� ���� ������ �뺸
//	money : ĳ���� ������
struct stX2G_CH_MONEY_NTF
{
	stX2G_CH_MONEY_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//object�� ���� ���� ���� �뺸
//	objectindex : ���� ���� ���� ��ü index
struct stX2G_CH_SETUP_NO_RIVAL_NTF
{
	stX2G_CH_SETUP_NO_RIVAL_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//object�� ���� ���� ���� �뺸
//	objectindex : ���� ���� ���� ��ü index
struct stX2G_CH_RELEASE_NO_RIVAL_NTF
{
	stX2G_CH_RELEASE_NO_RIVAL_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//object�� �ɷ�ġ ���� �뺸
// objectindex : �ɷ�ġ ����� ��ü
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


//Ʃ�͸��� ���� ��û
//	tutorial : Ʃ�͸��� ���࿩��(0:������, 1:����, 2:�Ϸ�)
struct stX2G_CH_COMPLETED_TUTORIAL_REQ
{
	stX2G_CH_COMPLETED_TUTORIAL_REQ()
		: tutorial(0)
	{
	}

	TUTORIAL_TYPE_T tutorial;
};


//Ʃ�͸��� ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_CH_COMPLETED_TUTORIAL_ACK
{
	stX2G_CH_COMPLETED_TUTORIAL_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//���� �ɼ� ���� ��û
//	gameoption : //���ӳ� �ɼ�(CHAR_GAME_OPTION : �ŷ�����,��Ƽ����)
struct stX2G_CH_CHAR_GAME_OPTION_REQ
{
	stX2G_CH_CHAR_GAME_OPTION_REQ()
		: gameoption(0)
	{
	}

	CHAR_GAME_OPTION_T gameoption;
};


//Battle Formation ���� ��û
//	battletype : �Ϲ�����, ��Ƽ����
//	_stObjectBattleo : �������� �뺴�� ����(char�� ����(0)���� �뺴�� ��ġ�� ��������� �����Ѵ�.) -- char ��ġ�� �������� ����
//	bestfriendsoldierindex : best friend �뺴
//	_stBattleToggleSoldier : toggle �뺴
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


//Battle Formation ���� ��û�� ���� ����
//	_stBattleFormation : �������� �뺴�� ����(char�� ����(0)���� �뺴�� ��ġ�� ��������� �����Ѵ�.) -- char ��ġ�� �������� ����
//	bestfriendsoldierindex : best friend �뺴
struct stX2G_CH_BATTLE_FORMATION_ACK
{
	stX2G_CH_BATTLE_FORMATION_ACK()
		: bestfriendsoldierindex(0)
	{
	}

	std::vector<_stBattleFormation> formation;
	GAMEOBJECTID bestfriendsoldierindex;
};


//world�� ���� ��û(ĳ���� �����ؼ� ó�� world ������ ��)
//	zonecode : �����ϰ��� �ϴ� zone code --������ �ʴ´�. ���� ������ ��
//	objectindex : ������ ĳ���� index
struct stX2G_WD_WORLD_ENTER_REQ
{
	stX2G_WD_WORLD_ENTER_REQ()
		: zonecode(0), objectindex(0)
	{
	}

	ZONECODE zonecode;
	GAMEOBJECTID objectindex;
};


//portal ��� ��û
//	objectindex : ����� portal index
struct stX2G_WD_USE_PORTAL_REQ
{
	stX2G_WD_USE_PORTAL_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//world�� ���� ��û�� ���� ����(�ڽſ��� �뺸�Ѵ�.)
//	result : ���� �����
//	_stEnterObjectData : zone ������ ��ü�� ����
struct stX2G_WD_WORLD_ENTER_ACK
{
	stX2G_WD_WORLD_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stEnterObjectData> enterdata;
};


//npc ��ȭ�� Quest�� ���� world �̵� ��û
//	_stWorldChangeForQuest : ���̵� ������ Quest ����
struct stX2G_WD_WORLD_CHANGE_FOR_QUEST_REQ
{
	stX2G_WD_WORLD_CHANGE_FOR_QUEST_REQ()
	{
	}

	std::vector<_stWorldChangeForQuest> questinfo;
};


//world�� ���� ��û�� ���� ����(�ڽſ��� �뺸�Ѵ�.)
//	result : ���� �����
struct stX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK
{
	stX2G_WD_WORLD_CHANGE_FOR_QUEST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//world�� ������ ������ ���� �뺸(Ÿ�ο��Ը� ����)
//	_stZoneCharData : �ɸ��� ������ ���� ����ü
//	_stZoneHiredSoldierData : �뺴 ������ ���� ����ü
//	_stMonsterData : ���� ������ ���� ����ü
//	_stTownNpcData : town NPC ������ ���� ����ü
//	_stPortalData : portal ������ ���� ����ü
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


//world�� �����ϴ� ��ü�� ���� �뺸(������ �ɸ��Ϳ��� ����)
//	_stZoneCharData : �ɸ��� ������ ���� ����ü
//	_stZoneHiredSoldierData : �뺴 ������ ���� ����ü
//	_stMonsterData : ���� ������ ���� ����ü
//	_stTownNpcData : town NPC ������ ���� ����ü
//	_stPortalData : portal ������ ���� ����ü
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


//world�� ���� ��û
struct stX2G_WD_WORLD_LEAVE_REQ
{
	stX2G_WD_WORLD_LEAVE_REQ()
	{
	}

};


//world���� ������ object(����/npc)�� ���� �뺸(Ÿ�ο��� ����)
//	_stLeaveObjectData : ������ ĳ���� index
struct stX2G_WD_LEAVE_OBJECT_NTF
{
	stX2G_WD_LEAVE_OBJECT_NTF()
	{
	}

	std::vector<_stLeaveObjectData> leaveobject;
};


//world�� �̵� ��û
//	x, y, z : �̵��� ��ġ(����ü�� vector�� �����Ѵ�.)
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


//world�� �̵� ��û�� ���� ����
//	result : ���� �����
struct stX2G_WD_MOVE_ACK
{
	stX2G_WD_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//world�� �̵��� object�� ���� �뺸
//	_stMoveObjectData : zone �̵� ��ü ����
//	servertime : ������ ����ð�
struct stX2G_WD_MOVE_NTF
{
	stX2G_WD_MOVE_NTF()
		: servertime(0)
	{
	}

	std::vector<_stMoveObjectData> moveobject;
	TIME_T servertime;
};


//world�� ���� ��û
//	x, y, z : ���� ��ġ(����ü�� vector�� �����Ѵ�.)
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


//world�� ���� object�� ���� �뺸
//	_stStopObjectData : zone ���� ��ü ����
struct stX2G_WD_STOP_NTF
{
	stX2G_WD_STOP_NTF()
	{
	}

	std::vector<_stStopObjectData> stopobject;
};


//�ɸ��� motion ��û
//	motion : ĳ���� motion
struct stX2G_WD_MOTION_REQ
{
	stX2G_WD_MOTION_REQ()
		: motion(0)
	{
	}

	MOTION_T motion;
};


//�ɸ��� motion ��ûû�� ���� ����
//	result : ���� �����
struct stX2G_WD_MOTION_ACK
{
	stX2G_WD_MOTION_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ɸ��� motion �뺸
//	_stObjectMotion : ĳ���� motion ���� ����ü
struct stX2G_WD_MOTION_NTF
{
	stX2G_WD_MOTION_NTF()
	{
	}

	std::vector<_stObjectMotion> motion;
};


//zone puzzle ���� ���� ��û
//	puzzle : ����� zone puzzle����
struct stX2G_WD_WORLD_PUZZLE_REQ
{
	stX2G_WD_WORLD_PUZZLE_REQ()
	{
	}

	ZONEPUZZLE puzzle;
};


//zone puzzle ���� ���� �뺸
//	puzzle : ����� zone puzzle����
struct stX2G_WD_WORLD_PUZZLE_NTF
{
	stX2G_WD_WORLD_PUZZLE_NTF()
	{
	}

	ZONEPUZZLE puzzle;
};


//����� open ��û
//	worldmap : open�� �� ����
struct stX2G_WD_WORLD_MAP_OPEN_REQ
{
	stX2G_WD_WORLD_MAP_OPEN_REQ()
		: worldmap(0)
	{
	}

	WORLD_MAP_T worldmap;
};


//����� open ��û�� ���� ����
//	result : ���� �����
struct stX2G_WD_WORLD_MAP_OPEN_ACK
{
	stX2G_WD_WORLD_MAP_OPEN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//ü��(��ü ü��)
//	type : ü�� ����(normal, notice)
//	chatmsg : ü�� �޽���
struct stX2G_BD_CHAT_REQ
{
	stX2G_BD_CHAT_REQ()
		: type(0)
	{
	}

	CHAT_TYPE_T type;
	tstring chatmsg;
};


//ü�� �Ӹ� ��û(�Ӹ� ó�� �޴� ����� �����Ҷ� ���ȴ�)
//	toid : �޴� ��� GAMEOBJECTID
//	tonick : �޴� ��� nick(������ �������ϴµ�, �Ӹ��� toid�� �𸦰�� �����Ѵ�)
//	type : ü�� ����
//	chatmsg: ü�ø޽���
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


//chat ��û�� ���� ����
//	result : ���� �����
struct stX2G_BD_CHAT_ACK
{
	stX2G_BD_CHAT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//chat �ֺ� �뺸
//	_stChattingData : ü�� ����ü ����
struct stX2G_BD_CHAT_NTF
{
	stX2G_BD_CHAT_NTF()
	{
	}

	std::vector<_stChattingData> chatdata;
};


//���� �޽��� �뺸
//	_stNoticeChattingData : ���� ����
struct stX2G_BD_NOTICE_CHAT_NTF
{
	stX2G_BD_NOTICE_CHAT_NTF()
	{
	}

	std::vector<_stNoticeChattingData> noticedata;
};


//��ü�� hp/mp �����
//	_stRegenObjectData : regen ��ü ����
struct stX2G_OB_REGEN_NTF
{
	stX2G_OB_REGEN_NTF()
	{
	}

	std::vector<_stRegenObjectData> regenobject;
};


//��ü�� ���
//	objectindex : ����� ĳ���� index
struct stX2G_OB_DEATH_NTF
{
	stX2G_OB_DEATH_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//��ü�� ��Ȱ
//	_stRevivalObjectData : revival ��ü ����
struct stX2G_OB_REVIVAL_NTF
{
	stX2G_OB_REVIVAL_NTF()
	{
	}

	std::vector<_stRevivalObjectData> revivalobject;
};


//�ɸ��� skill ����
//	objectindex : object index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
//	_stSkillData : �ɸ��� skill ����
struct stX2G_SK_LOAD_CHAR_SKILL_ACK
{
	stX2G_SK_LOAD_CHAR_SKILL_ACK()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stSkillData> skilldata;
};


//learn skill ��û
//	objectindex : object index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
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


//learn skill ��û�� ���� ����
//	result : ���� �����
struct stX2G_SK_SKILL_LEARN_ACK
{
	stX2G_SK_SKILL_LEARN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//learn skill �뺸
//	_stLearnSkill : ��� ��ų ����
struct stX2G_SK_SKILL_LEARN_NTF
{
	stX2G_SK_SKILL_LEARN_NTF()
	{
	}

	std::vector<_stLearnSkill> learnskill;
};


//level up skill ��û
//	objectindex : object index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
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


//level up skill ��û�� ���� ����
//	result : ���� �����
struct stX2G_SK_SKILL_LEVELUP_ACK
{
	stX2G_SK_SKILL_LEVELUP_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//level up skill �뺸
//	_stLevelupSkill : level up ��ų ����
struct stX2G_SK_SKILL_LEVELUP_NTF
{
	stX2G_SK_SKILL_LEVELUP_NTF()
	{
	}

	std::vector<_stLevelupSkill> levelupskill;
};


//�ɸ��� skill quick slot ���� ���� ��û
struct stX2G_SK_SKILL_QUICK_SLOT_REQ
{
	stX2G_SK_SKILL_QUICK_SLOT_REQ()
	{
	}

	std::vector<_stSkillQuickSlot> quickslot;
};


//�ɸ��� skill quick slot ����
//	_stSkillQuickSlot : skill quick slot ����
struct stX2G_SK_SKILL_QUICK_SLOT_ACK
{
	stX2G_SK_SKILL_QUICK_SLOT_ACK()
	{
	}

	std::vector<_stSkillQuickSlot> quickslot;
};


//attack ��û
//	objectindex : ������ ĳ���� index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
//	targetboard : battle field�� target seat id (�� ��ġ)
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


//attack ��û�� ���� ����
//	result : ���� �����
struct stX2G_SK_ATTACK_ACK
{
	stX2G_SK_ATTACK_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//attack �뺸
//	_stAttackObjectData : �����ϴ� ��ü ����
//	_stTargetObjectData : ���ݹ޴� ��ü ����
//	servertime : ������ ����ð�
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


//���� ���� �뺸
//	_stBuffDebuff : �߰��� ���� ����
struct stX2G_SK_INSERT_BUFF_NTF
{
	stX2G_SK_INSERT_BUFF_NTF()
	{
	}

	std::vector<_stBuffDebuff> buffdata;
};


//���� �Ҹ� �뺸
//	_stBuffDebuff : �Ҹ�� ���� ����
struct stX2G_SK_DELETE_BUFF_NTF
{
	stX2G_SK_DELETE_BUFF_NTF()
	{
	}

	std::vector<_stBuffDebuff> buffdata;
};


//��ü�� hp/mp �����
//	_stAttackObjectData : �����ϴ� ��ü ����
//	_stRegenObjectData : regen ��ü ����
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


//���Ϳ� battle ��û(������ BF_BATTLE_STATUS_NTF �� �޴´�.)
//	objectindex : ���� ��� ���� object index
//	formation : ���� ��Ȳ(����,���)
struct stX2G_BF_BATTLE_OPEN_REQ
{
	stX2G_BF_BATTLE_OPEN_REQ()
		: objectindex(0), formation(0)
	{
	}

	GAMEOBJECTID objectindex;
	BATTLE_FORMATION_T formation;
};


//���Ϳ� battle ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_OPEN_ACK
{
	stX2G_BF_BATTLE_OPEN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//ĳ���� battle ���� ��û(������ BF_BATTLE_STATUS_NTF �� �޴´�.)
//	objectindex : �������� ��� ���� object index
struct stX2G_BF_BATTLE_INTRUDE_CHAR_REQ
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//ĳ���� battle ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_INTRUDE_CHAR_ACK
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle �� �����ϴ� �ο����� �뺸
//	chardata : battle char ����
//	monsterdata : battle monster ����
struct stX2G_BF_BATTLE_INTRUDE_CHAR_NTF
{
	stX2G_BF_BATTLE_INTRUDE_CHAR_NTF()
	{
	}

	std::vector<_stOpenBattleObjectData> chardata;
	std::vector<_stOpenBattleObjectData> monsterdata;
};


//Monster battle ���� ��û(������ BF_BATTLE_STATUS_NTF �� �޴´�.)
//	objectindex : ���� ���� object index(�������� char�� �ֺ� monster�� ������δ�.)
struct stX2G_BF_BATTLE_INTRUDE_MONSTER_REQ
{
	stX2G_BF_BATTLE_INTRUDE_MONSTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Monster battle ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_INTRUDE_MONSTER_ACK
{
	stX2G_BF_BATTLE_INTRUDE_MONSTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle �� �����ϴ� �ο����� �뺸
//	chardata : battle char ����
//	monsterdata : battle monster ����
struct stX2G_BF_BATTLE_OBJECT_NTF
{
	stX2G_BF_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stOpenBattleObjectData> chardata;
	std::vector<_stOpenBattleObjectData> monsterdata;
};


//battle field �� ���� ��û
//	board : battle field seat id (�� ��ġ)
//[encrypt] BF_BATTLE_ENTER_REQ(BOARDINDEX board)
//battle field �� ���� ��û�� ���� ����
//	result : ���� �����
//	_stEnterBattleObjectData : battle ������ ��ü�� ����
struct stX2G_BF_BATTLE_ENTER_ACK
{
	stX2G_BF_BATTLE_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stEnterBattleObjectData> enterdata;
};


//battle field �� ������ ������ ���� �뺸(Ÿ��/�ڽſ��� ����)
//	_stBattleChar : �ɸ����� ���� ������ ���� ����ü( _stCharData �� ���е� )
//	_stBattleHiredSoldier : �뺴 ������ ���� ����ü( __stHiredSoldierData�� ���е�)
//	_stBattleMonster : ������ ���� ������ ���� ����ü
//	servertime : ������ ����ð�
struct stX2G_BF_ENTER_BATTLE_OBJECT_NTF
{
	stX2G_BF_ENTER_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stBattleChar> battlechar;
	std::vector<_stBattleHiredSoldier> battlehiredsoldier;
	std::vector<_stBattleMonster> battlemonster;
};


//battle field �� �����ϴ� ��ü�� ���� �뺸(Ÿ�ο��� ����)
//	_stBattleChar : �ɸ����� ���� ������ ���� ����ü( _stCharData �� ���е� )
//	_stBattleHiredSoldier : �뺴 ������ ���� ����ü( __stHiredSoldierData�� ���е�)
//	_stBattleMonster : ���� ������ ���� ����ü
//	servertime : ������ ����ð�
struct stX2G_BF_ALL_BATTLE_OBJECT_NTF
{
	stX2G_BF_ALL_BATTLE_OBJECT_NTF()
	{
	}

	std::vector<_stBattleChar> battlechar;
	std::vector<_stBattleHiredSoldier> battlehiredsoldier;
	std::vector<_stBattleMonster> battlemonster;
};


//battle field �� ���� ��û
struct stX2G_BF_BATTLE_LEAVE_REQ
{
	stX2G_BF_BATTLE_LEAVE_REQ()
	{
	}

};


//battle field �� ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_LEAVE_ACK
{
	stX2G_BF_BATTLE_LEAVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field ���� ������ object(����/npc)�� ���� �뺸(Ÿ�ο��� ����)
//	_stLeaveBattleObjectData : battle ������ object ������ ���� ����ü
//	servertime : ������ ����ð�
struct stX2G_BF_LEAVE_BATTLE_OBJECT_NTF
{
	stX2G_BF_LEAVE_BATTLE_OBJECT_NTF()
		: servertime(0)
	{
	}

	std::vector<_stLeaveBattleObjectData> leaveobject;
	TIME_T servertime;
};


//battle field �� �̵� ��û
//	objectindex : ������ ĳ���� index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
//	board : �̵��� battle ��ġ index
struct stX2G_BF_BATTLE_MOVE_REQ
{
	stX2G_BF_BATTLE_MOVE_REQ()
		: objectindex(0), board(0)
	{
	}

	GAMEOBJECTID objectindex;
	BOARDINDEX board;
};


//battle field �� �̵� ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_MOVE_ACK
{
	stX2G_BF_BATTLE_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field �� �̵��� object�� ���� �뺸
//	_stMoveBattleObjectData : battle field �̵� ��ü ����
//	servertime : ������ ����ð�
struct stX2G_BF_BATTLE_MOVE_NTF
{
	stX2G_BF_BATTLE_MOVE_NTF()
		: servertime(0)
	{
	}

	std::vector<_stMoveBattleObjectData> moveobject;
	TIME_T servertime;
};


//battle field �� ���� object�� ���� �뺸
//	_stStopObjectData : zone ���� ��ü ����
struct stX2G_BF_BATTLE_STOP_NTF
{
	stX2G_BF_BATTLE_STOP_NTF()
	{
	}

	std::vector<_stStopObjectData> stopobject;
};


//battle status ���� ��û
struct stX2G_BF_BATTLE_NEXT_STATUS_REQ
{
	stX2G_BF_BATTLE_NEXT_STATUS_REQ()
	{
	}

};


//battle status ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_NEXT_STATUS_ACK
{
	stX2G_BF_BATTLE_NEXT_STATUS_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//battle field �� status ���� �뺸
//	status : ������ battle field ����
//	servertime : ������ ����ð�
struct stX2G_BF_BATTLE_STATUS_NTF
{
	stX2G_BF_BATTLE_STATUS_NTF()
		: status(0), servertime(0)
	{
	}

	BATTLE_STATUS_T status;
	TIME_T servertime;
};


//battle field �� waiting list(����ڸ��) �뺸
//	currentturn : ���� turn ��ȣ(TURN_T) -- ������ ���� ����� �� ����.
//	servertime : ������ ����ð�
//	movepower : ���� turn object�� movepower
//	_stBattleTurnWaitingObject : battle ���� ����� ���
//	_stBattleTurnBonusCard : battle bonus card ���
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


//������
//battle �̵� ��� ��û
//	objectindex : ������ ĳ���� index(�뺴�� �� �ֱ⿡ index�� �޴´�.)
//	destboard : ��ǥ ��ġ
//	skillcode : skill table id
//[encrypt] BF_FIND_PATH_REQ(GAMEOBJECTID objectindex, BOARDINDEX destboard, SKILLCODE skillcode)
//������
//battle �̵� ��� ��û�� ���� ����
//	result : ���� �����
//	board : �̵� ���
//[encrypt] BF_FIND_PATH_ACK(RESULT_T result, std::vector<_stBoardIndex> board)
//battle PvP ��û
//	objectindex : PvP ��� ĳ���� index
//	bisparty : 0.������, �׿ܴ� pvp party��
struct stX2G_BF_BATTLE_PVP_REQ
{
	stX2G_BF_BATTLE_PVP_REQ()
		: objectindex(0), bisparty(0)
	{
	}

	GAMEOBJECTID objectindex;
	UINT8 bisparty;
};


//battle PvP ��û�� �����Ѵ�.(��뿡�� �뺸�Ѵ�.)
//	_stPvPRequestObjectData : PvP ��û�� ��ü�� ����
struct stX2G_BF_BATTLE_PVP_ACK
{
	stX2G_BF_BATTLE_PVP_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stPvPRequestObjectData> enterdata;
};


//battle PvP ��û�� ���� ����(��û��-öȸ����, ������-������ ��������)
//	pvpindex : pvp ���� index
//	result : ���� �����(0 �̿��� ���� ����ó����)
struct stX2G_BF_BATTLE_PVP_RESULT_REQ
{
	stX2G_BF_BATTLE_PVP_RESULT_REQ()
		: pvpindex(0), result(0)
	{
	}

	BATTLEPVPINDEX pvpindex;
	RESULT_T result;
};


//battle PvP ������ ��뿡�� �뺸
//	result : ���� �����
struct stX2G_BF_BATTLE_PVP_RESULT_ACK
{
	stX2G_BF_BATTLE_PVP_RESULT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//monster entertime skip ��û
//	objectindex : skip ��ü ����
struct stX2G_BF_BATTLE_SKIP_ENTER_REQ
{
	stX2G_BF_BATTLE_SKIP_ENTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//monster entertime skip ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_SKIP_ENTER_ACK
{
	stX2G_BF_BATTLE_SKIP_ENTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//monster leavetime skip ��û
//	objectindex : skip ��ü ����
struct stX2G_BF_BATTLE_SKIP_LEAVE_REQ
{
	stX2G_BF_BATTLE_SKIP_LEAVE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//monster leavetime skip ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_SKIP_LEAVE_ACK
{
	stX2G_BF_BATTLE_SKIP_LEAVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//char skill casting skip ��û
//	objectindex : skip ��ü ����
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//char skill casting skip ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//char skill casting skip �뺸
//	result : ���� �����
struct stX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF
{
	stX2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF()
	{
	}

};


//�뺴 toggle ��û
//	objectindex : ���� turn object
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


//�뺴 toggle ��û�� ���� ����
//	result : ���� �����
struct stX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK
{
	stX2G_BF_BATTLE_TOGGLE_SOLDIER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�뺴 toggle ��û�� ���� ����
//	_stBattleHiredSoldier : ��ü ���Ե� ��ü ����
struct stX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF
{
	stX2G_BF_BATTLE_TOGGLE_SOLDIER_NTF()
	{
	}

	std::vector<_stBattleHiredSoldier> togglehiredsoldier;
};


//�ɸ��� inventory ���� ��û(������)
//[encrypt] IT_LOAD_INVENTORY_ITEM_REQ()
//�ɸ��� inventory ����
//	objectindex : ��ü ����
//	_stItemData : ������ item ����
struct stX2G_IT_LOAD_INVENTORY_ITEM_ACK
{
	stX2G_IT_LOAD_INVENTORY_ITEM_ACK()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stItemData> itemdata;
};


//�ɸ��� item quick slot ���� ���� ��û
struct stX2G_IT_QUICK_SLOT_REQ
{
	stX2G_IT_QUICK_SLOT_REQ()
	{
	}

	std::vector<_stItemQuickSlot> quickslot;
};


//�ɸ��� item quick slot ����
//	objectindex : ��ü ����
//	_stItemQuickSlot : item quick slot ����
struct stX2G_IT_QUICK_SLOT_ACK
{
	stX2G_IT_QUICK_SLOT_ACK()
	{
	}

	std::vector<_stItemQuickSlot> quickslot;
};


//������ ���� ��û
//	_stBuyItem : ���� ����
struct stX2G_IT_BUY_ITEM_REQ
{
	stX2G_IT_BUY_ITEM_REQ()
	{
	}

	std::vector<_stBuyItem> buyitem;
};


//������ ���� ��û�� ���� ����
//	result : ���� �����
//	objectindex : ��ü ����
//	money : ������ ������ money
//	_stItemData : ������ item ����
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


//������ �Ǹ� ��û
//	objectindex : ��ü ����
//	itemindex : �Ǹ� ������ index
struct stX2G_IT_SELL_ITEM_REQ
{
	stX2G_IT_SELL_ITEM_REQ()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//������ �Ǹ� ��û�� ���� ����
//	result : ���� �����
//	_stSellItem : �Ǹ�����
struct stX2G_IT_SELL_ITEM_ACK
{
	stX2G_IT_SELL_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stSellItem> sellitem;
};


//����� monster�� ���� ������ �ݱ�(������)
//	objectindex : ��� ���� object index
//	_stPickupItem : ȹ�� item ����(item code)
//[encrypt] IT_PICKUP_ITEM_REQ(GAMEOBJECTID objectindex, std::vector<_stPickupItem> pickupitem)
//����� monster�� ���� ������ �ݱ⿡ ���� ����
//	result : ���� �����
//	objectindex : ������  object index
//	_stItemData : ȹ�� item ����(item �� ����)
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


//����� monster�� ���� ������ ���� �뺸
//	objectindex : ������ ���� ����� object index
//	_stPickupItem : ȹ�� item ����
//	_stPickupObject : ���� �����ڵ� ����
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


//������ �ı�(������) ��û
//	objectindex : ��ü ����
//	itemindex : �ı� ������ index
struct stX2G_IT_DESTROY_ITEM_REQ
{
	stX2G_IT_DESTROY_ITEM_REQ()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//������ �ı�(������) ��û�� ���� ����
//	result : ���� �����
//	_stDestroyItem : �ı�����
struct stX2G_IT_DESTROY_ITEM_ACK
{
	stX2G_IT_DESTROY_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stDestroyItem> destroyitem;
};


//������ inventory ��ġ ���� ��û
//	objectindex : ��ü ����
//	_stInventorySlot : ����� item ����
struct stX2G_IT_INVENTORY_CHANGE_REQ
{
	stX2G_IT_INVENTORY_CHANGE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stInventorySlot> inventorydata;
};


//������ inventory ��ġ ���� ��û�� ���� ����
//	result : ���� �����
//	objectindex : ��ü ����
//	_stInventorySlot : ����� item ����
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


//������ Equip ��ġ ���� ��û
//	objectindex : ��ü ����
//	_stEquipPart : ����� item ����
struct stX2G_IT_EQUIP_CHANGE_REQ
{
	stX2G_IT_EQUIP_CHANGE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stEquipPart> equipdata;
};


//������ Equip ��ġ ���� ��û�� ���� ����(�ڽſ��� �뺸)
//	result : ���� �����
//	objectindex : equip ���� object index
//	_stEquipPart : ����� item ����
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


//������ ���� �ֺ� �뺸(�ڽ��� ����)
//	objectindex : equip ���� object index
//	_stObjectItemData(equipitem) : ���� item ����
//	_stObjectItemData(unequipitem) : Ż�� item ����
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


//������ �ٸ� ��ü���� ���� ��û
//	_stGiftInventorySlot : ����� item ����
struct stX2G_IT_GIFT_REQ
{
	stX2G_IT_GIFT_REQ()
	{
	}

	std::vector<_stGiftInventorySlot> giftdata;
};


//������ �ٸ� ��ü���� ���� ��û�� ���� ����
//	result : ���� �����
//	_stGiftInventorySlot : ����� item ����
struct stX2G_IT_GIFT_ACK
{
	stX2G_IT_GIFT_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stGiftInventorySlot> giftdata;
};


//������ �ٸ� ��ü���� ����(Ż��) ��û
//	fromid : �ִ� ��ü ����
//	toid : �޴� ��ü ����
//	_stEquipPart : ����� item ����(�޴� ��ü)
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


//������ �ٸ� ��ü���� ����(Ż��) ��û�� ���� ����(�ڽſ��� �뺸)
//	result : ���� �����
//	fromid : �ִ� ��ü ����
//	toid : �޴� ��ü ����
//	_stEquipPart : ����� item ����
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


//������ �ٸ� ��ü���� ����(Ż��) �ֺ� �뺸(�ڽ��� ����)
//	_stZoneObjectItemData(equipitem) : ���� item ����
//	_stZoneObjectItemData(unequipitem) : Ż�� item ����
struct stX2G_IT_GIFT_EQUIP_CHANGE_NTF
{
	stX2G_IT_GIFT_EQUIP_CHANGE_NTF()
	{
	}

	std::vector<_stZoneObjectItemData> equipitem;
	std::vector<_stZoneObjectItemData> unequipitem;
};


//���������� drop ������ ��� ��û(������)
//	objectindex : ���������� index
//[encrypt] IT_NPC_DROP_ITEM_REQ(GAMEOBJECTID objectindex)
//����� monster�� drop ������ ��Ͽ�û�� ���� ����(������)
//	result : ���� �����
//[encrypt] IT_NPC_DROP_ITEM_ACK(RESULT_T result)
//����� monster�� drop ������ / �������� �������� ������ ���(������)
//	objectindex : ����� monster index
//	_stPickupItem : Drop item ����
//[encrypt] IT_NPC_DROP_ITEM_NTF(GAMEOBJECTID objectindex, std::vector<_stPickupItem> pickupitem)
//������ ��� ��û(field ����)
//	_stUseItemOnField  : ������ ��� ����
struct stX2G_IT_USE_ITEM_REQ
{
	stX2G_IT_USE_ITEM_REQ()
	{
	}

	std::vector<_stUseItemOnField> useiteminfo;
};


//������ ��� ��û(battle field ����)
//	_stUseItemOnBattle : ������ ��� ����
struct stX2G_IT_USE_ITEM_ON_BATTLE_REQ
{
	stX2G_IT_USE_ITEM_ON_BATTLE_REQ()
	{
	}

	std::vector<_stUseItemOnBattle> useiteminfo;
};


//������ ��� ��û�� ���� ����
//	result : ���� �����
//	_stUseItemChar : ���� ������ ����
struct stX2G_IT_USE_ITEM_ACK
{
	stX2G_IT_USE_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stUseItemChar> useitem;
};


//������ ��� �뺸
//	_stUseItemNtf : ��� ������ ����
struct stX2G_IT_USE_ITEM_NTF
{
	stX2G_IT_USE_ITEM_NTF()
	{
	}

	std::vector<_stUseItemNtf> useitem;
};


//���ŵ� ������ ���� �뺸
//	_stUpdateItemcard : ���ŵ� ������ ����
struct stX2G_IT_UPDATE_ITEM_NTF
{
	stX2G_IT_UPDATE_ITEM_NTF()
	{
	}

	std::vector<_stUpdateItemcard> updateitem;
};


//������ �и� ��û
//	fromid : �ִ� ��ü ����
//	toid : �޴� ��ü ����
//	sourceitemindex : �и��� ���� ������ index
//	itemcount : �и��� ����
//	slot : �и��� �κ���ġ
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


//������ �и� ��û�� ���� ����
//	result : ���� �����
//	fromid : �ִ� ��ü ����
//	toid : �޴� ��ü ����
//	_stItemSplite : �и��� ������ ����
//	_stItemData : ������ item ����(item �� ����)
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


//������ ���� ��û
//	fromid : �ִ� ��ü ����
//	toid : �޴� ��ü ����
//	sourceitemindex : �ִ� ��ü�� ������ index
//	itemindex : �޴� ��ü�� ������ index
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


//������ ���� ��û�� ���� ����
//	result : ���� �����
//	_stItemCombine : ���� ������ ����
struct stX2G_IT_COMBINE_ITEM_ACK
{
	stX2G_IT_COMBINE_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stItemCombine> itemcombine;
};


//Quest ��� ��û
struct stX2G_QT_CHAR_QUEST_LIST_REQ
{
	stX2G_QT_CHAR_QUEST_LIST_REQ()
	{
	}

};


//Quest ��� ��û�� ���� ����
//	TQuest : Quest ����
//	_stQuestUpdate : Quest ����
//	_stQuestProgressUpdate : Progress ����
struct stX2G_QT_CHAR_QUEST_LIST_ACK
{
	stX2G_QT_CHAR_QUEST_LIST_ACK()
	{
	}

	std::vector<_stQuestUpdate> questdata;
	std::vector<_stQuestProgressUpdate> progressdata;
};


//new Quest ��� ��û
//	questcode : ����� Quest code
struct stX2G_QT_CHAR_QUEST_INSERT_REQ
{
	stX2G_QT_CHAR_QUEST_INSERT_REQ()
		: questcode(0)
	{
	}

	QUESTCODE questcode;
};


//new Quest ��� ��û�� ���� ����
//	result : ���� �����
//	questcode : ������ Quest code
struct stX2G_QT_CHAR_QUEST_INSERT_ACK
{
	stX2G_QT_CHAR_QUEST_INSERT_ACK()
		: result(0), questcode(0)
	{
	}

	RESULT_T result;
	QUESTCODE questcode;
};


//town npc�� ��ȭ ��û
//	objectindex : ��ȭ���� npc ����
struct stX2G_QT_CHAR_HELLO_NPC_REQ
{
	stX2G_QT_CHAR_HELLO_NPC_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//town npc�� ��ȭ ��û�� ���� ����(�����ÿ� WD_STOP_NTF �� ������.)
//	result : ���� �����
struct stX2G_QT_CHAR_HELLO_NPC_ACK
{
	stX2G_QT_CHAR_HELLO_NPC_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//town npc�� ��ȭ ���� ��û
//	objectindex : ��ȭ ���� npc ����
struct stX2G_QT_CHAR_GOODBYE_NPC_REQ
{
	stX2G_QT_CHAR_GOODBYE_NPC_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Quest npc�� ��ȭ ��û(�ַ� npc���� ��ȭ or ������ ��쿡 ó���ȴ�)
//	_stQuestTalkNpc : Quest npc ����
struct stX2G_QT_CHAR_QUEST_TALK_NPC_REQ
{
	stX2G_QT_CHAR_QUEST_TALK_NPC_REQ()
	{
	}

	std::vector<_stQuestTalkNpc> questnpc;
};


//Quest npc�� ��ȭ ��û�� ���� ����
//	result : ���� �����
struct stX2G_QT_CHAR_QUEST_TALK_NPC_ACK
{
	stX2G_QT_CHAR_QUEST_TALK_NPC_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Quest ���� ��û�� ���� ����
//	_stQuestUpdate : ���ŵ� Quest ����
struct stX2G_QT_CHAR_QUEST_UPDATE_ACK
{
	stX2G_QT_CHAR_QUEST_UPDATE_ACK()
	{
	}

	std::vector<_stQuestUpdate> questdata;
};


//Quest Progress ���� ��û�� ���� ����
//	_stQuestProgressUpdate : ���ŵ� Quest Progress ����
struct stX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK
{
	stX2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK()
	{
	}

	std::vector<_stQuestProgressUpdate> progressdata;
};


//Quest ���� ��û
//	questcode : ���� ���� Quest
//	order : ���� ���� ������ Reward ����(������ ���)
struct stX2G_QT_CHAR_QUEST_REWARD_REQ
{
	stX2G_QT_CHAR_QUEST_REWARD_REQ()
		: questcode(0), order(0)
	{
	}

	QUESTCODE questcode;
	UINT8 order;
};


//Quest ���� ��û�� ���� ����
//	result : ���� �����
//	objectindex : ���� ���� objectindex
//	_stQuestRewardItem : Quest ���� ����
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


//Quest ���� ��û
//	questcode : ������ quest code
struct stX2G_QT_CHAR_QUEST_DELETE_REQ
{
	stX2G_QT_CHAR_QUEST_DELETE_REQ()
		: questcode(0)
	{
	}

	QUESTCODE questcode;
};


//Quest ���� ��û�� ���� ����
//	result : ���� �����
//	questcode : ������ Quest code
struct stX2G_QT_CHAR_QUEST_DELETE_ACK
{
	stX2G_QT_CHAR_QUEST_DELETE_ACK()
		: result(0), questcode(0)
	{
	}

	RESULT_T result;
	QUESTCODE questcode;
};


//mail list ��û
struct stX2G_ML_MAIL_LIST_REQ
{
	stX2G_ML_MAIL_LIST_REQ()
	{
	}

};


//mail list ��û�� ���� ����
//	result : ���� �����
//	_stMailList : mail ����
struct stX2G_ML_MAIL_LIST_ACK
{
	stX2G_ML_MAIL_LIST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<_stMailList> mail;
};


//mail send ��û
//	_stSendMail : ������ mail ����
struct stX2G_ML_SEND_MAIL_REQ
{
	stX2G_ML_SEND_MAIL_REQ()
	{
	}

	std::vector<_stSendMail> sendmail;
};


//mail send ��û�� ���� ����
//	result : ���� �����
struct stX2G_ML_SEND_MAIL_ACK
{
	stX2G_ML_SEND_MAIL_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//���� mail �뺸
//	_stMailList : mail ����
struct stX2G_ML_RECIEVE_MAIL_NTF
{
	stX2G_ML_RECIEVE_MAIL_NTF()
	{
	}

	std::vector<_stMailList> mail;
};


//mail ���� ���� ��û
// _stChangeMailStatus : mail ���� ���� ����
struct stX2G_ML_CHANGE_MAIL_STATUS_REQ
{
	stX2G_ML_CHANGE_MAIL_STATUS_REQ()
	{
	}

	std::vector<_stChangeMailStatus> changemail;
};


//mail ���� ���� ��û�� ���� ����
//	result : ���� �����
//	_stChangeMailStatus : mail ���� ���� ����
//	_stTakeMailItem : mail���� ȸ���� money, ������ ����
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


//���� mail ������ ȸ�� �뺸
//	_stChangeMailStatus : mail ����
//	money : ���� ���� money
//	_stItemData : ȸ���� mail ������ ����
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


//Party ���� ��û
//	objectindex : ��Ƽ�� �ʴ��� ��� object index
struct stX2G_PT_CREATE_PARTY_REQ
{
	stX2G_PT_CREATE_PARTY_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_CREATE_PARTY_ACK
{
	stX2G_PT_CREATE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party ���� ���� �뺸
//	_stCreatePartyBossInfo : boss ����
struct stX2G_PT_CREATE_PARTY_NTF
{
	stX2G_PT_CREATE_PARTY_NTF()
	{
	}

	std::vector<_stCreatePartyBossInfo> bossinfo;
};


//Party ���� ���� ����
//	_stCreatePartyAccept : ���� �����
struct stX2G_PT_CREATE_PARTY_ACCEPT_REQ
{
	stX2G_PT_CREATE_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stCreatePartyAccept> partyaccept;
};


//������ object ���� �뺸(��Ƽ�� �����ɹ����� �뺸)
//	_stPartyChar : ������ ��ü ����
//	_stPartyHiredSoldier : ������ ��ü�� �뺴 ����
struct stX2G_PT_ENTER_PARTY_MEMBER_NTF
{
	stX2G_PT_ENTER_PARTY_MEMBER_NTF()
	{
	}

	std::vector<_stPartyChar> partychar;
	std::vector<_stPartyHiredSoldier> partyhiredsoldier;
};


//Party�� �����ɹ� ���� �뺸(������ �������� �뺸)
//	_stPartyInfo : Party ����
//	_stPartyChar : Party �ɹ� ��ü ����
//	_stPartyHiredSoldier : Party �ɹ� ��ü�� �뺴 ����
struct stX2G_PT_ALL_PARTY_MEMBER_NTF
{
	stX2G_PT_ALL_PARTY_MEMBER_NTF()
	{
	}

	std::vector<_stPartyInfo> partyinfo;
	std::vector<_stPartyChar> partychar;
	std::vector<_stPartyHiredSoldier> partyhiredsoldier;
};


//������ object ���� �뺸(��Ƽ�� �����ɹ����� �뺸)
//	objectindex : ������ ��ü�� �뺴 ����
struct stX2G_PT_LEAVE_PARTY_MEMBER_NTF
{
	stX2G_PT_LEAVE_PARTY_MEMBER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party �Ҹ� ��û
struct stX2G_PT_DELETE_PARTY_REQ
{
	stX2G_PT_DELETE_PARTY_REQ()
	{
	}

};


//Party �Ҹ� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_DELETE_PARTY_ACK
{
	stX2G_PT_DELETE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party �Ҹ� ���� �뺸
struct stX2G_PT_DELETE_PARTY_NTF
{
	stX2G_PT_DELETE_PARTY_NTF()
	{
	}

};


//Party �ʴ� ��û( ������� )
//	objectindex : ��Ƽ�� �ʴ��� ��� object index
struct stX2G_PT_INVITE_PARTY_REQ
{
	stX2G_PT_INVITE_PARTY_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party �ʴ� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_INVITE_PARTY_ACK
{
	stX2G_PT_INVITE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party �ʴ��� ��󿡰� �ʴ� ��û �뺸(���� --> �ʴ��� ���)
//	_stInvitePartyBossInfo : boss ����
struct stX2G_PT_INVITE_PARTY_NTF
{
	stX2G_PT_INVITE_PARTY_NTF()
	{
	}

	std::vector<_stInvitePartyBossInfo> bossinfo;
};


//Party �ʴ� ����
//	_stInvitePartyAccept : ���� �����
struct stX2G_PT_INVITE_PARTY_ACCEPT_REQ
{
	stX2G_PT_INVITE_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stInvitePartyAccept> partyaccept;
};


//Party ���� ��û( �Ϲ� ���� ���� )
//	partyindex : ������ party index
struct stX2G_PT_ENTER_PARTY_REQ
{
	stX2G_PT_ENTER_PARTY_REQ()
		: partyindex(0)
	{
	}

	GAMEOBJECTID partyindex;
};


//Party ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_ENTER_PARTY_ACK
{
	stX2G_PT_ENTER_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party ���忡�� ���� ��û �뺸( �Ϲ����� --> ���� )
struct stX2G_PT_ENTER_PARTY_NTF
{
	stX2G_PT_ENTER_PARTY_NTF()
	{
	}

	std::vector<_stEnterPartyCharInfo> enterobject;
};


//Party ���� ����
//	_stEnterPartyAccept : ���� �����
struct stX2G_PT_ENTER_PARTY_ACCEPT_REQ
{
	stX2G_PT_ENTER_PARTY_ACCEPT_REQ()
	{
	}

	std::vector<_stEnterPartyAccept> partyaccept;
};


//Party Ż�� ��û
struct stX2G_PT_LEAVE_PARTY_REQ
{
	stX2G_PT_LEAVE_PARTY_REQ()
	{
	}

};


//Party Ż�� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_LEAVE_PARTY_ACK
{
	stX2G_PT_LEAVE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party Ż�� �뺸
//	objectindex : Ż���� ��ü ����
struct stX2G_PT_LEAVE_PARTY_NTF
{
	stX2G_PT_LEAVE_PARTY_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party �ɹ� �߹� ��û
//	objectindex : �߹��� ��ü ����
struct stX2G_PT_BANISH_PARTY_MEMBER_REQ
{
	stX2G_PT_BANISH_PARTY_MEMBER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party �ɹ� �߹� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_BANISH_PARTY_MEMBER_ACK
{
	stX2G_PT_BANISH_PARTY_MEMBER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party �ɹ� �߹� �뺸
//	objectindex : �߹�� ��ü ����
struct stX2G_PT_BANISH_PARTY_MEMBER_NTF
{
	stX2G_PT_BANISH_PARTY_MEMBER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party ���� ���� ��û
//	objectindex : ���ο� boss ��ü
struct stX2G_PT_CHANGE_MASTER_REQ
{
	stX2G_PT_CHANGE_MASTER_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party ���� ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_CHANGE_MASTER_ACK
{
	stX2G_PT_CHANGE_MASTER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party ���� ���� �뺸
//	objectindex : ���ο� boss ��ü ����
struct stX2G_PT_CHANGE_MASTER_NTF
{
	stX2G_PT_CHANGE_MASTER_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//Party member OM LINE �뺸
//	_stPartyOnOffLine : ���� ��ü ����
struct stX2G_PT_ONLINE_PARTY_NTF
{
	stX2G_PT_ONLINE_PARTY_NTF()
	{
	}

	std::vector<_stPartyOnOffLine> onoff;
};


//Party member OFF LINE �뺸
//	_stPartyOnOffLine : ���� ���� ��ü ����
struct stX2G_PT_OFFLINE_PARTY_NTF
{
	stX2G_PT_OFFLINE_PARTY_NTF()
	{
	}

	std::vector<_stPartyOnOffLine> onoff;
};


//Party �й� Rule ��û
//	rule : ������ �й� Rule
struct stX2G_PT_CHANGE_DISTRIBUTE_REQ
{
	stX2G_PT_CHANGE_DISTRIBUTE_REQ()
		: rule(0)
	{
	}

	DISTRIBUTE_RULE_T rule;
};


//Party �й� Rule ��û�� ���� ����
//	result : ���� �����
struct stX2G_PT_CHANGE_DISTRIBUTE_ACK
{
	stX2G_PT_CHANGE_DISTRIBUTE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//Party �й� Rule �뺸
//	rule : ����� �й� Rule
struct stX2G_PT_CHANGE_DISTRIBUTE_NTF
{
	stX2G_PT_CHANGE_DISTRIBUTE_NTF()
		: rule(0)
	{
	}

	DISTRIBUTE_RULE_T rule;
};


//Party member �̵� �뺸
//	_stPartyMemberPosition : ��ü�� �̵� ����
struct stX2G_PT_PARTY_MEMBER_MOVE_NTF
{
	stX2G_PT_PARTY_MEMBER_MOVE_NTF()
	{
	}

	std::vector<_stPartyMemberPosition> moveobject;
};


//Party member regen
//	_stPartyMemberRegen : ��ü regen ����
struct stX2G_PT_PARTY_MEMBER_REGEN_NTF
{
	stX2G_PT_PARTY_MEMBER_REGEN_NTF()
	{
	}

	std::vector<_stPartyMemberRegen> partyregen;
};


//Party member damage
//	_stPartyMemberDamage : ��ü damage ����
struct stX2G_PT_PARTY_MEMBER_DAMAGE_NTF
{
	stX2G_PT_PARTY_MEMBER_DAMAGE_NTF()
	{
	}

	std::vector<_stPartyMemberDamage> partydamage;
};


//Party member revival
//	_stPartyMemberRevival : ��ü damage ����
struct stX2G_PT_PARTY_MEMBER_REVIVAL_NTF
{
	stX2G_PT_PARTY_MEMBER_REVIVAL_NTF()
	{
	}

	std::vector<_stPartyMemberRevival> partyrevival;
};


//Party member dead
//	_stPartyMemberDead : ��� ��ü ����
struct stX2G_PT_PARTY_MEMBER_DEAD_NTF
{
	stX2G_PT_PARTY_MEMBER_DEAD_NTF()
	{
	}

	std::vector<_stPartyMemberDead> partydead;
};


//�ŷ� ��û
//	objectindex : �ŷ��� ��� object
struct stX2G_TD_TRADE_REQ
{
	stX2G_TD_TRADE_REQ()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//�ŷ� ��û�� ���� ����
//	result : ���� �����
//	tradeindex : trade index(������)
struct stX2G_TD_TRADE_ACK
{
	stX2G_TD_TRADE_ACK()
		: result(0), tradeindex(0)
	{
	}

	RESULT_T result;
	TRADEINDEX tradeindex;
};


//�ŷ� �뺸
//	_stTradeAsker : �ŷ��� ����
struct stX2G_TD_TRADE_NTF
{
	stX2G_TD_TRADE_NTF()
	{
	}

	std::vector<_stTradeAsker> traderinfo;
};


//�ŷ� ����/�ź�
//	tradeindex : trade index
//	bisenter : 1:����, �׿ܴ� �ź�
struct stX2G_TD_TRADE_ENTER_REQ
{
	stX2G_TD_TRADE_ENTER_REQ()
		: tradeindex(0), bisenter(0)
	{
	}

	TRADEINDEX tradeindex;
	UINT8 bisenter;
};


//�ŷ� ��� ��û(�ŷ��ϷḦ �����Ŀ��� ó���� ���� �ʴ´�.)
struct stX2G_TD_TRADE_CANCEL_REQ
{
	stX2G_TD_TRADE_CANCEL_REQ()
	{
	}

};


//�ŷ� ��� ��û�� ���� ����
//	result : ���� �����
struct stX2G_TD_TRADE_CANCEL_NTF
{
	stX2G_TD_TRADE_CANCEL_NTF()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ� money ���/���� ��û(��� ���Ŀ��� ������/money ��Ϲ� ������ �Ұ����ϴ�.)
//	money :
struct stX2G_TD_TRADE_UPLOAD_MONEY_REQ
{
	stX2G_TD_TRADE_UPLOAD_MONEY_REQ()
		: money(0)
	{
	}

	INT32 money;
};


//�ŷ� money ���/���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_TD_TRADE_UPLOAD_MONEY_ACK
{
	stX2G_TD_TRADE_UPLOAD_MONEY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ� money ���/���� �뺸
//	objectindex : money ��� object
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


//�ŷ� item ��� ��û(��� ���Ŀ��� ������/money ��Ϲ� ������ �Ұ����ϴ�.)
//	itemindex : ��� ������
struct stX2G_TD_TRADE_UPLOAD_ITEM_REQ
{
	stX2G_TD_TRADE_UPLOAD_ITEM_REQ()
		: itemindex(0)
	{
	}

	ITEMINDEX itemindex;
};


//�ŷ� item ��� ��û�� ���� ����(�ڽſ��� �뺸)
//	result : ���� �����
//	itemindex : ��� ������
struct stX2G_TD_TRADE_UPLOAD_ITEM_ACK
{
	stX2G_TD_TRADE_UPLOAD_ITEM_ACK()
		: result(0), itemindex(0)
	{
	}

	RESULT_T result;
	ITEMINDEX itemindex;
};


//�ŷ� item ��� �뺸(���濡�� �뺸)
//	objectindex : item ��� object
//	_stItemData : ��� ������
struct stX2G_TD_TRADE_UPLOAD_ITEM_NTF
{
	stX2G_TD_TRADE_UPLOAD_ITEM_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	std::vector<_stItemData> itemdata;
};


//�ŷ� item ���� ��û(��� ���Ŀ��� ������/money ��Ϲ� ������ �Ұ����ϴ�.)
//	itemindex : ���� ������
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_REQ
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_REQ()
		: itemindex(0)
	{
	}

	ITEMINDEX itemindex;
};


//�ŷ� item ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_ACK
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ� item ���� �뺸
//	objectindex : item ���� object
//	itemindex : ���� ������
struct stX2G_TD_TRADE_DOWNLOAD_ITEM_NTF
{
	stX2G_TD_TRADE_DOWNLOAD_ITEM_NTF()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//�ŷ� ü�� ��û
//	chatmsg : ü��
struct stX2G_TD_TRADE_CHAT_REQ
{
	stX2G_TD_TRADE_CHAT_REQ()
	{
	}

	tstring chatmsg;
};


//�ŷ� ü�� �뺸
//	_stTraderChatData : ü�� ����
struct stX2G_TD_TRADE_CHAT_NTF
{
	stX2G_TD_TRADE_CHAT_NTF()
	{
	}

	std::vector<_stTraderChatData> chatdata;
};


//�ŷ� ��ϿϷ� ��û(��� ���Ŀ��� ������/money ��Ϲ� ������ �Ұ����ϴ�.)
struct stX2G_TD_TRADE_ACCEPT_REQ
{
	stX2G_TD_TRADE_ACCEPT_REQ()
	{
	}

};


//�ŷ� ��ϿϷ� �뺸
//	objectindex : ��� �Ϸ� object
struct stX2G_TD_TRADE_ACCEPT_NTF
{
	stX2G_TD_TRADE_ACCEPT_NTF()
		: objectindex(0)
	{
	}

	GAMEOBJECTID objectindex;
};


//�ŷ��Ϸ� ��û
struct stX2G_TD_TRADE_COMPLETE_REQ
{
	stX2G_TD_TRADE_COMPLETE_REQ()
	{
	}

};


//�ŷ��Ϸ� ��û�� ���� ����
//	result : ���� �����
struct stX2G_TD_TRADE_COMPLETE_ACK
{
	stX2G_TD_TRADE_COMPLETE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ��Ϸ� �뺸
//	objectindex : �ŷ��Ϸ� object
//	itemindex : �ŷ��� ������ ������
struct stX2G_TD_TRADE_COMPLETE_NTF
{
	stX2G_TD_TRADE_COMPLETE_NTF()
		: objectindex(0), itemindex(0)
	{
	}

	GAMEOBJECTID objectindex;
	ITEMINDEX itemindex;
};


//�ŷ���� �뺸(�ŷ��� ����� ������ �����ֿ��� �뺸�Ѵ� - �κ����� �Ұ����� ���� ���������� ���ۿ���)
//	money :
//	_stItemData : �ŷ� ������
struct stX2G_TD_TRADE_LIST_NTF
{
	stX2G_TD_TRADE_LIST_NTF()
		: money(0)
	{
	}

	INT32 money;
	std::vector<_stItemData> itemdata;
};


//��Ÿ�� ��û
//	_stAuctionListRequest : ��� ��� ��û ����
struct stX2G_AU_AUCTION_LIST_REQ
{
	stX2G_AU_AUCTION_LIST_REQ()
	{
	}

	std::vector<_stAuctionListRequest> auctionrequest;
};


//��Ÿ�� ��û�� ���� ����
//	result : ���� �����
struct stX2G_AU_AUCTION_LIST_ACK
{
	stX2G_AU_AUCTION_LIST_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ���� �뺸
//	_stAuctionList : ��� ���
struct stX2G_AU_AUCTION_LIST_NTF
{
	stX2G_AU_AUCTION_LIST_NTF()
	{
	}

	std::vector<_stAuctionList> auctionlist;
};


//��ŵ�� ��û
//	_stAuctionCreate : ��� ��� ����
struct stX2G_AU_AUCTION_CREATE_REQ
{
	stX2G_AU_AUCTION_CREATE_REQ()
	{
	}

	std::vector<_stAuctionCreate> auctioncreate;
};


//��ŵ�� ��û�� ���� ����
//	result : ���� �����
struct stX2G_AU_AUCTION_CREATE_ACK
{
	stX2G_AU_AUCTION_CREATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//��ŵ�� �뺸
//	_stAuctionCreateItem : ��ϵ� ������ ����
struct stX2G_AU_AUCTION_CREATE_NTF
{
	stX2G_AU_AUCTION_CREATE_NTF()
	{
	}

	std::vector<_stAuctionCreateItem> auctionitem;
};


//������� ��û
//	_stAuctionTender : ���� ����
struct stX2G_AU_AUCTION_TENDER_REQ
{
	stX2G_AU_AUCTION_TENDER_REQ()
	{
	}

	std::vector<_stAuctionTender> auctiontender;
};


//������� ��û�� ���� ����
//	result : ���� �����
struct stX2G_AU_AUCTION_TENDER_ACK
{
	stX2G_AU_AUCTION_TENDER_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//�ŷ����� �뺸
//	money : ������ ���� money
struct stX2G_AU_AUCTION_TENDER_NTF
{
	stX2G_AU_AUCTION_TENDER_NTF()
		: money(0)
	{
	}

	INT32 money;
};


//���ȸ�� ��û
//	auctionindex : ��� ����
struct stX2G_AU_AUCTION_RETURN_REQ
{
	stX2G_AU_AUCTION_RETURN_REQ()
	{
	}

	AUCTIONINDEX auctionindex;
};


//���ȸ�� ��û�� ���� ����
//	result : ���� �����
struct stX2G_AU_AUCTION_RETURN_ACK
{
	stX2G_AU_AUCTION_RETURN_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};
