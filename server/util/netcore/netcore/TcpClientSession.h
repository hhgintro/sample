#pragma once


namespace NetCore {

	// 클라이언트 통신을 담당할 CTcpClientSession 개체
	// CClientSession을 상속받아서 사용합니다.
	class CTcpClientSession : public CClientSession
	{
	protected:
		// 클라이언트가 접속 성공되었을때 호출되는 가상함수
		VOID OnIoConnected(VOID);
		// 클라이언트가 접속 종료되었을때 호출되는 가상함수
		VOID OnIoDisconnected(VOID);

		VOID OnIoSend(VOID);
		VOID OnIoRecv(VOID);

	public:
		CTcpClientSession() {}
		~CTcpClientSession() {}

	};

};//..namespace NetCore {