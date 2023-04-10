#pragma once

#define MAX_COL_NUM		256


class CMyTBLBase
{
protected:
	virtual void _GetData()	{};

public:
	CMyTBLBase(void);
	virtual ~CMyTBLBase(void);

	BOOL Open(CMysqlConnect* pMysql,TCHAR* szQuery,...);
	BOOL Fetch();
	void Cleanup();

protected:
	CMysqlConnect*	m_pMysql;
	MYSQL_ROW		m_MysqlRow;

};
