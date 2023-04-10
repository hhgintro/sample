#pragma once


namespace NetCore {

	const int RESERVED_CONNECTION_POOL = 5;	//일정수 이상의 connection을 미리 준비해 둔다.

	// Connected Session을 관리하는 클래스
	// 다중 스레드 환경에서 안전하게 사용하기 위해서 CMultiThreadSync를 상속받습니다.
	class CRemoteSessionManager : public HisUtil::CSingleton<CRemoteSessionManager>// : public CMultiThreadSync<CRemoteSessionManager>
	{
		struct stRemoteSessionIP
		{
			HisUtil::CMemoryPool<ADDR_PORT, CRemoteSession> pool_;
		};

	public:
		typedef HisUtil::CMemoryQueuePool<CRemoteSession> REMOTE_QUEUE_POOL;
		typedef HisUtil::CMemoryPool<HOSTID, CRemoteSession> REMOTE_SESSION_POOL;

		//typedef HisUtil::CMemoryPool<INT64, CRemoteSession> REMOTE_SESSION_POOL_FOR_UDP;
		typedef HisUtil::CMemoryPool<ADDR_IP, stRemoteSessionIP> REMOTE_SESSION_POOL_FOR_UDP;


	public:
		CRemoteSessionManager(VOID) : dwMaxUserCount_(0), dwCurrentSessionCount_(0), nRecvTcpPoolSize_(0), nRecvUdpPoolCnt_(0) {}
		virtual ~CRemoteSessionManager(VOID) {}

		// 시작하는 함수
		BOOL Begin(int nMaxUser, int nRecvTcpPoolSize, int nRecvUdpPoolCnt);
		// 종료하는 함수
		VOID End(VOID);
		void Update();

		BOOL AcceptNewConnection();

		IRemote* FindRemote(HOSTID remote);

		// 접속된 모든 Session에 패킷을 전송하는 함수
		VOID SendAll(HisUtil::CMsg& msg);//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)
		VOID SendToAll(HisUtil::CMsg& msg);//, DWORD dwProtocol, BYTE *pData, DWORD dwLength)

		void Connect(CRemoteSession* session);
		void Disconnect(CRemoteSession* session);

		void RegisterAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort, CRemoteSession* session);
		CRemoteSession* FindAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort);
		void RemoveAddressIPToSession(ADDR_IP remoteIP, ADDR_PORT remotePort);

		REMOTE_SESSION_POOL& GetRemoteSessionPool() { return RemoteSessionPool_; }

		inline VOID	IncreaseMaxUserCount(VOID) { InterlockedIncrement((LONG*)&dwMaxUserCount_); }
		inline VOID	IncreaseConnectedSessionCount(VOID) { InterlockedIncrement((LONG*)&dwCurrentSessionCount_); }
		inline VOID	DecreaseConnectedSessionCount(VOID) { InterlockedDecrement((LONG*)&dwCurrentSessionCount_); }


	private:

		REMOTE_QUEUE_POOL RemoteQueuePool_;		//session을 생성한다.
		REMOTE_SESSION_POOL RemoteSessionPool_;	//접속한 유저 목록(HOSTID로 관리된다. - RemoteQueuePool_ 에서 가져다 씁니다. )

		//INT64 : MAKEINT64(ip,port)-udp ip/port로 remote를 관리한다.
		REMOTE_SESSION_POOL_FOR_UDP RemoteSessionPoolForUdp_;

		DWORD dwMaxUserCount_;
		DWORD dwCurrentSessionCount_;

		SOCKET listensocket_;

		int nRecvTcpPoolSize_;
		int nRecvUdpPoolCnt_;

		//HisUtil::CCritSecBase csRemote_;
	};

};//..namespace NetCore {