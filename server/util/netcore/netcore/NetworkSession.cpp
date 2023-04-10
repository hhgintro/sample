#include "stdafx.h"

namespace NetCore {


	CNetworkSession::CNetworkSession(VOID)
	{
		memset(&AcceptOverlapped_, 0, sizeof(AcceptOverlapped_));
		memset(&ReadOverlapped_, 0, sizeof(ReadOverlapped_));
		memset(&WriteOverlapped_, 0, sizeof(WriteOverlapped_));

		memset(ReadBuffer_, 0, sizeof(ReadBuffer_));
		memset(&UdpRemoteSockAddr_, 0, sizeof(UdpRemoteSockAddr_));

		socket_ = NULL;


		//ReliableUdpThreadWakeUpEvent_ = NULL;
		//ReliableUdpWriteCompleteEvent_ = NULL;
		//bIsReliableUdpSending_ = FALSE;

		AcceptOverlapped_.IoType = IO_ACCEPT;
		ReadOverlapped_.IoType = IO_READ;
		WriteOverlapped_.IoType = IO_WRITE;

		AcceptOverlapped_.Object = this;
		ReadOverlapped_.Object = this;
		WriteOverlapped_.Object = this;

		bIsConnected_ = FALSE;
	}

	CNetworkSession::~CNetworkSession(VOID)
	{
		if (socket_)
		{
			closesocket(socket_);
			socket_ = NULL;
		}

		HisUtil::CThread::EndThread();


		//if (ReliableUdpThreadWakeUpEvent_)
		//{
		//	CloseHandle(ReliableUdpThreadWakeUpEvent_);
		//	ReliableUdpThreadWakeUpEvent_ = NULL;
		//}
		//if (ReliableUdpWriteCompleteEvent_)
		//{
		//	CloseHandle(ReliableUdpWriteCompleteEvent_);
		//	ReliableUdpWriteCompleteEvent_ = NULL;
		//}

		poolReliableSend_.End();

		AcceptOverlapped_.Object = NULL;
		ReadOverlapped_.Object = NULL;
		WriteOverlapped_.Object = NULL;
	}

	//udp send�� ó���մϴ�.
	VOID CNetworkSession::OnWorkerThread(int index)
	{
		//HG_TODO : reliable�̶�� ������ �ƾ� ������ ���ϰ� �ִٸ� �����°��� �����Ѵ�.
		//int try_count = 0;//�õ�ȸ��

		while (TRUE == IsRunning())
		{
			Sleep(1);


			//�������� ����Ÿ�� �ִ��� Ȯ���Ѵ�.
			std::vector<stUdpPacket*> vecAll;
			poolSendedUdp_.GetAllList(vecAll);
			for(int i=0; i<vecAll.size(); ++i) {
				stUdpPacket* temp = vecAll[0];
				if (NULL == temp)	continue;

				//���� ���� �ð��� �ȵǾ���.(�Ǿղ��� üũ�մϴ�. ��ȣ������ ���ĵǱ� ������)
				if (temp->updatetime < GetTickCount64())
				{
					//LOGEVENT("HG_YELLOW", L"num(%d) pre-updatetime(%lld)", temp->msg.GetNum(), temp->updatetime);
					temp->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
					//LOGEVENT("HG_YELLOW", L"num(%d) updatetime(%lld)", temp->msg.GetNum(), temp->updatetime);

					//������
					LOGEVENT("Network_Packet_Number_Info", _T("--> udp data SENDING(**RE**)...(packet id(0x%04x) packet num(%d) 0x%08x, port:0x%04x)"), temp->msg.ID(), temp->msg.GetNum(), temp->ip, temp->port);
					SendTo(temp->ip, temp->port, (UCHAR*)temp->msg.GetBuf(), temp->msg.GetSize());
					
					if (5 < ++temp->tick)
						poolSendedUdp_.Erase(temp->msg.GetNum());
				}
		
				//HG[2021.02.22]������Ŷ�� ������ ���� ���� ��� �Ʒ��� ó���� �ʿ���� �Ǵ��ߴµ�.
				//	100, 101��  101 ��Ŷ�� ���� ������ ��쿡�� 100 ��Ŷ�� ���޵� �� ���
				// �Ʒ� continue�� �ּ�ó����
				//continue;
			}


			//����Ÿ�� ������ ����
			if(poolReliableSend_.GetCurPoolCount() <= 0)
				continue;

			stUdpPacket* packet = poolSendedUdp_.Create();
			if (NULL == packet)
			{
				LOGEVENT("Network_Base_Core_Error", _T("fail Create Sended UDP pool"));
				continue;
			}
			packet->Clear();

			//���� ��Ŷ�� �����´�.
			if (poolReliableSend_.Pop(packet->msg.GetBuf(), HisUtil::MSG_TOTAL_SIZE, packet->ip, packet->port))
			{
				//������ ������ ���, �ٽ� ������ �ð��� �����Ѵ�.
				packet->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
				//LOGEVENT("HG_YELLOW", L"first num(%d) updatetime(%lld)", packet->msg.GetNum(), packet->updatetime);
				poolSendedUdp_.Insert(packet->msg.GetNum(), packet);

				SendTo(packet->ip, packet->port, (UCHAR*)packet->msg.GetBuf(), packet->msg.GetSize());
				LOGEVENT("Network_Packet_Number_Info", _T("--> udp data SENDING...(packet id(0x%04x) packet num(%d) 0x%08x, port:0x%04x)"), packet->msg.ID(), packet->msg.GetNum(), packet->ip, packet->port);
			}
			else
			{
				//����Ÿ�� ����������...����ó��
				goto RELIABLE_SENDED_POOL_RELEASE;
			}


			//�Ʒ����� ������ �߻��� �� ó���� �����ϱ⿡ ���������.
			continue;

			//===================
			// ����ó��
			//===================
			//����� ������ ���(packet ������ ����ó���� �κ�)��...ó���Ǿ�� �մϴ�.
RELIABLE_SENDED_POOL_RELEASE:
			poolSendedUdp_.Erase(packet);
			continue;
		}//..while (TRUE)
	}

	BOOL CNetworkSession::Begin(VOID)
	{
		if (socket_)
			return FALSE;

		memset(ReadBuffer_, 0, sizeof(ReadBuffer_));
		memset(&UdpRemoteSockAddr_, 0, sizeof(UdpRemoteSockAddr_));

		socket_ = NULL;

		//ReliableUdpThreadWakeUpEvent_ = NULL;
		//ReliableUdpWriteCompleteEvent_ = NULL;
		//bIsReliableUdpSending_ = FALSE;

		bIsConnected_ = FALSE;
		return TRUE;
	}

	BOOL CNetworkSession::End(VOID)
	{
		if (socket_)
		{
			closesocket(socket_);
			socket_ = NULL;
		}
		/*	���� ó���� �Ҿ���
		ZeroMemory(reinterpret_cast<PVOID>(&AcceptOverlapped_.Overlapped), sizeof(OVERLAPPED))

		if(TransmitFile(socket_,
		NULL,
		0,
		0,
		&AcceptOverlapped_.Overlapped,
		NULL,
		TF_DISCONNECT | TF_REUSE_SOCKET) == FALSE)
		{
		int iError = WSAGetLastError()
		if(iError != WSA_IO_PENDING)
		{
		LOGEVENT("Network_Base_Core_Error", _T("Error TransmitFile(%d) : HOSTID(0x%p)"), iError, this)
		return FALSE
		}
		}

		LOGEVENT("Network_Base_Core_Info", _T("reuse socket : HOSTID(0x%p)"), this)
		*/

		memset(ReadBuffer_, 0, sizeof(ReadBuffer_));
		memset(&UdpRemoteSockAddr_, 0, sizeof(UdpRemoteSockAddr_));


		poolReliableSend_.End();
		poolSendedUdp_.Clear();
		poolRecvUnreliableUdp_.Clear();
		poolRecvReliableUdp_.Clear();

		//bIsReliableUdpSending_ = FALSE;
		HisUtil::CThread::EndThread();
		return TRUE;
	}

	BOOL CNetworkSession::Listen(ADDR_PORT port)
	{
		//if (port <= 0 || !socket_)
		if (!socket_)
			return FALSE;

		SOCKADDR_IN ListenSocketInfo;
		ListenSocketInfo.sin_family = AF_INET;
		ListenSocketInfo.sin_port = port;// htons(port);
		ListenSocketInfo.sin_addr.S_un.S_addr = INADDR_ANY;// htonl(INADDR_ANY);

		if (bind(socket_, (struct sockaddr*) &ListenSocketInfo, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
			return FALSE;

		if (listen(socket_, 5) == SOCKET_ERROR)
			return FALSE;

		LINGER Linger;
		Linger.l_onoff = 1;
		Linger.l_linger = 0;

		if (setsockopt(socket_, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(LINGER)) == SOCKET_ERROR)
			return FALSE;

		return TRUE;
	}

	BOOL CNetworkSession::Accept(SOCKET listenSocket)
	{
		if (!listenSocket)
			return FALSE;

		if (!socket_)
		{
			socket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
			if (socket_ == INVALID_SOCKET)
				return FALSE;
		}

		//BOOL NoDelay = TRUE
		//setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, (const char FAR *)&NoDelay, sizeof(NoDelay))

		if (!AcceptEx(listenSocket,
			socket_,
			ReadBuffer_,
			0,//sizeof(ReadBuffer_), 
			sizeof(sockaddr_in) + 16,
			sizeof(sockaddr_in) + 16,
			NULL,
			&AcceptOverlapped_.Overlapped))
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error AcceptEx(%d)"), iError);
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOL CNetworkSession::TcpBind(VOID)
	{
		if (socket_)
			return FALSE;

		socket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (socket_ == INVALID_SOCKET)
			return FALSE;


		//BOOL NoDelay = TRUE;
		//setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, (const char FAR *)&NoDelay, sizeof(NoDelay));
		return TRUE;
	}

	BOOL CNetworkSession::UdpBind(ADDR_PORT port, int nSendUdpPoolCnt)
	{
		if (socket_)
			return FALSE;

		SOCKADDR_IN RemoteIPInfo;
		RemoteIPInfo.sin_family = AF_INET;
		RemoteIPInfo.sin_port = port;// htons(port);
		RemoteIPInfo.sin_addr.S_un.S_addr = INADDR_ANY;//htonl(INADDR_ANY)

		socket_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (socket_ == INVALID_SOCKET)
			return FALSE;

		//soketoption
		//SocketOption();

		if (bind(socket_, (struct sockaddr*) &RemoteIPInfo, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			LOGEVENT("Network_Base_Core_Error", _T("Error UdpBind(%d)"), iError);
			return FALSE;
		}


		//ReliableUdpThreadWakeUpEvent_ = CreateEvent(0, FALSE, FALSE, 0);
		//if (ReliableUdpThreadWakeUpEvent_ == NULL)
		//	return FALSE;

		//ReliableUdpWriteCompleteEvent_ = CreateEvent(0, FALSE, FALSE, 0);
		//if (ReliableUdpWriteCompleteEvent_ == NULL)
		//	return FALSE;


		//poolReliableSend_
		LOGEVENT("Network_Base_Core_Info", _T("udp reliable send buffer count(%d)"), nSendUdpPoolCnt);
		if (poolReliableSend_.Begin(nSendUdpPoolCnt) == NULL)
			return FALSE;

		//HG[20921.02.22]������ thread�� �ϳ��� �ȴ�.
		//SYSTEM_INFO SystemInfo;
		//GetSystemInfo(&SystemInfo);
		HisUtil::CThread::BeginThread(1);// SystemInfo.dwNumberOfProcessors * 2 + 1);

		return TRUE;
	}

	//void CNetworkSession::SocketOption()
	//{
	//	// --------------------------------------- 
	//	// ������ �ʱ�ȭ�ϰ� setsockopt�� ȣ���մϴ�. 
	//	// SO_KEEPALIVE �Ű� ������ ���� ���� ���ǿ��� Keepalive �޽�����
	//	// �������� �ϴ� ���� �ɼ� �Դϴ�.SO_KEEPALIVE ���� �ɼ� ��
	//	// setsockopt �Լ��� ���޵Ǵ� �ο� ���� �ʿ�� �մϴ�.���� ��� ������ Keepalive �޽����� �������� �����˴ϴ�.
	//	// False �̸� ������ Keepalive �޽����� ������ �ʵ��� �����˴ϴ�.
	//	//�� �ڵ� ������ getsockopt �Լ��� ����Ͽ�
	//	// ������ SO_KEEPALIVE ���¸� Ȯ�� �Ͽ� setsockopt �Լ���
	//	// �׽�Ʈ�մϴ� .

	//	int iOptVal = 0;
	//	int iOptLen = sizeof(iOptVal);
	//	BOOL bOptVal = TRUE;
	//	int bOptLen = sizeof(bOptVal);

	//	int iResult = getsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char *)& iOptVal, &iOptLen);
	//	if (iResult == SOCKET_ERROR) {
	//		LOGEVENT("Network_Base_Core_Error", _T("SO_KEEPALIVE�� ���� getsockopt�� %u ������ �����߽��ϴ�"), WSAGetLastError());
	//	}
	//	else
	//		LOGEVENT("Network_Base_Core_Info", _T("SO_KEEPALIVE �� %d"), iOptVal);

	//	iResult = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char *)& bOptVal, bOptLen);
	//	if (iResult == SOCKET_ERROR) {
	//		LOGEVENT("Network_Base_Core_Error", _T("SO_KEEPALIVE�� ���� setsockopt�� %u ������ �����߽��ϴ�"), WSAGetLastError());
	//	}
	//	else
	//		LOGEVENT("Network_Base_Core_Info", _T("Set SO_KEEPALIVE : ON"));

	//	iResult = getsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char *)& iOptVal, &iOptLen);
	//	if (iResult == SOCKET_ERROR) {
	//		LOGEVENT("Network_Base_Core_Error", _T("SO_KEEPALIVE�� ���� getsockopt�� %u ������ �����߽��ϴ�"), WSAGetLastError());
	//	}
	//	else
	//		LOGEVENT("Network_Base_Core_Info", _T("SO_KEEPALIVE �� %d"), iOptVal);
	//}

	BOOL CNetworkSession::InitializeRecvForIocp(VOID)
	{
		if (!socket_)
			return FALSE;

		WSABUF	WsaBuf;
		DWORD	ReadBytes = 0;
		DWORD	ReadFlag = 0;

		WsaBuf.buf = (CHAR*)ReadBuffer_;
		WsaBuf.len = sizeof(ReadBuffer_);

		INT ReturnValue = WSARecv(socket_,
			&WsaBuf,
			1,
			&ReadBytes,
			&ReadFlag,
			&ReadOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error Iocp WSARecv(%d)"), iError);
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOL CNetworkSession::RecvForIocp(HisUtil::CPacketBuffer& pPaketBuffer, int dataLength)
	{
		if (!socket_ || dataLength <= 0 || HisUtil::MSG_TOTAL_SIZE <= dataLength)
			return FALSE;

		//memcpy(data, ReadBuffer_, dataLength);
		if (FALSE == pPaketBuffer.Push(ReadBuffer_, dataLength))
		{
			LOGEVENT("Network_Base_Core_Error", _T("Error recv buffer push"));
			//return FALSE;
		}

		return InitializeRecvForIocp();
	}

	BOOL CNetworkSession::RecvForEventSelect(HisUtil::CPacketBuffer& pPaketBuffer, DWORD& ReadBytes)
	{
		if (!socket_)
			return FALSE;

		WSABUF	WsaBuf;
		//DWORD	ReadBytes	= 0;
		DWORD	ReadFlag = 0;

		WsaBuf.buf = (CHAR*)ReadBuffer_;
		WsaBuf.len = sizeof(ReadBuffer_);

		INT		ReturnValue = WSARecv(socket_,
			&WsaBuf,
			1,
			&ReadBytes,
			&ReadFlag,
			&ReadOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error EventSelect WSARecv(%d)"), iError);
				return FALSE;
			}
		}

		////HG_TEST
		//LOGEVENT("HG_GREEN", _T("==================================================="));
		//LOGEVENT("HG_GREEN", _T("recv packet size : %d"), *((PacketSize*)(ReadBuffer_ + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE);
		//LOGEVENT("HG_GREEN", _T("recv packet num : %d"), *((PacketNum*)(ReadBuffer_ + MSG_HEADER_PROTOCOL_NUM_POS)));
		//LOGEVENT("HG_GREEN", _T("recv packet ID : 0x%04x"), *((PacketID*)(ReadBuffer_ + MSG_HEADER_PROTOCOL_ID_POS)));
		//LOGEVENT("HG_GREEN", _T("==================================================="));

		if (ReadBytes != *((HisUtil::PacketSize*)(ReadBuffer_ + HisUtil::MSG_HEADER_PROTOCOL_SIZE_POS)) + HisUtil::MSG_HEADER_SIZE)
		{
			//packet�� ���Ŀ��⿡ ����� �ִ� ����(�����Դϴ�.)
			LOGEVENT("Session_Base_Info", _T("Info ���� packet ũ��� ���� ����Ÿ ũ�Ⱑ �ٸ���.(%d/%d)")
				, ReadBytes
				, *((HisUtil::PacketSize*)(ReadBuffer_ + HisUtil::MSG_HEADER_PROTOCOL_SIZE_POS)) + HisUtil::MSG_HEADER_SIZE);
		}

		//memcpy(data, ReadBuffer_, ReadBytes);
		//dataLength = ReadBytes;
		if(FALSE == pPaketBuffer.Push(ReadBuffer_, ReadBytes))
		{
			LOGEVENT("Network_Base_Core_Error", _T("Error recv buffer push"));
			//return FALSE;
		}


		return TRUE;
	}

	BOOL CNetworkSession::Send(BYTE *data, DWORD dataLength)
	{
		if (!socket_ || !data || dataLength <= 0)
			return FALSE;

		WSABUF	WsaBuf;
		DWORD	WriteBytes = 0;
		DWORD	WriteFlag = 0;

		WsaBuf.buf = (CHAR*)data;
		WsaBuf.len = dataLength;

		INT		ReturnValue = WSASend(socket_,
			&WsaBuf,
			1,
			&WriteBytes,
			WriteFlag,
			&WriteOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error WSASend(%d)"), iError);
				return FALSE;
			}
		}

		////HG_TEST
		//LOGEVENT("HG_GREEN", _T("==================================================="));
		//LOGEVENT("HG_GREEN", _T("send socket : %d, result : %d"), socket_, ReturnValue);
		//LOGEVENT("HG_GREEN", _T("send packet size : %d"), *((PacketSize*)(data + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE);
		//LOGEVENT("HG_GREEN", _T("send packet num : %d"), *((PacketNum*)(data + MSG_HEADER_PROTOCOL_NUM_POS)));
		//LOGEVENT("HG_GREEN", _T("send packet ID : 0x%04x"), *((PacketID*)(data + MSG_HEADER_PROTOCOL_ID_POS)));
		//LOGEVENT("HG_GREEN", _T("==================================================="));

		return TRUE;
	}

	BOOL CNetworkSession::Connect(ADDR_IP ip, ADDR_PORT port)
	{
		if (!socket_ || !ip || port <= 0)
			return FALSE;

		SOCKADDR_IN si;
		si.sin_family = AF_INET;
		si.sin_port = port;// htons(port);
		//si.sin_addr.s_addr = inet_addr("127.0.0.1"); ==> inet_pton(AF_INET, szIP, &nIP);
		si.sin_addr.s_addr = ip;

		if (WSAConnect(socket_, (LPSOCKADDR)&si, sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error WSAConnect(%d)"), iError);
				return FALSE;
			}
		}

		return TRUE;
	}

	//gethostbyname()����ϱ� ���ؼ���.
	//�ش�������Ʈ --> �Ӽ� --> C/C++ --> Preprocessor -> Preprocessor Definitions��
	//"_WINSOCK_DEPRECATED_NO_WARNINGS" �߰�
	//#define _WINSOCK_DEPRECATED_NO_WARNINGS	�̰� �ҿ����.
	BOOL CNetworkSession::GetPrivateIP(std::vector<ADDR_IP>& vecIP)
	{
		if(!socket_)
			return FALSE;


		char ac[80];
		::gethostname(ac,sizeof(ac));
		struct hostent* phe = gethostbyname(ac);
		if(NULL == phe)
			return FALSE;
	
		for(int i=0; phe->h_addr_list[i]!=0; ++i)
		{
			//in_addr addr
			//addr.S_un.S_addr = ulUserIP
			//inet_ntoa(addr)
			struct in_addr addr;
			memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
			LOGEVENT("Network_Base_Core_Info", _T("my address[%d] : %d.%d.%d.%d"), i, addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);//, addr.sinet_ntoa(addr));
			vecIP.push_back(addr.S_un.S_addr);
		} // for(int i=0 phe->h_addr_list[i]!=0 ++i)
	
		return TRUE;
	}
	//�׳� �Ѱ��� �����´�.
	ADDR_IP CNetworkSession::GetPrivateIP()
	{
		std::vector<ADDR_IP> vecIP;
		GetPrivateIP(vecIP);
		if (vecIP.size() <= 0)
			return 0;
		return vecIP[0];
	}
	ADDR_PORT CNetworkSession::GetPrivatePort(VOID)
	{
		if (!socket_)
			return 0;
	
		SOCKADDR_IN Addr;
		ZeroMemory(&Addr, sizeof(Addr));
	
		INT AddrLength = sizeof(Addr);
		if (::getsockname(socket_, (sockaddr*) &Addr, &AddrLength) != SOCKET_ERROR)
			return Addr.sin_port;//ntohs(Addr.sin_port)
	
		return 0;
	}

	BOOL CNetworkSession::InitializeRecvFromForIocp(VOID)
	{
		if (!socket_)
			return FALSE;

		WSABUF	WsaBuf;
		DWORD	ReadBytes = 0;
		DWORD	ReadFlag = 0;
		INT		RemoteIPInfoSize = sizeof(UdpRemoteSockAddr_);

		WsaBuf.buf = (CHAR*)ReadBuffer_;
		WsaBuf.len = sizeof(ReadBuffer_);

		//LOGEVENT("HG_CYAN", L"WSARecvFrom IOCP");
		INT		ReturnValue = WSARecvFrom(socket_,
			&WsaBuf,
			1,
			&ReadBytes,
			&ReadFlag,
			(SOCKADDR*)&UdpRemoteSockAddr_,
			&RemoteIPInfoSize,
			&ReadOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error Iocp WSARecvFrom(%d)"), iError);
				return FALSE;
			}
		}

		return TRUE;
	}

	void CNetworkSession::SendUdpAck(HisUtil::PacketNum num, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		//LOGEVENT("Network_Base_Core_Info", _T("(FOR TEST)udp ack NOT sending...num(%d), (ip:0x%08x, port:0x%04x)"), num, remoteIP, remotePort);
		//return;

		WORD Ack = UDP_ACK;

		BYTE buf[100] = "";
		int pos = 0;
		memcpy(buf, &Ack, sizeof(Ack));
		pos += sizeof(Ack);
		//packet num
		memcpy(buf + pos, &num, sizeof(num));
		pos += sizeof(num);

		SendTo(remoteIP, remotePort, buf, pos);
		LOGEVENT("Network_Base_Core_Info", _T("udp ack sending...num(%d), (ip:0x%08x, port:0x%04x)"), num, remoteIP, remotePort);
	}

	BOOL CNetworkSession::IsRecvUdpAck(ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		WORD Ack = 0;
		memcpy(&Ack, ReadBuffer_, sizeof(Ack));
		if (UDP_ACK == Ack)
		{
			//���� packet num
			HisUtil::PacketNum num = 0;
			memcpy(&num, ReadBuffer_ + sizeof(Ack), sizeof(num));

			//SetEvent(ReliableUdpWriteCompleteEvent_);
			poolSendedUdp_.Erase(num);//������ pool���� �����.(�ٽ� ���� �ʿ����)
			LOGEVENT("Network_Base_Core_Info", _T("udp ack recving... ���޿Ϸ�(packet num:%d, 0x%08x, port:0x%04x)"), num, remoteIP, remotePort);
			return TRUE;
		}
		return FALSE;
	}

	BOOL CNetworkSession::RecvUdpPacket(int ReadBytes, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		stUdpPacket* packet = poolRecvReliableUdp_.Create();
		if (NULL == packet)
		{
			LOGEVENT("Network_Base_Core_Info", _T("error Create UDP packet"));
			return FALSE;
		}
		packet->Clear();
		packet->msg.Copy(ReadBuffer_, ReadBytes);
		packet->ip = remoteIP;
		packet->port = remotePort;

		if (RELIABLE == packet->msg.GetContext())
		{
			if (NULL == poolRecvReliableUdp_.Find(packet->msg.GetNum()))
				poolRecvReliableUdp_.Insert(packet->msg.GetNum(), packet);
			else {
				poolRecvReliableUdp_.Erase(packet);//������� �ʰ� ��ȯ�� ������.
				LOGEVENT("Network_Base_Core_Info", _T("���� num(%d)�� �־ �����Ǵ� packet"), packet->msg.GetNum());
			}
			//RELIABLE�� ��츸, �޾Ҵٰ� �˷��ش�.
			SendUdpAck(packet->msg.GetNum(), remoteIP, remotePort);
		}
		else
		{
			poolRecvUnreliableUdp_.Push(packet);
		}
		return TRUE;
	}

	BOOL CNetworkSession::RecvFromForIocp(int dataLength)//, BYTE *data, DWORD &dataLength)
	{
		if (!socket_ || dataLength <= 0 || HisUtil::MSG_TOTAL_SIZE <= dataLength)
			return FALSE;

		//memcpy(remoteIP, inet_ntoa(UdpRemoteSockAddr_.sin_addr), 32)
		ADDR_IP remoteIP = UdpRemoteSockAddr_.sin_addr.S_un.S_addr;//inet_ntoa(UdpRemoteSockAddr_.sin_addr))
		ADDR_PORT remotePort = UdpRemoteSockAddr_.sin_port;//ntohs(UdpRemoteSockAddr_.sin_port)

		//size
		//WORD Ack = 0;
		//memcpy(&Ack, ReadBuffer_, sizeof(Ack));
		//if (UDP_ACK == Ack)
		//{
		//	//���� packet num
		//	HisUtil::PacketNum num = 0;
		//	memcpy(&num, ReadBuffer_ + sizeof(Ack), sizeof(num));

		//	SetEvent(ReliableUdpWriteCompleteEvent_);
		//	LOGEVENT("Network_Base_Core_Info", _T("udp ack recving... ���޿Ϸ�(packet num:%d, 0x%08x, port:0x%04x)"), num, remoteIP, remotePort);

		//	InitializeRecvFromForIocp();
		//	return FALSE;
		//}

		//���� �Ϸ�
		if (TRUE == IsRecvUdpAck(remoteIP, remotePort))
		{
			InitializeRecvFromForIocp();
			return FALSE;
		}

		//pPaketBuffer.Push(ReadBuffer_, dataLength, remoteIP, remotePort);
		////memcpy(data, ReadBuffer_, dataLength)

		//stUdpPacket* packet = poolRecvReliableUdp.Create();
		//if (NULL == packet)
		//{
		//	LOGEVENT("Network_Base_Core_Info", _T("error Create UDP packet"));
		//	return FALSE;
		//}
		//packet->msg.Clear();
		//packet->msg.Copy(ReadBuffer_, dataLength);
		//packet->ip = remoteIP;
		//packet->port = remotePort;
		//if (NULL == poolRecvReliableUdp.Find(packet->msg.GetNum()))
		//	poolRecvReliableUdp.Insert(packet->msg.GetNum(), packet);
		//else
		//	poolRecvReliableUdp.Erase(packet);//������� �ʰ� ��ȯ�� ������.

		////RELIABLE�� ��츸, �޾Ҵٰ� �˷��ش�.
		//if(RELIABLE == packet->msg.GetContext())
		//	SendUdpAck(packet->msg.GetNum(), remoteIP, remotePort);

		RecvUdpPacket(dataLength, remoteIP, remotePort);

		return InitializeRecvFromForIocp();
	}

	BOOL CNetworkSession::RecvFromForEventSelect(DWORD& ReadBytes)//, BYTE *data, DWORD &dataLength)
	{
		if (!socket_)
			return FALSE;


		WSABUF		WsaBuf;
		DWORD		ReadFlag = 0;
		INT			RemoteIPInfoSize = sizeof(UdpRemoteSockAddr_);

		WsaBuf.buf = (CHAR*)ReadBuffer_;
		WsaBuf.len = sizeof(ReadBuffer_);

		//LOGEVENT("HG_CYAN", L"WSARecvFrom EventSelect");
		INT		ReturnValue = WSARecvFrom(socket_,
			&WsaBuf,
			1,
			&ReadBytes,
			&ReadFlag,
			(SOCKADDR*)&UdpRemoteSockAddr_,
			&RemoteIPInfoSize,
			&ReadOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error EventSelect WSARecvFrom(%d)"), iError);
				return FALSE;
			}
		}

		//memcpy(remoteIP, inet_ntoa(UdpRemoteSockAddr_.sin_addr), 32)
		ADDR_IP remoteIP = UdpRemoteSockAddr_.sin_addr.S_un.S_addr;//inet_ntoa(UdpRemoteSockAddr_.sin_addr))
		ADDR_PORT remotePort = UdpRemoteSockAddr_.sin_port;//ntohs(UdpRemoteSockAddr_.sin_port)

														   //size
		//WORD Ack = 0;
		//memcpy(&Ack, ReadBuffer_, sizeof(Ack));
		//if (UDP_ACK == Ack)
		//{
		//	//���� packet num
		//	HisUtil::PacketNum num = 0;
		//	memcpy(&num, ReadBuffer_ + sizeof(Ack), sizeof(num));

		//	SetEvent(ReliableUdpWriteCompleteEvent_);
		//	LOGEVENT("Network_Base_Core_Info", _T("udp ack recving... ���޿Ϸ�(packet num:%d, 0x%08x, port:0x%04x)"), num, remoteIP, remotePort);
		//	return FALSE;
		//}

		//���� �Ϸ�
		if (TRUE == IsRecvUdpAck(remoteIP, remotePort))
			return FALSE;

		//pPaketBuffer.Push(ReadBuffer_, ReadBytes, remoteIP, remotePort);
		////memcpy(data, ReadBuffer_, ReadBytes)

		//stUdpPacket* packet = poolRecvReliableUdp.Create();
		//if (NULL == packet)
		//{
		//	LOGEVENT("Network_Base_Core_Info", _T("error Create UDP packet"));
		//	return FALSE;
		//}
		//packet->msg.Clear();
		//packet->msg.Copy(ReadBuffer_, ReadBytes);
		//packet->ip = remoteIP;
		//packet->port = remotePort;
		//if (NULL == poolRecvReliableUdp.Find(packet->msg.GetNum()))
		//	poolRecvReliableUdp.Insert(packet->msg.GetNum(), packet);
		//else
		//	poolRecvReliableUdp.Erase(packet);//������� �ʰ� ��ȯ�� ������.

		////RELIABLE�� ��츸, �޾Ҵٰ� �˷��ش�.
		//if (RELIABLE == packet->msg.GetContext())
		//	SendUdpAck(Ack, packet->msg.GetNum(), remoteIP, remotePort);
		RecvUdpPacket(ReadBytes, remoteIP, remotePort);
		return TRUE;
	}

	BOOL CNetworkSession::GetFromUnreliablePacket(HisUtil::CMsg& msgRecv, ADDR_IP& remoteIP, ADDR_PORT& remotePort)//, DWORD &protocol, BYTE *packet, DWORD &packetLength)
	{
		stUdpPacket* packet = poolRecvUnreliableUdp_.Front_Pop();
		if (NULL == packet)
			return FALSE;

		//setting
		msgRecv = packet->msg;
		remoteIP = packet->ip;
		remotePort = packet->port;

		//�ݵ�� �޸� ��ȯ(���� �޾Ҵ� ������ �����ش�.)
		poolRecvReliableUdp_.Erase(packet);
		return TRUE;
	}

	BOOL CNetworkSession::SendToReliable(ADDR_IP remoteIP, ADDR_PORT remotePort, BYTE *data, DWORD dataLength)
	{
		if (!socket_ || !remoteIP || remotePort <= 0 || !data || dataLength <= 0)
			return FALSE;

		//if (!ReliableSendQueue_.Push(this, data, dataLength, remoteIP, remotePort))
		if (!poolReliableSend_.Push(data, dataLength, remoteIP, remotePort))
			return FALSE;

		//if (!bIsReliableUdpSending_)
		//{
		//	bIsReliableUdpSending_ = TRUE;
		//	SetEvent(ReliableUdpThreadWakeUpEvent_);
		//}

		return TRUE;
	}

	BOOL CNetworkSession::SendTo(ADDR_IP remoteIP, ADDR_PORT remotePort, BYTE *data, DWORD dataLength)
	{
		if (!socket_ || !remoteIP || remotePort <= 0 || !data || dataLength <= 0)
			return FALSE;

		WSABUF		WsaBuf;
		DWORD		WriteBytes = 0;
		DWORD		WriteFlag = 0;

		SOCKADDR_IN	RemoteIPInfo;
		INT			RemoteIPInfoSize = sizeof(RemoteIPInfo);

		WsaBuf.buf = (CHAR*)data;
		WsaBuf.len = dataLength;

		RemoteIPInfo.sin_family = AF_INET;
		RemoteIPInfo.sin_addr.S_un.S_addr = remoteIP;//inet_addr(remoteIP) ==> inet_pton(AF_INET, szIP, &nIP);
		RemoteIPInfo.sin_port = remotePort;//htons(remotePort)

		//LOGEVENT("HG_YELLOW", L"WSASendTo IOCP");
		INT		ReturnValue = WSASendTo(socket_,
			&WsaBuf,
			1,
			&WriteBytes,
			WriteFlag,
			(SOCKADDR*)&RemoteIPInfo,
			RemoteIPInfoSize,
			&WriteOverlapped_.Overlapped,
			NULL);

		if (ReturnValue == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != ERROR_IO_PENDING && iError != WSAEWOULDBLOCK)
			{
				LOGEVENT("Network_Base_Core_Error", _T("Error WSASendTo(%d)"), iError);
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOL CNetworkSession::GetRemotePublicIPAfterAccept(std::wstring& remoteIP, ADDR_PORT &remotePort)
	{
		//if (!remoteIP)
		//	return FALSE;

		sockaddr_in		*Local = NULL;
		INT				LocalLength = 0;

		sockaddr_in		*Remote = NULL;
		INT				RemoteLength = 0;

		GetAcceptExSockaddrs(ReadBuffer_,
			0,//sizeof(ReadBuffer_), 
			sizeof(sockaddr_in) + 16,
			sizeof(sockaddr_in) + 16,
			(sockaddr **)&Local,
			&LocalLength,
			(sockaddr **)&Remote,
			&RemoteLength);

		//_tcscpy(remoteIP, (LPTSTR)(inet_ntoa(Remote->sin_addr)));
		CHAR	TempRemoteIP[32] = { 0, };
		void *addr = &(Remote->sin_addr);
		inet_ntop(((sockaddr*)Remote)->sa_family, addr, TempRemoteIP, sizeof(TempRemoteIP));
		//strcpy_s(TempRemoteIP, sizeof(TempRemoteIP), );
		remotePort = ntohs(Remote->sin_port);

		//printf("accept : %s / %d", TempRemoteIP, remotePort);
		remoteIP = HisUtil::CA2W(CP_ACP, TempRemoteIP);
		//LOGEVENT("HG_YELLOW", _T("accept : %s / %d"), remoteIP.c_str(), remotePort);
		return TRUE;
	}

	BOOL CNetworkSession::SendTcpComplete(VOID)
	{
		//////AUTO_LOCK(csSession_);//CThreadSync Sync

		//// WriteQueue���� Pop�� �� �ָ� �ȴ�.
		//SetEvent(TcpWriteCompleteEvent_);
		return TRUE;//WriteQueue.Pop();
		////CMsg tempmsg;
		////return queueSendTcpPacket_.Pop(tempmsg.GetBuf(), MSG_TOTAL_SIZE);
	}

	BOOL CNetworkSession::SendUdpComplete(VOID)
	{
		//////AUTO_LOCK(csSession_);//CThreadSync Sync

		//// WriteQueue���� Pop�� �� �ָ� �ȴ�.
		//SetEvent(UnreliableUdpWriteCompleteEvent_);
		return TRUE;//WriteQueue.Pop();
	}

};//..namespace NetCore {