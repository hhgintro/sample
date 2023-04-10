#pragma once

class CClientWorld;

//사용자에 의해 선언되어지는 class 이다
class CBalanceClient : public CNetClient, public X2B_SEND
{
public:
	CBalanceClient(void);
	virtual ~CBalanceClient(void);

	VOID OnIoConnected(VOID);
	VOID OnIoDisconnected(VOID);
	VOID OnIoRecv(CMsg& msgRecv);
	VOID OnIoSend(VOID);

	VOID OnIoServerHolePunchingCompleted();

	VOID OnJoinGroup(HOSTID remote);
	VOID OnLeaveGroup(HOSTID remote);

	void Update();

	void Login();
	//void JoinGroup();
	//void LeaveGroup();
	//void SayHelloPeer();

	IRemote* FindRemote(HOSTID remote) { return CNetClient::FindRemote(remote); }
	CPacketSession* FindPacketSession(HOSTID remote, BOOL bIsUdp) { return CNetClient::FindPacketSession(remote, bIsUdp); }

	CClientWorld* GetOwner() { return owner_; }
	void SetOwner(CClientWorld* owner) { owner_ = owner; }

private:

	//////////
	void OnX2B_AC_LOGIN_ACK(CMsg& msgRecv);

	CClientWorld* owner_;
};
