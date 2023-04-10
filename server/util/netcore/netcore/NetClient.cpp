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
		ADD_BIT_FLAG(ConnectStatus_, C_STATUS::eC_Connected);//���ӵ��
		GetPeerPool().End();
	}
	VOID CNetClient::OnIoDisconnected(VOID)
	{
		ClientTcpSession_.End();
		ClientUdpSession_.End();

		ConnectStatus_ = C_STATUS::eC_Closed;//��������

		//client�� �������� ���� �ʴ´�.
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
		LOGEVENT("HG_CYAN", _T("��� Peer(%d)���� �غ�(Ȧ��Ī)�� �Ϸ�Ǿ����ϴ�."), (int)vecAll.size());
	}

	DWORD CNetClient::BeginClient(ADDR_IP ip, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvTcpPoolSize, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, BOOL reconnect/*FALSE*/)
	{
		//AUTO_LOCK(csNet_);


		//�������̳�?
		if (TRUE == IsConnected())
			return ERR_CLIENT_IS_CONNECTED;

		if (++attemptcount_ < 2)
		{
			//���� �õ����̳�?
			if (TRUE == IsAttemptConnecting())
				return ERR_CLIENT_IS_CONNECTING;
		}
		attemptcount_ = 0;


		//���� �õ�
		ADD_BIT_FLAG(ConnectStatus_, C_STATUS::eC_AttemptConnect);//���ӵ��

		RemoteServer_.Clear();
		//������ ���� ����
		RemoteServer_.SetRemotePublicIP(ip);
		RemoteServer_.SetRemotePublicTcpPort(portTcp);
		//SIGN_UP_ACK���� ���ŵ˴ϴ�.
		//RemoteServer_.SetRemotePublicUdpPort(portUdp);

		nRecvTcpPoolSize_ = nRecvTcpPoolSize;
		nRecvUdpPoolCnt_ = nRecvUdpPoolCnt;
		nSendUdpPoolCnt_ = nSendUdpPoolCnt;

		ClientTcpSession_.SetOwner(this);
		LOGEVENT("Session_Base_Info", _T("+ Tcp socket begin"));
		if (FALSE == ClientTcpSession_.BeginTcp(ip, portTcp, nRecvTcpPoolSize_))
		{
			ConnectStatus_ = C_STATUS::eC_Closed;//��������
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
			ConnectStatus_ = C_STATUS::eC_Closed;//��������
			return ERR_CLIENT_FAIL_BEGIN_UDP;
		}
		//UDP private ip/port�� �̰��� �����ٰ� ����ϸ� �ǰڱ���.
		////wchar_t wzAddr[16] = L"";
		//HisUtil::IP_nTow(ClientUdpSession_.GetPrivateIP(), wzAddr, sizeof(wzAddr));
		//wprintf(L"local udp ip:%s\n", wzAddr);
		//printf("udp port:%d\n", ClientUdpSession_.GetPrivatePort());

		//�翬�Ῡ��
		reconnect_ = reconnect;
		return SERVER_OK;
	}

	BOOL CNetClient::End()
	{
		ClientTcpSession_.End();
		LOGEVENT("Session_Base_Info", _T("ClientTcpSession_.End();"));

		ClientUdpSession_.End();
		LOGEVENT("Session_Base_Info", _T("ClientUdpSession_.End();"));

		ConnectStatus_ = C_STATUS::eC_Closed;//��������

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

		////HG[2017.11.01]udp ��� Ȯ�ε� : udp�� ������� �ʽ��ϴ�.
		//return;

		//�����ֱ⸶�� ���ŵǾ�� �ϴ� �׸�
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

		//����ڰ� ������ ����...
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

		////Ȧ��Ī�� ������ ���� ����
		//if (peer->GetHolePunchingStep() == enSuccess)
		//	return TRUE;

		////hole-punching ������ ��쿡�� ����.
		//if (peer->GetHolePunchingStep() == enFailed)
		//	return FALSE;

		switch (peer->GetHolePunchingStep())
		{
			//Ȧ��Ī�� ������ ���� ����
		case enPrivateSuccess:
		case enPublicSuccess:
			//���������� ����.
			GetHolpunchingPool().Erase(peer->GetHostID());
			return TRUE;

			//hole-punching ������ ��쿡�� ����.
		//case enPrivateFailed://public�� �����ϹǷ� ���⼭�� �ּ�ó����.
		case enPublicFailed:
			//public���� �����ϸ�...����.
			GetHolpunchingPool().Erase(peer->GetHostID());
			return FALSE;

		default:
			break;
		}

		//�õ� ȸ�� ����
		if (HOLE_PUNCHING_ATTEMPT_COUNT < peer->IncHolePunchingAttempt())
		{
			//Ȧ��Ī ����
			//������ ���� ���� ��û�Ѵ�.

			//Peer ���� Ȧ��Ī ����� �����Ѵ�.
			peer->SetHolePunchingAttempt(0);
			//private�õ������ϸ�...public�����ϰ� �׸��� �����ϸ�. FAILó��
			if(enPublicAttempt == peer->GetHolePunchingStep())
			{
				peer->SetHolePunchingStep(enPublicFailed);
				LOGEVENT("Session_Base_Error", _T("(public)failed hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());

				////Peer ���� Ȧ��Ī ����� ������ �뺸�Ѵ�.
				//stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF stNtf;
				//stNtf.result = ERR_HOLE_PUNCHING_EXCEED_THE_COUNT_LIMIT;
				//stNtf.remoteFrom = remoteClient_.GetHostID();
				//stNtf.remoteTo = peer->GetHostID();
				//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(Host_Server, RELIABLE, stNtf);
				return FALSE;
			}

			//public �õ�����.
			peer->SetHolePunchingStep(enPublicAttempt);
			LOGEVENT("Session_Base_Info", _T("(public attempt)hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());
		}

		//�̰� �� ��� udp ������ �����ϴ�.
		if(enNotYet == peer->GetHolePunchingStep())
		{
			peer->SetHolePunchingStep(enPrivateAttempt);
			LOGEVENT("Session_Base_Info", _T("(private attempt)hole punching from peer(0x%p) to peer(0x%p)"), remoteClient_.GetHostID(), peer->GetHostID());
		}

		//HG_TODO : private �� ������ �� ���
		//HG_TODO : public �� ������ �� ���
		//HG_TODO : server �� ������ �� ���


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
		//������ ����Ǿ��ٸ�...
		if (FALSE == IsConnected())
		{
			LOGEVENT("Session_Base_Error", _T("Fail disconnected netclient : �������ᰡ �ƴѵ� ��µǸ� �����ֽ�"));
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
		//������ ������� ������ ���� ������� ���� �׳� �����ش�.


		// �������ݿ� ���� switch ��
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

			// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
			//OnIoDisconnected(pObject);
			//LOGEVENT("HG_RED", _T("������ �����մϴ�."));

		} break;
		}
		msgRecv.Clear();
	}

};//..namespace NetCore {