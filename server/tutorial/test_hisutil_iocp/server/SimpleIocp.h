#pragma once

#define MAX_BUFFER        1024


class CSimpleIocp
{
	struct SOCKETINFO
	{
		WSAOVERLAPPED overlapped;
		WSABUF dataBuffer;
		SOCKET socket;
		char messageBuffer[MAX_BUFFER];
		int receiveBytes;
		int sendBytes;
	};

public:
	CSimpleIocp();
	virtual ~CSimpleIocp();

	BOOL Begin(UINT16 port);
	void End();

	static unsigned int CALLBACK _AcceptThread(void* lpParam);
	void OnAcceptThread();

	static unsigned int CALLBACK _WorkThread(void* lpParam);
	void OnWorkThread();


	void Send(SOCKET sock, char* buff, int size);

	//===========================================
	//이 함수는 상속 받은 class에서 Overriding(함수재정의)하세요.(overloading(인자가다른것)과 헷갈리네)
	virtual void OnIoRecv(SOCKET sock, char* buff, int size);

private:

	SOCKET m_listenSocket;
	HANDLE m_hIOCP;

};

