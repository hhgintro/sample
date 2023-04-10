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
			TIME_T updatetime;	//다시 전송할 시간.
			int tick;
		};

		//정렬을 해야하므로 std::map으로 선언함
		typedef HisUtil::CMemoryPool<HisUtil::PacketNum, stUdpPacket, std::map<HisUtil::PacketNum, stUdpPacket*> >	UDP_RELIABLE_POOL;
		typedef HisUtil::CMemoryQueuePool<stUdpPacket>					UDP_UNRELIABLE_POOL;

	public:
		CNetworkSession(VOID);
		virtual ~CNetworkSession(VOID);

	private:
		OVERLAPPED_EX AcceptOverlapped_;
		OVERLAPPED_EX ReadOverlapped_;
		OVERLAPPED_EX WriteOverlapped_;

		char ReadBuffer_[HisUtil::MSG_TOTAL_SIZE * 100];//버퍼크기를 늘이고 나서 (접속시점에) 서버 안죽네.
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

		//poolReliableSend_에서 보내진 msg를 가지고 있다가 UDP_ACK가 오면...삭제
		//일정시간동안 UDP_ACK가 없으면...다시 전송.
		UDP_RELIABLE_POOL poolSendedUdp_;
		UDP_UNRELIABLE_POOL poolRecvUnreliableUdp_;	//받은 UDP중 UNRELIABEL을 담아서 처리한다.


		// 접속되었는지 판별하는 변수
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
		ADDR_IP GetPrivateIP();		//그냥 IP 한개만 가져온다.
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

		// bIsConnected_의 값을 설정하고 가져오는 함수
		//VOID SetConnected(BOOL bConnected) { CThreadSync Sync; bIsConnected_ = bConnected; }
		//BOOL IsConnected(VOID) { CThreadSync Sync; return bIsConnected_; }
		VOID SetConnected(BOOL bConnected) { bIsConnected_ = bConnected; }
		BOOL IsConnected(VOID) { return bIsConnected_; }

		SOCKET GetSocket(VOID) { return socket_; }

		BOOL GetRemotePublicIPAfterAccept(std::wstring& remoteIP, ADDR_PORT &remotePort);

		virtual void OnWorkerThread(int index);

	protected:
		//UDP_ACK 인지 체크합니다.
		BOOL IsRecvUdpAck(ADDR_IP remoteIP, ADDR_PORT remotePort);
		//받은 패킷을 pool에 저장합니다.
		BOOL RecvUdpPacket(int ReadBytes, ADDR_IP remoteIP, ADDR_PORT remotePort);
		//udp를 받았다고 보낸사람에게 알려준다.
		void SendUdpAck(HisUtil::PacketNum num, ADDR_IP remoteIP, ADDR_PORT remotePort);

	};

};//..namespace NetCore {