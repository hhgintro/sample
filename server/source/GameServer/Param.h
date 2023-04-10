#pragma once


class CParam : public HisUtil::IParamBase, public HisUtil::CSingleton<CParam>
{
public:
	CParam(void) : ip(0), port_tcp(0), port_udp(0), max_channel(0), server_status(0)
		, max_user(0), avatar_update_time(0)
		, ipMaster(0), portMaster(0)
	{}
	~CParam(void) {}

private:
	virtual int Read();
		int Read_DB(LPCTSTR keyName, HisUtil::ADO_DATABASE_INFO& dbinfo);

public:

	ADDR_IP ip;     //서버 ip
	ADDR_PORT port_tcp;			//서버 port
	ADDR_PORT port_udp;			//서버 port
	INT32 max_channel;		//최대 channel수
	UINT8 server_status;	//enum SERVER_STATUS

	UINT16 max_user;	//최대 동접수

	TIME_T avatar_update_time; //(단위:ms)아바타 갱신주기


	//master
	//std::wstring ipMaster;
	//UINT16 portMaster;
	ADDR_IP	ipMaster;
	ADDR_PORT portMaster;

};

