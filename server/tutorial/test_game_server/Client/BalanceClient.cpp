#include "StdAfx.h"
#include "BalanceClient.h"


CBalanceClient::CBalanceClient(void)
{
}

CBalanceClient::~CBalanceClient(void)
{
}


VOID CBalanceClient::OnIoConnected(VOID)
{
	CNetClient::OnIoConnected();
	LOGEVENT("HG_WHITE", _T("balance에 접속되었습니다."));
}

VOID CBalanceClient::OnIoDisconnected(VOID)
{
	CNetClient::OnIoDisconnected();
	LOGEVENT("HG_WHITE", _T("balance와 접속이 종료 되었습니다."));
}

VOID CBalanceClient::OnIoRecv(CMsg& msgRecv)
{
	// 프로토콜에 따른 switch 문
	switch (msgRecv.ID())
	{
		//tcp



		//udp
		ON_RECEIVE_ON_CLIENT(X2B_AC_LOGIN_ACK);
		//ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_FINE_THANKS_PEER_ACK);

	default:
		{
			LOGEVENT("Session_Base_Error", _T("Not Support Protocol(0x%04x)"), msgRecv.ID());

			// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_GRAY", _T("접속을 해제합니다."));

		} break;
	}

}

VOID CBalanceClient::OnIoSend(VOID)
{
	//LOGEVENT("HG_GRAY", _T("데이타 보낸 후처리는 여기에서 하세요"));

}

VOID CBalanceClient::OnIoServerHolePunchingCompleted()
{
	LOGEVENT("HG_WHITE", _T("서버와의 준비(홀펀칭)가 완료되었습니다."));

	Sleep(1000);//login서버 실행될때 까지 잠시 대기
	Login();
}

VOID CBalanceClient::OnJoinGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Join Group 처리는 여기에서 하세요 Host id(0x%08x)"), remote);

}

VOID CBalanceClient::OnLeaveGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group 처리는 여기에서 하세요 Host id(0x%08x)"), remote);

}

void CBalanceClient::Update()
{
	CNetClient::Update();
}

//remoteIP : 서버 ip
//remotePort : 서버 port
void CBalanceClient::Login()
{
	CHAR account[ACCOUNT_NAME_LENGTH] = "";
	sprintf(account, "Dummy_%x", this);

	stX2B_AC_LOGIN_REQ stReq;
	stReq.account = account;
	stReq.authkey = "1111";
	stReq.version = PT_VERSION;

	//stReq.account = "test_01";
	//stReq.authkey = "1234";
	SEND_X2B_AC_LOGIN_REQ(Host_Server, RELIABLE, stReq);

	GetOwner()->GetGameClient().SetAccount(stReq.account);
}

//void CBalanceClient::JoinGroup()
//{
//	//stX2L_CH_JOIN_GROUP_REQ st;
//	//st.remote = remoteClient_.GetHostID();
//	//SEND_X2L_CH_JOIN_GROUP_REQ(Host_Server, RELIABLE, st);
//}
//
//void CBalanceClient::LeaveGroup()
//{
//	//stX2L_CH_LEAVE_GROUP_REQ st;
//	//st.remote = remoteClient_.GetHostID();
//	//SEND_X2L_CH_LEAVE_GROUP_REQ(Host_Server, RELIABLE, st);
//}


//IRemote* CBalanceClient::FindRemote(HOSTID remote)
//{
//	return GetPeerPool().Find(remote);
//}
//
//CPacketSession* CBalanceClient::FindPacketSession(HOSTID remote, BOOL bIsUdp)
//{
//	if(bIsUdp)
//		return GetUdpSession();
//	return GetTcpSession();
//}

//void CBalanceClient::SayHelloPeer()
//{
//	std::vector<CRemotePeer*> vecList;
//	GetPeerPool().GetAllList(vecList);
//	for(std::vector<CRemotePeer*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
//	{
//		CRemotePeer* peer = *iter;
//		if(!peer)
//			continue;
//
//		//stX2L_CH_UDP_HELLO_PEER_REQ stReq;
//		//stReq.remoteFrom = remoteClient_.GetHostID();
//		//stReq.remoteTo = peer->GetHostID();
//		//SEND_X2L_CH_UDP_HELLO_PEER_REQ(peer->GetHostID(), RELIABLE, stReq);
//	}
//}
