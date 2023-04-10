#pragma once

namespace NetCore {

	typedef void(*func_OnIoRecvUdpPacket)(void*, ADDR_IP, ADDR_PORT, HisUtil::CMsg&);

	class CNetUdpIocp : public CIocp
	{
	public:

	public:
		CNetUdpIocp(VOID);
		virtual ~CNetUdpIocp(VOID);

	private:
		CPacketSession UdpSession_;

		//HANDLE GameThreadHandle_;
		//HANDLE GameThreadDestroyEvent_;

		//함수포인터 개체
		func_OnIoRecvUdpPacket m_OnIoRecvPacket;

	public:
		BOOL Begin(ADDR_PORT port, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, void* owner, void* callback_OnIoRecvPacket);
		BOOL End(VOID);

		//void SetOwner(CNetServer* server, void* func) {
		//	CIocp::SetOwner(server);
		//	m_OnIoRecvPacket = (func_OnIoRecvUdpPacket)func;
		//}

		//VOID ResetThreadCallback(VOID);

		BOOL SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort);//, DWORD protocol, const BYTE *packet, DWORD packetLength)

		CPacketSession*	GetUdpSession() { return &UdpSession_; }

		ADDR_PORT GetPrivatePort() { return UdpSession_.GetPrivatePort(); }

	protected:
		// CIocp 상속 가상함수들을 재선언 합니다.
		VOID OnIoRecv(VOID *object, DWORD dataLength);
		VOID OnIoSend(VOID *object, DWORD dataLength);
		VOID OnIoConnected(VOID *object) {}
		VOID OnIoDisconnected(VOID *object) {}

	};

};//..namespace NetCore {