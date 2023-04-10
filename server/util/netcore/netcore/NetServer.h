#pragma once

namespace NetCore {

	class CNetServer : public INetServerEvent, public NetC2S_SEND
	{
		typedef HisUtil::CMemoryPool<P2PGROUPID, CP2PGroup> GROUP_POOL;

	public:
		CNetServer(void);
		virtual ~CNetServer(void);

		DWORD Start(int maxuser, ADDR_PORT portTcp, ADDR_PORT portUdp, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, int nRemoteRecvTcpPoolSize, int nRemoteRecvUdpPoolCnt);

		//extra udp pool
		DWORD AddExtraUdp(ADDR_PORT portUdp, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, void* owner, void* callback_OnIoRecvPacket);
		void SubExtraUdp(ADDR_PORT portUdp);
		//portUdp 로 바인딩된 CNetUdpIocp개체를 이용해서 보내게 된다.
		BOOL SendExtraUdp(ADDR_PORT portUdp, HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort);

		virtual void Update();//일정주기 갱신을 요하는 처리

		P2PGROUPID CreateP2PGroup();
		void DestroyP2PGroup() {}
		void JoinP2PGroup(P2PGROUPID id, CRemoteSession* session);
		void LeaveP2PGroup(P2PGROUPID id, CRemoteSession* session);

		//강제로 접속을 종료한다.
		virtual void ProcessDisconnect(CRemoteSession* session);
		virtual void ProcessDisconnect(HOSTID remote);

		virtual IRemote* FindRemote(HOSTID remote);
		virtual CPacketSession* FindPacketSession(IRemote* peer, bool bIsUdp);

		//return : false이면 받은 protocol을 무시한다.
		virtual BOOL CheckSessionStatus(CRemoteSession* session, int check);

		CNetIocp& GetNetIocp() { return NetIocp_; }
		CNetUdpIocp& GetNetUdpIocp() { return NetUdpIocp_; }

		ADDR_IP GetPrivateIP() { return NetIocp_.GetPrivateIP(); }

		ADDR_PORT& GetTcpPort() { return portTcp_; }
		void SetTcpPort(ADDR_PORT port) { portTcp_ = port; }

		ADDR_PORT& GetUdpPort() { return portUdp_; }
		void SetUdpPort(ADDR_PORT port) { portUdp_ = port; }

		//CP2PGroup& GetP2PGroup()		{ return P2PGroup_; }
		//GroupPool& GetP2PGroupPool()	{ return mapGroupPool_; }

	//protected:

	private:

		static void Callback_OnIoConnected(void* owner, CRemoteSession* session);
		static void Callback_OnIoDisconnected(void* owner, CRemoteSession* session);
		static void Callback_OnIoRecvTcpPacket(void* owner, CRemoteSession* session, HisUtil::CMsg& msgRecv);
		static void Callback_OnIoRecvUdpPacket(void* owner, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);

		void OnIoRecvNetServerPacket(CRemoteSession* session, HisUtil::CMsg& msgRecv);
		void OnIoRecvNetServerPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);
		void OnIoRecvNetServerPacket(CRemoteSession* session, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);

		//////////////////////////////////////////////////////////////////////////
		// 프로토콜 처리 함수

		//TCP
		void OnNetC2S_CORE_SIGN_UP_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);
		//void OnNetC2S_CORE_HEART_BEAT_ACK(CRemoteSession* session, HisUtil::CMsg& msgRecv);


		//UDP
		void OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort);
		void OnNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);
		void OnCORE_UDP_RELAY_SERVER_TO_PEER_NTF(CRemoteSession* session, HisUtil::CMsg& msgRecv);

		//void OnNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(CRemoteSession* session, HisUtil::CMsg& msgRecv);

#if __HEART_BEAT__
		void OnNetC2S_CORE_HEART_BEAT_ACK(CRemoteSession* session, HisUtil::CMsg& msgRecv);
#endif //..__HEART_BEAT__

		//..// 프로토콜 처리 함수
		//////////////////////////////////////////////////////////////////////////

	private:
		CNetUdpIocp NetUdpIocp_;
		CNetIocp NetIocp_;
		HisUtil::CMemoryPool<ADDR_PORT, CNetUdpIocp> ExtraUdpPool_;	//extra udp pool

		ADDR_PORT portTcp_;
		ADDR_PORT portUdp_;

		//CP2PGroup P2PGroup_;
		GROUP_POOL P2PGroupPool_;
		//TIME_T servertime_;//모듈 안전 보완을 위해


		HisUtil::CModule m_module;
	};

};//..namespace NetCore {