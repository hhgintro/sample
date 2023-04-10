#pragma once

namespace NetCore {

	class INetClientEvent
	{
	public:
		INetClientEvent(void);
		virtual ~INetClientEvent(void);


		virtual VOID OnIoConnected(VOID) = 0;
		virtual VOID OnIoDisconnected(VOID) = 0;
		virtual VOID OnIoRecv(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort) = 0;
		virtual VOID OnIoSend(VOID) = 0;

		virtual VOID OnIoServerHolePunchingCompleted() = 0;

		virtual VOID OnJoinGroup(HOSTID remote) = 0;
		virtual VOID OnLeaveGroup(HOSTID remote) = 0;
	};

};//..namespace NetCore {