#pragma once

//class CAvatarInfo;
//class CAccountInfo;

// Connected Session�� �����ϴ� Ŭ����
// ���� ������ ȯ�濡�� �����ϰ� ����ϱ� ���ؼ� CMultiThreadSync�� ��ӹ޽��ϴ�.
class CAccountManager : /*public HisUtil::CThread,*/ public HisUtil::CSingleton<CAccountManager>// : public CMultiThreadSync<CAccountManager>
{
public:
	typedef HisUtil::CMemoryPool<ACCOUNTPK, CAccountData>			ACCOUNTPK_POOL;
	typedef HisUtil::CMemoryPool<std::wstring, CAccountData>		ACCOUNTID_POOL;
	typedef HisUtil::CMemoryPool<HOSTID, CAccountData>				HOSTID_POOL;

public:
	CAccountManager(VOID) {}
	virtual ~CAccountManager(VOID) {}

	// �����ϴ� �Լ�
	BOOL Begin(int nMaxUser);
	// �����ϴ� �Լ�
	VOID End(VOID);
	//void Update(); //private ���� �ű�.

	// ���Ӽ��� ������
	//void OnWorkerThread(int index);

	/*
		���� ���Ӵܰ� - accountid�� ��ϵ� ���� �ִ��� Ȯ���ϰ�
			- ������ host�� �׳� �־��ְ�
			- ���ٸ� Accountpool�� �����ؼ� host�� �־��ְ�, ���� avatar�� avatarpool�� �־��ش�AVATAR_BASE_POOL

		���� ���� ����
			- AccountPool �� AvatarPool���� host������ �����ְ�, hostpool������ �����.

		�����ð��� ���� ��쿡(game���� ó������, DBcache���� ó������ �����)
			- Accountpool�� avatarpool�� �����ش�.
			
	*/

	CAccountData* Find(ACCOUNTPK accountpk) { return GetAccountPkPool().Find(accountpk); }
	CAccountData* Find(std::wstring accountid) { return GetAccountIDPool().Find(accountid); }






	////���� ���� Ŭ����
	ACCOUNTPK_POOL& GetAccountPkPool()	{ return m_poolAccountPk; }		//���������� ����Ѵ�
	ACCOUNTID_POOL& GetAccountIDPool()	{ return m_poolAccountID; }
	HOSTID_POOL& GetHostIDPool()		{ return m_poolHostID; }
	////..//���� ���� Ŭ����



	BOOL NewJoin(IN HOSTID remote, IN ACCOUNTPK accountpk, IN const std::wstring& accountid, OUT CAccountData** account);		//ó�� �����Ҷ�
	BOOL ReJoin(IN HOSTID remote, CAccountData* account);
	//CAvatarData* CreateAvatar(IN CAccountData* account, AVATARPK avatarpk, AVATARCODE avatarcode, const Proud::String& nickname);	//�ƹ�Ÿ load/ ������ ȣ��

	void RemoveAccount(HOSTID remote);
	void RemoveAccount(CAccountData* account);		//���������� �����ð��� ������ �������� �ڵ� ȣ���
	//void RemoveAvatar(CAccountData* account, CAvatarData* avatar);
	//void RemoveAvatar(CAccountData* account, AVATARPK avatarpk);
	//void RemoveWeapon(CAccountData* account, CWeapon* weapon);


	//void MakeAccountInfo(IN CAccountData* account, OUT _stAccountInfo& info);
	//void MakeAvartarInfo(IN CAvatarData* avatar, OUT _stAvatarInfo_DB& info);

private:
	void Update();


private:

	//���� ���� Ŭ����
	ACCOUNTPK_POOL		m_poolAccountPk;		//���������� ����Ѵ�.
	ACCOUNTID_POOL		m_poolAccountID;
	HOSTID_POOL			m_poolHostID;
	//..//���� ���� Ŭ����


	//Proud::CriticalSection m_cs;

};

//#define ACCOUNTMANAGER		CAccountManager::Instance()

