#include "StdAfx.h"

CServer::CServer(void)
{
	MasterServerGroupID_ = CreateP2PGroup();
}

CServer::~CServer(void)
{
}

DWORD CServer::Start(int maxuser, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, int nRemoteRecvTcpPoolSize, int nRemoteRecvUdpPoolCnt)
{
	CNetServer::Start(maxuser, portTcp, portUdp, nRecvUdpPoolCnt, nSendUdpPoolCnt, nRemoteRecvTcpPoolSize, nRemoteRecvUdpPoolCnt);

	//추가 udp
	CNetServer::AddExtraUdp(htons(9999), 100, 100, this, &Callback_OnIoRecvUdpPacket);//+1))
	return 0;
}

void CServer::Callback_OnIoRecvUdpPacket(void* owner, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
{
	CServer* target = (CServer*)owner;
	if (NULL == target)	return;
	target->OnIoRecvPacket(remoteIP, remotePort, msgRecv);
}

void CServer::OnIoRecvPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
{
	//LOGEVENT("HG_WHITE", _T("received: CServer::OnIoRecvPacket()"));

	//		CRemoteSession* session = CRemoteSessionManager::Instance().FindAddressIPToSession(remoteIP, remotePort);
	//NULL 체크하지 마세요.??이유는 분석중(서버연결 진행안됨)
	//이유: OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ 에서는 ip/port로 session정보를 찾을 수 없기 때문.
	//if(NULL == session)
	//	continue;
	//		OnIoRecvPacket(session, remoteIP, remotePort, msgRecv);
}

VOID CServer::OnIoConnected(NetCore::CRemoteSession* session)
{
	LOGEVENT("HG_WHITE", _T("Host id(0x%08x)가 접속하였습니다."), session);
	//JoinP2PGroup(TestServerGroupID_, session);	//절대 여기서 join하지 마세요. 서버와 홀펀칭 이후에 진행해야 합니다.

#ifdef __HEART_BEAT__
#ifdef _DEBUG
	//디버깅을 위해 시간을 크게 늘렸다.
	//session->SetHeartBeatPermitTick(TIME_HOUR(1));
	session->SetHeartBeatPermitTick(TIME_MIN(1));
#else
	//서버간의 통신은 짧을 필요가 없어서 크게 잡았다.
	session->SetHeartBeatPermitTick(TIME_MIN(1));
#endif //..#ifdef _DEBUG
#endif //..__HEART_BEAT__
}

VOID CServer::OnIoDisconnected(NetCore::CRemoteSession* session)
{
	LOGEVENT("HG_WHITE", _T("Host id(0x%08x) 접속 종료되었습니다."), session);
	
	LeaveP2PGroup(MasterServerGroupID_, session);

	////서버다운된 유저의 정보를 삭제한다.
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
	//			//제거
	//			CAccountManager::Instance().GetAccountInfoPool().Erase(accountinfo->GetAccountPK());
	//		}
	//	}//..for(int i=0; i<(int)vecAll.size(); ++i)
	//}
	
	//CAccountManager::Instance().RemoveAccount(session->GetHostID());
}

VOID CServer::OnIoRecv(NetCore::CRemoteSession* session, HisUtil::CMsg& msgRecv)
{
	TIME_T timeTakes = HisUtil::GetUniversalTime();

	// 프로토콜에 따른 switch 문
	switch (msgRecv.ID())
	{
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

			// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
			//udp 의 object는 user의 개체가 아니기 때문에 disconnect대상이 아니다.
			//user의 index를 부여할 방법을 모색하라.
			ProcessDisconnect(session);


		} break;
	}
}

VOID CServer::OnIoSend(NetCore::CRemoteSession* session, DWORD dataLength)
{
	//LOGEVENT("HG_GRAY", _T("데이타 보낸 후처리는 여기에서 하세요 Host id(0x%08x)"), session);

}

VOID CServer::OnHolePunchingServer(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Hole Punching Server 처리는 여기에서 하세요 Host id(0x%08x)"), session);
	//JoinP2PGroup(MasterServerGroupID_, session);
}

VOID CServer::OnJoinGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Join Group 처리는 여기에서 하세요 Host id(0x%08x)"), session);

}

VOID CServer::OnHolePunchingGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Hole-Punching Group 처리는 여기에서 하세요 Host id(0x%08x)"), session);

}

VOID CServer::OnLeaveGroup(NetCore::CRemoteSession* session)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group 처리는 여기에서 하세요 Host id(0x%08x)"), session);

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
////이전 접속자에게는 중복 접속시도를 한다고 통보후에 접속을 종료시키고,
////이후 접속자에게는 중복 접속이 확인되었다고 통보후에 접속을 허가 한다.
//BOOL CServer::CheckDuplicateLogin(CAccountInfo* accountinfo, NetCore::CRemoteSession* session)
//{
//	if(NULL == accountinfo)
//		return FALSE;
//
//#ifdef _HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//#else
//
//	//to. 이전 접속자
//	if(accountinfo->GetRemoteGame())
//	{
//		stM2_AC_CERTIFY_ACK stAck;
//		stAck.result = ERR_LOGIN_DUPLICATION_DISCONNECT;
//		stAck.remoteX = accountinfo->GetRemoteClientGame();
//		//game서버에 접속하고 있는 remoteX를 종료시킨다.
//		SEND_M2_AC_CERTIFY_ACK(accountinfo->GetRemoteGame(), RELIABLE, stAck);
//		//HG_TODO : game서버에서 접속 종료 체크할 것
//	}
////	else
//	if( accountinfo->GetRemoteBalance())
//	{
//		stM2_AC_LOGIN_ACK stAck;
//		stAck.result = ERR_LOGIN_DUPLICATION_DISCONNECT;
//		stAck.remoteBalance = accountinfo->GetRemoteBalance();
//		stAck.remoteX = accountinfo->GetRemoteClientBalance();
//		//login서버를 통해 balance서버에 접속하고 있는 remoteX를 종료시킨다.
//		SEND_M2_AC_LOGIN_ACK(session->GetHostID(), RELIABLE, stAck);
//		//HG_TODO : game서버에서 접속 종료 체크할 것
//	}
//	//..//to. 이전 접속자
//
//	//제거
//	CAccountManager::Instance().GetAccountInfoPool().Erase(accountinfo->GetAccountPK());
//
//#endif //_HG_TEST_NO_CHECK_DUPLICATE_ACCOUNT_
//
//	return TRUE;
//}
