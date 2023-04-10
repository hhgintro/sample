#include "StdAfx.h"


//
//void CServer::OnM2_JOIN_GROUP_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(M2_JOIN_GROUP_REQ);
//	if(FALSE == CheckSessionStatus(session, eChk_Session))
//		return;
//
//
//	for(int i=0; i<(int)st.serverinfo.size(); ++i)
//	{
//		session->SetRemoteServerInfo(st.serverinfo[i]);
//		JoinP2PGroup(MasterServerGroupID_, session);
//	}
//}
//
////void CServer::OnX2L_CH_LEAVE_GROUP_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
////{
////	READ_PACKET(X2L_CH_LEAVE_GROUP_REQ);
////	st.group;
////
////	//CRemoteSession* session = (CRemoteSession*)FindRemote(st.remote);
////	if(NULL == session || FALSE == session->IsConnected())
////	{
////		LOGEVENT("Session_Info_Error", _T("Error ������ ����� ��ü�Դϴ�. : 0x%08x"), st.remote);
////		return;
////	}
////
////	LeaveP2PGroup(GameServerGroupID_, session);
////}
//
//
//void CServer::OnM2_AC_LOGIN_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(M2_AC_LOGIN_REQ);
//	if(FALSE == CheckSessionStatus(session, eChk_Session))
//		return;
//
//	CAccountInfo* accountinfo = NULL;
//
//	stM2_AC_LOGIN_ACK stAck;
//
//	//HG_TODO : Ŭ���̾�Ʈ ��� ������ ���� �������̴�.
//	//���Ŀ��� �ݵ�� ���µǾ�� �� �ڵ��Դϴ�.
/////*//HG_TEST : �׽�Ʈ�� ���ؼ� �ߺ� üũ�� ���� �ʴ´�.
//
//	//�ߺ� üũ
//	CAccountManager::ACCOUNT_INFO_POOL& pool = CAccountManager::Instance().GetAccountInfoPool();
//	CAccountInfo* prev_accountinfo = pool.Find(st.accountpk);
//	BOOL bDuplicated = CheckDuplicateLogin(prev_accountinfo, session);
//
//
//	//���� ���� ����/���
//	accountinfo = pool.Create();
//	accountinfo->Clear();
//	accountinfo->SetAccountPK(st.accountpk);
//	accountinfo->SetAccount(st.account);
//	accountinfo->SetRemoteBalance(st.remoteBalance);
//	accountinfo->SetRemoteClientBalance(st.remoteX);
//	pool.Insert(st.accountpk, accountinfo);
//
//
//
/////*/
//
//	//HG_TODO : login������ ���ؼ� ���ӵ� ���¸� �����Ų��.
//	//���� game������ ���Խ� ������ �˻縦 ����.
//	char key[16]  = "";
//	HisUtil::GetRandomString(key, sizeof(key));
//	accountinfo->SetMasterKey(key);
//	accountinfo->SetCreditRating(eIssued_Master_Key);
//
//	//..
//
//
//	//�뺸
//	//stM2_AC_LOGIN_ACK stAck;
//	stAck.result = ERR_SUCCESS;
//	if(TRUE == bDuplicated)
//	{
//		//AccountInfo �� ���� �������� ������ ������ �ش�.
//		//stM2_AC_LOGIN_ACK stAck;
//		stAck.result_noti = ERR_LOGIN_DUPLICATION_NOTIFY;
//	}
//	stAck.remoteBalance = st.remoteBalance;
//	stAck.remoteX = st.remoteX;
//	stAck.accountpk = accountinfo->GetAccountPK();
//	stAck.account = accountinfo->GetAccount();
//	stAck.masterkey = accountinfo->GetMasterKey();
//	stAck.gameserverno = st.gameserverno;
//	SEND_M2_AC_LOGIN_ACK(session->GetHostID(), RELIABLE, stAck);
//}
//
//void CServer::OnM2_AC_LOGOUT_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(M2_AC_LOGOUT_REQ);
//	if(FALSE == CheckSessionStatus(session, eChk_Session))
//		return;
//
//	CAccountManager::ACCOUNT_INFO_POOL& pool = CAccountManager::Instance().GetAccountInfoPool();
//	CAccountInfo* accountinfo = pool.Find(st.accountpk);
//	if(NULL != accountinfo)
//	{
//		//HG_TODO : ���� ���� ����� balace / game server�� ���� ���� ���� ����
//		//game ���� ������ �Ǿ� ���� �ʴٸ� �ߺ����������� ���� ������ clear()�� ������ ��� �Ѵ�.
//		switch(st.entry)
//		{
//		case eRemote_BalanceServer:
//			{
//				////�ߺ����ӵ� ���
//				////���� �����ڸ� ���� �����߱⶧���� ��������ó���� �ʿ����.
//				//if(TRUE == accountinfo->GetDuplicatedConnect())
//				//	break;
//
//				if(accountinfo->GetRemoteBalance() != st.remoteServer)
//					break;
//				if(accountinfo->GetRemoteClientBalance() != st.remoteX)
//					break;
//
//				pool.Erase(st.accountpk);
//				accountinfo->SetRemoteBalance(0);
//			}
//			break;
//
//		case eRemote_GameServer:
//			{
//				////�ߺ����ӵ� ���
//				////���� �����ڸ� ���� �����߱⶧���� ��������ó���� �ʿ����.
//				//if(TRUE == accountinfo->GetDuplicatedConnect())
//				//	break;
//
//				if(accountinfo->GetRemoteGame() != st.remoteServer)
//					break;
//				if(accountinfo->GetRemoteClientGame() != st.remoteX)
//					break;
//
//				pool.Erase(st.accountpk);
//				accountinfo->SetRemoteGame(0);
//			}
//			break;
//		}//..switch(st.entry)
//	}//..if(NULL != accountinfo)
//}
//
//void CServer::OnM2_AC_CERTIFY_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(M2_AC_CERTIFY_REQ);
//	if(FALSE == CheckSessionStatus(session, eChk_Session))
//		return;
//
//
//	stM2_AC_CERTIFY_ACK stAck;
//	stAck.result = ERR_CERTIFY_ACCOUNT;
//	stAck.remoteX = st.remoteX;
//
//	CAccountInfo* accountinfo = NULL;
//
//	//HG_TODO : game ������ ������ ������ masterkey�� �����Ѵ�.(�α����� ��, balance������ ���ؼ� ���޵Ǿ���.)
//	CAccountManager::ACCOUNT_INFO_POOL& pool = CAccountManager::Instance().GetAccountInfoPool();
//	std::vector<CAccountInfo*> vecAll;
//	pool.GetAllList(vecAll);
//
//	for(int i=0; i<(int)vecAll.size(); ++i)
//	{
//		if(NULL == vecAll[i])
//			continue;
//
//		if(vecAll[i]->GetAccount() == st.account)
//		{
//			accountinfo = vecAll[i];
//			break;
//		}
//	}
//	//..
//
//	//����Ȯ���� �ȵȴٸ�...����ó��
//	if(NULL == accountinfo)
//	{
//		WCHAR wzAccount[ACCOUNT_NAME_LENGTH] = _T("");
//		HisUtil::CA2W(st.account.c_str(), wzAccount, ACCOUNT_NAME_LENGTH);
//		LOGEVENT("HG_GRAY", _T("============= master �������� Account(%s) ============"), wzAccount);
//		for(int i=0; i<(int)vecAll.size(); ++i)
//		{
//			if(NULL == vecAll[i])
//				continue;
//
//			LOGEVENT("HG_GRAY", _T("		AccountPool(%s)"), vecAll[i]->GetAccount().c_str());
//		}
//		LOGEVENT("HG_GRAY", _T("=========================================="));
//
//		SEND_M2_AC_CERTIFY_ACK(session->GetHostID(), RELIABLE, stAck);
//		return;
//	}
//
//
//#ifdef _HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//#else
//	//HG_TODO : login������ ���� �����
//	//game�������� ������ �ް� �ִ��� üũ�Ѵ�.
//
//	if(eIssued_Master_Key != accountinfo->GetCreditRating())
//	{
//		stAck.result = ERR_ISSUED_ACCOUNT_MASTER_KEY;
//		SEND_M2_AC_CERTIFY_ACK(session->GetHostID(), RELIABLE, stAck);
//		return;
//	}
//
//	if(accountinfo->GetMasterKey() != st.masterkey)
//	{
//		stAck.result = ERR_CERTIFY_ACCOUNT_MASTER_KEY;
//		SEND_M2_AC_CERTIFY_ACK(session->GetHostID(), RELIABLE, stAck);
//		return;
//	}
//	//..
//
//	//HG_TODO : game������ ���� ���������� �Ϸ�Ǿ��ٰ� ���¸� �����Ų��.
//	//���� �ҹ����� ó���� �˻��ϱ� ����
//	//..
//
//
//#endif //_HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//
//	//������ ���ٸ�...
//	stAck.result = ERR_SUCCESS;
//	stAck.accountpk = accountinfo->GetAccountPK();
//	stAck.account = accountinfo->GetAccount();
//	accountinfo->SetRemoteGame(st.remoteGame);
//	accountinfo->SetRemoteClientGame(st.remoteX);
//	accountinfo->SetRemoteBalance(0);
//	accountinfo->SetRemoteClientBalance(0);
//	accountinfo->SetCreditRating(eCertify_Master_Key);
//
//	SEND_M2_AC_CERTIFY_ACK(session->GetHostID(), RELIABLE, stAck);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
////���� status
//void CServer::OnC2_UDP_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(C2_UDP_CHANGE_SERVER_STATUS_REQ);
//	//	remoteFrom : control������ �� host id
//	//	remoteTo : shutdown ��ų ������ host id
//
//	//�ƹ��͵� ���� �ʴ´�.
//	return;
//
//	////setting...
//	//CWorld::Instance().GetRemoteServerInfo().serverstatus_ = st.status;
//
//
//	////��� �뺸
//	//stC2_UDP_CHANGE_SERVER_STATUS_ACK stAck;
//	//stAck.remoteTo = st.remoteTo;
//	//stAck.status = st.status;
//	//SEND_C2_UDP_CHANGE_SERVER_STATUS_ACK(st.remoteFrom, RELIABLE, stAck);
//
//
//	////balance�뺸...
//	//{
//	//	std::vector<CRemotePeer*> vecAll;
//	//	GetPeerPool().GetAllList(vecAll);
//	//	for(int i=0; i<(int)vecAll.size(); ++i)
//	//	{
//	//		CRemotePeer* peer = vecAll[i];
//	//		if(NULL == peer)
//	//			continue;
//
//	//		//balance ����
//	//		if(eRemote_BalanceServer != peer->GetRemoteEntry())
//	//			continue;
//
//	//		stM2_UDP_CHANGE_SERVER_STATUS_NTF stNtf;
//	//		stNtf.remote = GetRemoteClient().GetHostID();
//	//		stNtf.status = st.status;
//	//		SEND_M2_UDP_CHANGE_SERVER_STATUS_NTF(peer->GetHostID(), UNRELIABLE, stNtf);
//	//	}
//
//	//	LOGEVENT("HG_YELLOW", _T("���� ����(%d)"), st.status);
//	//}
//
//	//switch(st.status)
//	//{
//	//	//���� ����
//	//case eS_Shutdown:
//	//	{
//	//		Sleep(SERVER_SHUTDOWN_SLEEP_TICK);
//	//		::exit(0x7777);
//	//	} break;
//	//}
//
//
//}
