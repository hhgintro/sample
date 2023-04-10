#pragma once

namespace NetCore {

	//class CRemoteSession;
	//typedef void(*func_OnIoConnected)(void*, CRemoteSession*);
	typedef void(*func_OnIoConnected)(void* owner, void* session);
	typedef void(*func_OnIoDisconnected)(void* owner, void* session);
	typedef void(*func_OnIoRecvTcpPacket)(void* owner, void* session, HisUtil::CMsg&);

	class CNetIocp : public CIocp
	{
	public:
		CNetIocp(VOID);
		virtual ~CNetIocp(VOID);

	private:
		CNetworkSession	mListenSession;
		//CPacketSession mListenSession;

		//함수포인터 개체
		func_OnIoConnected m_OnIoConnected;
		func_OnIoDisconnected m_OnIoDisconnected;
		func_OnIoRecvTcpPacket m_OnIoRecvPacket;

	public:
		BOOL Begin(ADDR_PORT port, void* owner, void* Callback_OnIoConnected, void* Callback_OnIoDisconnected, void* callback_OnIoRecvPacket);
		BOOL End(VOID);

		CNetworkSession& GetListenSession() { return mListenSession; }

		ADDR_IP GetPrivateIP();
		ADDR_PORT GetPrivatePort();

		//void SetOwner(CNetServer* server, void* func_Connect, void* func_Disconnect, void* func_RecvPacket ) {
		//	CIocp::SetOwner(server);
		//	m_OnIoConnected = (func_OnIoConnected)func_Connect;
		//	m_OnIoDisconnected = (func_OnIoDisconnected)func_Disconnect;
		//	m_OnIoRecvPacket = (func_OnIoRecvTcpPacket)func_RecvPacket;
		//}

		//protected:
			// CIocp 상속 가상함수들을 재선언 합니다.
		VOID OnIoRecv(VOID *object, DWORD dataLength);
		VOID OnIoSend(VOID *object, DWORD dataLength);
		VOID OnIoConnected(VOID *object);
		VOID OnIoDisconnected(VOID *object);


	};

};//..namespace NetCore {