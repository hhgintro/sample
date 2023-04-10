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
////		LOGEVENT("Session_Info_Error", _T("Error 접속이 종료된 개체입니다. : 0x%08x"), st.remote);
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
//	//HG_TODO : 클라이언트 모듈 전달을 위해 막은것이다.
//	//이후에는 반드시 오픈되어야 할 코드입니다.
/////*//HG_TEST : 테스트를 위해서 중복 체크를 하지 않는다.
//
//	//중복 체크
//	CAccountManager::ACCOUNT_INFO_POOL& pool = CAccountManager::Instance().GetAccountInfoPool();
//	CAccountInfo* prev_accountinfo = pool.Find(st.accountpk);
//	BOOL bDuplicated = CheckDuplicateLogin(prev_accountinfo, session);
//
//
//	//유저 접속 생성/등록
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
//	//HG_TODO : login서버를 통해서 접속된 상태를 적용시킨다.
//	//이후 game서버에 진입시 적법성 검사를 위해.
//	char key[16]  = "";
//	HisUtil::GetRandomString(key, sizeof(key));
//	accountinfo->SetMasterKey(key);
//	accountinfo->SetCreditRating(eIssued_Master_Key);
//
//	//..
//
//
//	//통보
//	//stM2_AC_LOGIN_ACK stAck;
//	stAck.result = ERR_SUCCESS;
//	if(TRUE == bDuplicated)
//	{
//		//AccountInfo 를 이후 접속자의 정보로 설정해 준다.
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
//		//HG_TODO : 유저 접속 종료시 balace / game server로 부터 접속 종료 접수
//		//game 서버 접속이 되어 있지 않다면 중복오류방지를 위해 계정을 clear()를 진행해 줘야 한다.
//		switch(st.entry)
//		{
//		case eRemote_BalanceServer:
//			{
//				////중복접속된 경우
//				////이전 접속자를 강제 삭제했기때문에 접속종료처리할 필요없다.
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
//				////중복접속된 경우
//				////이전 접속자를 강제 삭제했기때문에 접속종료처리할 필요없다.
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
//	//HG_TODO : game 서버에 접속한 유저의 masterkey를 검증한다.(로그인할 때, balance서버를 통해서 전달되었다.)
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
//	//계정확인이 안된다면...오류처리
//	if(NULL == accountinfo)
//	{
//		WCHAR wzAccount[ACCOUNT_NAME_LENGTH] = _T("");
//		HisUtil::CA2W(st.account.c_str(), wzAccount, ACCOUNT_NAME_LENGTH);
//		LOGEVENT("HG_GRAY", _T("============= master 계정정보 Account(%s) ============"), wzAccount);
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
//	//HG_TODO : login서버를 통해 등록후
//	//game서버에서 인증을 받고 있는지 체크한다.
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
//	//HG_TODO : game서버를 통해 인증절차가 완료되었다고 상태를 적용시킨다.
//	//이후 불법적인 처리를 검사하기 위해
//	//..
//
//
//#endif //_HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//
//	//오류가 없다면...
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
////서버 status
//void CServer::OnC2_UDP_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(C2_UDP_CHANGE_SERVER_STATUS_REQ);
//	//	remoteFrom : control서버의 는 host id
//	//	remoteTo : shutdown 시킬 서버의 host id
//
//	//아무것도 하지 않는다.
//	return;
//
//	////setting...
//	//CWorld::Instance().GetRemoteServerInfo().serverstatus_ = st.status;
//
//
//	////결과 통보
//	//stC2_UDP_CHANGE_SERVER_STATUS_ACK stAck;
//	//stAck.remoteTo = st.remoteTo;
//	//stAck.status = st.status;
//	//SEND_C2_UDP_CHANGE_SERVER_STATUS_ACK(st.remoteFrom, RELIABLE, stAck);
//
//
//	////balance통보...
//	//{
//	//	std::vector<CRemotePeer*> vecAll;
//	//	GetPeerPool().GetAllList(vecAll);
//	//	for(int i=0; i<(int)vecAll.size(); ++i)
//	//	{
//	//		CRemotePeer* peer = vecAll[i];
//	//		if(NULL == peer)
//	//			continue;
//
//	//		//balance 서버
//	//		if(eRemote_BalanceServer != peer->GetRemoteEntry())
//	//			continue;
//
//	//		stM2_UDP_CHANGE_SERVER_STATUS_NTF stNtf;
//	//		stNtf.remote = GetRemoteClient().GetHostID();
//	//		stNtf.status = st.status;
//	//		SEND_M2_UDP_CHANGE_SERVER_STATUS_NTF(peer->GetHostID(), UNRELIABLE, stNtf);
//	//	}
//
//	//	LOGEVENT("HG_YELLOW", _T("상태 변경(%d)"), st.status);
//	//}
//
//	//switch(st.status)
//	//{
//	//	//서버 종료
//	//case eS_Shutdown:
//	//	{
//	//		Sleep(SERVER_SHUTDOWN_SLEEP_TICK);
//	//		::exit(0x7777);
//	//	} break;
//	//}
//
//
//}
