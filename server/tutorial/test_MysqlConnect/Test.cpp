// Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwError = 0;
	BYTE bResult = 0;

	CMysqlConnect m_mysql;
	dwError = m_mysql.Connect("localhost","root","star1001","rapcon", 3306);
	if( dwError == 0 ) {

		TCHAR szQuery[1024] = "";
		TCHAR szAccount[32] = "";
		TCHAR szCreateTime[32] = "";
		int iAccountID = 0;

		CTBLCharData tblCharData;
		//wsprintf(szQuery,"SELECT id,name,createtime FROM usergameinfo limit %d", 1);
		if(tblCharData.Open(&m_mysql,"SELECT * FROM radio_tbl limit %d", 2))
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

	return 0;
}

