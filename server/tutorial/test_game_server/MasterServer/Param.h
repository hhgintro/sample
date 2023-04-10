#pragma once


class CParam : public HisUtil::IParamBase, public HisUtil::CSingleton<CParam>
{
public:
	CParam(void) : ip(0), port_tcp(0), port_udp(0)//, max_channel(0), server_status(0)
		, max_user(0)//, avatar_update_time(0)
		, ServerRecvUdpPoolCount(0), ServerSendUdpPoolCount(0), RemoteRecvTcpPoolSize(0), RemoteRecvUdpPoolCount(0)
	{}
	~CParam(void) {}

private:
	virtual int Read();
		int Read_DB(LPCTSTR keyName, HisUtil::ADO_DATABASE_INFO& dbinfo);

public:

	ADDR_IP ip;     //���� ip
	ADDR_PORT port_tcp;			//���� port
	ADDR_PORT port_udp;			//���� port
	//INT32 max_channel;		//�ִ� channel��
	//UINT8 server_status;	//enum SERVER_STATUS

	UINT16 max_user;	//�ִ� ������

	int ServerRecvUdpPoolCount;		//server�ڽ��� recv udp pool
	int ServerSendUdpPoolCount;		//server�ڽ��� send udp pool
	int RemoteRecvTcpPoolSize;		//������ remote�� recv tcp pool
	int RemoteRecvUdpPoolCount;		//������ remote�� recv udp pool

	//TIME_T avatar_update_time; //(����:ms)�ƹ�Ÿ �����ֱ�
};

