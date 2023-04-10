#pragma once

//class CAvatarInfo;
//class CAccountInfo;

// Connected Session을 관리하는 클래스
// 다중 스레드 환경에서 안전하게 사용하기 위해서 CMultiThreadSync를 상속받습니다.
class CAccountManager : /*public HisUtil::CThread,*/ public HisUtil::CSingleton<CAccountManager>// : public CMultiThreadSync<CAccountManager>
{
public:
	typedef HisUtil::CMemoryPool<ACCOUNTPK, CAccountData>			ACCOUNTPK_POOL;
	typedef HisUtil::CMemoryPool<std::wstring, CAccountData>		ACCOUNTID_POOL;
	typedef HisUtil::CMemoryPool<HOSTID, CAccountData>				HOSTID_POOL;

public:
	CAccountManager(VOID) {}
	virtual ~CAccountManager(VOID) {}

	// 시작하는 함수
	BOOL Begin(int nMaxUser);
	// 종료하는 함수
	VOID End(VOID);
	//void Update(); //private 으로 옮김.

	// 게임서버 쓰레드
	//void OnWorkerThread(int index);

	/*
		유저 접속단계 - accountid로 등록된 것이 있는지 확인하고
			- 있으면 host를 그냥 넣어주고
			- 없다면 Accountpool을 생성해서 host를 넣어주고, 하위 avatar도 avatarpool에 넣어준다AVATAR_BASE_POOL

		유저 접속 종료
			- AccountPool 과 AvatarPool에서 host정보를 지워주고, hostpool에서도 지운다.

		일정시간이 지난 경우에(game에서 처리할지, DBcache에서 처리할지 고심중)
			- Accountpool과 avatarpool도 지워준다.
			
	*/

	CAccountData* Find(ACCOUNTPK accountpk) { return GetAccountPkPool().Find(accountpk); }
	CAccountData* Find(std::wstring accountid) { return GetAccountIDPool().Find(accountid); }






	////유저 관리 클래스
	ACCOUNTPK_POOL& GetAccountPkPool()	{ return m_poolAccountPk; }		//유저생성을 담당한다
	ACCOUNTID_POOL& GetAccountIDPool()	{ return m_poolAccountID; }
	HOSTID_POOL& GetHostIDPool()		{ return m_poolHostID; }
	////..//유저 관리 클래스



	BOOL NewJoin(IN HOSTID remote, IN ACCOUNTPK accountpk, IN const std::wstring& accountid, OUT CAccountData** account);		//처음 접속할때
	BOOL ReJoin(IN HOSTID remote, CAccountData* account);
	//CAvatarData* CreateAvatar(IN CAccountData* account, AVATARPK avatarpk, AVATARCODE avatarcode, const Proud::String& nickname);	//아바타 load/ 생성시 호출

	void RemoveAccount(HOSTID remote);
	void RemoveAccount(CAccountData* account);		//접속종료후 일정시간이 지나면 서버에서 자동 호출됨
	//void RemoveAvatar(CAccountData* account, CAvatarData* avatar);
	//void RemoveAvatar(CAccountData* account, AVATARPK avatarpk);
	//void RemoveWeapon(CAccountData* account, CWeapon* weapon);


	//void MakeAccountInfo(IN CAccountData* account, OUT _stAccountInfo& info);
	//void MakeAvartarInfo(IN CAvatarData* avatar, OUT _stAvatarInfo_DB& info);

private:
	void Update();


private:

	//유저 관리 클래스
	ACCOUNTPK_POOL		m_poolAccountPk;		//유저생성을 담당한다.
	ACCOUNTID_POOL		m_poolAccountID;
	HOSTID_POOL			m_poolHostID;
	//..//유저 관리 클래스


	//Proud::CriticalSection m_cs;

};

//#define ACCOUNTMANAGER		CAccountManager::Instance()

