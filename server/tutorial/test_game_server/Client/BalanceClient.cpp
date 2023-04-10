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
	LOGEVENT("HG_WHITE", _T("balance�� ���ӵǾ����ϴ�."));
}

VOID CBalanceClient::OnIoDisconnected(VOID)
{
	CNetClient::OnIoDisconnected();
	LOGEVENT("HG_WHITE", _T("balance�� ������ ���� �Ǿ����ϴ�."));
}

VOID CBalanceClient::OnIoRecv(CMsg& msgRecv)
{
	// �������ݿ� ���� switch ��
	switch (msgRecv.ID())
	{
		//tcp



		//udp
		ON_RECEIVE_ON_CLIENT(X2B_AC_LOGIN_ACK);
		//ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_FINE_THANKS_PEER_ACK);

	default:
		{
			LOGEVENT("Session_Base_Error", _T("Not Support Protocol(0x%04x)"), msgRecv.ID());

			// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_GRAY", _T("������ �����մϴ�."));

		} break;
	}

}

VOID CBalanceClient::OnIoSend(VOID)
{
	//LOGEVENT("HG_GRAY", _T("����Ÿ ���� ��ó���� ���⿡�� �ϼ���"));

}

VOID CBalanceClient::OnIoServerHolePunchingCompleted()
{
	LOGEVENT("HG_WHITE", _T("�������� �غ�(Ȧ��Ī)�� �Ϸ�Ǿ����ϴ�."));

	Sleep(1000);//login���� ����ɶ� ���� ��� ���
	Login();
}

VOID CBalanceClient::OnJoinGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Join Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), remote);

}

VOID CBalanceClient::OnLeaveGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), remote);

}

void CBalanceClient::Update()
{
	CNetClient::Update();
}

//remoteIP : ���� ip
//remotePort : ���� port
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
