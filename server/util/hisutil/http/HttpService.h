#pragma once

//////////////////////////////////////////////////////////////////////////
/*
	제작 : 헬마, 2008-07 ~ 

	Win32API 단독 사용을 위해 C++ 의 string 클래스 위주로 작성
	CString 과의 암시적 형변환을 위해 LPCTSTR 추가

	. AddItem 에 키/값 쌍이 아닌 문자열을 추가할 수 있도록 추가

	. CHttpPost::AddItem 에 배열형식으로 구분자를 이용해 기존값에 추가할 수 있도록 추가
	. CHttpPost 에 구분자를 지정할 수 있도록 SetSeperator 추가 , 기본 구분자는 "|"

*/
//////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <utility>

#include <WinInet.h>
#include <Shlwapi.h>
#include <UrlMon.h>

#include "Base64Tool.h"
#include "HttpUtil.h"

#ifdef UNICODE
	#ifndef tstring
		#define tstring std::wstring
	#endif
#else
	#ifndef tstring
		#define tstring std::string
	#endif
#endif

namespace HisUtil
{
	class CHttpService;

	class CHttpPost
	{
	public:
		CHttpPost(void);
		~CHttpPost(void);

		// isInsert 가 true 이면 기존 값에 "|" 구분자를 사용하여 추가
		bool AddItem(const tstring& strName, const tstring& strData, bool IsInsert = false);
		bool AddItem(const tstring& strName, const LPCTSTR& strData, bool IsInsert = false);
		bool AddItem(const tstring& strName, int nData);
		bool AddItem(const tstring& strName, unsigned int nData);
		bool AddItem(const tstring& strName, const VARIANT& vt);
		bool AddItem(const tstring& strName, float nData);
		bool AddItem(const tstring& strName, double nData);
		bool AddItem(const tstring& strName);

		bool DeleteItem(const tstring& strName);
		void ClearItem();

		void SetSeparator(const tstring& strSep);

		tstring GetPost() const;
	
	protected:

	private:
		typedef std::map<tstring, tstring>	mapPost;
		mapPost	m_mapPost;
		tstring m_strSep;

	};

	// 이 클래스는 Post 데이터를 전송할 때 UTF8 형식으로 변환하여 전송하므로 받을 페이지에서 UTF8 데이터를 받을 수 있어야 함.
	/*
		클래스 사용순서 
	
		Method = POST 일 떄
			Open -> PostData -> DownloadFile 또는 DownloadPage
		Mothod = GET 일 때 ( CHttpPost 사용불가, http:// 형태로 쿼리 문자열까지 ? 이후에 모두 적어야 하며 이때는 어떠한 변환도 없이 그대로 전송됨 )
			OpenGet 이용 -> DownloadFile 또는 DownloadPage

		GetPage 함수는 DownloadFile 을 이용해서 파일로 받은 내용을 변수에도 받아보고 싶을 떄 사용

	*/
	class CHttpService
	{
	public:
		CHttpService();
		~CHttpService();

		enum tag_Service { HTTP_SERVICE = 0, HTTPS_SERVICE = 1 } ;

		// 서버명을 적을때 http:// 를 빼고 입력
		bool	Open(const std::string& strServer, const std::string& strPath, WORD nPort = INTERNET_DEFAULT_HTTP_PORT, tag_Service eService = HTTP_SERVICE );
		bool	Open(const std::wstring& strServer, const std::wstring& strPath, WORD nPort = INTERNET_DEFAULT_HTTP_PORT, tag_Service eService = HTTP_SERVICE );

		// 일반적인 URL 형태로 입력, http:// 또는 https:// 로 시작
		bool	Open(const std::string& strURL);
		bool	Open(const std::wstring& strURL);
		bool	Open(const LPCSTR& lpszURL);
		bool	Open(const LPCWSTR& lpszURL);

		bool	OpenGet(const std::string& strURL);
		bool	OpenGet(const std::wstring& strURL);
		bool	OpenGet(const LPCSTR& lpszURL);
		bool	OpenGet(const LPCWSTR& lpszURL);

		void	Close();

		bool	PostData(const std::string& strPostData, bool IsCanonicalized = false, bool IsPostUTF8 = true);
		bool	PostData(const std::wstring& strPostData = _T(""), bool IsCanonicalized = false, bool IsPostUTF8 = true);
		bool	PostData(const CHttpPost& post, bool IsPostUTF8 = true);

		// 웹 페이지 파일을 내려받습니다. 텍스트 파일만 테스트 했음
		bool	DownloadFile(const tstring& strFileName);
		bool	DownloadFile(const LPCTSTR& lpszFileName);

		std::string DownloadPage();

		std::string GetPage();

	private:
		std::wstring	m_strServer;
		std::wstring	m_strPath;
		WORD			m_dwPort;
		DWORD			m_dwFlags;
		int				m_CurPos;
		bool			m_IsPost;

		LPSTR		m_pszReceivedData;
		HINTERNET	hRequest;
		HINTERNET	hConnect;
		HINTERNET	hInternet;
	};

};//..namespace HisUtil