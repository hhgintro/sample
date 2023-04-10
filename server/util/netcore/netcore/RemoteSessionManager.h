#pragma once


namespace NetCore {

	const int RESERVED_CONNECTION_POOL = 5;	//������ �̻��� connection�� �̸� �غ��� �д�.

	// Connected Session�� �����ϴ� Ŭ����
	// ���� ������ ȯ�濡�� �����ϰ� ����ϱ� ���ؼ� CMultiThreadSync�� ��ӹ޽��ϴ�.
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

		// �����ϴ� �Լ�
		BOOL Begin(int nMaxUser, int nRecvTcpPoolSize, int nRecvUdpPoolCnt);
		// �����ϴ� �Լ�
		VOID End(VOID);
		void Update();

		BOOL AcceptNewConnection();

		IRemote* FindRemote(HOSTID remote);

		// ���ӵ� ��� Session�� ��Ŷ�� �����ϴ� �Լ�
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

		REMOTE_QUEUE_POOL RemoteQueuePool_;		//session�� �����Ѵ�.
		REMOTE_SESSION_POOL RemoteSessionPool_;	//������ ���� ���(HOSTID�� �����ȴ�. - RemoteQueuePool_ ���� ������ ���ϴ�. )

		//INT64 : MAKEINT64(ip,port)-udp ip/port�� remote�� �����Ѵ�.
		REMOTE_SESSION_POOL_FOR_UDP RemoteSessionPoolForUdp_;

		DWORD dwMaxUserCount_;
		DWORD dwCurrentSessionCount_;

		SOCKET listensocket_;

		int nRecvTcpPoolSize_;
		int nRecvUdpPoolCnt_;

		//HisUtil::CCritSecBase csRemote_;
	};

};//..namespace NetCore {