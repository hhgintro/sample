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
		HEART_BEAT_PERMIT_TICK = TIME_SEC(30);// TIME_MIN(1);//heart beat�� ��� üũ �ð�
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

		//�ʱ�ȭ.
		IRemote::Clear();

		// ��ü�� ������ �ݴϴ�.
		if (!CPacketSession::End())
			return FALSE;

		// ��ü�� �ٽ� �����ϰ� Accept���·� ����� �ݴϴ�.
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
		//������ ����Ǿ��ٸ�...
		if (FALSE == IsConnected())
		{
			//LOGEVENT("Session_Base_Error", _T("Fail disconnected netclient : �������ᰡ �ƴѵ� ��µǸ� �����ֽ�"));
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
			//�ʱⰪ�� 0�̹Ƿ� �������� �ʰ� �־� connectcomplete�Ǹ� �ð��� �ٽ� ������ �ش�.
			//(�Լ� SendConnectComplete() )
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
		//Sleep(500);//��Ȱ�� ������ ���� ��� delay
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

		//���� �ð��� �� ū(������) ��츦 ����ؼ�.
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