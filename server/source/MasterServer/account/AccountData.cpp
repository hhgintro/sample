#include "StdAfx.h"
#include "AccountData.h"

CAccountData::CAccountData(void)
	//: IGameObject(), IInvenObject()
	: m_accountpk(0), m_accountid(L""), m_party(NULL), m_room(NULL)
{}

CAccountData::~CAccountData(void)
{}

void CAccountData::Begin()
{
	Clear();
}

void CAccountData::End()
{
}

void CAccountData::Clear()
{
	m_accountpk = 0;
	m_accountid = L"";

	m_party = NULL;
	m_room = NULL;

	m_inven.Clear();
}

//void CAccountData::Update()
//{
//}

//리턴 : TRUE이면 신규접속
//BOOL CAccountData::LoginAccount()
//{
//	//Proud::CriticalSectionLock lock(m_csLogin, true);
//
//
//	////계정 메일은 접속할 때마다 받기 위해서 처리합니다.
//	//GetMailManager().Clear();
//	//SetIsLoadMailList(FALSE);
//
//
//	//(*account)->SetDisconnectedTime(GetTickCount64());	//접속 종료시간
//	//m_userIp = userip;
//	//m_marketLogin = market;//접속할때마다 달라질수 있다.
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T(" ------------------ 동접자수 %d"), GetHostPool().GetUsedMemSize());
//
//	//return bNewJoin;
//	return TRUE;
//}

//void CAccountData::LogoutAccount()
//{
//	//account의 게임정보를 DB에 기록합니다.
//	SaveGameData2DB();
//
//	LOGEVENT("HG_YELLOW", _T("accountpk[0x%x] Connected FALSE"), this->GetAccountPk());
//	//SetDisconnectedTime(GetTickCount64());	//접속 종료시간
//	//SetIsMasterReg(FALSE);
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T("Account(%s), Host(%d) : CAccountData::LogoutAccount()::SetIsMasterReg(FALSE);"), Proud::StringA2W(m_accountinfo.m_accountid).GetString(), remote);
//	//SetSelectedAvatar(NULL);
//	//HG_성능QA동안 주석처리
//	//NOTIFY_SYSTEM_LOG("HG_YELLOW", _T(" ** account[%s] 접속 종료"), GetNickname().GetString());
//
//
//	////master서버에 통보한다.
//	//CServerApp::Instance().GetMasterNetClient()->m_csProxy.RequestLogout(Proud::HostID_Server, Proud::RmiContext::ReliableSend
//	//	, m_accountinfo.m_accountid, remote);
//
//	//// 넷마블 로그 
//	//CNetMarbleLog::Instance().AccountLog( m_accountinfo.m_accountid, m_szChannelCode, m_userIp, false );
//
//
//	//메모리 삭제 이벤트 등록
//	//Insert(eSchedule_AccountRemove, CParam::Instance().account_caching_mem_release_delay_time);
//
//
//	////메모리에서 삭제...
//	////tick을 넘겨서 처리될 시점이 맞는지 체크합니다.
//	////(여러번 재접속이 진행된 경우, 마지막 접속종료될 때에 이전에 접속종료된 telegram에 의해 remove처리될 수 있다)
//	//Dispatch.Dispatch_Message(ACCOUNT_REMOVE_DELAY_TIME, this, this, eAccount_Remove, (void*)GetDisconnectedTime(), NULL);
//	////Dispatch.Dispatch_Message(TIME_SEC(60), account, account, eAccount_Remove, (void*)account->GetDisconnectedTime(), NULL);
//}


////bImmediately : TRUE이면 즉시 DB에 기록한다. FALSE이면 일정시간 이후에 저장이 가능하다.
//void CAccountData::SaveGameAvatar(CAvatarData* avatar)//, BOOL bImmediately)
//{
//	if(NULL == avatar)
//		return;
//
//	//if(NULL == GetUpdateAvatarPool().Find(avatar->GetAvatarPk()))
//	//	return;	//변경사항 없으니 무시.
//
//
//	//avatar의 게임정보를 DB에 기록합니다.
//	avatar->SaveGameData2DB();//bImmediately);
//
//
//	//메일 로딩에 대한 판별자를 이곳에서 초기화 해 줍니다.
//	//avatar->SetIsLoadMailList(FALSE);
//
//
//	//HG_성능QA동안 주석처리
//	//NOTIFY_SYSTEM_LOG("HG_WHITE", _T(" 접속중인 avatar[%s]를 world에서 뺍니다."), avatar->GetNickname().GetString());
//
//	////삭제
//	//GetUpdateAvatarPool().Erase(avatar->GetAvatarPk());
//}
//
////account의 게임정보를 DB에 기록합니다.
////bImmediately : TRUE이면 즉시 DB에 기록한다. FALSE이면 일정시간 이후에 저장이 가능하다.
//void CAccountData::SaveGameData2DB()
//{
//	////접속종료일때는 시간체크를 하지 않는다.
//	//TIME_T cur = GetTickCount64();
//	//if(FALSE == bImmediately && cur < m_saveDBtime)
//	//	return;
//	//m_saveDBtime = cur + CParam::Instance().avatar_db_save_update_time;
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T("  account(%s) DB saving."), GetAccountID().GetString());
//
//
//	SaveGameAvatar(GetSelectedAvatar());
//	SetSelectedAvatar(NULL);//재접속시 이전 avatar정보 DB update 방지.
//
//	// 데이타 저장
//	SaveGameData2DB_Account();
//
//	//인벤 업데이트
//	//SaveGameData2DB_Item();
//
//	//재료아이템 업데이트
//	//SaveGameData2DB_Material();
//}
//
//void CAccountData::SaveGameData2DB_Account()
//{
//	CDBManager::Instance().UpdateAccount(this);
//}
//
////void CAccountData::SaveGameData2DB_Item()
////{
////	std::vector<CItemCard*> vecAll;
////	GetUpdateInventoryPool().GetAllList(vecAll);
////	for(CItemCard* itemcard : vecAll)
////	{
////		if(NULL == itemcard)	continue;
////
////		//DB에 업데이트
////		CDBManager::Instance().UpdateItemCard(this, itemcard);
////	}
////
////	GetUpdateInventoryPool().End();
////}
//
//
//
//void CAccountData::HandleSchedule( const _stSchedule& schedule )
//{
//	switch (schedule.m_type)
//	{
//	case eSchedule_AccountLogout:
//
//		if(TRUE == GetIsConnected())
//		{
//			break;
//		}
//		
//		NOTIFY_SYSTEM_LOG("HG_MAGENTA", _T("LogoffEvent : accountpk[0x%x]"), GetAccountPk());
//		LogoutAccount();
//
//		break;
//	case eSchedule_AccountRemove:
//
//		if(TRUE == GetIsConnected())
//		{
//			break;
//		}
//		
//		NOTIFY_SYSTEM_LOG("HG_MAGENTA", _T("RemoveEvent : accountpk[0x%x]"), GetAccountPk());
//		//User서버에 노티해준다.
//		CServerApp::Instance().GetMasterNetClient()->m_User2DBProxy.NotifyAccountRemove(CServerApp::Instance().GetServerManager().GetRemoteUser(), Proud::RmiContext::ReliableSend
//			, GetAccountPk());
//
//		CAccountManager::Instance().RemoveAccount(this);
//		break;
//	default:
//		break;
//	}
//}
//
//
//GAME_RESULT CAccountData::Add_Gold(MONEY_T price)
//{
//	MONEY_T old = Get_Gold();
//
//	GAME_RESULT result = IMoneyObject::Add_Gold(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Add_Gold(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Add_Gold(%d) = old(%d) + add(%d)"), Get_Gold(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Add_Cash(MONEY_T price)
//{
//	MONEY_T old = Get_Cash();
//
//	GAME_RESULT result = IMoneyObject::Add_Cash(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Add_Cash(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Add_Cash(%d) = old(%d) + add(%d)"), Get_Cash(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Add_Heart(HEART_T price)
//{
//	HEART_T old = Get_Heart();
//
//	GAME_RESULT result = IMoneyObject::Add_Heart(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Add_Heart(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Add_Heart(%d) = old(%d) + add(%d)"), Get_Heart(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Add_Babel(STAMINA_T price)
//{
//	STAMINA_T old = Get_Babel();
//
//	GAME_RESULT result = IMoneyObject::Add_Babel(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Add_Babel(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Add_Babel(%d) = old(%d) + add(%d)"), Get_Babel(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Add_Raid(STAMINA_T price)
//{
//	STAMINA_T old = Get_Raid();
//
//	GAME_RESULT result = IMoneyObject::Add_Raid(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Add_Raid(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Add_Raid(%d) = old(%d) + add(%d)"), Get_Raid(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Sub_Gold(MONEY_T price)
//{
//	MONEY_T old = Get_Gold();
//
//	GAME_RESULT result = IMoneyObject::Sub_Gold(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Sub_Gold(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Sub_Gold(%d) = old(%d) - add(%d)"), Get_Gold(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Sub_Cash(MONEY_T price)
//{
//	MONEY_T old = Get_Cash();
//
//	GAME_RESULT result = IMoneyObject::Sub_Cash(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Sub_Cash(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Sub_Cash(%d) = old(%d) - add(%d)"), Get_Cash(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Sub_Heart(HEART_T price)
//{
//	HEART_T old = Get_Heart();
//
//	GAME_RESULT result = IMoneyObject::Sub_Heart(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Sub_Heart(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Sub_Heart(%d) = old(%d) - add(%d)"), Get_Heart(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Sub_Babel(STAMINA_T price)
//{
//	STAMINA_T old = Get_Babel();
//
//	GAME_RESULT result = IMoneyObject::Sub_Babel(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Sub_Babel(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Sub_Babel(%d) = old(%d) - add(%d)"), Get_Babel(), old, price);
//	return RESULT_OK;
//}
//
//GAME_RESULT CAccountData::Sub_Raid(STAMINA_T price)
//{
//	STAMINA_T old = Get_Raid();
//
//	GAME_RESULT result = IMoneyObject::Sub_Raid(price);
//	if(RESULT_OK != result)	{ LOGEVENT("HG_RED", _T("fail Sub_Raid(%d)"), result); return result; }
//
//	LOGEVENT("HG_GRAY", _T("Sub_Raid(%d) = old(%d) - add(%d)"), Get_Raid(), old, price);
//	return RESULT_OK;
//}
//
//MONEY_T CAccountData::Set_Gold(MONEY_T price)
//{
//	MONEY_T old = Get_Gold();
//	if(old == price)	return price;
//
//	MONEY_T cur = IMoneyObject::Set_Gold(price);
//	LOGEVENT("HG_GRAY", _T("Set_Gold(%d <-- %d)"), cur, old);
//	return cur;
//}
//
//MONEY_T CAccountData::Set_Cash(MONEY_T price)
//{
//	MONEY_T old = Get_Cash();
//	if(old == price)	return price;
//
//	MONEY_T cur = IMoneyObject::Set_Cash(price);
//	LOGEVENT("HG_GRAY", _T("Set_Cash(%d <-- %d)"), cur, old);
//	return cur;
//}
//
//HEART_T CAccountData::Set_Heart(HEART_T price)
//{
//	HEART_T old = Get_Heart();
//	if(old == price)	return price;
//
//	HEART_T cur = IMoneyObject::Set_Heart(price);
//	LOGEVENT("HG_GRAY", _T("Set_Heart(%d <-- %d)"), cur, old);
//	return cur;
//}
//
//STAMINA_T CAccountData::Set_Babel(STAMINA_T price)
//{
//	STAMINA_T old = Get_Babel();
//	if(old == price)	return price;
//
//	STAMINA_T cur = IMoneyObject::Set_Babel(price);
//	LOGEVENT("HG_GRAY", _T("Set_Babel(%d <-- %d)"), cur, old);
//	return cur;
//}
//
//STAMINA_T CAccountData::Set_Raid(STAMINA_T price)
//{
//	STAMINA_T old = Get_Raid();
//	if(old == price)	return price;
//
//	STAMINA_T cur = IMoneyObject::Set_Raid(price);
//	LOGEVENT("HG_GRAY", _T("Set_Raid(%d <-- %d)"), cur, old);
//	return cur;
//}
//
//CWeapon* CAccountData::CreateWeapon(const _stWeapon& Weapon)
//{
//	_stWeaponBase* base = CItemManager::Instance().GetWeaponBasePool().Find(Weapon.m_weaponcode);
//	if(NULL == base)	return NULL;
//	
//	//같은 그룹의 소울웨폰이 있는지 한번 체크 한다.
//	CWeapon* weapondata  = GetWeaponGroupPool().Find(base->m_weapongroup);
//	if(NULL != weapondata)		return weapondata;
//
//	weapondata = GetWeaponPool().Find(Weapon.m_weaponpk);
//	if(NULL != weapondata)		return weapondata;
//
//	weapondata = GetWeaponPool().Create();
//	weapondata->Clear();
//	weapondata->SetOwner(this);
//	weapondata->SetBase(base);
//	weapondata->Set(Weapon);
//	weapondata->SetEquipedAvatar(Weapon.m_equipedavatarpk);
//	//weapondata->SetWeaponDeckOrder(Weapon.m_deckorder);
//	GetWeaponPool().Insert(Weapon.m_weaponpk, weapondata);
//	
//	//그룹pool에 등록시킨다.
//	GetWeaponGroupPool().Insert(base->m_weapongroup, weapondata);
//
//	//weapon->ResetObjectAbility();
//	return weapondata;
//}
//
//
////GAME_RESULT CAccountData::Add_Money(MONEY_TYPE_T moneytype, MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Add_Money(moneytype, price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Sub_Money(MONEY_TYPE_T moneytype, MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Sub_Money(moneytype, price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
//
////GAME_RESULT CAccountData::Add_Money(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Add_Money(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Add_Cash(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Add_Cash(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Add_Stamina(STAMINA_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Add_Stamina(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Add_Heart(HEART_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Add_Heart(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Sub_Money(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Sub_Money(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Sub_Cash(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Sub_Cash(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Sub_Stamina(STAMINA_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Sub_Stamina(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
////
////GAME_RESULT CAccountData::Sub_Heart(HEART_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	GAME_RESULT result = IMoneyObject::Sub_Heart(price);
////	if(RESULT_OK != result)		return result;
////
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return RESULT_OK;
////}
//
////MONEY_T CAccountData::Set_Gold(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	MONEY_T money = IMoneyObject::Set_Gold(price);
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return money;
////}
////
////MONEY_T CAccountData::Set_Cash(MONEY_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	MONEY_T money = IMoneyObject::Set_Cash(price);
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return money;
////}
////
////STAMINA_T CAccountData::Set_Stamina(STAMINA_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	STAMINA_T money = IMoneyObject::Set_Stamina(price);
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return money;
////}
////
////HEART_T CAccountData::Set_Heart(HEART_T price, int a, BOOL bSaveDB/*FALSE*/)
////{
////	DBG_UNREFERENCED_PARAMETER(a);
////	HEART_T money = IMoneyObject::Set_Heart(price);
////	if(TRUE == bSaveDB/*FALSE*/)	SaveGameData2DB_Account();
////	return money;
////}
////
////_stLevelBase* GetWeaponRefineLevel(LEVEL_T level)
////{
////	return (_stLevelBase*)CLevelManager::Instance().GetRefineLevelPool().Find(level);
////}
//
//
//////money : 재련후 소지골드
////GAME_RESULT CAccountData::WeaponRefine(CWeaponItem* weaponItem, CItemCard * sourceItem, CItemCard* subItem, EXP_T addexp, OUT UINT8& remainSubItemCount)
////{
////	DBG_UNREFERENCED_PARAMETER(subItem);
////	DBG_UNREFERENCED_PARAMETER(addexp);
////	DBG_UNREFERENCED_PARAMETER(weaponItem);
////	DBG_UNREFERENCED_PARAMETER(sourceItem);
////	DBG_UNREFERENCED_PARAMETER(remainSubItemCount);
////
////
////
////	//if(NULL == weaponItem)		return NOT_FOUND_ITEM_IN_INVEN;
////
////
////	//// 경험치 지급.
////	//LEVEL_T new_level = 0;
////	//EXP_T new_exp = 0;
////	//CLevelManager::Instance().CheckObjectLevelUp(GetWeaponRefineLevel
////	//	, addexp, weaponItem->GetItemBase()->m_refinelevel, weaponItem->GetRefineLevel(), weaponItem->GetRefineExp()
////	//	, new_level, new_exp);
////
////
////	//ITEMPK subItempk = 0;
////	//UINT8  subItemCount = 0;
////	//if(NULL != subItem)
////	//{
////	//	subItempk = subItem->GetItemPK();
////	//	subItemCount = subItem->GetItemCount() - 1; //1개 소모되므로 -1
////	//}
////
////	////치트 때문에 추가되었습니다.. 
////	//ITEMPK sourceitempk;
////	//if(NULL == sourceItem)
////	//	sourceitempk = 0;
////	//else
////	//	sourceitempk = sourceItem->GetItemPK();
////
////	////DB에 업데이트 (아이템 remove, levelUpdate)
////	//GAME_RESULT result = CDBManager::Instance().RefineItem(weaponItem, new_level, new_exp, sourceitempk , subItempk, subItemCount);
////	//if(RESULT_OK != result)		return result;
////
////
////	////setting...
////	//weaponItem->SetRefineLevel(new_level);
////	//weaponItem->SetRefineExp(new_exp);
////
////
////	////왜 subItem->GetCount()를 쓰지 않고 인자를 직접 전달하나요? :  RemoveItemCard로 subItem 이 없어져서 바깥에서 SubItem에 접근하지 못할 가능성이 있기 때문입니다.
////	//remainSubItemCount = subItemCount;
////	return RESULT_OK;
////}
