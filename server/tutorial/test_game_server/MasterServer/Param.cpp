#include "stdafx.h"
#include "Param.h"


int CParam::Read()
{
	//WCHAR wzIP[MAX_IP_LENGTH] = L"";
	//if(FALSE == loader_.GetValue(L"common", L"ip", wzIP, sizeof(wzIP)))
	//	return SERVER_IP_INVALID;
	////ip = wzIP;
	//ip = HisUtil::IP_wTon(wzIP);

	//Listen socket port
	if (FALSE == loader_.GetValue(L"common", L"port_tcp", port_tcp))
		return SERVER_PORT_INVALID;
	port_tcp = htons(port_tcp);

	if (FALSE == loader_.GetValue(L"common", L"port_udp", port_udp))
		return SERVER_PORT_INVALID;
	port_udp = htons(port_udp);

	////max channel
	//if(FALSE == loader_.GetValue(L"common", L"maxchannel", max_channel))
	//	return GAMESERVER_INVALID_CHANNEL;

	////serverstatus
	//if(FALSE == loader_.GetValue(L"common", L"status", server_status))
	//	return INI_SERVER_STATUS;
	
	//max user
	if (FALSE == loader_.GetValue(L"common", L"max_user", max_user))
		return GAMESERVER_INVALID_MAX_USER;

	//server pool
	loader_.GetValue(L"common", L"ServerRecvUdpPoolCount", ServerRecvUdpPoolCount);
	loader_.GetValue(L"common", L"ServerSendUdpPoolCount", ServerSendUdpPoolCount);
	loader_.GetValue(L"common", L"RemoteRecvTcpPoolSize", RemoteRecvTcpPoolSize);
	loader_.GetValue(L"common", L"RemoteRecvUdpPoolCount", RemoteRecvUdpPoolCount);


	////(단위:ms)아바타 갱신주기
	//if(FALSE == loader_.GetValue(L"common", L"avatar_update_time", avatar_update_time))
	//	return AVATAR_UPDATE_TIME;


	return SERVER_OK;
}

int CParam::Read_DB(LPCTSTR keyName, HisUtil::ADO_DATABASE_INFO& dbinfo)
{
	//ip
	WCHAR wzIP[MAX_IP_LENGTH] = L"";
	if (FALSE == loader_.GetValue(keyName, L"ip", wzIP, sizeof(wzIP)))
		return SERVER_DB_IP_INVALID;
	dbinfo.m_ip = wzIP;

	//port
	if (FALSE == loader_.GetValue(keyName, L"port", dbinfo.m_port))
		return SERVER_DB_PORT_INVALID;

	//database
	WCHAR wzDatabase[64] = L"";
	if (FALSE == loader_.GetValue(keyName, L"database", wzDatabase, sizeof(wzDatabase)))
		return SERVER_DB_DATABASE_INVALID;
	dbinfo.m_database = wzDatabase;

	//user
	WCHAR wzUser[64] = L"";
	if (FALSE == loader_.GetValue(keyName, L"user", wzUser, sizeof(wzUser)))
		return SERVER_DB_USER_INVALID;
	dbinfo.m_user = wzUser;

	//passwd
	WCHAR wzPasswd[64] = L"";
	if (FALSE == loader_.GetValue(keyName, L"passwd", wzPasswd, sizeof(wzPasswd)))
		return SERVER_DB_PASSWD_INVALID;
	dbinfo.m_passwd = wzPasswd;

	return SERVER_OK;
}
