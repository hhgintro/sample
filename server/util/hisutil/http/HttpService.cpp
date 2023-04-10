#include "stdafx.h"

#include "HttpService.h"

#pragma comment(lib, "WinInet.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")

// #pragma warning(disable : 1786)
#pragma warning(disable : 4996)

namespace HisUtil
{

CHttpPost::CHttpPost()
{
	m_strSep = _T("|");
}

CHttpPost::~CHttpPost()
{

}

bool CHttpPost::AddItem(const tstring& strName, const tstring& strData, bool IsInsert /* = false */)
{
	std::pair< mapPost::iterator, bool > pr;

	if( IsInsert == true )
	{
		mapPost::iterator iter = m_mapPost.find( strName );
		if( iter == m_mapPost.end() )
			pr = m_mapPost.insert( make_pair( strName, strData ) );
		else
		{
			iter->second += m_strSep + strData;
			return true;
		}
	}
	else
	{
		pr = m_mapPost.insert( make_pair( strName, strData ) );
	}

	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName, const LPCTSTR& strData, bool IsInsert /* = false */)
{
	return AddItem(strName, tstring(strData), IsInsert);
}

bool CHttpPost::AddItem(const tstring& strName, int nData)
{
	std::pair< mapPost::iterator, bool > pr;
	pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), nData) ) );
	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName, unsigned int nData)
{
	std::pair< mapPost::iterator, bool > pr;
	pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), nData) ) );
	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName, float nData)
{
	std::pair< mapPost::iterator, bool > pr;
	pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), nData) ) );
	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName, double nData)
{
	std::pair< mapPost::iterator, bool > pr;
	pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), nData) ) );
	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName, const VARIANT& vt)
{
	std::pair< mapPost::iterator, bool > pr;

	switch( vt.vt )
	{
	case VT_EMPTY:
	case VT_NULL:
		pr = m_mapPost.insert( make_pair( strName, _T("") ) );
		break;
	case VT_I2:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), vt.iVal) ) );
		break;
	case VT_I2 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), *(vt.piVal)) ) );
		break;
	case VT_I4:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), vt.lVal) ) );
		break;
	case VT_I4 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), *(vt.plVal)) ) );
		break;
	case VT_R4:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), vt.fltVal) ) );
		break;
	case VT_R4 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), *(vt.pfltVal)) ) );
		break;
	case VT_R8:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), vt.dblVal) ) );
		break;
	case VT_R8 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%f"), *(vt.pdblVal)) ) );
		break;
	case VT_CY:
	case VT_CY | VT_BYREF:
		//pr = m_mapPost.insert( make_pair( strName, COleCurrency(vt).Format().GetString() ) );
		break;
	case VT_DATE:
	case VT_DATE | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, COleDateTime(vt).Format(_T("%Y-%m-%d %H-%M-%S")).GetString() ) );
		break;
	case VT_BSTR:
		pr = m_mapPost.insert( make_pair( strName, V_BSTR(&vt) ));
		break;
	case VT_BSTR | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, *(V_BSTRREF(&vt)) ));
		break;
	case VT_BOOL:
		pr = m_mapPost.insert( make_pair( strName, vt.boolVal == VARIANT_TRUE ? _T("True") : _T("False") ));
		break;
	case VT_BOOL | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, *(vt.pboolVal) == VARIANT_TRUE ? _T("True") : _T("False") ));
		break;
	case VT_DECIMAL:
		break;
	case VT_I1:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%c"), vt.cVal) ) );
		break;
	case VT_I1 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%c"), *(vt.pcVal)) ) );
		break;
	case VT_UI1:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%c"), vt.bVal) ) );
		break;
	case VT_UI1 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%c"), *(vt.pbVal)) ) );
		break;
	case VT_UI2:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), vt.uiVal) ) );
		break;
	case VT_UI2 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), *(vt.puiVal)) ) );
		break;
	case VT_UI4:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), vt.ulVal) ) );
		break;
	case VT_UI4 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), *(vt.pulVal)) ) );
		break;
	case VT_UI8:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%I64u"), vt.ullVal) ) );
		break;
	case VT_UI8 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%I64u"), *(vt.pullVal)) ) );
		break;
	case VT_I8:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%I64d"), vt.llVal) ) );
		break;
	case VT_I8 | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%I64d"), *(vt.pllVal)) ) );
		break;
	case VT_INT:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), vt.intVal) ) );
		break;
	case VT_INT | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%d"), *(vt.pintVal)) ) );
		break;
	case VT_UINT:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), vt.uintVal) ) );
		break;
	case VT_UINT | VT_BYREF:
		pr = m_mapPost.insert( make_pair( strName, format(_T("%u"), *(vt.puintVal)) ) );
		break;
	case VT_SAFEARRAY:
		break;
	case VT_LPSTR:
		break;
	case VT_LPWSTR:
		break;
	case VT_INT_PTR:
		break;
	case VT_UINT_PTR:
		break;
	case VT_ARRAY:
		break;
	}

	return pr.second;
}

bool CHttpPost::AddItem(const tstring& strName)
{
	std::pair< mapPost::iterator, bool > pr;
	pr = m_mapPost.insert( make_pair( strName, tstring() ) );
	return pr.second;
}

bool CHttpPost::DeleteItem(const tstring& strName)
{
	mapPost::iterator iter = m_mapPost.find(strName);

	if( iter != m_mapPost.end() )
	{
		m_mapPost.erase(iter);	
	}

	return true;
}

void CHttpPost::ClearItem()
{
	m_mapPost.clear();
}

void CHttpPost::SetSeparator(const tstring& strSep)
{
	m_strSep = strSep;
}

tstring CHttpPost::GetPost() const
{
	tstring strPost;
	tstring strTemp;

	for( mapPost::const_iterator iter = m_mapPost.begin(); iter != m_mapPost.end(); )
	{
		if( iter->first.empty() == false && iter->second.empty() == false )
			strTemp = format(_T("%s=%s"), iter->first.c_str(), iter->second.c_str() );
		else if( iter->first.empty() == false && iter->second.empty() )
			strTemp = format(_T("%s"), iter->first.c_str() );
			
		ULONG dwPostLength = (ULONG)_tcslen(strTemp.c_str()) * 3;
		LPTSTR postData = new TCHAR[dwPostLength];
		DWORD dwLength = 0;

		CoInternetParseUrl(strTemp.c_str(), PARSE_CANONICALIZE, URL_ESCAPE_UNSAFE, postData, dwPostLength, &dwLength, 0 );

		strPost += postData;
		delete [] postData;
		if( ++iter != m_mapPost.end() )
			if( *(strPost.rbegin()) != '&' )
				strPost += _T("&");
	}
	
	return strPost;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CHttpService::CHttpService() :	hConnect(NULL), hInternet(NULL), hRequest(NULL),
								m_dwPort(INTERNET_DEFAULT_HTTP_PORT),
								m_pszReceivedData(NULL),
								m_CurPos(0),
								m_IsPost(true)
{
	hInternet = ::InternetOpen(_T("ImonAgent"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if( hInternet == NULL )
		throw _T("CHttpService : InternetOpen Failed.");
}

CHttpService::~CHttpService()
{
	if( m_pszReceivedData != NULL )
		free(m_pszReceivedData);
	m_pszReceivedData = NULL;


	if( hRequest != NULL )
		InternetCloseHandle(hRequest);

	if( hConnect != NULL )
		InternetCloseHandle(hConnect);

	if( hInternet != NULL )
		InternetCloseHandle(hInternet);

}

bool CHttpService::Open(const std::string& strServer, const std::string& strPath, WORD nPort /* = INTERNET_DEFAULT_HTTP_PORT */, tag_Service eService /* = HTTP_SERVICE */ )
{
	if( hInternet == NULL )
		return false;

	if( strServer.empty() )
		return false;

	Close();

	wchar_t szServer[INTERNET_MAX_HOST_NAME_LENGTH + INTERNET_MAX_SCHEME_LENGTH] = {0,};
	wchar_t szPath[INTERNET_MAX_PATH_LENGTH] = {0,};

	mbstowcs(szServer, strServer.c_str(), INTERNET_MAX_HOST_NAME_LENGTH + INTERNET_MAX_SCHEME_LENGTH - 1);
	mbstowcs(szPath, strPath.c_str(), INTERNET_MAX_PATH_LENGTH - 1);

	m_strServer		= szServer;
	m_strPath		= szPath;
	m_dwPort		= nPort;

	if( hConnect != NULL )
		InternetCloseHandle(hConnect);

	DWORD m_dwFlags = INTERNET_FLAG_NO_CACHE_WRITE;
	if( nPort == INTERNET_DEFAULT_HTTPS_PORT || eService == HTTPS_SERVICE )
		m_dwFlags |= INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;;

	hConnect = ::InternetConnect(hInternet, m_strServer.c_str(), m_dwPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, m_dwFlags, 0);
	if( hConnect == NULL )
		return false;

	return true;
}

bool CHttpService::Open(const std::wstring& strServer, const std::wstring& strPath, WORD nPort /* = INTERNET_DEFAULT_HTTP_PORT */, tag_Service eService /* = HTTP_SERVICE */ )
{
	if( hInternet == NULL )
		return false;

	if( strServer.empty() )
		return false;

	Close();

	m_strServer		= strServer;
	m_strPath		= strPath;
	m_dwPort		= nPort;

	if( hConnect != NULL )
		InternetCloseHandle(hConnect);

	DWORD m_dwFlags = INTERNET_FLAG_NO_CACHE_WRITE;
	if( nPort == INTERNET_DEFAULT_HTTPS_PORT || eService == HTTPS_SERVICE )
		m_dwFlags |= INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;;

	hConnect = ::InternetConnect(hInternet, m_strServer.c_str(), m_dwPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, m_dwFlags, 0);
	if( hConnect == NULL )
		return false;

	return true;
}

bool CHttpService::Open(const std::string& strURL)
{
	if( hInternet == NULL )
		return false;

	if( strURL.empty() )
		return false;

	Close();

	URL_COMPONENTSA uc;
	ZeroMemory(&uc, sizeof(uc));

	uc.dwStructSize		= sizeof(uc);
	uc.dwHostNameLength	= 1;
	uc.dwUrlPathLength	= 1;

	if( ::InternetCrackUrlA(strURL.c_str(), (DWORD)strlen(strURL.c_str()), 0, &uc) == FALSE )
		return false;

	wchar_t szServer[INTERNET_MAX_HOST_NAME_LENGTH + INTERNET_MAX_SCHEME_LENGTH] = {0,};
	wchar_t szPath[INTERNET_MAX_PATH_LENGTH] = {0,};

	mbstowcs(szServer, std::string(uc.lpszHostName, uc.dwHostNameLength).c_str(), INTERNET_MAX_HOST_NAME_LENGTH + INTERNET_MAX_SCHEME_LENGTH - 1);
	mbstowcs(szPath, std::string(uc.lpszUrlPath, uc.dwUrlPathLength).c_str(), INTERNET_MAX_PATH_LENGTH - 1);

	m_strServer		= szServer;
	m_strPath		= szPath;
	m_dwPort		= uc.nPort;

	if( hConnect != NULL )
		InternetCloseHandle(hConnect);

	m_dwFlags = INTERNET_FLAG_NO_CACHE_WRITE;
	if( uc.nScheme == INTERNET_SCHEME_HTTPS )
		m_dwFlags |= INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;;

	hConnect = ::InternetConnect(hInternet, m_strServer.c_str(), m_dwPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	if( hConnect == NULL )
		return false;

	return true;
}

bool CHttpService::Open(const std::wstring& strURL)
{
	if( hInternet == NULL )
		return false;

	if( strURL.empty() )
		return false;

	Close();

	URL_COMPONENTS uc;
	ZeroMemory(&uc, sizeof(uc));

	uc.dwStructSize		= sizeof(uc);
	uc.dwHostNameLength	= 1;
	uc.dwUrlPathLength	= 1;
	
	if( ::InternetCrackUrl(strURL.c_str(), (DWORD)_tcslen(strURL.c_str()), 0, &uc) == FALSE )
		return false;

	m_strServer		= std::wstring(uc.lpszHostName, uc.dwHostNameLength);
	m_strPath		= std::wstring(uc.lpszUrlPath, uc.dwUrlPathLength);
	m_dwPort		= uc.nPort;

	if( hConnect != NULL )
		InternetCloseHandle(hConnect);

	m_dwFlags = INTERNET_FLAG_NO_CACHE_WRITE;
	if( uc.nScheme == INTERNET_SCHEME_HTTPS )
		m_dwFlags |= INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;;

	hConnect = ::InternetConnect(hInternet, m_strServer.c_str(), m_dwPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	if( hConnect == NULL )
		return false;

	return true;
}

bool CHttpService::Open(const LPCSTR& lpszURL)
{
	return Open(std::string(lpszURL));
}

bool CHttpService::Open(const LPCWSTR& lpszURL)
{
	return Open(std::wstring(lpszURL));
}

bool CHttpService::OpenGet(const std::string& strURL)
{
	if( hInternet == NULL )
		return false;

	hRequest = InternetOpenUrlA(hInternet, strURL.c_str(), NULL, 0, HTTP_QUERY_DATE, 0);
	if( hRequest == NULL )
		return false;

	m_IsPost = false;

	return true;
}

bool CHttpService::OpenGet(const std::wstring& strURL)
{
	if( hInternet == NULL )
		return false;

	hRequest = InternetOpenUrl(hInternet, strURL.c_str(), NULL, 0, HTTP_QUERY_DATE, 0);
	if( hRequest == NULL )
		return false;

	m_IsPost = false;

	return true;
}

bool CHttpService::OpenGet(const LPCSTR& lpszURL)
{
	return OpenGet(std::string(lpszURL));
}

bool CHttpService::OpenGet(const LPCWSTR& lpszURL)
{
	return OpenGet(std::wstring(lpszURL));
}

void CHttpService::Close()
{
	if( hRequest )
		InternetCloseHandle(hRequest);
	hRequest = NULL;

	if( hConnect )
		InternetCloseHandle(hConnect);
	hConnect = NULL;

	if( m_pszReceivedData != NULL )
		free(m_pszReceivedData);
	m_pszReceivedData = NULL;

	m_strServer = _T("");
	m_strPath = _T("");
	m_dwPort = INTERNET_DEFAULT_HTTP_PORT;
	m_dwFlags = 0;
	m_CurPos = 0;
}

bool CHttpService::PostData(const CHttpPost& post, bool IsPostUTF8 )
{
	if( hInternet == NULL || hConnect == NULL )
		return false;

	return PostData(post.GetPost(), true, IsPostUTF8);
}

bool CHttpService::PostData(const std::string& strPostData, bool IsCanonicalized /* = false */, bool IsPostUTF8 /* = true */)
{
	if( hInternet == NULL || hConnect == NULL )
		return false;

	char szHeaders[] = "Content-Type: application/x-www-form-urlencoded"; //content type for post...
	char szAccept[] = "*/*";
	LPSTR pszAcceptTypes[2] = {0,};
	pszAcceptTypes[0] = szAccept;

	DWORD dwPath = (DWORD)wcslen(m_strPath.c_str()) * sizeof(wchar_t) + 1;
	char *pszPath = new char[ dwPath ];
	ZeroMemory(pszPath, dwPath);

	hRequest = ::HttpOpenRequestA(hConnect, "POST", pszPath, NULL, NULL, (LPCSTR*)pszAcceptTypes, m_dwFlags, 0);
	if( hRequest == NULL )
	{
		delete [] pszPath;
		return false;
	}

	CT2U8 utf8;

	if( IsCanonicalized == true )
	{
		if( strPostData.empty() )
		{
			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), NULL, 0 ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == true )
		{
			utf8 = strPostData.c_str();

			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), (LPVOID)(LPSTR)utf8, (DWORD)utf8.GetLength() ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == false )
		{
			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), (LPVOID)(LPSTR)strPostData.c_str(), (DWORD)strlen(strPostData.c_str()) ) == FALSE )
				return false;
		}
	}
	else 
	{
		if( strPostData.empty() )
		{
			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), NULL, 0 ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == true )
		{
			DWORD dwPostData = (DWORD)strlen(strPostData.c_str()) * sizeof(wchar_t) + 1;
			wchar_t *pszPostData = new wchar_t[ dwPostData ];
			ZeroMemory(pszPostData, dwPostData );

			if( MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, strPostData.c_str(), dwPostData, pszPostData, dwPostData) == 0 )
			{
				delete [] pszPostData;
				return false;
			}
			
			ULONG dwPostLength = dwPostData == 1 ? 0 : (ULONG)wcslen(pszPostData) * 3;
			LPWSTR postData = dwPostLength == 0 ? NULL : new wchar_t[dwPostLength];
			ZeroMemory(postData, dwPostLength);
			DWORD dwLength = 0; 

			if( postData != NULL && FAILED(CoInternetParseUrl(pszPostData, PARSE_CANONICALIZE, URL_ESCAPE_UNSAFE , postData, dwPostLength, &dwLength, 0)) )
			{
				delete [] pszPostData;
				return false;
			}

			if( postData != NULL )
				utf8 = postData;

			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), 
				postData == NULL ? NULL : (LPVOID)(LPSTR)utf8, postData == NULL ? 0 : (DWORD)utf8.GetLength()) == FALSE )
			{
				if( pszPostData )
					delete [] pszPostData;

				if( postData )
					delete [] postData;

				return false;
			}

			delete [] pszPostData;
			delete [] postData;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == false )
		{
			DWORD dwPostData = (DWORD)strlen(strPostData.c_str()) * sizeof(wchar_t) + 1;
			wchar_t *pszPostData = new wchar_t[ dwPostData ];
			ZeroMemory(pszPostData, dwPostData );

			if( MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, strPostData.c_str(), dwPostData, pszPostData, dwPostData) == 0 )
			{
				delete [] pszPostData;
				return false;
			}

			ULONG dwPostLength = strPostData.empty() ? 0 : (ULONG)wcslen(pszPostData) * 3;
			LPWSTR postData = dwPostLength == 0 ? NULL : new wchar_t[dwPostLength];
			ZeroMemory(postData, dwPostLength);
			DWORD dwLength = 0; 

			if( postData != NULL && FAILED(CoInternetParseUrl(pszPostData, PARSE_CANONICALIZE, URL_ESCAPE_UNSAFE , postData, dwPostLength, &dwLength, 0)) )
			{
				delete [] pszPostData;
				return false;
			}

			int nLen = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, postData, (DWORD)wcslen(postData), NULL, 0, NULL, NULL);

			char *pszPostDataA = new char[nLen + 1];
			ZeroMemory(pszPostDataA, nLen + 1);

			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, postData, (DWORD)_tcslen(postData), pszPostDataA, nLen, NULL, NULL );

			if( ::HttpSendRequestA(hRequest, szHeaders, (DWORD)strlen(szHeaders), (LPVOID)pszPostDataA, nLen + 1 ) == FALSE )
			{
				delete [] pszPostData;
				delete [] pszPostDataA;
				return false;
			}

			delete [] pszPostData;
			delete [] pszPostDataA;
			delete [] postData;
		}
	}

	return true;
}

bool CHttpService::PostData(const std::wstring& strPostData /* = _T */, bool IsCanonicalized /* = false */, bool IsPostUTF8 /* = true */)
{
	if( hInternet == NULL || hConnect == NULL )
		return false;

	wchar_t szHeaders[] = _T("Content-Type: application/x-www-form-urlencoded"); //content type for post...
	wchar_t szAccept[] = _T("*/*");
	LPWSTR pszAcceptTypes[2] = {0,};
	pszAcceptTypes[0] = szAccept;

	hRequest = ::HttpOpenRequest(hConnect, _T("POST"), m_strPath.c_str(), NULL, NULL, (LPCTSTR*)pszAcceptTypes, m_dwFlags, 0);
	if( hRequest == NULL )
		return false;

	CT2U8 utf8;

	if( IsCanonicalized == true )
	{
		if( strPostData.empty() )
		{	
			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)wcslen(szHeaders), NULL, 0 ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == true )
		{
			utf8 = strPostData.c_str();

			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)wcslen(szHeaders), (LPVOID)(LPSTR)utf8, (DWORD)utf8.GetLength() ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == false )
		{
			int nLen = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, 
				strPostData.c_str(), (DWORD)wcslen(strPostData.c_str()), NULL, 0, NULL, NULL);
			
			char *pszPostData = new char[nLen + 1];
			ZeroMemory(pszPostData, nLen + 1);

			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, strPostData.c_str(), (DWORD)wcslen(strPostData.c_str()), pszPostData, nLen, NULL, NULL );

			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)wcslen(szHeaders), (LPVOID)pszPostData, nLen + 1 ) == FALSE )
			{
				delete [] pszPostData;
				return false;
			}
			delete [] pszPostData;
		}
	}
	else
	{
		if( strPostData.empty() )
		{
			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)_tcslen(szHeaders), NULL, 0 ) == FALSE )
				return false;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == true )
		{
			ULONG dwPostLength = strPostData.empty() ? 0 : (DWORD)_tcslen(strPostData.c_str()) * 3;
			LPTSTR postData = dwPostLength == 0 ? NULL : new TCHAR[dwPostLength];
			ZeroMemory(postData, dwPostLength);
			DWORD dwLength = 0; 

			if( postData != NULL && FAILED(CoInternetParseUrl(strPostData.c_str(), PARSE_CANONICALIZE, URL_ESCAPE_UNSAFE , postData, dwPostLength, &dwLength, 0)) )
				return false;

			if( postData != NULL )
				utf8 = postData;

			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)_tcslen(szHeaders), 
				postData == NULL ? NULL : (LPVOID)(LPSTR)utf8, postData == NULL ? 0 : (DWORD)utf8.GetLength()) == FALSE )
			{
				if( postData )
					delete [] postData;

				return false;
			}

			delete [] postData;
		}
		else if( strPostData.empty() == false && IsPostUTF8 == false )
		{
			ULONG dwPostLength = strPostData.empty() ? 0 : (ULONG)_tcslen(strPostData.c_str()) * 3;
			LPTSTR postData = dwPostLength == 0 ? NULL : new TCHAR[dwPostLength];
			ZeroMemory(postData, dwPostLength);
			DWORD dwLength = 0; 

			if( postData != NULL && FAILED(CoInternetParseUrl(strPostData.c_str(), PARSE_CANONICALIZE, URL_ESCAPE_UNSAFE , postData, dwPostLength, &dwLength, 0)) )
			{
				delete [] postData;
				return false;
			}

			if( ::HttpSendRequest(hRequest, szHeaders, (DWORD)wcslen(szHeaders), (LPVOID)(LPWSTR)postData, (DWORD)wcslen(postData) * sizeof(wchar_t) ) == FALSE )
			{
				delete [] postData;
				return false;
			}

			delete [] postData;
		}
	}
	
	m_IsPost = true;

	return true;
}

bool CHttpService::DownloadFile(const LPCTSTR& lpszFileName)
{
	return DownloadFile(tstring(lpszFileName));
}

bool CHttpService::DownloadFile(const tstring& strFileName)
{
	if( !strFileName.empty() )
	{
		DownloadPage();

		HANDLE hFile = ::CreateFile(strFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
		if( hFile == INVALID_HANDLE_VALUE )
			return false;

		DWORD ddd = (DWORD)strlen(m_pszReceivedData);

		WriteFile(hFile, m_pszReceivedData, m_CurPos, &ddd, NULL );

		CloseHandle(hFile);
	}
	else
		return false;

	return true;
}

std::string CHttpService::DownloadPage()
{
	if( m_pszReceivedData != NULL )
		free(m_pszReceivedData);
	m_pszReceivedData = NULL;

	if( hInternet == NULL || 
		(m_IsPost == true && hConnect == NULL) || 
		hRequest == NULL )
		return "";
	
	const DWORD dwReadSize = 8192;
	char mr[dwReadSize] = {0,};
	DWORD rd = 0;
	m_CurPos = 0;
	m_pszReceivedData = (char *)calloc(dwReadSize + 1, sizeof(char) );

	while( ::InternetReadFile(hRequest, mr, dwReadSize - 1, &rd) )
	{
		if( rd == 0 ) 
			break;

		mr[rd] = '\0';
		m_CurPos += rd;
		m_pszReceivedData[m_CurPos] = '\0';
		strcat(m_pszReceivedData, mr );
		if( m_pszReceivedData != NULL )
		{
			char* pTemp = (char*)realloc(m_pszReceivedData, m_CurPos + dwReadSize);
			if( pTemp != NULL )
				m_pszReceivedData = pTemp;
		}
	}

	return m_pszReceivedData;
}

std::string CHttpService::GetPage()
{
	if( m_pszReceivedData == NULL )
		return "";

	return m_pszReceivedData;
}

};//..namespace HisUtil
