#include "StdAfx.h"
#include "mysqlconnect.h"


CMysqlConnect::CMysqlConnect(void) : mysql(NULL), mysql_res(NULL), mysql_row(NULL)
{
}

CMysqlConnect::~CMysqlConnect(void)
{
	Disconnect();
}

DWORD CMysqlConnect::Connect( LPCTSTR szIP, LPCTSTR szUser, LPCTSTR szPasswd, LPCTSTR szDB, WORD wPort )
{
	mysql=mysql_init(NULL);
	if(!mysql)
		return ERR_CONNECTDB_MYSQL_INIT;

	mysql=mysql_real_connect(mysql,szIP,szUser,szPasswd,szDB,wPort,NULL,0);
	if( !mysql )
		return ERR_CONNECTDB_MYSQL_CONNECT;
	return 0;
}

void CMysqlConnect::Disconnect()
{
	if(mysql) {
		mysql_close(mysql);
		mysql = NULL;
	}
}


BOOL CMysqlConnect::Open(TCHAR* szQuery)
{
	if(mysql_query(mysql, szQuery)) {
		ErrorLog(szQuery);
		return FALSE;
	}
	mysql_res = mysql_store_result(mysql);
	if(!mysql_res)
		return FALSE;
	return TRUE;
}

BOOL CMysqlConnect::Fetch()
{
	mysql_row = mysql_fetch_row(mysql_res);
	if( mysql_row == NULL )
		return FALSE;
	return TRUE;
}

void CMysqlConnect::Cleanup()
{
	if( mysql_res )
	{
		mysql_free_result(mysql_res);
		mysql_res = NULL;
	}
}

void CMysqlConnect::ErrorLog(LPCTSTR szLog)
{
	HANDLE hLog			= NULL;
	CHAR   szTime[128]	= _T("");;
	DWORD  dwBytes		= 0;

	hLog = CreateFile(".\\DBError.log", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	if(!hLog)
		return;
	if(SetFilePointer(hLog, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER)
		return;

	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	wsprintf( szTime,
		"[%04u-%02u-%02u %02u:%02u:%02u] [%s] [%s]\r\n",
		stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond, mysql_error(mysql), szLog );
	WriteFile(hLog, szTime, static_cast<DWORD>(lstrlen(szTime)), &dwBytes, NULL);

	CloseHandle(hLog);
}
