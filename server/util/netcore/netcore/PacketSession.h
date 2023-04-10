#pragma once


namespace NetCore {

	typedef struct _READ_PACKET_INFO
	{
		ADDR_IP ip;			//보내온 곳 ip
		ADDR_PORT port;
		HisUtil::PacketNum	recvLastPacketNumber;	//마지막에 받은 패킷번호
		volatile HisUtil::PacketNum	sendPacketNumber;		//보낼 패킷번호
		TIME_T updatetime;	//
	} READ_PACKET_INFO;

	class CPacketSession : public CNetworkSession
	{
	public:
		CPacketSession(VOID);
		virtual ~CPacketSession(VOID);

	public:
		BOOL	Begin(int nRecvTcpPoolSize, int nRecvUdpPoolCnt);
		BOOL	End(VOID);

		BOOL	RecvPacketForIocp(int readLength);
		BOOL	RecvPacketForEventSelect(DWORD& ReadBytes);

		BOOL	RecvFromPacketForIocp(DWORD readLength);
		BOOL	RecvFromPacketForEventSelect(DWORD& readLength);

		BOOL	SendPacket(HisUtil::CMsg& msg);//, DWORD protocol, const BYTE *packet, DWORD packetLength)
		BOOL	SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort);//, DWORD protocol, const BYTE *packet, DWORD packetLength)
		//BOOL	SendTcpComplete(VOID);
		//BOOL	SendUnreliableUdpComplete(VOID);

		BOOL	ResetUdp(VOID);

		BOOL	GetPacket(HisUtil::CMsg& msgRecv);//, DWORD &protocol, BYTE *packet, DWORD &packetLength)
			BOOL CheckTcpPacketNum(HisUtil::CMsg& msgRecv);
		BOOL	GetFromPacket(HisUtil::CMsg& msgRecv, ADDR_IP& remoteIP, ADDR_PORT& remotePort);//, DWORD &protocol, BYTE *packet, DWORD &packetLength)
			BOOL CheckUdpPacketNum(stUdpPacket* packet);

		/*!
		//동일 ip/port에서 메시지가 들어올 확률은 그의없지만,
		//만약에 이전 num가 남아 있다면, 데이타를 받을수 없게되는 문제로 인해
		//해당 ip/port를 소유한 remote가 접속종료시에 같이 clear 한다.
		*/
		READ_PACKET_INFO* GetPacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort);
		void	ReleasePacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort);

	private:
		HisUtil::CPacketBuffer	queueRecvTcpPacket_;
		//HisUtil::CPoolBuffer	queueRecvUdpPacket_;

		//HisUtil::CPoolBuffer	queueSendPacket_;
		//HisUtil::CPoolBuffer	queueSendTcpPacket_;

		//INT				mRemainLength
		HisUtil::PacketNum	mCurrentPacketNumber;		//TCP전용(send용)
		HisUtil::PacketNum	mLastReadTcpPacketNumber;	//TCP전용

		//std::vector<READ_PACKET_INFO>		mLastReadPacketInfoVectorForUdp;
		HisUtil::CMemoryPool<INT64, READ_PACKET_INFO> LastPacketInfoForUdp_;

		HANDLE				TcpSendCompleteEvent_;	// send completed event

	protected:
		HisUtil::CCritSecBase csSession_;

		HisUtil::CCritSecBase csCurrentPacketNumber_;	//mCurrentPacketNumber을 보호한다.
		HisUtil::CCritSecBase csLastPacketNumber_;		//mLastReadTcpPacketNumber을 보호한다.



	};

};//..namespace NetCore {