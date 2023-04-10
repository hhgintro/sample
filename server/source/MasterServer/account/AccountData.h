#pragma once

class CParty;
class CRoom;
class CAccountData// : public IGameObject, public IInvenObject, public IMoneyObject, public IScheduler
{
	//typedef CMemoryPool<AVATARPK, CAvatarData> AVATAR_POOL;
	//typedef CMemoryPool<WEAPONPK, CWeapon> WEAPON_POOL;
	//typedef CMemoryPool<WEAPONGROUP, CWeapon> WEAPON_GROUP_POOL;
	//typedef CMemoryPool<SHOPCODE, SHOPCODE>			SHOPCASH_FIRST_BUY_POOL;	//현금상점 처음 구매 정보
	//typedef CMemoryPool<SHOPCODE, _stShopCash_Monthly> SHOPCASH_MONTHLY_POOL;	//월정액 구매 정보
	//typedef CMemoryPool<GACHACODE, _stGacha_Free> GACHA_FREE_POOL;				//가챠 무료 시간 풀

public:
	CAccountData(void);
	virtual ~CAccountData(void);

	virtual void Begin();
	virtual void End();

	virtual void Clear();
	//virtual void Update();

	//virtual OBJECT_TYPE_T GetObjectType() { return eObject_Type_Account; }

	HOSTID GetHostID() { return m_remote; }
	void SetHostID(HOSTID remote) { m_remote = remote; }

	ACCOUNTPK GetAccountPK() { return m_accountpk; }
	void SetAccountPK(ACCOUNTPK pk) { m_accountpk = pk; }

	std::wstring GetAccountID() { return m_accountid; }
	void SetAccountID(std::wstring id) { m_accountid = id; }

	//ROOMINDEX GetRoomIndex() { return m_roomindex; }
	//void SetRoomIndex(ROOMINDEX index) { m_roomindex = index; }
	CParty* GetParty() { return m_party; }
	void SetParty(CParty* party) { m_party = party; }

	CRoom*	GetRoom() { return m_room; }
	void SetRoom(CRoom* room) { m_room = room; }

	//CRoom*	GetWaiginRoom() { return m_waiting; }
	//void SetWaitinRoom(CRoom* room) { m_waiting = room; }

	stInven& GetInven() { return m_inven; }
	void SetInven(stInven& inven) { m_inven = inven; }

private:
	HOSTID			m_remote;
	ACCOUNTPK		m_accountpk;			//계정pk
	std::wstring	m_accountid;

	//ROOMINDEX		m_roomindex;		//입장한 방 번호
	CParty*			m_party;
	CRoom*			m_room;				//입장한 방(광장포함)
	//CRoom*			m_waiting;			//입장한 대기방

	stInven			m_inven;
};
