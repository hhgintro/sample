#include "stdafx.h"
#include "RemoteSession.h"

namespace NetCore {

	extern CNetServer* g_server;

	CRemoteSession::CRemoteSession(VOID)
	{
		Clear();
	}

	CRemoteSession::~CRemoteSession(VOID)
	{
	}

	void CRemoteSession::Clear()
	{
		IRemote::Clear();

		mTcpPacketNumber = 0;
		mUdpPacketNumber = 0;

#if __HEART_BEAT__
		vecHeartBeat_.clear();
		TotolHeartBeat_ = 0;
		AverageHeartBeat_ = 0;
		//LastHeartBeatTime_ = 0;
		HEART_BEAT_PERMIT_TICK = TIME_SEC(30);// TIME_MIN(1);//heart beat를 허용 체크 시간
		//LOGEVENT("HG_RED", _T("SET HeartBeatPermitTick(%u) clear"), HEART_BEAT_PERMIT_TICK);
		LastHeartBeatTime_ = ::GetTickCount64() + (HEART_BEAT_PERMIT_TICK * 2);
		HeartBeatTime_ = ::GetTickCount64() + (HEART_BEAT_REQUEST_TICK * 2);
#endif //..__HEART_BEAT__

		//choice_charinfo_ = NULL;
		//accountinfo_ = NULL;

		//bIsDuplicatedConnect_ = FALSE;

		bReady_ = FALSE;
	}

	BOOL CRemoteSession::Begin(int nRecvTcpPoolSize, int nRecvUdpPoolCnt)
	{
		////AUTO_LOCK(csSession_);//CThreadSync Sync
		if (!g_server)
			return FALSE;

		Clear();
		//return CPacketSession::Begin(MSG_TOTAL_SIZE * MAX_RECV_QUEUE_COUNT, MAX_RECV_UDP_QUEUE_COUNT);
		return CPacketSession::Begin(nRecvTcpPoolSize, nRecvUdpPoolCnt);
	}

	BOOL CRemoteSession::End(SOCKET listenSocket, int nRecvTcpPoolSize, int nRecvUdpPoolCnt)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		LOGEVENT("Session_Base_Packet", _T("user disconnected : HOSTID(0x%p)"), this);

		if (!g_server)
			return FALSE;

		//초기화.
		IRemote::Clear();

		// 개체를 종료해 줍니다.
		if (!CPacketSession::End())
			return FALSE;

		// 개체를 다시 시작하고 Accept상태로 만들어 줍니다.
		if (!Begin(nRecvTcpPoolSize, nRecvUdpPoolCnt))
		{
			LOGEVENT("Session_Base_Error", _T("Error CNetIocp::Begin"));
			return FALSE;
		}

		if (!CPacketSession::Accept(listenSocket))
		{
			LOGEVENT("Session_Base_Error", _T("Error CNetIocp::Accept"));
			return FALSE;
		}

		if (!g_server->GetNetIocp().RegisterSocketToIocp(GetSocket(), reinterpret_cast<ULONG_PTR>(this)))
		{
			LOGEVENT("Session_Base_Error", _T("Error CNetIocp::RegisterSocketToIocp"));
			return FALSE;
		}

		return TRUE;
	}

	IRemote* CRemoteSession::FindRemote(HOSTID remote)
	{
		return this;
	}

	CPacketSession* CRemoteSession::FindPacketSession(IRemote* peer, bool bIsUdp)
	{
		//접속이 종료되었다면...
		if (FALSE == IsConnected())
		{
			//LOGEVENT("Session_Base_Error", _T("Fail disconnected netclient : 접속종료가 아닌데 출력되면 문제있슴"));
			return NULL;
		}


		if (bIsUdp)
		{
			switch (GetHolePunchingStep())
			{
			case enPublicAttempt:
			case enPublicSuccess:
			case enPrivateAttempt:
			case enPrivateSuccess:
				return g_server->GetNetUdpIocp().GetUdpSession();
			}
		}

		return this;
	}

	void CRemoteSession::Update(SOCKET listenSocket)
	{
		if (FALSE == IsConnected())
			return;

#if __HEART_BEAT__
		if (TRUE == GetSessionReady())
		{
			//LastHeartBeatTime_
			//초기값이 0이므로 끊어지지 않고 있어 connectcomplete되면 시간을 다시 설정해 준다.
			//(함수 SendConnectComplete() )
			TIME_T current_tick = ::GetTickCount64();
			if (LastHeartBeatTime_ + HEART_BEAT_PERMIT_TICK < current_tick)
			{
				if (NULL != g_server)
					g_server->ProcessDisconnect(this);
				LOGEVENT("Session_Base_Error", _T("Error HeartBeatPermitTick(%u) OVER(%u)"), HEART_BEAT_PERMIT_TICK, (current_tick-LastHeartBeatTime_));
				return;
			}
		}

		SendHeartBeat();
#endif //..__HEART_BEAT__
	}

	void CRemoteSession::SendConnectComplete()
	{
		//Sleep(500);//원활한 접속을 위해 잠시 delay
		stNetC2S_CORE_CONNECT_COMPLETED_NTF stNtf;
		stNtf.remote = GetHostID();
		SEND_NetC2S_CORE_CONNECT_COMPLETED_NTF(GetHostID(), stNtf);
	}
#if __HEART_BEAT__
	void CRemoteSession::SendHeartBeat()
	{
		if (::GetTickCount64() < HeartBeatTime_)
			return;
		HeartBeatTime_ = ::GetTickCount64() + HEART_BEAT_REQUEST_TICK;

		if (FALSE == GetSessionReady())
			return;

		stNetC2S_CORE_HEART_BEAT_REQ stReq;
		stReq.servertime = ::GetTickCount64();
		SEND_NetC2S_CORE_HEART_BEAT_REQ(GetHostID(), stReq);
	}

	void CRemoteSession::SetHeartBeat(TIME_T beat)
	{
		LastHeartBeatTime_ = ::GetTickCount64();

		//보낸 시간이 더 큰(기이한) 경우를 대비해서.
		TIME_T diff = LastHeartBeatTime_ - beat;
		TotolHeartBeat_ += diff;
		vecHeartBeat_.push_back(diff);

		if (HEART_BEAT_AVERAGE_COUNT < vecHeartBeat_.size())
		{
			std::vector<TIME_T>::iterator iter = vecHeartBeat_.begin();
			TotolHeartBeat_ -= (*iter);
			vecHeartBeat_.erase(iter);
		}

		AverageHeartBeat_ = TotolHeartBeat_ / vecHeartBeat_.size();
	}

	UINT64 CRemoteSession::GetHeartBeat()
	{
		return AverageHeartBeat_;
	}
#endif //..__HEART_BEAT__

};//..namespace NetCore {