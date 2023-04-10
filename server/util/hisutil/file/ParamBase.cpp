#include "stdafx.h"
#include "ParamBase.h"

namespace HisUtil {

	int IParamBase::Read_DB(LPCTSTR keyName, ADO_DATABASE_INFO& dbinfo)
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

	int IParamBase::Read_Ftp(LPCTSTR keyName, FTP_SERVER_INFO& ftp)
	{
		//ip
		WCHAR wzIP[MAX_PATH] = L"";
		if (FALSE == loader_.GetValue(keyName, L"ftp", wzIP, sizeof(wzIP)))
			return FTP_IP_INVALID;
		ftp.m_ip = wzIP;

		//port
		if (FALSE == loader_.GetValue(keyName, L"port", ftp.m_port))
			return FTP_PORT_INVALID;

		//user
		WCHAR wzUser[64] = L"";
		if (FALSE == loader_.GetValue(keyName, L"user", wzUser, sizeof(wzUser)))
			return FTP_USER_INVALID;
		ftp.m_user = wzUser;

		//passwd
		WCHAR wzPasswd[64] = L"";
		if (FALSE == loader_.GetValue(keyName, L"passwd", wzPasswd, sizeof(wzPasswd)))
			return FTP_PASSWD_INVALID;
		ftp.m_passwd = wzPasswd;

		//database
		WCHAR wzPath[MAX_PATH] = L"";
		if (FALSE == loader_.GetValue(keyName, L"path", wzPath, sizeof(wzPath)))
			return FTP_PATH_INVALID;
		ftp.m_path = wzPath;

		return SERVER_OK;
	}

};//..namespace HisUtil {
