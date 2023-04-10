#pragma once


namespace NetCore {

	class CRemoteSession;

	class INetServerEvent
	{
	public:
		INetServerEvent(void);
		virtual ~INetServerEvent(void);


		virtual VOID OnIoConnected(CRemoteSession* session) = 0;
		virtual VOID OnIoDisconnected(CRemoteSession* session) = 0;
		virtual VOID OnIoRecv(CRemoteSession* session, HisUtil::CMsg& msgRecv) = 0;
		virtual VOID OnIoSend(CRemoteSession* session, DWORD dataLength) = 0;

		virtual VOID OnHolePunchingServer(CRemoteSession* session) = 0;
		virtual VOID OnJoinGroup(CRemoteSession* session) = 0;
		virtual VOID OnLeaveGroup(CRemoteSession* session) = 0;
	};

};//..namespace NetCore {