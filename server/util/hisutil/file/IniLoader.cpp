#include "stdafx.h"
#include "IniLoader.h"

namespace HisUtil {

	CIniLoader::CIniLoader(VOID)
		: file_(0)
	{
		ZeroMemory(m_filename, sizeof(m_filename));
	}

	CIniLoader::~CIniLoader(VOID)
	{
		Close();
	}

	BOOL CIniLoader::Open(LPCTSTR filename)
	{
		if (!filename)
			return FALSE;

		_tcsncpy_s(m_filename, filename, MAX_PATH);

		if(0 != _tfopen_s(&file_, m_filename, _T("r")) )
			return FALSE;

		Close();
		return TRUE;
	}

	BOOL CIniLoader::Close(VOID)
	{
		if(file_)
		{
			fclose(file_);
			file_ = NULL;
		}
		return TRUE;
	}

	//BOOL CIniLoader::GetValue(LPCTSTR keyName, LPCTSTR valueName, LPDWORD values)
	//{
	//	if (!keyName || !valueName || !value)
	//		return FALSE
	//
	//	//모듈 보호
	//	if(FALSE == m_module.CheckValid())
	//		return TRUE;
	//
	//	if(0 == (*values = GetPrivateProfileInt(keyName, valueName, 0, mFileName)))
	//		return FALSE
	//
	//	return TRUE
	//}

	BOOL CIniLoader::GetValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT& values)
	{
		if (!keyName || !valueName)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		TCHAR temp[64] = {0,};

		if(0 == GetPrivateProfileString(keyName, valueName, _T(""), temp, 64, m_filename))
			return FALSE;

		values = (FLOAT) _tstof(temp);
		return TRUE;
	}

	BOOL CIniLoader::GetValue(LPCTSTR keyName, LPCTSTR valueName, LPTSTR values, UINT32 bufferLength)
	{
		//if (!keyName || !valueName || !values || !bufferLength)
		if (!keyName || !valueName || !bufferLength)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		if(0 == GetPrivateProfileString(keyName, valueName, _T(""), values, bufferLength, m_filename))
			return FALSE;

		return TRUE;
	}

	BOOL CIniLoader::GetNormalValue(LPCTSTR keyName, LPCTSTR valueName, UINT32& values)
	{
		if (!keyName || !valueName)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		UINT32 temp = 0;
		if(DEFAULT_VALUE == (temp = GetPrivateProfileInt(keyName, valueName, DEFAULT_VALUE, m_filename)))
			return FALSE;

		values = temp;
		return TRUE;
	}

	BOOL CIniLoader::SetValue(LPCTSTR keyName, LPCTSTR valueName, UINT32 values)
	{
		if (!keyName || !valueName)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		TCHAR temp[64]	= {0,};
		//_itot(values, temp, 64);
		_stprintf_s(temp, 64, _T("%d"), values);

		BOOL ret = WritePrivateProfileString(keyName, valueName, temp, m_filename);
		//DWORD error = GetLastError();
		return ret;
	}

	BOOL CIniLoader::SetValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR values)
	{
		if (!keyName || !valueName || !values)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		BOOL ret = WritePrivateProfileString(keyName, valueName, values, m_filename);
		//DWORD error = GetLastError();
		return ret;
	}

	BOOL CIniLoader::SetValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT values)
	{
		if (!keyName || !valueName)
			return FALSE;

		//모듈 보호
		if(FALSE == m_module.CheckValid())
			return TRUE;

		TCHAR temp[64]	= {0,};
		_stprintf_s(temp, 64, _T("%f"), values);

		BOOL ret = WritePrivateProfileString(keyName, valueName, temp, m_filename);
		//DWORD error = GetLastError();
		return ret;
	}


};//..namespace HisUtil {