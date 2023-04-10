#include "stdafx.h"
#include "ftp.h"


namespace HisUtil {

	#include <wininet.h>
	#pragma comment(lib, "wininet")
	BOOL sendFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, const TCHAR* localFullPath, TCHAR* remoteDir, WCHAR* remoteFile)
	{
		//#include <wininet.h>
		//#pragma comment(lib, "wininet")
		//int ret = sendFtp(L"upload.mori.netmarble.net", 10021, L"dc", L"#$dav17@d", L"D:\\다운로드\\2013_10_22_14_18\\DCGameServer.exe", L"server_patch\\2013_10_24", L"DCGameServer.exe");

		HINTERNET hInternet;
		HINTERNET hFtpSession;
		hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
		if(hInternet==NULL)
		{
			return FALSE;
		}
		hFtpSession = InternetConnect(hInternet,(LPTSTR)ftp , port, (LPTSTR)user, (LPTSTR)pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
		if(hFtpSession==NULL)
		{
			return FALSE;
		}

		if(FALSE == FtpCreateDirectory(hFtpSession, remoteDir))//디렉토리 생성을 시도
			return FALSE;

		TCHAR wzRemoteFile[MAX_PATH] = _T("");
		_stprintf_s(wzRemoteFile, _T("%s\\%s"), remoteDir, remoteFile);
		BOOL result = FtpPutFile(hFtpSession, (LPTSTR)localFullPath, (LPTSTR)wzRemoteFile, FTP_TRANSFER_TYPE_BINARY, 0);
		Sleep(1000);
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hInternet);
		if(TRUE == result)
			return TRUE;

		return FALSE;
	}

	BOOL recvFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, TCHAR* remoteFullPath, const TCHAR* localFullPath)
	{
		//#include <wininet.h>
		//#pragma comment(lib, "wininet")
		//int ret = recvFtp(L"upload.mori.netmarble.net", 10021, L"dc", L"#$dav17@d", L"server_patch\\2013_10_24\\DCGameServer.exe", L"D:\\다운로드\\2013_10_22_14_18\\DCGameServer.exe");

		HINTERNET hInternet;
		HINTERNET hFtpSession;
		hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
		if(hInternet==NULL)
		{
			return FALSE;
		}
		hFtpSession = InternetConnect(hInternet,(LPTSTR)ftp , port, (LPTSTR)user, (LPTSTR)pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
		if(hFtpSession==NULL)
		{
			return FALSE;
		}

		BOOL result = FtpGetFile(hFtpSession, (LPTSTR)remoteFullPath, (LPTSTR)localFullPath, 0, 0, FTP_TRANSFER_TYPE_BINARY, 0);
		Sleep(1000);
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hInternet);
		if(TRUE == result)
			return TRUE;

		return FALSE;
	}

};//namespace HisUtil {