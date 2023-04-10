#pragma once


class CDBManager
{
public:
	CDBManager();
	~CDBManager();


	void init(HisUtil::ADO_DATABASE_INFO& info);
	void init(TCHAR* ip, UINT16 port, TCHAR* database, TCHAR* user, TCHAR* passwd);

	BOOL connect(HisUtil::CAdoConnection* conn);

	HisUtil::CAdoConnection* GetConnection();
	void Release(HisUtil::CAdoConnection* conn);

public:
	HisUtil::ADO_DATABASE_INFO _info;
	HisUtil::CMemoryQueuePool<HisUtil::CAdoConnection> _pooConn;

};

