#pragma once

#include <map>

namespace NetCore {

class CNetworkSession : public HisUtil::CThread
	{
	protected:
		struct stUdpPacket
		{
			void Clear() {
				msg.Clear();
				ip			= 0;
				port		= 0;
				updatetime	= 0;
				tick		= 0;
			}

			HisUtil::CMsg msg;
			ADDR_IP ip;
			ADDR_PORT port;
			TIME_T updatetime;	//�ٽ� ������ �ð�.
			int tick;
		};

		//������ �ؾ��ϹǷ� std::map���� ������
		typedef HisUtil::CMemoryPool<HisUtil::PacketNum, stUdpPacket, std::map<HisUtil::PacketNum, stUdpPacket*> >	UDP_RELIABLE_POOL;
		typedef HisUtil::CMemoryQueuePool<stUdpPacket>					UDP_UNRELIABLE_POOL;

	public:
		CNetworkSession(VOID);
		virtual ~CNetworkSession(VOID);

	private:
		OVERLAPPED_EX AcceptOverlapped_;
		OVERLAPPED_EX ReadOverlapped_;
		OVERLAPPED_EX WriteOverlapped_;

		char ReadBuffer_[HisUtil::MSG_TOTAL_SIZE * 100];//����ũ�⸦ ���̰� ���� (���ӽ�����) ���� ���׳�.
		SOCKADDR_IN	UdpRemoteSockAddr_;
		SOCKET socket_;

		////send tcp
		//CPoolBuffer poolTcpSend_;
		//HANDLE TcpThreadWakeUpEvent_;
		//HANDLE TcpWriteCompleteEvent_;
		//BOOL bIsTcpSending_;

		////send unreliable
		//CPoolBuffer poolUnreliableSend_;
		//HANDLE UnreliableUdpThreadWakeUpEvent_;
		//HANDLE UnreliableUdpWriteCompleteEvent_;
		//BOOL bIsUnreliableUdpSending_;

		//send reliable
		HisUtil::CPoolBuffer poolReliableSend_;
		//HANDLE ReliableUdpThreadWakeUpEvent_;
		//HANDLE ReliableUdpWriteCompleteEvent_;
		//BOOL bIsReliableUdpSending_;

		//poolReliableSend_���� ������ msg�� ������ �ִٰ� UDP_ACK�� ����...����
		//�����ð����� UDP_ACK�� ������...�ٽ� ����.
		UDP_RELIABLE_POOL poolSendedUdp_;
		UDP_UNRELIABLE_POOL poolRecvUnreliableUdp_;	//���� UDP�� UNRELIABEL�� ��Ƽ� ó���Ѵ�.


		// ���ӵǾ����� �Ǻ��ϴ� ����
		BOOL bIsConnected_;

	protected:
		UDP_RELIABLE_POOL poolRecvReliableUdp_;


	public:
		BOOL Begin(VOID);
		BOOL End(VOID);

		BOOL Listen(ADDR_PORT port);
		BOOL Accept(SOCKET listenSocket);

		BOOL TcpBind(VOID);
		BOOL UdpBind(ADDR_PORT port, int nSendUdpPoolCnt);

		void SocketOption();
		BOOL GetPrivateIP(std::vector<ADDR_IP>& vecIP);
		ADDR_IP GetPrivateIP();		//�׳� IP �Ѱ��� �����´�.
		ADDR_PORT GetPrivatePort(VOID);

		BOOL InitializeRecvForIocp(VOID);
		BOOL RecvForIocp(HisUtil::CPacketBuffer& pPaketBuffer, int dataLength);
		BOOL RecvForEventSelect(HisUtil::CPacketBuffer& pPaketBuffer, DWORD& ReadBytes);

		BOOL Send(BYTE *data, DWORD dataLength);

		BOOL InitializeRecvFromForIocp(VOID);
		BOOL RecvFromForIocp(int dataLength);//, BYTE *data, DWORD &dataLength)
		BOOL RecvFromForEventSelect(DWORD& ReadBytes);//, BYTE *data, DWORD &dataLength)

		virtual BOOL GetFromUnreliablePacket(HisUtil::CMsg& msgRecv, ADDR_IP& remoteIP, ADDR_PORT& remotePort);//, DWORD &protocol, BYTE *packet, DWORD &packetLength)

		virtual BOOL SendToReliable(ADDR_IP remoteIP, ADDR_PORT remotePort, BYTE *data, DWORD dataLength);
		virtual BOOL SendTo(ADDR_IP remoteIP, ADDR_PORT remotePort, BYTE *data, DWORD dataLength);

		BOOL Connect(ADDR_IP ip, ADDR_PORT port);

		BOOL SendTcpComplete(VOID);
		BOOL SendUdpComplete(VOID);

		// bIsConnected_�� ���� �����ϰ� �������� �Լ�
		//VOID SetConnected(BOOL bConnected) { CThreadSync Sync; bIsConnected_ = bConnected; }
		//BOOL IsConnected(VOID) { CThreadSync Sync; return bIsConnected_; }
		VOID SetConnected(BOOL bConnected) { bIsConnected_ = bConnected; }
		BOOL IsConnected(VOID) { return bIsConnected_; }

		SOCKET GetSocket(VOID) { return socket_; }

		BOOL GetRemotePublicIPAfterAccept(std::wstring& remoteIP, ADDR_PORT &remotePort);

		virtual void OnWorkerThread(int index);

	protected:
		//UDP_ACK ���� üũ�մϴ�.
		BOOL IsRecvUdpAck(ADDR_IP remoteIP, ADDR_PORT remotePort);
		//���� ��Ŷ�� pool�� �����մϴ�.
		BOOL RecvUdpPacket(int ReadBytes, ADDR_IP remoteIP, ADDR_PORT remotePort);
		//udp�� �޾Ҵٰ� ����������� �˷��ش�.
		void SendUdpAck(HisUtil::PacketNum num, ADDR_IP remoteIP, ADDR_PORT remotePort);

	};

};//..namespace NetCore {