#include "stdafx.h"
#include "Param.h"


int CParam::Read()
{
	//===============================================
	//server
	{
		WCHAR wzIP[MAX_IP_LENGTH] = L"";
		if (FALSE == loader_.GetValue(L"server", L"ip", wzIP, sizeof(wzIP)))
			return SERVER_IP_INVALID;
		//ip = wzIP;
		ip = HisUtil::IP_wTon(wzIP);

		//Listen socket port
		if (FALSE == loader_.GetValue(L"server", L"port_tcp", port_tcp))
			return SERVER_PORT_INVALID;
		port_tcp = htons(port_tcp);

		if (FALSE == loader_.GetValue(L"server", L"port_udp", port_udp))
			return SERVER_PORT_INVALID;
		port_udp = htons(port_udp);

		//max channel
		if (FALSE == loader_.GetValue(L"server", L"maxchannel", max_channel))
			return GAMESERVER_INVALID_CHANNEL;

		//serverstatus
		if (FALSE == loader_.GetValue(L"server", L"status", server_status))
			return INI_SERVER_STATUS;

		//max user
		if (FALSE == loader_.GetValue(L"server", L"max_user", max_user))
			return GAMESERVER_INVALID_MAX_USER;


		//(단위:ms)아바타 갱신주기
		if (FALSE == loader_.GetValue(L"server", L"avatar_update_time", avatar_update_time))
			return AVATAR_UPDATE_TIME;
	}



	//===============================================
	//master server
	{
		WCHAR wzIP[MAX_IP_LENGTH] = L"";
		if (FALSE == loader_.GetValue(L"master", L"ip", wzIP, sizeof(wzIP)))
			return MASTER_IP_INVALID;
		//ipMaster = wzIP;
		ipMaster = HisUtil::IP_wTon(wzIP);

		if (FALSE == loader_.GetValue(L"master", L"port", portMaster))
			return MASTER_PORT_INVALID;
		portMaster = htons(portMaster);
	}

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
