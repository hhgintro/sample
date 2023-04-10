#include "stdafx.h"


// CAccountManager�� �����ϴ� �Լ�
BOOL CAccountManager::Begin(int nMaxUser)
{
	GetAccountPkPool().Begin(nMaxUser);


	////HG[2010.10.26]���� ������ ������.(Dispatch-> �������� �ȵ�)
	////���߾����带 �����ϱ�. LuaScript���� �ٿ�Ǵ� ����߻�
	////�켱 ���� ������� ������ ���� ������ �����Ѵ�.
	////SYSTEM_INFO SystemInfo;
	////GetSystemInfo(&SystemInfo);
	//CThread::BeginThread(1);//SystemInfo.dwNumberOfProcessors);

	return TRUE;
}

// RemoteSessionManager�� �����ϴ� �Լ�
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
//	// ���ӵǾ� �ִ� ��ü�� ���
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
	���� ���Ӵܰ� - accountid�� ��ϵ� ���� �ִ��� Ȯ���ϰ�
		- ������ host�� �׳� �־��ְ�
		- ���ٸ� Accountpool�� �����ؼ� host�� �־��ְ�, ���� avatar�� avatarpool�� �־��ش�AVATAR_BASE_POOL

	���� ���� ����
		- AccountPool �� AvatarPool���� host������ �����ְ�, hostpool������ �����.

	�����ð��� ���� ��쿡(game���� ó������, DBcache���� ó������ �����)
		- Accountpool�� avatarpool�� �����ش�.
			
*/

//ó�� �����ϴ� �����̸�
//	Accountpool�� �����ؼ� host�� �־��ְ�, ���� avatar�� avatarpool�� �־��ش�
// ���� : �ű������̸� TRUE, ������(�޸𸮿� �־�����)�̸� FALSE
BOOL CAccountManager::NewJoin(IN HOSTID remote, IN ACCOUNTPK accountpk, IN const std::wstring& accountid, OUT CAccountData** account)
{
	//// Ŭ���̾�Ʈ ip ���� ���ڿ� �б�
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


	//�������ϸ� �޸� ���� event�� ������ �־�� ����.
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
//	//CAccountData�� �־��ش�.
//	account->GetAvatarPool().Insert(avatarpk, avatar);
//	return avatar;
//}
//
////projectB
//
////���������� ��쿡�� �޸𸮿��� �����Ⱓ ����Ÿ�� ������ �ִ´�.(���� ���� ���ῡ ���)
//CAvatarData* CAccountManager::FindNick(const Proud::String& nickname)
//{
//	CAvatarData* avatar = GetAccountIDPool().Find(nickname);
//	if(NULL == avatar)		return NULL;
//
//	//if(avatar != GetOwner()->GetSelectedAvatar())
//	//{
//	//	//NOTIFY_SYSTEM_LOG("HG_GREEN", _T("����� ���� ������ �ɱ��? (%s:%d) "), Proud::StringA2W(__FUNCTION__), __LINE__);
//	////���� ���ѻ����� �ƹ�Ÿ�� �����ϴ� ��쵵 ���� �մϴ�.
//	////	return NULL;
//	//}
//	return avatar;
//}
//
////���������� ��쿡�� �޸𸮿��� �����Ⱓ ����Ÿ�� ������ �ִ´�.(���� ���� ���ῡ ���)
//CAvatarData* CAccountManager::FindPK(AVATARPK avatarpk)
//{
//	CAvatarData* avatar = GetAvatarPool().Find(avatarpk);
//	if(NULL == avatar)		return NULL;
//	//if(avatar != GetOwner()->GetSelectedAvatar())
//	//{
//	//	//NOTIFY_SYSTEM_LOG("HG_GREEN", _T("����� ���� ������ �ɱ��? (%s:%d) "), Proud::StringA2W(__FUNCTION__), __LINE__);
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

	//party ����
	if (NULL != account->GetParty())
		account->GetParty()->LeaveParty(account);

	//��(����) ����
	if (NULL != account->GetRoom())
		account->GetRoom()->LeaveRoom(account);

	GetAccountIDPool().Erase(account->GetAccountID());
	GetAccountPkPool().Erase(account->GetAccountPK());
	GetHostIDPool().Erase(account->GetHostID());
}

void CAccountManager::RemoveAccount(CAccountData* account)
{
	if(NULL == account)		return;

	//������ ������ �������� ����ϴ�.
	//RemoveItemAll(account);


	////�ƹ�Ÿ�� �����.
	//std::vector<CAvatarData*> vecAll;
	//account->GetAvatarPool().GetAllList(vecAll);
	//for(int i=0; i<(int)vecAll.size(); ++i)
	//{
	//	CAvatarData* avatar = vecAll[i];
	//	if(NULL == avatar)	continue;

	//	//����� ���翡 üũ�� ���ǹ���.
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
//	//�ƹ�Ÿ�� ������ �������� ����ϴ�.
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
//	//�ƹ�Ÿ�� ����ϴ�.
//	GetAvatarPool().Erase(avatar->GetAvatarPk());
//	GetAccountIDPool().Erase(avatar->GetNickname());
//
//
//
//	//account���� �����ش�.
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
//	//weapon�� ����ϴ�.
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
//	//ability �߰�(level�� ���հ���)
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