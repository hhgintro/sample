#include "stdafx.h"
#include "SimpleIocp.h"



CSimpleIocp::CSimpleIocp()
{
}


CSimpleIocp::~CSimpleIocp()
{
	End();
}


BOOL CSimpleIocp::Begin(UINT16 port)
{
	// Winsock Start - windock.dll �ε�
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("Error - Can not load 'winsock.dll' file\n");
		return FALSE;
	}


	// 1. ���ϻ���  
	m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_listenSocket == INVALID_SOCKET)
	{
		printf("Error - Invalid socket\n");
		return FALSE;
	}

	// �������� ��ü����
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 2. ���ϼ���
	if (bind(m_listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("Error - Fail bind\n");
		// 6. ��������
		closesocket(m_listenSocket);
		// Winsock End
		WSACleanup();
		return FALSE;
	}

	// 3. ���Ŵ�⿭����
	if (listen(m_listenSocket, 5) == SOCKET_ERROR)
	{
		printf("Error - Fail listen\n");
		// 6. ��������
		closesocket(m_listenSocket);
		// Winsock End
		WSACleanup();
		return FALSE;
	}

	// �Ϸ����� ó���ϴ� ��ü(CP : Completion Port) ����
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);


	// ��Ŀ������ ����
	// - CPU * 2��
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	int threadCount = systemInfo.dwNumberOfProcessors;
//	unsigned long threadId;
	// - thread Handler ����
	//HANDLE *hThread = (HANDLE *)malloc(threadCount * sizeof(HANDLE));
	// - thread ����
	for (int i = 0; i < threadCount; i++)
	{
	///	hThread[i] = CreateThread(NULL, 0, _Thread, &hIOCP, 0, &threadId);
		HANDLE WorkerThread = (HANDLE)::_beginthreadex(NULL, 0, _WorkThread, this, 0, NULL);
	}

	//accept ������
	HANDLE WorkerThread = (HANDLE)::_beginthreadex(NULL, 0, _AcceptThread, this, 0, NULL);

	return TRUE;
}

void CSimpleIocp::End()
{
	// 6-2. ���� ��������
	closesocket(m_listenSocket);

	// Winsock End
	WSACleanup();
}

unsigned int CALLBACK CSimpleIocp::_AcceptThread(void* lpParam)
{
	CSimpleIocp* parm = (CSimpleIocp*)lpParam;
	if (NULL == parm)
		return 0;

	parm->OnAcceptThread();
	return 0;
}

void CSimpleIocp::OnAcceptThread()
{
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	memset(&clientAddr, 0, addrLen);
	SOCKET clientSocket;
	SOCKETINFO *socketInfo;
	DWORD receiveBytes;
	DWORD flags;

	while (1)
	{
		clientSocket = accept(m_listenSocket, (struct sockaddr *)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			printf("Error - Accept Failure\n");
			return;
		}

		socketInfo = (struct SOCKETINFO *)malloc(sizeof(struct SOCKETINFO));
		memset((void *)socketInfo, 0x00, sizeof(struct SOCKETINFO));
		socketInfo->socket = clientSocket;
		socketInfo->receiveBytes = 0;
		socketInfo->sendBytes = 0;
		socketInfo->dataBuffer.len = MAX_BUFFER;
		socketInfo->dataBuffer.buf = socketInfo->messageBuffer;
		flags = 0;

		m_hIOCP = CreateIoCompletionPort((HANDLE)clientSocket, m_hIOCP, (ULONG_PTR)socketInfo, 0);

		// ��ø ��Ĺ�� �����ϰ� �Ϸ�� ����� �Լ��� �Ѱ��ش�.
		if (WSARecv(socketInfo->socket, &socketInfo->dataBuffer, 1, &receiveBytes, &flags, &(socketInfo->overlapped), NULL))
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				printf("Error - IO pending Failure\n");
				return;
			}
		}
	}

}


unsigned int CALLBACK CSimpleIocp::_WorkThread(void* lpParam)
{
	CSimpleIocp* parm = (CSimpleIocp*)lpParam;
	if (NULL == parm)
		return 0;

	parm->OnWorkThread();
	return 0;
}

void CSimpleIocp::OnWorkThread()
{
	//HANDLE threadHandler = *((HANDLE *)hIOCP);
	DWORD receiveBytes;
	//DWORD sendBytes;
	ULONG_PTR completionKey;
	DWORD flags;
	struct SOCKETINFO *eventSocket;
	while (1)
	{
		// ����� �Ϸ� ���
		if (GetQueuedCompletionStatus(m_hIOCP, &receiveBytes, &completionKey, (LPOVERLAPPED *)&eventSocket, INFINITE) == 0)
		{
			printf("Error - GetQueuedCompletionStatus Failure\n");
			closesocket(eventSocket->socket);
			free(eventSocket);
			return;
		}

		eventSocket->dataBuffer.len = receiveBytes;

		if (receiveBytes == 0)
		{
			closesocket(eventSocket->socket);
			free(eventSocket);
			continue;
		}
		else
		{
			//printf("TRACE - Receive message : %s (%d bytes)\n", eventSocket->dataBuffer.buf, eventSocket->dataBuffer.len);
			OnIoRecv(eventSocket->socket, eventSocket->dataBuffer.buf, eventSocket->dataBuffer.len);

			//if (WSASend(eventSocket->socket, &(eventSocket->dataBuffer), 1, &sendBytes, 0, NULL, NULL) == SOCKET_ERROR)
			//{
			//	if (WSAGetLastError() != WSA_IO_PENDING)
			//	{
			//		printf("Error - Fail WSASend(error_code : %d)\n", WSAGetLastError());
			//	}
			//}
			//printf("TRACE - Send message : %s (%d bytes)\n", eventSocket->dataBuffer.buf, eventSocket->dataBuffer.len);

			memset(eventSocket->messageBuffer, 0x00, MAX_BUFFER);
			eventSocket->receiveBytes = 0;
			eventSocket->sendBytes = 0;
			eventSocket->dataBuffer.len = MAX_BUFFER;
			eventSocket->dataBuffer.buf = eventSocket->messageBuffer;
			flags = 0;

			if (WSARecv(eventSocket->socket, &(eventSocket->dataBuffer), 1, &receiveBytes, &flags, &eventSocket->overlapped, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					printf("Error - Fail WSARecv(error_code : %d)\n", WSAGetLastError());
				}
			}
		}
	}

}

void CSimpleIocp::Send(SOCKET sock, char* buff, int size)
{
	WSABUF dataBuffer;
	dataBuffer.buf = buff;
	dataBuffer.len = size;

	DWORD sendBytes = 0;
	if (WSASend(sock, &dataBuffer, 1, &sendBytes, 0, NULL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("Error - Fail WSASend(error_code : %d)\n", WSAGetLastError());
		}
	}

	printf("TRACE - Send message : %s (%d bytes)\n", buff, sendBytes);

}

void CSimpleIocp::OnIoRecv(SOCKET sock, char* buff, int size)
{
	printf("TRACE - Receive message : %s (%d bytes)\n", buff, size);

	Send(sock, buff, size);
}
