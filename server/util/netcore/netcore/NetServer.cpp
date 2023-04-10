#include "stdafx.h"
#include "NetServer.h"

namespace NetCore {

	CNetServer* g_server;

	CNetServer::CNetServer(void)
	{
		g_server = this;
	}

	CNetServer::~CNetServer(void)
	{
		NetUdpIocp_.End();
		NetIocp_.End();

		//extra udp pool
		std::vector<CNetUdpIocp*> vecAll;
		ExtraUdpPool_.GetAllList(vecAll);
		for (int i = 0; i < vecAll.size(); ++i)
		{
			CNetUdpIocp* udp = vecAll[i];
			if (NULL == udp)	continue;
			udp->End();
		}
		ExtraUdpPool_.End();
	}

	//OnIoRecvUdpPacket

	DWORD CNetServer::Start(int maxuser, ADDR_PORT portTcp, ADDR_PORT portUdp
		, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, int nRemoteRecvTcpPoolSize, int nRemoteRecvUdpPoolCnt)
	{
		//servertime_ = HisUtil::RandInt(TIME_HOUR(24), TIME_HOUR(72));

		//udp iocp ��� ����
		//NetUdpIocp_.SetOwner(this, &CNetServer::OnIoRecvUdpPacket);
		//NetUdpIocp_.SetOwner(this, &Callback_OnIoRecvUdpPacket);
		//SetUdpPort(portUdp);	//Begin()���� ó��(0�� �����)
		LOGEVENT("Session_Base_Info", _T("+ GameUdpIocp Startup"));
		if (!NetUdpIocp_.Begin(portUdp, nRecvUdpPoolCnt, nSendUdpPoolCnt, this, &Callback_OnIoRecvUdpPacket))//+1))
		{
			LOGEVENT("Session_Base_Error", _T("GameUdpIocp stopped..."));
			return ERR_SERVER_UDP_BEGIN;
		}
		SetUdpPort(NetUdpIocp_.GetPrivatePort());	//Begin()���� ó��(0�� �����)

		//tcp udp iocp ��� ����
		//NetIocp_.SetOwner(this, &Callback_OnIoConnected, &Callback_OnIoDisconnected, &Callback_OnIoRecvTcpPacket);
		//SetTcpPort(portTcp);	//Begin()���� ó��(0�� �����)
		LOGEVENT("Session_Base_Info", _T("+ GameIocp Startup"));
		if (!NetIocp_.Begin(portTcp, this, &Callback_OnIoConnected, &Callback_OnIoDisconnected, &Callback_OnIoRecvTcpPacket))
		{
			LOGEVENT("Session_Base_Error", _T("GameIocp stopped..."));
			return ERR_SERVER_TCP_BEGIN;
		}
		SetTcpPort(NetIocp_.GetPrivatePort());	//Begin()���� ó��(0�� �����)

		if (FALSE == CRemoteSessionManager::Instance().Begin(maxuser, nRemoteRecvTcpPoolSize, nRemoteRecvUdpPoolCnt))
		{
			LOGEVENT("Session_Base_Error", _T("RemoteClient stopped..."));
			return ERR_SERVER_REMOTE_SESSION_POOL;
		}

		return SERVER_OK;
	}

	//extra udp pool
	//ADDR_PORT = htons(port);
	DWORD CNetServer::AddExtraUdp(ADDR_PORT portUdp, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, void* owner, void* callback_OnIoRecvPacket)
	{
		CNetUdpIocp* udp = ExtraUdpPool_.Find(portUdp);
		if (NULL != udp) {

			LOGEVENT("Session_Base_Error", _T("CNetServer::AddExtraUdp() already port..."));
			return ERR_SERVER_SAME_UDP_PORT;
		}

		udp = ExtraUdpPool_.Create();
		if (!udp->Begin(portUdp, nRecvUdpPoolCnt, nSendUdpPoolCnt, owner, callback_OnIoRecvPacket))//+1))
		{
			ExtraUdpPool_.Erase(udp);	//��üȸ��
			LOGEVENT("Session_Base_Error", _T("CNetServer::AddExtraUdp() stopped..."));
			return ERR_SERVER_UDP_BEGIN;
		}

		ExtraUdpPool_.Insert(portUdp, udp);
		return SERVER_OK;
	}

	//extra udp pool
	void CNetServer::SubExtraUdp(ADDR_PORT portUdp)
	{
		CNetUdpIocp* udp = ExtraUdpPool_.Find(portUdp);
		if (NULL == udp)	return;
		
		//erase
		udp->End();
		ExtraUdpPool_.Erase(portUdp);
	}

	//extra udp pool
	BOOL CNetServer::SendExtraUdp(ADDR_PORT portUdp, HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		CNetUdpIocp* udp = ExtraUdpPool_.Find(portUdp);
		if (NULL == udp)
		{
			LOGEVENT("Session_Base_Error", _T("CNetServer::SendExtraUdp() udp is NULL."));
			return FALSE;
		}
		return udp->SendToPacket(msg, remoteIP, remotePort);
	}

	void CNetServer::Update()
	{
		CRemoteSessionManager::Instance().Update();
	}

	P2PGROUPID CNetServer::CreateP2PGroup()
	{
		//create
		CP2PGroup* group = P2PGroupPool_.Create();
		group->Clear();

		//insert
		group->SetGroupID((P2PGROUPID)group);
		P2PGroupPool_.Insert(group->GetGroupID(), group);
		return group->GetGroupID();
	}

	void CNetServer::JoinP2PGroup(P2PGROUPID id, CRemoteSession* session)
	{
		CP2PGroup* group = P2PGroupPool_.Find(id);
		if (NULL == group)
		{
			LOGEVENT("Session_Base_Error", _T("failed join not exist Group id (0x%p)"), id);
			return;
		}

		//���翩�� üũ
		IRemote* remote = group->GetGroupPeerPool().Find(session->GetHostID());
		if (NULL != remote)//already member
			return;

		//1.1 Group �ɹ��� ������ ���� ����ü
		stNetC2S_CORE_JOIN_GROUP_NTF stJoin;
		stJoin.group = group->GetGroupID();

		if (false == group->JoinGroup(session->GetHostID(), session))
		{
			//stAck.result = 9999;
			//SEND_CORE_TCP_PACKET(NetC2S_CORE_JOIN_GROUP_NTF, stAck, session);
			LOGEVENT("Session_Base_Error", _T("failed join group Host id (0x%p)"), session);
			return;
		}


		//group member�� �ڽŻ��̸�...����
		if (1 < (int)group->GetGroupPeerPool().GetUsedMemSize())
		{
			//2.1 �ڽ��� ������ ����
			stNetC2S_CORE_ENTER_GROUP_NTF stEnter;
			stEnter.group = group->GetGroupID();
			//stEnter.peerinfo.remote = session->GetHostID();
			//stEnter.peerinfo.entry = session->GetRemoteEntry();
			//stEnter.peerinfo.publicIP = session->GetRemotePublicIP();
			//stEnter.peerinfo.publicPort = session->GetRemotePublicPort();
			//stEnter.peerinfo.privateIP = session->GetRemotePrivateIP();
			//stEnter.peerinfo.privatePort = session->GetRemotePrivatePort();

			//stEnter.peerinfo.serverinfo = session->GetRemoteServerInfo();
			stRemoteEndpoint selfinfo;
			selfinfo.remote			= session->GetHostID();
			selfinfo.entry			= session->GetRemoteEntry();
			selfinfo.publicIP		= session->GetRemotePublicIP();
			selfinfo.portTcp		= session->GetRemotePublicTcpPort();
			selfinfo.portUdp		= session->GetRemotePublicUdpPort();
			selfinfo.privateIP		= session->GetRemotePrivateIP();
			selfinfo.privatePort	= session->GetRemotePrivateUdpPort();
			//selfinfo.serverinfo		= session->GetRemoteServerInfo();

			stEnter.peerinfo.push_back(selfinfo);


			//1.2 Group �ɹ��� Ȯ���Ѵ�.
			std::vector<IRemote*> GroupPeers;
			group->GetGroupPeerPool().GetAllList(GroupPeers);
			for (int i = 0; i < (int)GroupPeers.size(); ++i)
			{
				CRemoteSession* peer = (CRemoteSession*)GroupPeers[i];
				if (0 == peer || false == peer->IsConnected())
					continue;


				//�ڽ��� ����
				if (session == peer)
					continue;


				//control�� ����
				//if(eRemote_ControlServer != peer->GetRemoteEntry())
				{
					//1.3 Group �ɹ��� ������ �����Ѵ�.
					stRemoteEndpoint info;
					info.remote			= peer->GetHostID();
					info.entry			= peer->GetRemoteEntry();
					info.publicIP		= peer->GetRemotePublicIP();
					info.portTcp		= peer->GetRemotePublicTcpPort();
					info.portUdp		= peer->GetRemotePublicUdpPort();
					info.privateIP		= peer->GetRemotePrivateIP();
					info.privatePort	= peer->GetRemotePrivateUdpPort();
					//info.serverinfo		= peer->GetRemoteServerInfo();

					stJoin.peerinfo.push_back(info);
				}

				//2.2 ������ �ڽ��� ������ �ֺ��� �뺸
				SEND_NetC2S_CORE_ENTER_GROUP_NTF(peer->GetHostID(), stEnter);
			}
		}

		//1.4 Group �ɹ��� ������ �����´�.
		if (0 < stJoin.peerinfo.size())
			SEND_NetC2S_CORE_JOIN_GROUP_NTF(session->GetHostID(), stJoin);
	}

	//void CNetServer::HolPunchingGroup(P2PGROUPID id, CRemoteSession* session)
	//{

	//}

	void CNetServer::LeaveP2PGroup(P2PGROUPID id, CRemoteSession* session)
	{
		CP2PGroup* group = P2PGroupPool_.Find(id);
		if (NULL == group)
		{
			//LOGEVENT("Session_Base_Error", _T("failed join not exist Group id (0x%p)"), id);
			return;
		}

		//���翩�� üũ
		IRemote* remote = group->GetGroupPeerPool().Find(session->GetHostID());
		if (NULL == remote)//not member
			return;

		stNetC2S_CORE_LEAVE_GROUP_NTF stNtf;
		stNtf.group = group->GetGroupID();
		stNtf.remote = session->GetHostID();


		//1.1 Group �ɹ��� Ȯ���Ѵ�.
		std::vector<IRemote*> GroupPeers;
		group->GetGroupPeerPool().GetAllList(GroupPeers);
		for (int i = 0; i < (int)GroupPeers.size(); ++i)
		{
			CRemoteSession* peer = (CRemoteSession*)GroupPeers[i];
			if (0 == peer || false == peer->IsConnected())
				continue;

			//if(session == peer)
			//	continue

			//1.2 ������ �ڽ��� ������ �ֺ��� �뺸
			SEND_NetC2S_CORE_LEAVE_GROUP_NTF(peer->GetHostID(), stNtf);
		}

		//2.1 �ڽ��� group���� ����
		group->LeaveGroup(session->GetHostID());

		OnLeaveGroup(session);
	}

	void CNetServer::ProcessDisconnect(CRemoteSession* session)
	{
		NetIocp_.OnIoDisconnected(session);
	}
	void CNetServer::ProcessDisconnect(HOSTID remote)
	{
		ProcessDisconnect((CRemoteSession*)FindRemote(remote));
	}

	IRemote* CNetServer::FindRemote(HOSTID remote)
	{
		return CRemoteSessionManager::Instance().FindRemote(remote);
	}

	CPacketSession* CNetServer::FindPacketSession(IRemote* peer, bool bIsUdp)
	{
		CRemoteSession* session = (CRemoteSession*)FindRemote(peer->GetHostID());

		//������ ����Ǿ��ٸ�...
		if (NULL == session || FALSE == session->IsConnected())
		{
			//LOGEVENT("Session_Base_Error", _T("Fail disconnected netserver remote(0x%p) : �������ᰡ �ƴѵ� ��µǸ� �����ֽ�"), remote);
			return NULL;
		}

		//HG_TODO : ���⿡�� udp ��Ŷ���� tcp��Ŷ���� ������ �ʿ��մϴ�.
		//..

		if (bIsUdp)
		{
			switch (session->GetHolePunchingStep())
			{
			case enPrivateAttempt:
			case enPrivateSuccess:
			case enPublicAttempt:
			case enPublicSuccess:
				return NetUdpIocp_.GetUdpSession();
			}
		}

		return (CPacketSession*)session;
	}

	BOOL CNetServer::CheckSessionStatus(CRemoteSession* session, int check)
	{
		//CHK_SESSION_LEVEL check
		if (TRUE == CHECK_BIT_FLAG(check, NetCore::eChk_Session))
		{
			if (NULL == session)
			{
				LOGEVENT("Session_Base_Error", _T("Error �˼� ���� session �Դϴ�."));
				return FALSE;
			}
			if (FALSE == session->IsConnected())
			{
				LOGEVENT("Session_Base_Error", _T("Error ������ ����� ��ü�Դϴ�. : 0x%p"), session->GetHostID());
				return FALSE;
			}
		}
		//if (TRUE == CHECK_BIT_FLAG(check, eChk_AccountInfo))
		//{
		//	if (NULL == session->GetAccountInfo())
		//	{
		//		LOGEVENT("Session_Base_Error", _T("Error Session�� AccountInfo������ �����ϴ�. : 0x%p"), session->GetHostID());
		//		return FALSE;
		//	}
		//}
		//if (TRUE == CHECK_BIT_FLAG(check, eChk_CharInfo))
		//{
		//	CCharInfo* charinfo = session->GetChoiceCharInfo();
		//	if (NULL == charinfo)
		//	{
		//		LOGEVENT("Session_Base_Error", _T("Error Session�� CharInfo������ �����ϴ�. : 0x%p"), session->GetHostID());
		//		return FALSE;
		//	}
		//}

		return TRUE;
	}

	//static function
	void CNetServer::Callback_OnIoConnected(void* owner, CRemoteSession* session)
	{
		CNetServer* target = (CNetServer*)owner;
		if (NULL == target)	return;
		target->OnIoConnected(session);
	}
	//static function
	void CNetServer::Callback_OnIoDisconnected(void* owner, CRemoteSession* session)
	{
		CNetServer* target = (CNetServer*)owner;
		if (NULL == target)	return;
		target->OnIoDisconnected(session);
	}
	//static function
	void CNetServer::Callback_OnIoRecvTcpPacket(void* owner, CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		CNetServer* target = (CNetServer*)owner;
		if (NULL == target)	return;
		target->OnIoRecvNetServerPacket(session, msgRecv);
	}
	//static function
	void CNetServer::Callback_OnIoRecvUdpPacket(void* owner, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
	{
		CNetServer* target = (CNetServer*)owner;
		if (NULL == target)	return;
		target->OnIoRecvNetServerPacket(remoteIP, remotePort, msgRecv);
	}

	//from NetIocp
	void CNetServer::OnIoRecvNetServerPacket(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		//LOGEVENT("HG_WHITE", _T("received: CNetServer::OnIoRecvNetServerPacket()"));
		ADDR_IP remoteIP = 0;
		ADDR_PORT remotePort = 0;
		OnIoRecvNetServerPacket(session, remoteIP, remotePort, msgRecv);
	}
	//from NotUdpIocp
	void CNetServer::OnIoRecvNetServerPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
	{
		CRemoteSession* session = CRemoteSessionManager::Instance().FindAddressIPToSession(remoteIP, remotePort);
		//NULL üũ���� ������.??������ �м���(�������� ����ȵ�)
		//����: OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ ������ ip/port�� session������ ã�� �� ���� ����.
		//if(NULL == session)
		//	continue;

		if(NULL != session)
			LOGEVENT("Session_Base_Info", _T(" # recv data : from entry(%d), size(%d)"), session->GetRemoteEntry(), msgRecv.GetSize());

		OnIoRecvNetServerPacket(session, remoteIP, remotePort, msgRecv);
	}

	void CNetServer::OnIoRecvNetServerPacket(CRemoteSession* session, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
	{
		//��� ��ȣ
		if (FALSE == m_module.CheckValid())
			return;

		TIME_T timeTakes = HisUtil::GetUniversalTime();

		// �������ݿ� ���� switch ��
		switch (msgRecv.ID())
		{
			//TCP
			ON_RECEIVE_FROM_CLIENT(NetC2S_CORE_SIGN_UP_REQ)
			//ON_RECEIVE_FROM_CLIENT(NetC2S_CORE_HEART_BEAT_ACK)

			//UDP-holepunching to server
			ON_RECEIVE_FROM_CLIENT_UDP(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ)
			ON_RECEIVE_FROM_CLIENT(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ)
			ON_RECEIVE_FROM_CLIENT(CORE_UDP_RELAY_SERVER_TO_PEER_NTF)
			
			//not using
			//UDP-holepunching to peer(client)
			//ON_RECEIVE_FROM_CLIENT(NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF)

#if __HEART_BEAT__
			ON_RECEIVE_FROM_CLIENT(NetC2S_CORE_HEART_BEAT_ACK)
#endif //..__HEART_BEAT__

		default:
			{
				if(NULL != session)
					OnIoRecv(session, msgRecv);

				//LOGEVENT("HG_RED", _T("Not Support TCP Protocol(0x%04x)! Host id(0x%p)"), msgRecv.ID(), object)

				// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
				//OnIoDisconnected(object)

			} break;
		}
		msgRecv.Clear();
	}

};//..namespace NetCore {