#pragma once

namespace NetCore {

	//�����ð����� Ȧ��Ī�� �õ��Ѵ�.(Ȧ��Ī�� �������� ���� peer������)
	const int HOLE_PUNCHING_DELAY_TICK = TIME_SEC(5);

	class CNetClient : public INetClientEvent, public NetC2S_SEND, public NetC2C_SEND
	{
	public:
		typedef HisUtil::CMemoryPool<HOSTID, CRemotePeer> REMOTE_PEER_POOL;

	private:
		CTcpClientSession ClientTcpSession_;
		CUdpClientSession ClientUdpSession_;

		//CP2PGroup P2PGroup_;

		TIME_T tickHolePunching_;

		//ADDR_IP serverIP_;
		//ADDR_PORT serverTcpPort_;
		//ADDR_PORT serverUdpPort_;

	protected:

		int ConnectStatus_;//C_STAUTS
		TIME_T tickReconnect_;
		int attemptcount_;	//���� �õ�ȸ��

		//Ŭ���̾�Ʈ �ڽ�
		CRemotePeer	remoteClient_;
		//REMOTE_ENTRY_T entry_;
		BOOL reconnect_;			//��������� �翬��õ� ����

		//netclient�ڽ��� ������ ����� �Ҷ� port
		//ADDR_PORT serverTcpPort_;

		//���� group �� �ٸ� members
		REMOTE_PEER_POOL mapPeerPool_;
		//hole punching �����
		REMOTE_PEER_POOL mapHolpunchingPool_;

		//������ ����
		CRemotePeer RemoteServer_;


		//REMOTE_CLIENT_STATUS status_;

		int nRecvTcpPoolSize_;
		int nRecvUdpPoolCnt_;
		int nSendUdpPoolCnt_;

		//HisUtil::CCritSecBase csNet_;

	public:
		CNetClient(void);
		virtual ~CNetClient(void);

		virtual VOID OnIoConnected(VOID);
		virtual VOID OnIoDisconnected(VOID);
		virtual VOID OnHolepunchingComplete(VOID);
		

		//�����ֱ� ������ ���ϴ� ó��
		virtual void Update();
		//BOOL IsConnected() { return eC_Connected == (ConnectStatus_ & eC_Connected); }
		BOOL IsConnected() { return CHECK_BIT_FLAG(ConnectStatus_, C_STATUS::eC_Connected); }
		BOOL IsAttemptConnecting() { return CHECK_BIT_FLAG(ConnectStatus_, C_STATUS::eC_AttemptConnect); }

		DWORD BeginClient(ADDR_IP ip, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvTcpPoolSize, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, BOOL reconnect=FALSE);
		BOOL End();

		//�ֱ������� Ȧ��Ī�� �õ��Ѵ�.
		BOOL HolePunching();
		//remote�� Ȧ��Ī�� �õ��Ѵ�.
		BOOL HolePunching(HOSTID remote);
		BOOL HolePunching(CRemotePeer* peer);

		CTcpClientSession& GetTcpSession() { return ClientTcpSession_; }
		CUdpClientSession& GetUdpSession() { return ClientUdpSession_; }

		virtual IRemote* FindRemote(HOSTID remote);
		virtual CPacketSession* FindPacketSession(IRemote* peer, bool bIsUdp);


		//remoteIP, remotePort
		//������ ������� ������ ���� ������� ���� �׳� �����ش�.
		void OnIoRecvPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);

		////netclient�ڽ��� ������ ����� �Ҷ� port
		//void SetServerTcpPort(ADDR_PORT port) { GetRemoteClient().GetRemoteServerInfo().portTcp_ = port; }
		//ADDR_PORT GetServerTcpPort() { return GetRemoteClient().GetRemoteServerInfo().portTcp_; }

		void SetRemoteEntry(REMOTE_ENTRY_T entry) { GetRemoteClient().SetRemoteEntry(entry); }
		REMOTE_ENTRY_T GetRemoteEntry() { return GetRemoteClient().GetRemoteEntry(); }

		//void SetStatus(REMOTE_CLIENT_STATUS s) { status_ = s; }
		//REMOTE_CLIENT_STATUS GetStatus() { return status_; }


		//CP2PGroup& GetP2PGroup() { return P2PGroup_; }

		//�ڽ��� ����
		CRemotePeer& GetRemoteClient() { return remoteClient_; }
		//Ÿ���� ����
		REMOTE_PEER_POOL& GetPeerPool() { return mapPeerPool_; }
		//hole punching �����
		REMOTE_PEER_POOL& GetHolpunchingPool() { return mapHolpunchingPool_; }
		//������ ������ ����
		CRemotePeer& GetRemoteServer() { return RemoteServer_; }

		//ADDR_IP GetServerIP() { return serverIP_; }
		//void SetServerIP(ADDR_IP ip) { serverIP_ = ip; }

		//ADDR_PORT GetServerTcpPort() { return serverTcpPort_; }
		//void SetServerTcpPort(ADDR_PORT port) { serverTcpPort_ = port; }

		//ADDR_PORT GetServerUdpPort() { return serverUdpPort_; }
		//void SetServerUdpPort(ADDR_PORT port) { serverUdpPort_ = port; }


	private:
		//TCP
		void OnNetC2S_CORE_CONNECT_COMPLETED_NTF(HisUtil::CMsg& msgRecv);
		void OnNetC2S_CORE_SIGN_UP_ACK(HisUtil::CMsg& msgRecv);

		void OnNetC2S_CORE_JOIN_GROUP_NTF(HisUtil::CMsg& msgRecv);
		void OnNetC2S_CORE_ENTER_GROUP_NTF(HisUtil::CMsg& msgRecv);
		void OnNetC2S_CORE_LEAVE_GROUP_NTF(HisUtil::CMsg& msgRecv);



		void OnNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF(HisUtil::CMsg& msgRecv);

		//UDP
		void OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort);
		void OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort);

		void OnNetC2S_CORE_HEART_BEAT_REQ(HisUtil::CMsg& msgRecv);
		void OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(HisUtil::CMsg& msgRecv);


	};

};//..namespace NetCore {