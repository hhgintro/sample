#include "stdafx.h"
#include "BaseDBManager.h"


#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "adoEOF")

namespace HisUtil {

	CBaseDBManager::CBaseDBManager()
	{
		::CoInitialize(NULL);

		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		//HisUtil::CThread::BeginThread(1);// SystemInfo.dwNumberOfProcessors * 2 + 1);

	}


	CBaseDBManager::~CBaseDBManager()
	{
		//HisUtil::CThread::EndThread();

		poolConn_.End();
		::CoUninitialize();
	}


	void CBaseDBManager::init(WCHAR* wzConnStr)
	{
		m_wzConnStr = wzConnStr;
	}

	BOOL CBaseDBManager::connect(HisUtil::CAdoConnection* conn)
	{
		////bstr_t szConn = L"Driver={MySQL ODBC 8.0 Unicode Driver};server=localhost;port=3306;Database=world;User ID=root;Password=star1001;";
		//TCHAR szConn[1024] = _T("");
		//_stprintf_s(szConn, _T("Driver={MySQL ODBC 8.0 Unicode Driver};server=%s;port=%d;Database=%s;User ID=%s;Password=%s;")
		//	, _info.m_ip.c_str(), _info.m_port, _info.m_database.c_str(), _info.m_user.c_str(), _info.m_passwd.c_str());

		//HisUtil::CAdoConnection _conn1;
		//if (FALSE == _conn1.Open(szConn))
		//	return FALSE;

		// ***** CAdoConnection 개체는 ::CoInitialize(NULL)가 먼저 호출되어야 합니다. *****//
		if (FALSE == conn->Open((WCHAR*)m_wzConnStr.c_str()))
			return FALSE;
		return TRUE;
	}

	HisUtil::CAdoConnection* CBaseDBManager::GetConnection()
	{
		//return *_conn;
		HisUtil::CAdoConnection* conn = poolConn_.Front_Pop();
		if (NULL == conn)
			conn = poolConn_.Create();

		BOOL ret = connect(conn);
		if (FALSE == ret)
		{
			Release(conn);
			return NULL;
		}
		return conn;
	}

	void CBaseDBManager::Release(HisUtil::CAdoConnection* conn)
	{
		if (NULL == conn)
			return;
		conn->Close();
		poolConn_.Release(conn);
	}

	//void CDBManager::OnWorkerThread(int index)
	//{
	//	while (true)
	//	{
	//		Sleep(1);
	//		//printf("thread index: %d\n", index);
	//
	//		HisUtil::CSPBase* base = GetWork();
	//		if(NULL == base) continue;
	//
	//		base->Open();
	//		base->GetResult();
	//
	//		base->CleanUp();
	//		ReleaseWork(base);
	//	}
	//}
};//..namespace HisUtil {