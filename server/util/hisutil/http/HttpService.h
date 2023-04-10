#pragma once

//////////////////////////////////////////////////////////////////////////
/*
	���� : �︶, 2008-07 ~ 

	Win32API �ܵ� ����� ���� C++ �� string Ŭ���� ���ַ� �ۼ�
	CString ���� �Ͻ��� ����ȯ�� ���� LPCTSTR �߰�

	. AddItem �� Ű/�� ���� �ƴ� ���ڿ��� �߰��� �� �ֵ��� �߰�

	. CHttpPost::AddItem �� �迭�������� �����ڸ� �̿��� �������� �߰��� �� �ֵ��� �߰�
	. CHttpPost �� �����ڸ� ������ �� �ֵ��� SetSeperator �߰� , �⺻ �����ڴ� "|"

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

		// isInsert �� true �̸� ���� ���� "|" �����ڸ� ����Ͽ� �߰�
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

	// �� Ŭ������ Post �����͸� ������ �� UTF8 �������� ��ȯ�Ͽ� �����ϹǷ� ���� ���������� UTF8 �����͸� ���� �� �־�� ��.
	/*
		Ŭ���� ������ 
	
		Method = POST �� ��
			Open -> PostData -> DownloadFile �Ǵ� DownloadPage
		Mothod = GET �� �� ( CHttpPost ���Ұ�, http:// ���·� ���� ���ڿ����� ? ���Ŀ� ��� ����� �ϸ� �̶��� ��� ��ȯ�� ���� �״�� ���۵� )
			OpenGet �̿� -> DownloadFile �Ǵ� DownloadPage

		GetPage �Լ��� DownloadFile �� �̿��ؼ� ���Ϸ� ���� ������ �������� �޾ƺ��� ���� �� ���

	*/
	class CHttpService
	{
	public:
		CHttpService();
		~CHttpService();

		enum tag_Service { HTTP_SERVICE = 0, HTTPS_SERVICE = 1 } ;

		// �������� ������ http:// �� ���� �Է�
		bool	Open(const std::string& strServer, const std::string& strPath, WORD nPort = INTERNET_DEFAULT_HTTP_PORT, tag_Service eService = HTTP_SERVICE );
		bool	Open(const std::wstring& strServer, const std::wstring& strPath, WORD nPort = INTERNET_DEFAULT_HTTP_PORT, tag_Service eService = HTTP_SERVICE );

		// �Ϲ����� URL ���·� �Է�, http:// �Ǵ� https:// �� ����
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

		// �� ������ ������ �����޽��ϴ�. �ؽ�Ʈ ���ϸ� �׽�Ʈ ����
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