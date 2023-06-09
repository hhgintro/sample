#pragma once


class CParam : public HisUtil::IParamBase, public HisUtil::CSingleton<CParam>
{
public:
	CParam(void) : ip(0), port_tcp(0), port_udp(0)//, max_channel(0), server_status(0)
		, max_user(0)//, avatar_update_time(0)
		, ServerRecvUdpPoolCount(0), ServerSendUdpPoolCount(0), RemoteRecvTcpPoolSize(0), RemoteRecvUdpPoolCount(0)
		, ip_master(0), port_master(0)
		, ClientRecvTcpPoolSize(0), ClientRecvUdpPoolCount(0), ClientSendUdpPoolCount(0)
	{}
	~CParam(void) {}

private:
	virtual int Read();
		int Read_DB(LPCTSTR keyName, HisUtil::ADO_DATABASE_INFO& dbinfo);

public:

	ADDR_IP ip;     //서버 ip
	ADDR_PORT port_tcp;			//서버 port
	ADDR_PORT port_udp;			//서버 port
	//INT32 max_channel;		//최대 channel수
	//UINT8 server_status;	//enum SERVER_STATUS

	UINT16 max_user;	//최대 동접수

	int ServerRecvUdpPoolCount;		//server자신의 recv udp pool
	int ServerSendUdpPoolCount;		//server자신의 send udp pool
	int RemoteRecvTcpPoolSize;		//접속한 remote의 recv tcp pool
	int RemoteRecvUdpPoolCount;		//접속한 remote의 recv udp pool

	//TIME_T avatar_update_time; //(단위:ms)아바타 갱신주기

	ADDR_IP ip_master;			//master서버 ip
	ADDR_PORT port_master;		//master서버 port

	int ClientRecvTcpPoolSize;		//master에 접속한 자신의 recv tcp pool
	int ClientRecvUdpPoolCount;		//master에 접속한 자신의 recv udp pool
	int ClientSendUdpPoolCount;		//master에 접속한 자신의 send udp pool

};

