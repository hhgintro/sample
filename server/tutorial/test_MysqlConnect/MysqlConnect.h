

#pragma once

#include <mysql.h>


#define BEGIN_TBLCOL_MAP()								\
	virtual void _GetData ()							\
	{

#define COLUMN_ENTRY(n,v)								\
		GetData (n,v);

#define COLUMN_ENTRY_STRING(n,v,s)						\
		GetData (n,v,s);

#define PARAM_ENTRY(n,v)								\
		BindParam (n,v);

#define PARAM_ENTRY_STRING(n,v,s)						\
		BindParam (n,v,s);

#define END_PARAM_MAP()									\
	}


class CMysqlConnect
{
private:
	MYSQL*		mysql;
	MYSQL_RES*	mysql_res;
	MYSQL_ROW	mysql_row;

public:
	CMysqlConnect(void);
	virtual ~CMysqlConnect(void);

	inline MYSQL_ROW GetMysqlRow() { return mysql_row; }

	DWORD Connect( LPCTSTR szIP, LPCTSTR szUser, LPCTSTR szPasswd, LPCTSTR szDB, WORD wPort );
	void Disconnect();

	BOOL Open(TCHAR* szQuery);
	BOOL Fetch();
	void Cleanup();


	void ErrorLog(LPCTSTR szLog);
};
