#include "stdafx.h"
#include "RemoteSessionManager.h"


namespace NetCore {

	extern CNetServer* g_server;

	// CRemoteSessionManager를 시작하는 함수
	BOOL CRemoteSessionManager::Begin(int nMaxUser, int nRecvTcpPoolSize, int nRecvUdpPoolCnt)
	{
		// 동기화 개체
		//AUTO_LOCK(csRemote_);//CThreadSync Sync	

		if (0 == g_server)
			return FALSE;

		listensocket_ = g_server->GetNetIocp().GetListenSession().GetSocket();
		nRecvTcpPoolSize_ = nRecvTcpPoolSize;
		nRecvUdpPoolCnt_ = nRecvUdpPoolCnt;

		// 파라미터로 Listen개체의 소켓을 받아야 합니다.
		// 값이 NULL일 경우 실패합니다.
		if (nMaxUser <= 0 || !listensocket_)
			return FALSE;

		RemoteQueuePool_.Begin(nMaxUser);
		for (int i = 0; i < nMaxUser; ++i)
		{
			//초기 접속자를 예약해 둔다.
			if (FALSE == AcceptNewConnection())
			{
				End();
				return FALSE;
			}
		}
		return TRUE;
	}

	// RemoteSessionManager를 종료하는 함수
	VOID CRemoteSessionManager::End(VOID)
	{
		// 동기화 개체
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		//접속자 정보 정리
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

	// 접속된 모든 Session에 데이터를 전송하는 함수
	VOID CRemoteSessionManager::SendAll(HisUtil::CMsg& msg)//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)
	{
		// 동기화 개체
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		// 접속된 모든 개체에 WritePacket을 해 줍니다.
		std::vector<CRemoteSession*> vecList;
		RemoteSessionPool_.GetAllList(vecList);
		for (std::vector<CRemoteSession*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
		{
			CRemoteSession* session = *iter;
			// 접속되어 있는 개체일 경우만 WritePacket을 해 줍니다.
			if (session && session->IsConnected())
			{
				if (!session->SendPacket(msg))//, dwProtocol, pData, dwLength)
					session->End(listensocket_, nRecvTcpPoolSize_, nRecvUdpPoolCnt_);
			}
		}
	}

	// 접속된 모든 Session에 데이터를 전송하는 함수
	VOID CRemoteSessionManager::SendToAll(HisUtil::CMsg& msg)//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)
	{
		// 동기화 개체
		//AUTO_LOCK(csRemote_);//CThreadSync Sync

		std::vector<CRemoteSession*> vecList;
		RemoteSessionPool_.GetAllList(vecList);
		for (std::vector<CRemoteSession*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
		{
			CRemoteSession* session = *iter;
			// 접속되어 있는 개체일 경우만 WritePacket을 해 줍니다.
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

		//접속자가 일정수 이상일 경우
		if (dwMaxUserCount_ < dwCurrentSessionCount_ + RESERVED_CONNECTION_POOL)
		{
			//여유 접속자를 예약해 둔다.
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

		////CRemoteSession개체는 재사용되기 때분에 erase()를 호출하면 안된다.
		////그래서 아래처럼 처리했다.
		////bRestoreExcept : bIsAllocated_가 true라 하더라도 해제할때 free로 반환하지 않겠다는 뜻
		////	사용예 )	socket으로 할당된 유저의 정보.
		////				접속이 해지되었더라도 socket은 재사용되기 때문에
		////				memFree_에 넣을 수 없다. 그렇다고 erase하지 않으면 memUsed_에 비접속자 정보를 담게된다.
		//RemoteSessionPool_.Pop(session->GetHostID());

		//queue-pool에서 꺼내서 사용하고, 다 쓰면 session-pool을 queue-pool에 반납한다.
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



		//ip/port로 등록된 remote를 clear 한다.
		RemoveAddressIPToSession(session->GetRemotePublicIP(), session->GetRemotePublicUdpPort());

		//CPacketSession의 packet number를 clear 한다.
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