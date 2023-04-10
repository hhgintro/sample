#pragma once


#include "mytblBase.h"


/*실행의 예
	CMysqlConnect m_mysql;
	DWORD dwError = m_mysql.Connect("localhost","root","root","rakion", 3306);
	if( dwError == 0 ) {

		TCHAR szQuery[1024] = "";
		TCHAR szAccount[32] = "";
		TCHAR szCreateTime[32] = "";
		int iAccountID = 0;

		CTBLCharData tblCharData;
		//wsprintf(szQuery,"SELECT id,name,createtime FROM usergameinfo limit %d", 1);
		if(tblCharData.Open(&m_mysql,"SELECT id,name,createtime FROM usergameinfo limit %d", 2))
		{
			while(tblCharData.Fetch())
			{
				iAccountID = tblCharData.m_iAccountID;
				memcpy(szAccount, tblCharData.m_szAccount, 32);
				memcpy(szCreateTime, tblCharData.m_szCreateTime, 32);
			}
		}
		tblCharData.Cleanup();

		m_mysql.Disconnect();
	}
*/

class CTBLCharData : public CMyTBLBase
{
public:
	int		m_iAccountID;
	TCHAR	m_szAccount[21];
	TCHAR	m_szCreateTime[21];

protected:
BEGIN_TBLCOL_MAP()
	m_iAccountID = static_cast<ULONG>(atol(m_MysqlRow[0]));
	lstrcpy(reinterpret_cast<LPTSTR>(m_szAccount), reinterpret_cast<LPCTSTR>(m_MysqlRow[1]));
	lstrcpy(reinterpret_cast<LPTSTR>(m_szCreateTime), reinterpret_cast<LPCTSTR>(m_MysqlRow[2]));
END_PARAM_MAP()
};
