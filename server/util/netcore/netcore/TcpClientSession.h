#pragma once


namespace NetCore {

	// Ŭ���̾�Ʈ ����� ����� CTcpClientSession ��ü
	// CClientSession�� ��ӹ޾Ƽ� ����մϴ�.
	class CTcpClientSession : public CClientSession
	{
	protected:
		// Ŭ���̾�Ʈ�� ���� �����Ǿ����� ȣ��Ǵ� �����Լ�
		VOID OnIoConnected(VOID);
		// Ŭ���̾�Ʈ�� ���� ����Ǿ����� ȣ��Ǵ� �����Լ�
		VOID OnIoDisconnected(VOID);

		VOID OnIoSend(VOID);
		VOID OnIoRecv(VOID);

	public:
		CTcpClientSession() {}
		~CTcpClientSession() {}

	};

};//..namespace NetCore {