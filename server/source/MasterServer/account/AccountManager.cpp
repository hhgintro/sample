#include "stdafx.h"


// CAccountManager를 시작하는 함수
BOOL CAccountManager::Begin(int nMaxUser)
{
	GetAccountPkPool().Begin(nMaxUser);


	////HG[2010.10.26]다중 돌리지 마세요.(Dispatch-> 때문에라도 안됨)
	////다중쓰레드를 돌리니깐. LuaScript에서 다운되는 현상발생
	////우선 단일 쓰레드로 돌리고 차후 적용을 검토한다.
	////SYSTEM_INFO SystemInfo;
	////GetSystemInfo(&SystemInfo);
	//CThread::BeginThread(1);//SystemInfo.dwNumberOfProcessors);

	return TRUE;
}

// RemoteSessionManager를 종료하는 함수
VOID CAccountManager::End(VOID)
{
	//CThread::EndThread();

	GetAccountPkPool().End();
	GetAccountIDPool().End();
	GetHostIDPool().End();
	//GetAvatarPool().End();

	//GetAvatarBasePool().End();
}


//void CAccountManager::Update()
//{
//	// 접속되어 있는 개체일 경우
//	std::vector<CAccountData*> vecAll;
//	GetAccountPkPool().GetAllList(vecAll);
//	for(int i=0; i<(int)vecAll.size(); ++i)
//	{
//		CAccountData* account = vecAll[i];
//		if(NULL == account)
//			continue;
//
//		account->Update();
//	}
//}



//void CAccountManager::OnWorkerThread(int index)
//{
//	DBG_UNREFERENCED_PARAMETER(index);
//	while(TRUE == IsRunning())
//	{
//		Sleep(1);
//
//		Update();
//	}//..while(TRUE == IsRunning())
//}


/*
	유저 접속단계 - accountid로 등록된 것이 있는지 확인하고
		- 있으면 host를 그냥 넣어주고
		- 없다면 Accountpool을 생성해서 host를 넣어주고, 하위 avatar도 avatarpool에 넣어준다AVATAR_BASE_POOL

	유저 접속 종료
		- AccountPool 과 AvatarPool에서 host정보를 지워주고, hostpool에서도 지운다.

	일정시간이 지난 경우에(game에서 처리할지, DBcache에서 처리할지 고심중)
		- Accountpool과 avatarpool도 지워준다.
			
*/

//처음 접속하는 유저이면
//	Accountpool을 생성해서 host를 넣어주고, 하위 avatar도 avatarpool에 넣어준다
// 리턴 : 신규접속이면 TRUE, 재접속(메모리에 있었으면)이면 FALSE
BOOL CAccountManager::NewJoin(IN HOSTID remote, IN ACCOUNTPK accountpk, IN const std::wstring& accountid, OUT CAccountData** account)
{
	//// 클라이언트 ip 정보 문자열 읽기
	//Proud::CNetClientInfo clientinfo;
	//CServerApp::Instance().GetServer().m_netServer->GetClientInfo(remote, clientinfo);
	//Proud::String& userip = clientinfo.m_TcpAddrFromServer.ToString();

	*account = Find(accountpk);
	if(NULL == *account)
	{
		(*account) = GetAccountPkPool().Create();
		(*account)->Clear();

		(*account)->SetHostID(remote);
		(*account)->SetAccountPK(accountpk);
		(*account)->SetAccountID(accountid);
		GetAccountPkPool().Insert(accountpk, (*account));

		GetAccountIDPool().Insert(accountid, (*account));
		GetHostIDPool().Insert(remote, (*account));
	}
	else
	{
		LOGEVENT("HG_YELLOW", L"remote : 0x%08x --> 0x%08x", (*account)->GetHostID(), remote);
		ReJoin(remote, *account);
	}


	//재접속하면 메모리 삭제 event는 제거해 주어야 겠음.
	//(*account)->LoginAccount();

	return TRUE;
}

BOOL CAccountManager::ReJoin(IN HOSTID remote, CAccountData* account)
{
	//old - disconnect
	CWorld::Instance().GetServer().ProcessDisconnect(account->GetHostID());
	GetHostIDPool().Erase(account->GetHostID());
	LOGEVENT("HG_RED", L"remote change 0x%08x --> 0x%08x", account->GetHostID(), remote);
	//new
	GetHostIDPool().Insert(remote, account);
	account->SetHostID(remote);
	return TRUE;
}

//CAvatarData* CAccountManager::CreateAvatar(IN CAccountData* account, AVATARPK avatarpk, AVATARCODE avatarcode, const Proud::String& nickname)
//{
//	//base
//	_stAvatarBase* base = GetAvatarBasePool().Find(avatarcode);
//	if(NULL == base)		return NULL;
//
//	CAvatarData* avatar = GetAvatarPool().Find(avatarpk);
//	if(NULL != avatar)		return avatar;
//
//
//	avatar = GetAvatarPool().Create();
//	//setting...
//	avatar->Clear();
//	avatar->SetOwner(account);
//	avatar->SetBase(base);
//	avatar->SetAvatarPk(avatarpk);
//	avatar->SetAvatarCode(avatarcode);
//	avatar->SetNickname(nickname);
//
//	GetAvatarPool().Insert(avatarpk, avatar);
//	GetAccountIDPool().Insert(nickname, avatar);
//
//	//CAccountData에 넣어준다.
//	account->GetAvatarPool().Insert(avatarpk, avatar);
//	return avatar;
//}
//
////projectB
//
////접속종료한 경우에도 메모리에서 일정기간 데이타를 가지고 있는다.(잦은 접속 종료에 대비)
//CAvatarData* CAccountManager::FindNick(const Proud::String& nickname)
//{
//	CAvatarData* avatar = GetAccountIDPool().Find(nickname);
//	if(NULL == avatar)		return NULL;
//
//	//if(avatar != GetOwner()->GetSelectedAvatar())
//	//{
//	//	//NOTIFY_SYSTEM_LOG("HG_GREEN", _T("여기는 언제 들어오는 걸까요? (%s:%d) "), Proud::StringA2W(__FUNCTION__), __LINE__);
//	////접속 안한상태의 아바타를 접근하는 경우도 존재 합니다.
//	////	return NULL;
//	//}
//	return avatar;
//}
//
////접속종료한 경우에도 메모리에서 일정기간 데이타를 가지고 있는다.(잦은 접속 종료에 대비)
//CAvatarData* CAccountManager::FindPK(AVATARPK avatarpk)
//{
//	CAvatarData* avatar = GetAvatarPool().Find(avatarpk);
//	if(NULL == avatar)		return NULL;
//	//if(avatar != GetOwner()->GetSelectedAvatar())
//	//{
//	//	//NOTIFY_SYSTEM_LOG("HG_GREEN", _T("여기는 언제 들어오는 걸까요? (%s:%d) "), Proud::StringA2W(__FUNCTION__), __LINE__);
//	//	return NULL;
//	//}
//	return avatar;
//}

void CAccountManager::RemoveAccount(HOSTID remote)
{
	CAccountData* account = GetHostIDPool().Find(remote);
	if (NULL == account)
	{
		LOGEVENT("HG_WHITE", _T("not found AccountData(remote:%x)"), remote);
		return;
	}

	//party 퇴장
	if (NULL != account->GetParty())
		account->GetParty()->LeaveParty(account);

	//방(광장) 퇴장
	if (NULL != account->GetRoom())
		account->GetRoom()->LeaveRoom(account);

	GetAccountIDPool().Erase(account->GetAccountID());
	GetAccountPkPool().Erase(account->GetAccountPK());
	GetHostIDPool().Erase(account->GetHostID());
}

void CAccountManager::RemoveAccount(CAccountData* account)
{
	if(NULL == account)		return;

	//계정이 소지한 아이템을 지웁니다.
	//RemoveItemAll(account);


	////아바타를 지운다.
	//std::vector<CAvatarData*> vecAll;
	//account->GetAvatarPool().GetAllList(vecAll);
	//for(int i=0; i<(int)vecAll.size(); ++i)
	//{
	//	CAvatarData* avatar = vecAll[i];
	//	if(NULL == avatar)	continue;

	//	//지우는 마당에 체크는 무의미함.
	//	//if(FALSE == avatar->GetIsConnected())
	//	//	continue;

	//	RemoveAvatar(account, avatar);
	//}
	GetAccountIDPool().Erase(account->GetAccountID());
	GetAccountPkPool().Erase(account->GetAccountPK());
	GetHostIDPool().Erase(account->GetHostID());
}

//void CAccountManager::RemoveAvatar(CAccountData* account, CAvatarData* avatar)
//{
//	if(NULL == avatar || NULL == account)
//		return;
//
//
//	//아바타가 소지한 아이템을 지웁니다.
//	//RemoveItemAll(avatar);
//
//	std::vector<CWeapon*> vecAll;
//	account->GetWeaponPool().GetAllList(vecAll);
//	for(CWeapon* weapon : vecAll)
//	{
//		if(NULL == weapon)	continue;
//
//		RemoveWeapon(account, weapon);
//	}
//
//	//아바타를 지웁니다.
//	GetAvatarPool().Erase(avatar->GetAvatarPk());
//	GetAccountIDPool().Erase(avatar->GetNickname());
//
//
//
//	//account에서 지워준다.
//	account->GetAvatarPool().Erase(avatar->GetAvatarPk());
//}
//
//void CAccountManager::RemoveAvatar(CAccountData* account, AVATARPK avatarpk)
//{
//	if(NULL == account)	return;
//
//	CAvatarData* avatar = account->GetAvatarPool().Find(avatarpk);
//	if(NULL == avatar)		return;
//
//	RemoveAvatar(account, avatar);
//}
//
//void CAccountManager::RemoveWeapon(CAccountData * account, CWeapon* weapon)
//{
//	if(NULL == account || NULL == weapon)
//		return;
//	
//	//weapon을 지웁니다.
//	account->GetWeaponPool().Erase(weapon->GetWeaponPk());
//}
//
//
//void CAccountManager::MakeAccountInfo(IN CAccountData* account, OUT _stAccountInfo& info)
//{
//	info.m_accountpk	= account->GetAccountPk();
//	info.m_accountid	= account->GetAccountID();
//
//	//info.m_super		= account->GetSuperMan();
//	info.m_avatars		= account->GetMaxAvatarSlot();
//	info.m_inven		= account->GetMaxInvenSlot();
//	info.m_vip			= account->GetVip();
//
//	info.m_lastattend	= account->GetLastAttend();
//	info.m_attendcount	= account->GetAttendCount();
//	info.m_clearTower	= account->GetClearTowerID();
//
//	info.m_money		= account->Get_Gold();
//	info.m_cash			= account->Get_Cash();
//	info.m_heart		= account->Get_Heart();
//	info.m_babel		= account->Get_Babel();
//	info.m_explore		= account->Get_Explore();
//	info.m_raid			= account->Get_Raid();
//	info.m_pvp			= account->Get_PvP();
//
//}
//
//void CAccountManager::MakeAvartarInfo(IN CAvatarData* avatar, OUT _stAvatarInfo_DB& info)
//{
//	info.m_avatarPk		= avatar->GetAvatarPk();
//	info.m_avatarcode	= avatar->GetAvatarCode();
//	info.m_nickname		= avatar->GetNickname();
//	info.m_slot			= avatar->GetAvatarSlot();
//
//	info.m_equip		= avatar->GetMaxEquipSlot();
//	info.m_weapon		= avatar->GetMaxWeaponSlot();
//	//info.m_inven = avatar->GetMaxInvenSlot();
//
//	info.m_level		= avatar->GetLevel();
//	info.m_exp			= avatar->GetExp();
//	info.m_RaidLevel	= avatar->GetRaidLevel();
//	info.m_RaidExp		= avatar->GetRaidExp();
//	info.m_PvpLevel		= avatar->GetPvpLevel();
//	info.m_PvpExp		= avatar->GetPvpExp();
//
//	//ability 추가(level로 조합가능)
//	//info.m_hp = avatar->GetHp();
//	////info.m_ability.m_hp = avatar->GetHp();	
//	////info.m_ability.m_maxhp = avatar->GetMaxHp();	
//	////info.m_ability.m_attack = avatar->GetAttack();
//	////info.m_ability.m_defense = avatar->GetDefense();
//	////info.m_ability.m_ratioCritical = avatar->GetRatioCritical();
//	////info.m_ability.m_critical = avatar->GetCritical();
//	////info.m_ability.m_ratioAvoid = avatar->GetRatioAvoid();
//
//}