#pragma once

//#include <atlstr.h>
//#include <wininet.h>	//HINTERNET( CHisFtp ) && "wininet.lib"
//#pragma comment(lib, "wininet.lib")

namespace HisUtil {

	class CHisFtp
	{
	public:
		CHisFtp(void);
		~CHisFtp(void);


		//CHisFtp ftp;
		//if(FALSE == ftp.Open(_T("upload.****.****.net"), 21, _T("user"), _T("passwd")))
		//{
		//	_tprintf(_T("open faile\n"));
		//	return 0;
		//}
		BOOL Open(const TCHAR* ip, unsigned short port, const TCHAR* user, const TCHAR* pass);
		void Close();

		//현재 위치 변경
		BOOL GetRemoteDirectory(OUT TCHAR* dir, DWORD len);
		BOOL SetRemoteDirectory(IN TCHAR* dir);

		////upload file
		//if(FALSE == ftp.UploadFile(_T("D:\\Ftp\\workpatch\\PatchVersion\\Patch_v21\\Patch_v21_v19.zip")
		//	, _T("\\server_patch\\test1\\test2\\test3")
		//	, _T("Patch_v21_v19.zip")))
		//{
		//	_tprintf(_T("send fail\n"));
		//	return 0;
		//}
		BOOL UploadFile(const TCHAR* localFullPath, TCHAR* remoteDir, WCHAR* remoteFile);

		////download file
		//if(FALSE == ftp.DownloadFile(_T("\\server_patch\\29\\config\\DtDragon.ini")
		//	, _T("D:\\Ftp\\workpatch\\PatchVersion\\tttt1\\tttt2\\DtDragon.ini")))
		//{
		//	_tprintf(_T("recv fail\n"));
		//	return 0;
		//}
		BOOL DownloadFile(const TCHAR* remoteFullPath, const TCHAR* localFullPath);

		////upload folder
		//if(FALSE == ftp.UploadFolder(_T("D:\\Ftp\\workpatch\\PatchVersion\\Patch_v21"), _T("\\server_patch\\Patch_v21")))
		//{
		//	_tprintf(_T("list fail\n"));
		//	return 0;
		//}
		BOOL UploadFolder(IN TCHAR* localDir, IN TCHAR* remoteDir);

		////download folder
		//if(FALSE == ftp.DownloadFolder(_T("\\server_patch\\29"), _T("D:\\Ftp\\workpatch\\PatchVersion\\29")))
		//{
		//	_tprintf(_T("list fail\n"));
		//	return 0;
		//}
		BOOL DownloadFolder(IN TCHAR* remoteDir, IN TCHAR* localDir);

	private:

		//remote file & directory 목록
		BOOL GetRemoteFilesWithSubDir(IN CString remoteDir, std::vector<WIN32_FIND_DATA>& fileArray);
		BOOL GetRemoteFiles(IN CString remoteDir, std::vector<WIN32_FIND_DATA>& fileArray);

		//하위디렉토리 포함하여 디렉토리를 생성한다
		//가령 strDirPath가 c:\123\456\789라면 c:\, c:\123, c:\123\456, c:\123\456\789 폴더를 생성한다
		BOOL CreateRemoteDirectory(CString strDirPath);


		//local file & directory 목록
		BOOL GetLocalFilesWithSubDir(IN CString localDir, std::vector<WIN32_FIND_DATA>& fileArray);
		BOOL GetLocalFiles(IN CString localDir, std::vector<WIN32_FIND_DATA>& fileArray);

		BOOL CreateLocalDirectory(CString strDirPath);

		BOOL FindRemoteFile(IN const TCHAR* remoteFullPath);

	private:
		HINTERNET m_hInternet;
		HINTERNET m_hFtpSession;

		HisUtil::CModule m_module;

	};

};//..namespace HisUtil {