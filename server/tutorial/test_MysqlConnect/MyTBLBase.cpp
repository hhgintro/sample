#include "StdAfx.h"
#include ".\mytblbase.h"

CMyTBLBase::CMyTBLBase(void) : m_pMysql(NULL),m_MysqlRow(NULL)
{
}

CMyTBLBase::~CMyTBLBase(void)
{
}

BOOL CMyTBLBase::Open(CMysqlConnect* pMysql, TCHAR* szQuery, ...)
{
	if( pMysql == NULL )
		return FALSE;

	TCHAR szMsg[256];
	va_list	pArg;

	va_start(pArg, szQuery);
	_vstprintf(szMsg, szQuery, pArg);
    va_end(pArg);

	m_pMysql = pMysql;
	if( m_pMysql->Open(szMsg)==FALSE )
		return FALSE;
	return TRUE;
}

BOOL CMyTBLBase::Fetch()
{
	if(m_pMysql->Fetch()==FALSE)
		return FALSE;

	m_MysqlRow = m_pMysql->GetMysqlRow();
	if( m_MysqlRow == NULL )
		return FALSE;

	_GetData();
	return TRUE;
}

void CMyTBLBase::Cleanup()
{
	m_pMysql->Cleanup();
}