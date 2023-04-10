#include "StdAfx.h"


CMasterClient::CMasterClient(void)
{
}

CMasterClient::~CMasterClient(void)
{
}


VOID CMasterClient::OnIoConnected(VOID)
{
	CNetClient::OnIoConnected();
	LOGEVENT("HG_WHITE", _T("master�� ���ӵǾ����ϴ�."));

}

VOID CMasterClient::OnIoDisconnected(VOID)
{
	CNetClient::OnIoDisconnected();
	LOGEVENT("HG_WHITE", _T("master�� ������ ���� �Ǿ����ϴ�."));

}

VOID CMasterClient::OnIoRecv(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
{
	// �������ݿ� ���� switch ��
	switch (msgRecv.ID())
	{
		////tcp
		//ON_RECEIVE_ON_CLIENT(M2_AC_CERTIFY_ACK);


		////udp
		//ON_RECEIVE_ON_CLIENT(C2_UDP_CHANGE_SERVER_STATUS_REQ);

		////ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_HELLO_PEER_REQ);
		////ON_RECEIVE_ON_CLIENT(X2L_CH_UDP_FINE_THANKS_PEER_ACK);

	case 0:
	default:
		{
			LOGEVENT("Session_Info_Error", _T("Not Support Protocol(0x%04x)"), msgRecv.ID());

			// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_GRAY", _T("������ �����մϴ�."));

		} break;
	}

}

VOID CMasterClient::OnIoSend(VOID)
{
	//LOGEVENT("HG_GRAY", _T("����Ÿ ���� ��ó���� ���⿡�� �ϼ���"));

}

VOID CMasterClient::OnIoServerHolePunchingCompleted()
{
	LOGEVENT("HG_WHITE", _T("�������� �غ�(Ȧ��Ī)�� �Ϸ�Ǿ����ϴ�."));
	////HG_TODO : ���� ������ master�� ��û�Ѵ�.
	//stM2_JOIN_GROUP_REQ st;
	//st.remote = remoteClient_.GetHostID();
	//st.serverinfo.push_back(CWorld::GetInstance()->GetRemoteServerInfo());

	//SEND_M2_JOIN_GROUP_REQ(Host_Server, RELIABLE, st);
}

VOID CMasterClient::OnJoinGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Join Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), remote);
	LOGEVENT("HG_WHITE", _T("Peer(0x%08x)���� �غ�(Ȧ��Ī)�� �Ϸ�Ǿ����ϴ�."), remote);

	std::vector<NetCore::CRemotePeer*> vecAll;
	GetPeerPool().GetAllList(vecAll);
	for (int i = 0; i < (int)vecAll.size(); ++i)
	{
		NetCore::CRemotePeer* peer = vecAll[i];
		if (NULL == peer)	continue;

		if (NetCore::enPrivateSuccess != peer->GetHolePunchingStep()
			&& NetCore::enPublicSuccess != peer->GetHolePunchingStep())
			return;
	}
	LOGEVENT("HG_CYAN", _T("��� Peer(%d)���� �غ�(Ȧ��Ī)�� �Ϸ�Ǿ����ϴ�."), (int)vecAll.size());
}

VOID CMasterClient::OnLeaveGroup(HOSTID remote)
{
	//LOGEVENT("HG_GRAY", _T("Leave Group ó���� ���⿡�� �ϼ��� Host id(0x%08x)"), remote);

}

void CMasterClient::Update()
{
	CNetClient::Update();
}
//
////remoteIP : ���� ip
////remotePort : ���� port
//void CMasterClient::Disconnect()
//{
//	stX2L_CH_DISCONNECT_REQ st;
//	SEND_X2L_CH_DISCONNECT_REQ(Host_Server, RELIABLE, st);
//}
//
//void CMasterClient::JoinGroup()
//{
//	stX2L_CH_JOIN_GROUP_REQ st;
//	st.remote = remoteClient_.GetHostID();
//	SEND_X2L_CH_JOIN_GROUP_REQ(Host_Server, RELIABLE, st);
//}
//
//void CMasterClient::LeaveGroup()
//{
//	stX2L_CH_LEAVE_GROUP_REQ st;
//	st.remote = remoteClient_.GetHostID();
//	SEND_X2L_CH_LEAVE_GROUP_REQ(Host_Server, RELIABLE, st);
//}
//
//
////IRemote* CMasterClient::FindRemote(HOSTID remote)
////{
////	return GetPeerPool().Find(remote);
////}
////
////CPacketSession* CMasterClient::FindPacketSession(IRemote* peer, BOOL bIsUdp)
////{
////	if(bIsUdp)
////		return GetUdpSession();
////	return GetTcpSession();
////}
//
//void CMasterClient::SayHelloPeer()
//{
//	std::vector<CRemotePeer*> vecList;
//	GetPeerPool().GetAllList(vecList);
//	for(std::vector<CRemotePeer*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
//	{
//		CRemotePeer* peer = *iter;
//		if(!peer)
//			continue;
//
//		stX2L_CH_UDP_HELLO_PEER_REQ stReq;
//		stReq.remoteFrom = remoteClient_.GetHostID();
//		stReq.remoteTo = peer->GetHostID();
//		SEND_X2L_CH_UDP_HELLO_PEER_REQ(peer->GetHostID(), RELIABLE, stReq);
//	}
//}

////game������ �����ڼ��� balance ������ �뺸�Ѵ�.
//void CMasterClient::SendCurrentUser()
//{
//	//master�������� ������� üũ
//	if(FALSE == IsConnected())
//		return;
//
//	//balance �������� ������.
//	std::vector<CRemotePeer*> vecAll;
//	GetPeerPool().GetAllList(vecAll);
//	for(int i=0; i<(int)vecAll.size(); ++i)
//	{
//		CRemotePeer* peer = vecAll[i];
//		if(NULL == peer)
//			continue;
//
//		//balance ����
//		if(eRemote_BalanceServer != peer->GetRemoteEntry())
//			continue;
//
//		_stGameServerInfo serverinfo;
//		serverinfo.remote_ = GetRemoteClient().GetHostID();
//		serverinfo.currentusers_ = CRemoteSessionManager::GetInstance()->GetRemoteSessionPool().GetUsedMemSize();
//
//		stM2_CH_UDP_CURRENT_USER_NTF stNtf;
//		stNtf.serverinfo.push_back(serverinfo);
//		SEND_M2_CH_UDP_CURRENT_USER_NTF(peer->GetHostID(), UNRELIABLE, stNtf);
//	}
//}
//
////game������ ������ control������ �뺸�Ѵ�.
//void CMasterClient::SendGameServerInfo()
//{
//	//balance �������� ������.
//	std::vector<CRemotePeer*> vecAll;
//	GetPeerPool().GetAllList(vecAll);
//	for(int i=0; i<(int)vecAll.size(); ++i)
//	{
//		CRemotePeer* peer = vecAll[i];
//		if(NULL == peer)
//			continue;
//
//		//control ����
//		if(eRemote_ControlServer != peer->GetRemoteEntry())
//			continue;
//
//		_stGameServerInfo gameinfo;
//		gameinfo.remote_ = GetRemoteClient().GetHostID();
//		gameinfo.currentusers_ = CRemoteSessionManager::GetInstance()->GetRemoteSessionPool().GetUsedMemSize();
//
//		stC2_UDP_GAME_SERVER_INFO_NTF stNtf;
//		stNtf.gameinfo.push_back(gameinfo);
//		SEND_C2_UDP_GAME_SERVER_INFO_NTF(peer->GetHostID(), UNRELIABLE, stNtf);
//	}
//}
//
//void CMasterClient::SendToCertyfyReq(HOSTID remote, stX2G_AC_CERTIFY_REQ& st, HOSTID remoteX)
//{
//	stM2_AC_CERTIFY_REQ stReq;
//	stReq.account = st.account;
//	stReq.masterkey = st.masterkey;
//	stReq.remoteGame = remoteClient_.GetHostID();//game������ host id
//	stReq.remoteX = remoteX;//���� ������ host id
//	SEND_M2_AC_CERTIFY_REQ(remote, RELIABLE, stReq);
//}
//
//void CMasterClient::SendToLogoutReq(CRemoteSession* session)
//{
//	CAccountInfo* accountinfo = session->GetAccountInfo();
//	if(NULL == accountinfo)
//		return;
//
//	if(TRUE == session->GetDuplicatedConnect())
//		return;
//
//	stM2_AC_LOGOUT_REQ stReq;
//	stReq.accountpk = accountinfo->GetAccountPK();
//	stReq.entry = entry_;
//	stReq.remoteServer = remoteClient_.GetHostID();//game������ host id
//	stReq.remoteX = session->GetHostID();//���� ������ host id
//	SEND_M2_AC_LOGOUT_REQ(Host_Server, RELIABLE, stReq);
//}