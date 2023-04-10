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

//���� : TRUE�̸� �ű�����
//BOOL CAccountData::LoginAccount()
//{
//	//Proud::CriticalSectionLock lock(m_csLogin, true);
//
//
//	////���� ������ ������ ������ �ޱ� ���ؼ� ó���մϴ�.
//	//GetMailManager().Clear();
//	//SetIsLoadMailList(FALSE);
//
//
//	//(*account)->SetDisconnectedTime(GetTickCount64());	//���� ����ð�
//	//m_userIp = userip;
//	//m_marketLogin = market;//�����Ҷ����� �޶����� �ִ�.
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T(" ------------------ �����ڼ� %d"), GetHostPool().GetUsedMemSize());
//
//	//return bNewJoin;
//	return TRUE;
//}

//void CAccountData::LogoutAccount()
//{
//	//account�� ���������� DB�� ����մϴ�.
//	SaveGameData2DB();
//
//	LOGEVENT("HG_YELLOW", _T("accountpk[0x%x] Connected FALSE"), this->GetAccountPk());
//	//SetDisconnectedTime(GetTickCount64());	//���� ����ð�
//	//SetIsMasterReg(FALSE);
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T("Account(%s), Host(%d) : CAccountData::LogoutAccount()::SetIsMasterReg(FALSE);"), Proud::StringA2W(m_accountinfo.m_accountid).GetString(), remote);
//	//SetSelectedAvatar(NULL);
//	//HG_����QA���� �ּ�ó��
//	//NOTIFY_SYSTEM_LOG("HG_YELLOW", _T(" ** account[%s] ���� ����"), GetNickname().GetString());
//
//
//	////master������ �뺸�Ѵ�.
//	//CServerApp::Instance().GetMasterNetClient()->m_csProxy.RequestLogout(Proud::HostID_Server, Proud::RmiContext::ReliableSend
//	//	, m_accountinfo.m_accountid, remote);
//
//	//// �ݸ��� �α� 
//	//CNetMarbleLog::Instance().AccountLog( m_accountinfo.m_accountid, m_szChannelCode, m_userIp, false );
//
//
//	//�޸� ���� �̺�Ʈ ���
//	//Insert(eSchedule_AccountRemove, CParam::Instance().account_caching_mem_release_delay_time);
//
//
//	////�޸𸮿��� ����...
//	////tick�� �Ѱܼ� ó���� ������ �´��� üũ�մϴ�.
//	////(������ �������� ����� ���, ������ ��������� ���� ������ ��������� telegram�� ���� removeó���� �� �ִ�)
//	//Dispatch.Dispatch_Message(ACCOUNT_REMOVE_DELAY_TIME, this, this, eAccount_Remove, (void*)GetDisconnectedTime(), NULL);
//	////Dispatch.Dispatch_Message(TIME_SEC(60), account, account, eAccount_Remove, (void*)account->GetDisconnectedTime(), NULL);
//}


////bImmediately : TRUE�̸� ��� DB�� ����Ѵ�. FALSE�̸� �����ð� ���Ŀ� ������ �����ϴ�.
//void CAccountData::SaveGameAvatar(CAvatarData* avatar)//, BOOL bImmediately)
//{
//	if(NULL == avatar)
//		return;
//
//	//if(NULL == GetUpdateAvatarPool().Find(avatar->GetAvatarPk()))
//	//	return;	//������� ������ ����.
//
//
//	//avatar�� ���������� DB�� ����մϴ�.
//	avatar->SaveGameData2DB();//bImmediately);
//
//
//	//���� �ε��� ���� �Ǻ��ڸ� �̰����� �ʱ�ȭ �� �ݴϴ�.
//	//avatar->SetIsLoadMailList(FALSE);
//
//
//	//HG_����QA���� �ּ�ó��
//	//NOTIFY_SYSTEM_LOG("HG_WHITE", _T(" �������� avatar[%s]�� world���� ���ϴ�."), avatar->GetNickname().GetString());
//
//	////����
//	//GetUpdateAvatarPool().Erase(avatar->GetAvatarPk());
//}
//
////account�� ���������� DB�� ����մϴ�.
////bImmediately : TRUE�̸� ��� DB�� ����Ѵ�. FALSE�̸� �����ð� ���Ŀ� ������ �����ϴ�.
//void CAccountData::SaveGameData2DB()
//{
//	////���������϶��� �ð�üũ�� ���� �ʴ´�.
//	//TIME_T cur = GetTickCount64();
//	//if(FALSE == bImmediately && cur < m_saveDBtime)
//	//	return;
//	//m_saveDBtime = cur + CParam::Instance().avatar_db_save_update_time;
//	//NOTIFY_SYSTEM_LOG("HG_GRAY", _T("  account(%s) DB saving."), GetAccountID().GetString());
//
//
//	SaveGameAvatar(GetSelectedAvatar());
//	SetSelectedAvatar(NULL);//�����ӽ� ���� avatar���� DB update ����.
//
//	// ����Ÿ ����
//	SaveGameData2DB_Account();
//
//	//�κ� ������Ʈ
//	//SaveGameData2DB_Item();
//
//	//�������� ������Ʈ
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
////		//DB�� ������Ʈ
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
//		//User������ ��Ƽ���ش�.
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
//	//���� �׷��� �ҿ������ �ִ��� �ѹ� üũ �Ѵ�.
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
//	//�׷�pool�� ��Ͻ�Ų��.
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
//////money : ����� �������
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
////	//// ����ġ ����.
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
////	//	subItemCount = subItem->GetItemCount() - 1; //1�� �Ҹ�ǹǷ� -1
////	//}
////
////	////ġƮ ������ �߰��Ǿ����ϴ�.. 
////	//ITEMPK sourceitempk;
////	//if(NULL == sourceItem)
////	//	sourceitempk = 0;
////	//else
////	//	sourceitempk = sourceItem->GetItemPK();
////
////	////DB�� ������Ʈ (������ remove, levelUpdate)
////	//GAME_RESULT result = CDBManager::Instance().RefineItem(weaponItem, new_level, new_exp, sourceitempk , subItempk, subItemCount);
////	//if(RESULT_OK != result)		return result;
////
////
////	////setting...
////	//weaponItem->SetRefineLevel(new_level);
////	//weaponItem->SetRefineExp(new_exp);
////
////
////	////�� subItem->GetCount()�� ���� �ʰ� ���ڸ� ���� �����ϳ���? :  RemoveItemCard�� subItem �� �������� �ٱ����� SubItem�� �������� ���� ���ɼ��� �ֱ� �����Դϴ�.
////	//remainSubItemCount = subItemCount;
////	return RESULT_OK;
////}
