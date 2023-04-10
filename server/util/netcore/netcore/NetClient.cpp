#include "stdafx.h"
#include "NetClient.h"

namespace NetCore {

	CNetClient::CNetClient(void) : tickHolePunching_(0), reconnect_(FALSE)//, status_(CLIENT_DISCONNECTED)
		//, serverIP_(0), serverTcpPort_(0), serverUdpPort_(0)
		, ConnectStatus_(C_STATUS::eC_Closed), tickReconnect_(0), attemptcount_(0)
		, nRecvTcpPoolSize_(0), nRecvUdpPoolCnt_(0), nSendUdpPoolCnt_(0)
	{
	}

	CNetClient::~CNetClient(void)
	{
	}

	VOID CNetClient::OnIoConnected(VOID)
	{
		ADD_BIT_FLAG(ConnectStatus_, C_STATUS::eC_Connected);//접속등록
		GetPeerPool().End();
	}
	VOID CNetClient::OnIoDisconnected(VOID)
	{
		ClientTcpSession_.End();
		ClientUdpSession_.End();

		ConnectStatus_ = C_STATUS::eC_Closed;//접속해제

		//client는 재접속을 하지 않는다.
		if (TRUE == reconnect_)
			BeginClient(RemoteServer_.GetRemotePublicIP(), RemoteServer_.GetRemotePublicTcpPort(), RemoteServer_.GetRemotePublicUdpPort()
				, nRecvTcpPoolSize_, nRecvUdpPoolCnt_, nSendUdpPoolCnt_, reconnect_);
	}

	VOID CNetClient::OnHolepunchingComplete(VOID)
	{
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
		LOGEVENT("HG_CYAN", _T("모든 Peer(%d)와의 준비(홀펀칭)가 완료되었습니다."), (int)vecAll.size());
	}

	DWORD CNetClient::BeginClient(ADDR_IP ip, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvTcpPoolSize, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, BOOL reconnect/*FALSE*/)
	{
		//AUTO_LOCK(csNet_);


		//접속중이냐?
		if (TRUE == IsConnected())
			return ERR_CLIENT_IS_CONNECTED;

		if (++attemptcount_ < 2)
		{
			//접속 시도중이냐?
			if (TRUE == IsAttemptConnecting())
				return ERR_CLIENT_IS_CONNECTING;
		}
		attemptcount_ = 0;


		//연결 시도
		ADD_BIT_FLAG(ConnectStatus_, C_STATUS::eC_AttemptConnect);//접속등록

		RemoteServer_.Clear();
		//접속할 서버 정보
		RemoteServer_.SetRemotePublicIP(ip);
		RemoteServer_.SetRemotePublicTcpPort(portTcp);
		//SIGN_UP_ACK에서 갱신됩니다.
		//RemoteServer_.SetRemotePublicUdpPort(portUdp);

		nRecvTcpPoolSize_ = nRecvTcpPoolSize;
		nRecvUdpPoolCnt_ = nRecvUdpPoolCnt;
		nSendUdpPoolCnt_ = nSendUdpPoolCnt;

		ClientTcpSession_.SetOwner(this);
		LOGEVENT("Session_Base_Info", _T("+ Tcp socket begin"));
		if (FALSE == ClientTcpSession_.BeginTcp(ip, portTcp, nRecvTcpPoolSize_))
		{
			ConnectStatus_ = C_STATUS::eC_Closed;//접속해제
			return ERR_CLIENT_FAIL_BEGIN_TCP;
		}
		//wchar_t wzAddr[16] = L"";
		//HisUtil::IP_nTow(ClientTcpSession_.GetPrivateIP(), wzAddr, sizeof(wzAddr));
		//wprintf(L"local tcp ip:%s\n", wzAddr);
		//printf("tcp port:%d\n", ClientTcpSession_.GetPrivatePort());

		ClientUdpSession_.SetOwner(this);
		LOGEVENT("Session_Base_Info", _T("+ Udp socket begin"));
		if (FALSE == ClientUdpSession_.BeginUdp(0, nRecvUdpPoolCnt_, nSendUdpPoolCnt))
		{
			ConnectStatus_ = C_STATUS::eC_Closed;//접속해제
			return ERR_CLIENT_FAIL_BEGIN_UDP;
		}
		//UDP private ip/port는 이것을 가져다가 사용하면 되겠군요.
		////wchar_t wzAddr[16] = L"";
		//HisUtil::IP_nTow(ClientUdpSession_.GetPrivateIP(), wzAddr, sizeof(wzAddr));
		//wprintf(L"local udp ip:%s\n", wzAddr);
		//printf("udp port:%d\n", ClientUdpSession_.GetPrivatePort());

		//재연결여부
		reconnect_ = reconnect;
		return SERVER_OK;
	}

	BOOL CNetClient::End()
	{
		ClientTcpSession_.End();
		LOGEVENT("Session_Base_Info", _T("ClientTcpSession_.End();"));

		ClientUdpSession_.End();
		LOGEVENT("Session_Base_Info", _T("ClientUdpSession_.End();"));

		ConnectStatus_ = C_STATUS::eC_Closed;//접속해제

		remoteClient_.Clear();
		RemoteServer_.Clear();

		mapPeerPool_.Clear();

		//entry_				= REMOTE_ENTRY::eNone;
		reconnect_			= FALSE;

		nRecvTcpPoolSize_	= 0;
		nRecvUdpPoolCnt_	= 0;
		nSendUdpPoolCnt_	= 0;

		//P2PGroupPool_.Clear();
		return TRUE;
	}

	void CNetClient::Update()
	{

		////HG[2017.11.01]udp 장애 확인됨 : udp를 사용하지 않습니다.
		//return;

		//일정주기마다 갱신되어야 하는 항목
		HolePunching();
	}

	BOOL CNetClient::HolePunching()
	{
		TIME_T present_time = ::GetTickCount64();
		if (present_time < tickHolePunching_)
			return FALSE;

		tickHolePunching_ = present_time + HOLE_PUNCHING_DELAY_TICK;

		//if(HisUtil::GetUniversalTime() < tickHolePunching_)
		//	return FALSE;

		//대상자가 없으면 무시...
		if (GetHolpunchingPool().GetUsedMemSize() <= 0)
			return FALSE;

		std::vector<CRemotePeer*> vecList;
		GetHolpunchingPool().GetAllList(vecList);
		for (std::vector<CRemotePeer*>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter)
			HolePunching(*iter);

		return TRUE;
	}

	BOOL CNetClient::HolePunching(HOSTID remote)
	{
		return HolePunching(GetPeerPool().Find(remote));
	}

	BOOL CNetClient::HolePunching(CRemotePeer* peer)
	{
		if (NULL == peer)
			return FALSE;

		////홀펀칭에 성공한 경우는 제외
		//if (peer->GetHolePunchingStep() == enSuccess)
		//	return TRUE;

		////hole-punching 실패한 경우에도 제외.
		//if (peer->GetHolePunchingStep() == enFailed)
		//	return FALSE;

		switch (peer->GetHolePunchingStep())
		{
			//홀펀칭에 성공한 경우는 제외
		case enPrivateSuccess:
		case enPublicSuccess:
			//성공했으니 제거.
			GetHolpunchingPool().Erase(peer->GetHostID());
			return TRUE;

			//hole-punching 실패한 경우에도 제외.
		//case enPrivateFailed://public을 진행하므로 여기서는 주석처리함.
		case enPublicFailed:
			//public마져 실패하면...제거.
			GetHolpunchingPool().Erase(peer->GetHostID());
			return FALSE;

		default:
			break;
		}

		//시도 회수 증가
		if (HOLE_PUNCHING_ATTEMPT_COUNT < peer->IncHolePunchingAttempt())
		{
			//홀펀칭 실패
			//서버를 통해 중재 요청한다.

			//Peer 간의 홀펀칭 결과를 저장한다.
			peer->SetHolePunchingAttempt(0);
			//private시도실패하면...public진행하고 그마져 실패하면. FAIL처리
			if(enPublicAttempt == peer->GetHolePunchingStep())
			{
				peer->SetHolePunchingStep(enPublicFailed);
				LOGEVENT("Session_Base_Error", _T("(public)failed hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());

				////Peer 간의 홀펀칭 결과를 서버에 통보한다.
				//stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF stNtf;
				//stNtf.result = ERR_HOLE_PUNCHING_EXCEED_THE_COUNT_LIMIT;
				//stNtf.remoteFrom = remoteClient_.GetHostID();
				//stNtf.remoteTo = peer->GetHostID();
				//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(Host_Server, RELIABLE, stNtf);
				return FALSE;
			}

			//public 시도진행.
			peer->SetHolePunchingStep(enPublicAttempt);
			LOGEVENT("Session_Base_Info", _T("(public attempt)hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());
		}

		//이걸 해 줘야 udp 전송이 가능하다.
		if(enNotYet == peer->GetHolePunchingStep())
		{
			peer->SetHolePunchingStep(enPrivateAttempt);
			LOGEVENT("Session_Base_Info", _T("(private attempt)hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());
		}

		//HG_TODO : private 로 보냈을 때 결과
		//HG_TODO : public 로 보냈을 때 결과
		//HG_TODO : server 로 보냈을 때 결과


		stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ stReq;
		stReq.remoteFrom = remoteClient_.GetHostID();
		stReq.remoteTo = peer->GetHostID();
		stReq.bpublic = peer->GetHolePunchingStep();
		SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(peer->GetHostID(), stReq);
		return TRUE;
	}

	IRemote* CNetClient::FindRemote(HOSTID remote)
	{
		if (Host_Server == remote)
			return &RemoteServer_;
		return GetPeerPool().Find(remote);
	}

	CPacketSession* CNetClient::FindPacketSession(IRemote* peer, bool bIsUdp)
	{
		//접속이 종료되었다면...
		if (FALSE == IsConnected())
		{
			LOGEVENT("Session_Base_Error", _T("Fail disconnected netclient : 접속종료가 아닌데 출력되면 문제있슴"));
			return NULL;
		}
		

		if (bIsUdp)
		{
			switch (RemoteServer_.GetHolePunchingStep())
			{
			case enPrivateAttempt:
			case enPrivateSuccess:
			case enPublicAttempt:
			case enPublicSuccess:
				return &ClientUdpSession_.GetPacketSession();
			}
		}

		return &ClientTcpSession_.GetPacketSession();
	}

	void CNetClient::OnIoRecvPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
	{
		//HG_TEST :
		//remoteIP, remotePort
		//지금은 사용하지 않지만 추후 디버깅을 위해 그냥 남겨준다.


		// 프로토콜에 따른 switch 문
		switch (msgRecv.ID())
		{
			//tcp
			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_CONNECT_COMPLETED_NTF);
			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_SIGN_UP_ACK);

			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_JOIN_GROUP_NTF);
			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_ENTER_GROUP_NTF);
			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_LEAVE_GROUP_NTF);


			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF);
			//udp
			ON_RECEIVE_ON_CLIENT_UDP(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ);
			ON_RECEIVE_ON_CLIENT_UDP(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK);

			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_HEART_BEAT_REQ);
			ON_RECEIVE_ON_CLIENT(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK);



		default:
		{
			OnIoRecv(msgRecv, remoteIP, remotePort);

			//LOGEVENT("HG_RED", _T("Not Support Tcp Protocol(0x%04x)"), msgRecv.ID());

			// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_RED", _T("접속을 해제합니다."));

		} break;
		}
		msgRecv.Clear();
	}

};//..namespace NetCore {