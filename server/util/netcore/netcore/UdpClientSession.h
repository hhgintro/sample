#pragma once


namespace NetCore {

	// 클라이언트 통신을 담당할 CTcpClientSession 개체
	// CClientSession을 상속받아서 사용합니다.
	class CUdpClientSession : public CClientSession
	{
	protected:
		VOID OnIoConnected(VOID) {}
		VOID OnIoDisconnected(VOID) {}

		VOID OnIoSend(VOID);
		VOID OnIoRecv(VOID);

		//public:
		//	void OnNetC2S_CORE_HEART_BEAT_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
		//	void OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
		//
		//	void OnCORE_UDP_HOLE_PUNCHING_PEER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
		//	void OnCORE_UDP_HOLE_PUNCHING_PEER_ACK(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
		//
		//	void OnCH_UDP_HELLO_PEER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)

	};

};//..namespace NetCore {