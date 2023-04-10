#pragma once

//사용자에 의해 선언되어지는 class 이다
class CMasterClient : public NetCore::CNetClient//, public M2_SEND, public C2_SEND
{
public:
	CMasterClient(void);
	virtual ~CMasterClient(void);

	VOID OnIoConnected(VOID);
	VOID OnIoDisconnected(VOID);
	VOID OnIoRecv(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort);
	VOID OnIoSend(VOID);

	VOID OnIoServerHolePunchingCompleted();

	VOID OnJoinGroup(HOSTID remote);
	VOID OnLeaveGroup(HOSTID remote);

	void Update();

	NetCore::IRemote* FindRemote(HOSTID remote) { return CNetClient::FindRemote(remote); }
	NetCore::CPacketSession* FindPacketSession(NetCore::IRemote* peer,bool bIsUdp) { return CNetClient::FindPacketSession(peer,bIsUdp); }

	////game서버의 접속자수를 balance 서버에 통보한다.
	//void SendCurrentUser();
	////game서버의 정보를 control 서버에 통보한다.
	//void SendGameServerInfo();

	//void SendToCertyfyReq(HOSTID remote, stX2G_AC_CERTIFY_REQ& st, HOSTID remoteX);
	//void SendToLogoutReq(CRemoteSession* session);

private:
	//void OnM2_AC_CERTIFY_ACK(HisUtil::CMsg& msgRecv);

	//////////

	//void OnC2_UDP_CHANGE_SERVER_STATUS_REQ(HisUtil::CMsg& msgRecv);


	//void OnX2L_CH_UDP_HELLO_PEER_REQ(CMsg& msgRecv);
	//void OnX2L_CH_UDP_FINE_THANKS_PEER_ACK(CMsg& msgRecv);

};
