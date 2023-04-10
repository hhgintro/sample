#include "stdafx.h"
#include "RemoteSessionManager.h"


namespace NetCore {

	extern CNetServer* g_server;

	// CRemoteSessionManager�� �����ϴ� �Լ�
	BOOL CRemoteSessionManager::Begin(int nMaxUser, int nRecvTcpPoolSize, int nRecvUdpPoolCnt)
	{
		// ����ȭ ��ü
		//AUTO_LOCK(csRemote_);//CThreadSync Sync	

		if (0 == g_server)
			return FALSE;

		listensocket_ = g_server->GetNetIocp().GetListenSession().GetSocket();
		nRecvTcpPoolSize_ = nRecvTcpPoolSize;
		nRecvUdpPoolCnt_ = nRecvUdpPoolCnt;

		// �Ķ���ͷ� Listen��ü�� ������ �޾ƾ� �մϴ�.
		// ���� NULL�� ��� �����մϴ�.
		if (nMaxUser <= 0 || !listensocket_)
			return FALSE;

		RemoteQueuePool_.Begin(nMaxUser);
		for (int i = 0; i < nMaxUser; ++i)
		{
			//�ʱ� �����ڸ� ������ �д�.
			if (FALSE == AcceptNewConnection())
			{
				End();
				return FALSE;
			}
		}
		return TRUE;
	}

	// RemoteSessionManager�� �����ϴ� �Լ�
	VOID CRemoteSessionManager::End(VOID)
	{
		// ����ȭ ��ü
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		//������ ���� ����
		RemoteSessionPool_.End();
		RemoteQueuePool_.End();
	}

	void CRemoteSessionManager::Update()
	{
		std::vector<CRemoteSession*> vecList;
		RemoteSessionPool_.GetAllList(vecList);
		for (std::vector<CRemoteSession*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
		{
			CRemoteSession* session = *iter;
			if (session)	session->Update(listensocket_);
		}
	}

	BOOL CRemoteSessionManager::AcceptNewConnection()
	{
		CRemoteSession* session = RemoteQueuePool_.Create();
		session->Clear();

		if (!session->Begin(nRecvTcpPoolSize_, nRecvUdpPoolCnt_))
		{
			LOGEVENT("Session_Base_Error", _T("failed begin for reserved new connection"));
			End();
			return FALSE;
		}

		if (!session->Accept(listensocket_))
		{
			LOGEVENT("Session_Base_Error", _T("failed accept for reserved new connection"));
			End();
			return FALSE;
		}

		if (!g_server->GetNetIocp().RegisterSocketToIocp(session->GetSocket(), reinterpret_cast<ULONG_PTR>(session)))
		{
			LOGEVENT("Session_Base_Error", _T("failed register for reserved new connection"));
			End();
			return FALSE;
		}

		IncreaseMaxUserCount();
		//LOGEVENT("Session_Base_Info", _T("reserved new connection host id(0x%p)"), session);
		return TRUE;
	}

	IRemote* CRemoteSessionManager::FindRemote(HOSTID remote)
	{
		return RemoteSessionPool_.Find(remote);
	}

	// ���ӵ� ��� Session�� �����͸� �����ϴ� �Լ�
	VOID CRemoteSessionManager::SendAll(HisUtil::CMsg& msg)//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)
	{
		// ����ȭ ��ü
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		// ���ӵ� ��� ��ü�� WritePacket�� �� �ݴϴ�.
		std::vector<CRemoteSession*> vecList;
		RemoteSessionPool_.GetAllList(vecList);
		for (std::vector<CRemoteSession*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
		{
			CRemoteSession* session = *iter;
			// ���ӵǾ� �ִ� ��ü�� ��츸 WritePacket�� �� �ݴϴ�.
			if (session && session->IsConnected())
			{
				if (!session->SendPacket(msg))//, dwProtocol, pData, dwLength)
					session->End(listensocket_, nRecvTcpPoolSize_, nRecvUdpPoolCnt_);
			}
		}
	}

	// ���ӵ� ��� Session�� �����͸� �����ϴ� �Լ�
	VOID CRemoteSessionManager::SendToAll(HisUtil::CMsg& msg)//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)
	{
		// ����ȭ ��ü
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		std::vector<CRemoteSession*> vecList;
		RemoteSessionPool_.GetAllList(vecList);
		for (std::vector<CRemoteSession*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
		{
			CRemoteSession* session = *iter;
			// ���ӵǾ� �ִ� ��ü�� ��츸 WritePacket�� �� �ݴϴ�.
			if (session && session->IsConnected())
			{
				if (!g_server->GetNetUdpIocp().SendToPacket(msg, session->GetRemotePublicIP(), session->GetRemotePublicUdpPort()))
					session->End(listensocket_, nRecvTcpPoolSize_, nRecvUdpPoolCnt_);
			}
		}
	}

	void CRemoteSessionManager::Connect(CRemoteSession* session)
	{
		//AUTO_LOCK(csRemote_);//CThreadSync Sync
		assert(session);
		if (NULL == session)
			return;


		session->SetHostID((HOSTID)session);
		RemoteSessionPool_.Insert(session->GetHostID(), session);

		//�����ڰ� ������ �̻��� ���
		if (dwMaxUserCount_ < dwCurrentSessionCount_ + RESERVED_CONNECTION_POOL)
		{
			//���� �����ڸ� ������ �д�.
			AcceptNewConnection();
		}

		session->SetConnected(TRUE);
		session->SendConnectComplete();
		IncreaseConnectedSessionCount();
	}

	void CRemoteSessionManager::Disconnect(CRemoteSession* session)
	{
		//AUTO_LOCK(csRemote_);//CThreadSync Sync
		assert(session);
		if (NULL == session)
			return;

		////CRemoteSession��ü�� ����Ǳ� ���п� erase()�� ȣ���ϸ� �ȵȴ�.
		////�׷��� �Ʒ�ó�� ó���ߴ�.
		////bRestoreExcept : bIsAllocated_�� true�� �ϴ��� �����Ҷ� free�� ��ȯ���� �ʰڴٴ� ��
		////	��뿹 )	socket���� �Ҵ�� ������ ����.
		////				������ �����Ǿ����� socket�� ����Ǳ� ������
		////				memFree_�� ���� �� ����. �׷��ٰ� erase���� ������ memUsed_�� �������� ������ ��Եȴ�.
		//RemoteSessionPool_.Pop(session->GetHostID());

		//queue-pool���� ������ ����ϰ�, �� ���� session-pool�� queue-pool�� �ݳ��Ѵ�.
		RemoteSessionPool_.Erase(session->GetHostID());
		RemoteQueuePool_.Push(session);

		//CAccountInfo* accountinfo = session->GetAccountInfo();
		//if(accountinfo)
		//{
		//	//del charinfo
		//	std::vector<CCharInfo*> vecAll;
		//	accountinfo->charpool_.GetAllList(vecAll);
		//	for(int i=0; i<(int)vecAll.size(); ++i)
		//	{
		//		CCharInfo* charinfo = vecAll[i];
		//		if(NULL == charinfo)
		//			continue;
		//		GetCharInfoPool().Erase(charinfo->charpk_);
		//	}

		//	//del accountinf
		//	GetAccountInfoPool().Erase(accountinfo->accountpk_);
		//}



		//ip/port�� ��ϵ� remote�� clear �Ѵ�.
		RemoveAddressIPToSession(session->GetRemotePublicIP(), session->GetRemotePublicUdpPort());

		//CPacketSession�� packet number�� clear �Ѵ�.
		g_server->GetNetUdpIocp().GetUdpSession()->ReleasePacketNumberFromAddressIP(session->GetRemotePublicIP(), session->GetRemotePublicUdpPort());


		session->SetConnected(FALSE);
		session->End(listensocket_, nRecvTcpPoolSize_, nRecvUdpPoolCnt_);
		DecreaseConnectedSessionCount();
		LOGEVENT("Session_Base_Packet", _T("# Client disconnected : HOSTID(0x%p)"), session);
	}

	void CRemoteSessionManager::RegisterAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort, CRemoteSession* session)
	{
		//RemoteSessionPoolForUdp_.Insert(MAKEINT64(remoteIP, remotePort), session);
		stRemoteSessionIP* ip = RemoteSessionPoolForUdp_.Find(remoteIP);
		if (NULL == ip)
		{
			ip = RemoteSessionPoolForUdp_.Create();
			RemoteSessionPoolForUdp_.Insert(remoteIP, ip);
		}
		ip->pool_.Insert(remotePort, session);
	}

	CRemoteSession* CRemoteSessionManager::FindAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		//return RemoteSessionPoolForUdp_.Find(MAKEINT64(remoteIP, remotePort));
		stRemoteSessionIP* ip = RemoteSessionPoolForUdp_.Find(remoteIP);
		if (NULL == ip)	return NULL;

		return ip->pool_.Find(remotePort);
	}

	void CRemoteSessionManager::RemoveAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		//RemoteSessionPoolForUdp_.Erase(MAKEINT64(remoteIP, remotePort));
		stRemoteSessionIP* ip = RemoteSessionPoolForUdp_.Find(remoteIP);
		if (NULL == ip)	return;

		ip->pool_.Erase(remotePort);
	}

};//..namespace NetCore {