#pragma once


namespace NetCore {

	typedef struct _READ_PACKET_INFO
	{
		ADDR_IP ip;			//������ �� ip
		ADDR_PORT port;
		HisUtil::PacketNum	recvLastPacketNumber;	//�������� ���� ��Ŷ��ȣ
		volatile HisUtil::PacketNum	sendPacketNumber;		//���� ��Ŷ��ȣ
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
		//���� ip/port���� �޽����� ���� Ȯ���� ���Ǿ�����,
		//���࿡ ���� num�� ���� �ִٸ�, ����Ÿ�� ������ ���ԵǴ� ������ ����
		//�ش� ip/port�� ������ remote�� ��������ÿ� ���� clear �Ѵ�.
		*/
		READ_PACKET_INFO* GetPacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort);
		void	ReleasePacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort);

	private:
		HisUtil::CPacketBuffer	queueRecvTcpPacket_;
		//HisUtil::CPoolBuffer	queueRecvUdpPacket_;

		//HisUtil::CPoolBuffer	queueSendPacket_;
		//HisUtil::CPoolBuffer	queueSendTcpPacket_;

		//INT				mRemainLength
		HisUtil::PacketNum	mCurrentPacketNumber;		//TCP����(send��)
		HisUtil::PacketNum	mLastReadTcpPacketNumber;	//TCP����

		//std::vector<READ_PACKET_INFO>		mLastReadPacketInfoVectorForUdp;
		HisUtil::CMemoryPool<INT64, READ_PACKET_INFO> LastPacketInfoForUdp_;

		HANDLE				TcpSendCompleteEvent_;	// send completed event

	protected:
		HisUtil::CCritSecBase csSession_;

		HisUtil::CCritSecBase csCurrentPacketNumber_;	//mCurrentPacketNumber�� ��ȣ�Ѵ�.
		HisUtil::CCritSecBase csLastPacketNumber_;		//mLastReadTcpPacketNumber�� ��ȣ�Ѵ�.



	};

};//..namespace NetCore {