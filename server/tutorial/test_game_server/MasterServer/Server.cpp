#include "StdAfx.h"

CServer::CServer(void)
{
	MasterServerGroupID_ = CreateP2PGroup();
}

CServer::~CServer(void)
{
}

VOID CServer::OnIoConnected(NetCore::CRemoteSession* session)
{
	std::wstring ip;
	ADDR_PORT port;
	session->GetRemotePublicIPAfterAccept(ip, port);
	LOGEVENT("HG_WHITE", _T("Host id(0x%08x) ip(%s/%d) �� �����Ͽ����ϴ�."), session, ip.c_str(), port);
	//JoinP2PGroup(TestServerGroupID_, session);	//���� ���⼭ join���� ������. ������ Ȧ��Ī ���Ŀ� �����ؾ� �մϴ�.

#ifdef __HEART_BEAT__
#ifdef _DEBUG
	//������� ���� �ð��� ũ�� �÷ȴ�.
	//session->SetHeartBeatPermitTick(TIME_HOUR(1));
	session->SetHeartBeatPermitTick(TIME_MIN(1));
#else
	//�������� ����� ª�� �ʿ䰡 ��� ũ�� ��Ҵ�.
	session->SetHeartBeatPermitTick(TIME_MIN(1));
#endif //..#ifdef _DEBUG
#endif //..__HEART_BEAT__
}

VOID CServer::OnIoDisconnected(NetCore::CRemoteSession* session)
{
	LOGEVENT("HG_WHITE", _T("Host id(0x%08x) ���� ����Ǿ����ϴ�."), session);
	
	LeaveP2PGroup(MasterServerGroupID_, session);

	////�����ٿ�� ������ ������ �����Ѵ�.
	//if(eRemote_GameServer == session->GetRemoteEntry())
	//{
	//	std::vector<CAccountInfo*> vecAll;
	//	CAccountManager::Instance().GetAccountInfoPool().GetAllList(vecAll);
	//	for(int i=0; i<(int)vecAll.size(); ++i)
	//	{
	//		CAccountInfo* accountinfo = vecAll[i];
	//		if(NULL == accountinfo)
	//			continue;

	//		if(session->GetHostID() == accountinfo->GetRemoteGame())
	//		{
	//			//����
	//			CAccountManager::Instance().GetAccountInfoPool().Erase(accountinfo->GetAccountPK());
	//		}
	//	}//..for(int i=0; i<(int)vecAll.size(); ++i)
	//}
	
	//CAccountManager::Instance().RemoveAccount(session->GetHostID());
}

VOID CServer::OnIoRecv(NetCore::CRemoteSession* session, HisUtil::CMsg& msgRecv)
{
	TIME_T timeTakes = HisUtil::GetUniversalTime();

	// �������ݿ� ���� switch ��
	switch (msgRecv.ID())
	{
		ON_RECEIVE_FROM_CLIENT(M2_BD_VOICE_CHAT_REQ);

		////TCP
		//ON_RECEIVE_FROM_CLIENT(M2_JOIN_GROUP_REQ);
		//ON_RECEIVE_FROM_CLIENT(M2_AC_LOGIN_REQ);
		//ON_RECEIVE_FROM_CLIENT(M2_AC_LOGOUT_REQ);

		//ON_RECEIVE_FROM_CLIENT(M2_AC_CERTIFY_REQ);


		////UDP
		//ON_RECEIVE_ON_CLIENT(C2_UDP_CHANGE_SERVER_STATUS_REQ);

	case 0:
	default:
		{
			LOGEVENT("Session_Info_Error", _T("Not Support Protocol(0x%04x)! Host id(0x%08x)"), msgRecv.ID(), session);

			// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
			//udp �� object�� user�� ��ü�� �ƴϱ� ������ disconnect����� �ƴϴ�.
			//user�� index�� �ο��� ����� ����϶�.
			ProcessDisconnect(session);


		} break;
	}
}

VOID CServer::OnIoSend(NetCore::CRemoteSession* session, DWORD dataLength)
{
	//LOGEVENT("HG_GRAY", _T("����Ÿ ���� ��ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), session);

}

VOID CServer::OnHolePunchingServer(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Hole Punching Server ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), session);
	JoinP2PGroup(MasterServerGroupID_, session);
}

VOID CServer::OnJoinGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Join Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), session);

}

VOID CServer::OnHolePunchingGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Hole-Punching Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), session);

}

VOID CServer::OnLeaveGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), session);

}

NetCore::IRemote* CServer::FindRemote(HOSTID remote)
{
	return CNetServer::FindRemote(remote);
}
NetCore::CPacketSession* CServer::FindPacketSession(NetCore::IRemote* peer, bool bIsUdp)
{
	return CNetServer::FindPacketSession(peer, bIsUdp);
}

////HG_TODO : 
////���� �����ڿ��Դ� �ߺ� ���ӽõ��� �Ѵٰ� �뺸�Ŀ� ������ �����Ű��,
////���� �����ڿ��Դ� �ߺ� ������ Ȯ�εǾ��ٰ� �뺸�Ŀ� ������ �㰡 �Ѵ�.
//BOOL CServer::CheckDuplicateLogin(CAccountInfo* accountinfo, NetCore::CRemoteSession* session)
//{
//	if(NULL == accountinfo)
//		return FALSE;
//
//#ifdef _HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//#else
//
//	//to. ���� ������
//	if(accountinfo->GetRemoteGame())
//	{
//		stM2_AC_CERTIFY_ACK stAck;
//		stAck.result = ERR_LOGIN_DUPLICATION_DISCONNECT;
//		stAck.remoteX = accountinfo->GetRemoteClientGame();
//		//game������ �����ϰ� �ִ� remoteX�� �����Ų��.
//		SEND_M2_AC_CERTIFY_ACK(accountinfo->GetRemoteGame(), RELIABLE, stAck);
//		//HG_TODO : game�������� ���� ���� üũ�� ��
//	}
////	else
//	if( accountinfo->GetRemoteBalance())
//	{
//		stM2_AC_LOGIN_ACK stAck;
//		stAck.result = ERR_LOGIN_DUPLICATION_DISCONNECT;
//		stAck.remoteBalance = accountinfo->GetRemoteBalance();
//		stAck.remoteX = accountinfo->GetRemoteClientBalance();
//		//login������ ���� balance������ �����ϰ� �ִ� remoteX�� �����Ų��.
//		SEND_M2_AC_LOGIN_ACK(session->GetHostID(), RELIABLE, stAck);
//		//HG_TODO : game�������� ���� ���� üũ�� ��
//	}
//	//..//to. ���� ������
//
//	//����
//	CAccountManager::Instance().GetAccountInfoPool().Erase(accountinfo->GetAccountPK());
//
//#endif //_HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//
//	return TRUE;
//}
