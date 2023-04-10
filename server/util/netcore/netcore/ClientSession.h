#pragma once

namespace NetCore {

	class IRemote;

	class CClientSession : public CEventSelect
	{
	public:
		CClientSession(VOID) {}
		virtual ~CClientSession(VOID) {}

		virtual BOOL	BeginTcp(ADDR_IP ip, ADDR_PORT port, int nRecvTcpPoolSize);
		virtual BOOL	BeginUdp(ADDR_PORT remotePort, int nRecvUdpPoolCnt, int nSendUdpPoolCnt);

		virtual BOOL	End(VOID);

		//IRemote* FindRemote(HOSTID remote);
		//CPacketSession* FindPacketSession(HOSTID remote, BOOL bIsUdp);

		virtual ADDR_IP		GetPrivateIP();
		virtual ADDR_PORT	GetPrivatePort();

		//virtual BOOL	ReadPacket(DWORD &protocol, BYTE *packet, DWORD &packetLength);
		//virtual BOOL	ReadFromPacket(DWORD &protocol, LPSTR remoteIP, WORD &remotePort, BYTE *packet, DWORD &packetLength);
		virtual BOOL	ReadPacket(void* pData);
		virtual BOOL	ReadFromPacket(void* pData, ADDR_IP& remoteIP, ADDR_PORT &remotePort);

		virtual BOOL	SendPacket(HisUtil::CMsg& msg);//, DWORD protocol, const BYTE *packet, int packetLength)
		virtual BOOL	SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort);//, DWORD protocol, const BYTE *packet, DWORD packetLength)

		CPacketSession& GetPacketSession() { return mSession; }

	protected:
		CPacketSession	mSession;
	};

};//..namespace NetCore {