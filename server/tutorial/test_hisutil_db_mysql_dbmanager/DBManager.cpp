#include "stdafx.h"
#include "DBManager.h"


#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "adoEOF")

CDBManager::CDBManager()
{
	::CoInitialize(NULL);
}


CDBManager::~CDBManager()
{
	_pooConn.End();
	::CoUninitialize();
}


void CDBManager::init(HisUtil::ADO_DATABASE_INFO& info)
{
	_info.m_ip			= info.m_ip;
	_info.m_port		= info.m_port;
	_info.m_database	= info.m_database;
	_info.m_user		= info.m_user;
	_info.m_passwd		= info.m_passwd;
}

void CDBManager::init(TCHAR* ip, UINT16 port, TCHAR* database, TCHAR* user, TCHAR* passwd)
{
	_info.m_ip			= ip;
	_info.m_port		= port;
	_info.m_database	= database;
	_info.m_user		= user;
	_info.m_passwd		= passwd;
}

BOOL CDBManager::connect(HisUtil::CAdoConnection* conn)
{
	//bstr_t szConn = L"Driver={MySQL ODBC 8.0 Unicode Driver};server=localhost;port=3306;Database=world;User ID=root;Password=star1001;";
	TCHAR szConn[1024] = _T("");
	_stprintf_s(szConn, _T("Driver={MySQL ODBC 8.0 Unicode Driver};server=%s;port=%d;Database=%s;User ID=%s;Password=%s;")
		, _info.m_ip.c_str(), _info.m_port, _info.m_database.c_str(), _info.m_user.c_str(), _info.m_passwd.c_str());

	//HisUtil::CAdoConnection _conn1;
	//if (FALSE == _conn1.Open(szConn))
	//	return FALSE;

	// ***** CAdoConnection 개체는 ::CoInitialize(NULL)가 먼저 호출되어야 합니다. *****//
	if (FALSE == conn->Open(szConn))
		return FALSE;
	return TRUE;
}

HisUtil::CAdoConnection* CDBManager::GetConnection()
{
	//return *_conn;
	HisUtil::CAdoConnection* conn = _pooConn.Front_Pop();
	if (NULL == conn)
		conn = _pooConn.Create();

	BOOL ret = connect(conn);
	if (FALSE == ret)
	{
		Release(conn);
		return NULL;
	}
	return conn;
}

void CDBManager::Release(HisUtil::CAdoConnection* conn)
{
	conn->Close();
	_pooConn.Release(conn);
}
