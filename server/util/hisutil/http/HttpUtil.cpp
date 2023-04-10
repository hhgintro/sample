#include "stdafx.h"

#include "HttpUtil.h"

#pragma warning(disable: 4996)
//#pragma warning(disable: 1786)


namespace HisUtil
{
	/* 유용한 std::string 에 대한 formatting 함수 */
	std::string format_arg_list(const char *fmt, va_list args)
	{
		if (!fmt) return "";
		int   result = -1, length = 2048;
		char *buffer = 0;
		while (result == -1)    {
			if (buffer)
				delete [] buffer;
			buffer = new char [length + 1];
			memset(buffer, 0, (length + 1) * sizeof(char) );

			// remove deprecate warning
			//result = _vsnprintf(buffer, length, fmt, args);

			result = _vsnprintf_s(buffer, length, _TRUNCATE, fmt, args);
			length *= 2;
		}
		std::string s(buffer);
		delete [] buffer;
		return s;
	}

	std::wstring format_arg_list(const wchar_t *fmt, va_list args)
	{
		if (!fmt) return L"";
		int   result = -1, length = 2048;
		wchar_t *buffer = 0;
		while (result == -1)    {
			if (buffer)
				delete [] buffer;
			buffer = new wchar_t [length + 1];
			memset(buffer, 0, (length + 1) * sizeof(wchar_t) );

			// remove deprecate warning
			//result = _vsnprintf(buffer, length, fmt, args);

			result = _vsnwprintf_s(buffer, length, _TRUNCATE, fmt, args);
			length *= 2;
		}
		std::wstring s(buffer);
		delete [] buffer;
		return s;
	}

	std::string format(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		std::string s = format_arg_list(fmt, args);
		va_end(args);
		return s;
	}

	std::wstring format(const wchar_t *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		std::wstring s = format_arg_list(fmt, args);
		va_end(args);
		return s;
	}

	bool IsWow64()
	{
		BOOL bIsWoW64 = FALSE;

		typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

		LPFN_ISWOW64PROCESS fnIsWow64Process;

		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
			GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

		if (NULL != fnIsWow64Process)
		{
			if (!fnIsWow64Process(GetCurrentProcess(),&bIsWoW64))
			{
				// handle error
			}
		}
		return bIsWoW64 != FALSE ? true : false;
	}

	bool EnablePrivilege(LPCTSTR szPrivilege)
	{
		BOOL bResult = FALSE;
		HANDLE hToken = NULL;
		TOKEN_PRIVILEGES tpOld, tpCurrent;

		if( !OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken) )
			return bResult != FALSE ? true : false;

		tpCurrent.PrivilegeCount = 1;
		tpCurrent.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		if( ::LookupPrivilegeValue(NULL, szPrivilege, &tpCurrent.Privileges[0].Luid) )
		{
			DWORD dwOld = sizeof(TOKEN_PRIVILEGES);
			if( ::AdjustTokenPrivileges(hToken, FALSE, &tpCurrent, dwOld, &tpOld, &dwOld) )
				bResult = TRUE;
			else
				bResult = FALSE;
		}
		else
			bResult = FALSE;

		CloseHandle(hToken);
		return bResult != FALSE ? true : false;
	}

	CHexToInt::CHexToInt() : pszTemp(NULL)
	{
		char szTemp[3] = {0,};

		for( int idx = 0; idx < 256; ++idx )
		{
			sprintf_s(szTemp, sizeof(szTemp), "%02x", idx);
			m_HexData.insert( std::make_pair( szTemp, idx) );
			memset(szTemp, 0, sizeof(szTemp));
		}
	}

	CHexToInt::~CHexToInt()
	{
		if( pszTemp )
			delete [] pszTemp;
		pszTemp = NULL;
	}

	std::vector<unsigned char> CHexToInt::Convert(const std::string& strConvert, bool IsExistToken /* = false */ )
	{
		if( strConvert.empty() )
			return std::vector<unsigned char>();

		std::vector<unsigned char> vecResult;
		size_t szAdd = 0;

		if( IsExistToken == false )
			szAdd = 2;
		else
			szAdd = 3;

		size_t nLength = strConvert.size();
		for( size_t nIDX = 0; nIDX < strConvert.size() ;nIDX = nIDX + szAdd )
			vecResult.push_back( m_HexData[ strConvert.substr(nIDX, 2) ] );

		return vecResult;
	}

	std::vector<unsigned char> CHexToInt::Convert(const std::wstring& strConvert, bool IsExistToken /* = false */)
	{
		if( strConvert.empty() )
			return std::vector<unsigned char>();

		if( pszTemp )
			delete [] pszTemp;
	
		pszTemp = NULL;

		pszTemp = new char[strConvert.size() + 1 ];
		memset(pszTemp, 0, strConvert.size() + 1);

		wcstombs(pszTemp, strConvert.c_str(), strConvert.size() );

		return Convert(pszTemp, IsExistToken);
	}

	bool LaunchAppWithDesktop(LPCTSTR pszApplicationPath, LPTSTR pszDesktopName )
	{
		bool bReturn = false;

		if(!pszApplicationPath || !pszDesktopName || !_tcslen(pszApplicationPath) || !_tcslen(pszDesktopName))
			return bReturn;

		TCHAR szDirectoryName[MAX_PATH] = {0};
		TCHAR szExplorerFile[MAX_PATH]= {0};

		_tcscpy_s(szDirectoryName,_tcslen(pszApplicationPath) + 1, pszApplicationPath);

		//if(!PathIsExe(pszApplicationPath))
		//	return bReturn;

		PathRemoveFileSpec(szDirectoryName);

		STARTUPINFO sInfo = {0};
		PROCESS_INFORMATION pInfo = {0};

		sInfo.cb = sizeof(sInfo);
		sInfo.lpDesktop = pszDesktopName;

		//Lanuching a application into dekstop
		BOOL bCreateProcessReturn = CreateProcess(pszApplicationPath,
			NULL,
			NULL,
			NULL,
			TRUE,
			NORMAL_PRIORITY_CLASS,
			NULL,
			szDirectoryName,
			&sInfo,
			&pInfo);

		if(bCreateProcessReturn)
			bReturn = true;

		return bReturn;
	}

	CT2U8::CT2U8() : m_pszUTF8(NULL), m_nLen(0)
	{

	}

	CT2U8::CT2U8(LPCSTR lpStr) : m_pszUTF8(NULL), m_nLen(0)
	{
		if( lpStr )
			m_nLen = ConvertCHARToUTF8(lpStr);
	}

	CT2U8::CT2U8(LPCWSTR lpwStr) : m_pszUTF8(NULL), m_nLen(0)
	{
		if( lpwStr )
			m_nLen = ConvertWCHARToUTF8(lpwStr);
	}

	CT2U8::CT2U8(const CT2U8& str) : m_pszUTF8(NULL), m_nLen(0)
	{
		if( str.m_nLen > 0 && str.m_pszUTF8 )
		{
			m_nLen		= str.m_nLen;
			m_pszUTF8	= new char[m_nLen];
			strncpy_s(m_pszUTF8, m_nLen, str.m_pszUTF8, m_nLen );
		}
	}

	CT2U8::~CT2U8()
	{
		DeletePtr();
	}

	CT2U8& CT2U8::operator =(LPCSTR& pszString)
	{
		DeletePtr();
		if( pszString )
			m_nLen = ConvertCHARToUTF8( pszString );

		return *this;
	}

	CT2U8& CT2U8::operator =(LPCWSTR& pszString)
	{
		DeletePtr();
		if( pszString )
			m_nLen = ConvertWCHARToUTF8( pszString );

		return *this;
	}

	CT2U8& CT2U8::operator =(const CT2U8 & szString)
	{
		DeletePtr();
	
		if( szString.m_nLen <= 0 )
			return *this;

		m_nLen		= szString.m_nLen;
		m_pszUTF8	= new char[m_nLen];
		strncpy_s(m_pszUTF8, m_nLen, szString.m_pszUTF8, m_nLen);

		return *this;
	}
	CT2U8::operator LPSTR()
	{
		return m_pszUTF8;
	}


	CT2U8::operator std::string()
	{
		return m_pszUTF8;
	}

	CT2U8::operator std::wstring()
	{
		std::wstring strString;
		size_t len = m_nLen;
		if( !m_pszUTF8 || m_nLen <= 0 )
		{
			return L"";
		}

		WCHAR* pszTemp = NULL;
		int nSize = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, 0, 0 );
		if( nSize == 0 )
		{
			len = 0;
			goto CLEANUP;
		}

		pszTemp = new WCHAR[nSize];
		ZeroMemory(pszTemp, nSize);

		len = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, pszTemp, nSize);

		if( len > 0 )
			strString = pszTemp;

	CLEANUP:
		if( pszTemp )
			delete [] pszTemp;

		pszTemp = NULL;

		return strString;
	}

	void CT2U8::DeletePtr()
	{
		if( m_pszUTF8 )
		{
			delete [] m_pszUTF8;
			m_pszUTF8	= NULL;
			m_nLen		= 0;

		}
	}

	size_t CT2U8::ConvertCHARToUTF8( LPCSTR pszString )
	{
		int nSize = 0;
		size_t len = strlen( pszString );
		if( len <= 0 )
			return 0;

		WCHAR *pszTemp = new WCHAR[len + 1];
		ZeroMemory(pszTemp, len + 1);

		if( (len = MultiByteToWideChar(CP_ACP, 0, pszString, -1 , pszTemp, (int)len+1)) == 0 )
			goto CLEANUP; 

		nSize = WideCharToMultiByte(CP_UTF8, 0, pszTemp, -1, 0, 0, 0, 0 );
		DeletePtr();

		m_pszUTF8 = new char[nSize];
		ZeroMemory(m_pszUTF8, nSize);
		len = WideCharToMultiByte(CP_UTF8, 0, pszTemp, -1, m_pszUTF8, nSize, 0, 0);
		len > 0 ? m_nLen = len : m_nLen = 0;


	CLEANUP:
		if( pszTemp )
			delete [] pszTemp;

		pszTemp = NULL;

		return len;
	}

	size_t CT2U8::ConvertWCHARToUTF8( LPCWSTR pszString )
	{
		size_t len = wcslen( pszString );
		if( len <= 0 )
			return 0;

		int nSize = WideCharToMultiByte(CP_UTF8, 0, pszString, -1, 0, 0, 0, 0 );
		DeletePtr();

		m_pszUTF8 = new char[nSize];
		ZeroMemory(m_pszUTF8, nSize );
		len = WideCharToMultiByte(CP_UTF8, 0, pszString, -1, m_pszUTF8, nSize, 0, 0);
		len > 0 ? m_nLen = len : m_nLen = 0;

		return len;
	}

	size_t CT2U8::ConvertUTF8ToCHAR(std::string& strString)
	{
		size_t len = m_nLen;
		if( !m_pszUTF8 || m_nLen <= 0 )
		{
			strString = "";
			return 0;
		}

		WCHAR* pszTempW = NULL;
		CHAR* pszTempA = NULL;

		size_t nSize = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, 0, 0);
		if( nSize == 0 )
		{
			len = 0;
			goto CLEANUP;
		}

		pszTempW = new WCHAR[nSize];
		ZeroMemory(pszTempW, nSize * sizeof(WCHAR));

		len = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, pszTempW, (int)nSize);
		if( len == 0 )
			goto CLEANUP;

		len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, pszTempW, -1, 0, 0, 0, 0);
		if( len == 0 )
			goto CLEANUP;

		pszTempA = new CHAR[len];
		ZeroMemory(pszTempA, len * sizeof(CHAR));

		len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, pszTempW, -1, pszTempA, (int)len, 0, 0);
		if( len == 0 )
			goto CLEANUP;

		strString = pszTempA;

	CLEANUP:

		if( pszTempW )
			delete [] pszTempW;

		pszTempW = NULL;

		if( pszTempA )
			delete [] pszTempA;

		pszTempA = NULL;

		return len;
	}

	size_t CT2U8::ConvertUTF8ToWCHAR(std::wstring& strString)
	{
		size_t len = m_nLen;
		if( !m_pszUTF8 || m_nLen <= 0 )
		{
			strString = _T("");
			return 0;
		}

		WCHAR* pszTemp = NULL;

		int nSize = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, 0, 0 );
		if( nSize == 0 )
		{
			len = 0;
			goto CLEANUP;
		}

		pszTemp = new WCHAR[nSize];
		ZeroMemory(pszTemp, nSize);

		len = MultiByteToWideChar(CP_UTF8, 0, m_pszUTF8, -1, pszTemp, nSize);

		if( len > 0 )
			strString = pszTemp;

	CLEANUP:
		if( pszTemp )
			delete [] pszTemp;

		pszTemp = NULL;

		return len;
	}

	std::string CT2U8::GetUTF8()
	{
		if( m_pszUTF8 == NULL )
			return "";

		return m_pszUTF8;
	}

	std::wstring CT2U8::GetUTF16()
	{
		if( m_pszUTF8 == NULL )
			return L"";

		return operator std::wstring () ;

	}
	void CT2U8::AssignUTF8(LPCSTR lpStr)
	{
		if( lpStr == NULL )
			return ;

		DeletePtr();

		m_pszUTF8 = strdup(lpStr);
		m_nLen = strlen(lpStr);
	}


};//..namespace HisUtil