#pragma once

//사용자에 의해 선언되어지는 class 이다
class CServer : public NetCore::CNetServer//, public M2_SEND, public C2_SEND
{
public:
	CServer(void);
	virtual ~CServer(void);

	DWORD Start(int maxuser, ADDR_PORT portTcp, ADDR_PORT portUdp
		, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, int nRemoteRecvTcpPoolSize, int nRemoteRecvUdpPoolCnt);

	VOID OnIoConnected(NetCore::CRemoteSession* session);
	VOID OnIoDisconnected(NetCore::CRemoteSession* session);
	VOID OnIoRecv(NetCore::CRemoteSession* session, HisUtil::CMsg& msgRecv);
	VOID OnIoSend(NetCore::CRemoteSession* session, DWORD dataLength);

	
	VOID OnHolePunchingServer(NetCore::CRemoteSession* session);
	VOID OnJoinGroup(NetCore::CRemoteSession* session);
	VOID OnHolePunchingGroup(NetCore::CRemoteSession* session);
	VOID OnLeaveGroup(NetCore::CRemoteSession* session);


	NetCore::IRemote* FindRemote(HOSTID remote);
	NetCore::CPacketSession* FindPacketSession(NetCore::IRemote* peer, bool bIsUdp);

	//BOOL CheckDuplicateLogin(CAccountInfo* accountinfo, CRemoteSession* session);
private:
	//////////////////////////////////////////////////////////////////////////
	// 프로토콜 처리 함수

	////TCP
	//void OnM2_JOIN_GROUP_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);
	//void OnM2_AC_LOGIN_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);
	//void OnM2_AC_LOGOUT_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);


	//void OnM2_AC_CERTIFY_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv);


	//////UDP
	////void OnCORE_UDP_HOLE_PUNCHING_SERVER_REQ(VOID* object, DWORD remoteIP, WORD remotePort, HisUtil::CMsg& msgRecv)

	//void OnC2_UDP_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv);


	//..// 프로토콜 처리 함수
	//////////////////////////////////////////////////////////////////////////

	//static function
	static void Callback_OnIoRecvUdpPacket(void* owner, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);
	//from NotUdpIocp
	void OnIoRecvPacket(ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv);

private:
	P2PGROUPID MasterServerGroupID_;
};
