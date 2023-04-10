#pragma once

namespace NetCore {

	//일정시간마다 홀펀칭을 시도한다.(홀펀칭이 성공하지 않은 peer간에만)
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
		int attemptcount_;	//접속 시도회수

		//클라이언트 자신
		CRemotePeer	remoteClient_;
		//REMOTE_ENTRY_T entry_;
		BOOL reconnect_;			//연결종료시 재연결시도 여부

		//netclient자신이 서버의 기능을 할때 port
		//ADDR_PORT serverTcpPort_;

		//동일 group 내 다른 members
		REMOTE_PEER_POOL mapPeerPool_;
		//hole punching 대상자
		REMOTE_PEER_POOL mapHolpunchingPool_;

		//접속할 서버
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
		

		//일정주기 갱신을 요하는 처리
		virtual void Update();
		//BOOL IsConnected() { return eC_Connected == (ConnectStatus_ & eC_Connected); }
		BOOL IsConnected() { return CHECK_BIT_FLAG(ConnectStatus_, C_STATUS::eC_Connected); }
		BOOL IsAttemptConnecting() { return CHECK_BIT_FLAG(ConnectStatus_, C_STATUS::eC_AttemptConnect); }

		DWORD BeginClient(ADDR_IP ip, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvTcpPoolSize, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, BOOL reconnect=FALSE);
		BOOL End();

		//주기적으로 홀펀칭을 시도한다.
		BOOL HolePunching();
		//remote와 홀펀칭을 시도한다.
		BOOL HolePunching(HOSTID remote);
		BOOL HolePunching(CRemotePeer* peer);

		CTcpClientSession& GetTcpSession() { return ClientTcpSession_; }
		CUdpClientSession& GetUdpSession() { return ClientUdpSession_; }

		virtual IRemote* FindRemote(HOSTID remote);
		virtual CPacketSession* FindPacketSession(IRemote* peer, bool bIsUdp);


		//remoteIP, remotePort
		//지금은 사용하지 않지만 추후 디버깅을 위해 그냥 남겨준다.
		void OnIoRecvPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);

		////netclient자신이 서버의 기능을 할때 port
		//void SetServerTcpPort(ADDR_PORT port) { GetRemoteClient().GetRemoteServerInfo().portTcp_ = port; }
		//ADDR_PORT GetServerTcpPort() { return GetRemoteClient().GetRemoteServerInfo().portTcp_; }

		void SetRemoteEntry(REMOTE_ENTRY_T entry) { GetRemoteClient().SetRemoteEntry(entry); }
		REMOTE_ENTRY_T GetRemoteEntry() { return GetRemoteClient().GetRemoteEntry(); }

		//void SetStatus(REMOTE_CLIENT_STATUS s) { status_ = s; }
		//REMOTE_CLIENT_STATUS GetStatus() { return status_; }


		//CP2PGroup& GetP2PGroup() { return P2PGroup_; }

		//자신의 정보
		CRemotePeer& GetRemoteClient() { return remoteClient_; }
		//타인의 정보
		REMOTE_PEER_POOL& GetPeerPool() { return mapPeerPool_; }
		//hole punching 대상자
		REMOTE_PEER_POOL& GetHolpunchingPool() { return mapHolpunchingPool_; }
		//접속할 서버의 정보
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