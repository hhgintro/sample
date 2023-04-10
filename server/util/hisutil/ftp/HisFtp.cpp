#include "stdafx.h"
#include "HisFtp.h"

namespace HisUtil {

	CHisFtp::CHisFtp(void)
		: m_hInternet(NULL), m_hFtpSession(NULL)
	{
	}


	CHisFtp::~CHisFtp(void)
	{
		Close();
	}

	BOOL CHisFtp::Open(const TCHAR* ip, unsigned short port, const TCHAR* user, const TCHAR* pass)
	{
		//��� ��ȣ
		if (FALSE == m_module.CheckValid())
			return TRUE;

		m_hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (m_hInternet == NULL)
			return FALSE;

		m_hFtpSession = InternetConnect(m_hInternet, (LPTSTR)ip, port, (LPTSTR)user, (LPTSTR)pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
		if (m_hFtpSession == NULL)
			return FALSE;

		return TRUE;
	}

	void CHisFtp::Close()
	{
		if (NULL != m_hFtpSession)
		{
			InternetCloseHandle(m_hFtpSession);
			m_hFtpSession = NULL;
		}

		if (NULL != m_hInternet)
		{
			InternetCloseHandle(m_hInternet);
			m_hInternet = NULL;
		}
	}

	BOOL CHisFtp::GetRemoteDirectory(OUT TCHAR* dir, DWORD len)
	{
		return FtpGetCurrentDirectory(m_hFtpSession, dir, &len);
	}

	//���� ��ġ ����
	BOOL CHisFtp::SetRemoteDirectory(IN TCHAR* dir)
	{
		return FtpSetCurrentDirectory(m_hFtpSession, dir);
	}

	//���ȣ��
	BOOL CHisFtp::GetRemoteFilesWithSubDir(IN CString remoteDir, std::vector<WIN32_FIND_DATA>& fileArray)
	{
		//current directoy
		if (FALSE == GetRemoteFiles(remoteDir, fileArray))
			return FALSE;

		for (int i = 0; i < (int)fileArray.size(); ++i)
		{
			//directory�̸�...
			if (fileArray[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//�ӽ� �����
				std::vector<WIN32_FIND_DATA> tempArray;

				//sub directory
				if (FALSE == GetRemoteFilesWithSubDir(fileArray[i].cFileName, tempArray))
					return FALSE;

				//�ӽ������ ����Ÿ�� �����ɴϴ�.
				fileArray.insert(fileArray.end(), tempArray.begin(), tempArray.end());
			}
		}
		return TRUE;
	}


	BOOL CHisFtp::GetRemoteFiles(IN CString remoteDir, std::vector<WIN32_FIND_DATA>& fileArray)
	{
		CString workDir;
		workDir.Format(_T("%s\\*"), remoteDir);

		WIN32_FIND_DATA find_data;
		memset(&find_data, 0, sizeof(WIN32_FIND_DATA));
		HINTERNET hFind = FtpFindFirstFile(m_hFtpSession, workDir, &find_data, INTERNET_FLAG_RELOAD, NULL);
		if (NULL == hFind)
			return FALSE;

		do
		{
			//strAddPath = AddRemoteFile(strRemoteDir, find_data, file_list);
			//���丮 �Ǵ� ���ϸ�
			CString filename = find_data.cFileName;
			_stprintf_s(find_data.cFileName, MAX_PATH, _T("%s\\%s"), remoteDir.GetString(), filename.GetString());
			fileArray.push_back(find_data);
			//if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

		} while (InternetFindNextFile(hFind, &find_data));

		InternetCloseHandle(hFind);
		return TRUE;
	}

	//���ȣ��
	BOOL CHisFtp::GetLocalFilesWithSubDir(IN CString localDir, std::vector<WIN32_FIND_DATA>& fileArray)
	{
		//current directoy
		if (FALSE == GetLocalFiles(localDir, fileArray))
			return FALSE;

		for (int i = 0; i < (int)fileArray.size(); ++i)
		{
			//directory�̸�...
			if (fileArray[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//�ӽ� �����
				std::vector<WIN32_FIND_DATA> tempArray;

				//sub directory
				if (FALSE == GetLocalFilesWithSubDir(fileArray[i].cFileName, tempArray))
					return FALSE;

				//�ӽ������ ����Ÿ�� �����ɴϴ�.
				fileArray.insert(fileArray.end(), tempArray.begin(), tempArray.end());
			}
		}
		return TRUE;
	}


	BOOL CHisFtp::GetLocalFiles(IN CString localDir, std::vector<WIN32_FIND_DATA>& fileArray)
	{
		CString workDir;
		workDir.Format(_T("%s\\*"), localDir);

		WIN32_FIND_DATA find_data;
		memset(&find_data, 0, sizeof(WIN32_FIND_DATA));
		HANDLE hFind = FindFirstFile(workDir, &find_data);
		if (NULL == hFind)
			return FALSE;

		do
		{
			if (0 != _tcscmp(find_data.cFileName, _T(".")) && _tcscmp(find_data.cFileName, _T("..")))
			{
				//strAddPath = AddRemoteFile(strRemoteDir, find_data, file_list);
				//���丮 �Ǵ� ���ϸ�
				CString filename = find_data.cFileName;
				_stprintf_s(find_data.cFileName, MAX_PATH, _T("%s\\%s"), localDir.GetString(), filename.GetString());
				fileArray.push_back(find_data);
				//if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			}

		} while (FindNextFile(hFind, &find_data));

		FindClose(hFind);
		return TRUE;
	}

	//	localFullPath : L"D:\\�ٿ�ε�\\2013_10_22_14_18\\DCGameServer.exe"
	//	remoteFullDir : L"\\server_patch\\2013_10_24"
	//	remoteFile : L"DCGameServer.exe"
	BOOL CHisFtp::UploadFile(const TCHAR* localFullPath, TCHAR* remoteFullDir, WCHAR* remoteFile)
	{
		//#include <wininet.h>
		//#pragma comment(lib, "wininet")
		if (NULL == m_hInternet || NULL == m_hFtpSession)
			return FALSE;

		//file / dir ���翩��(�������� �ʴ´ٸ�...)
		if (0 != _taccess_s(localFullPath, 0))
			return FALSE;

		//remote�� ������ ���� ��쿡 ������ �ش�.
		if (FALSE == SetRemoteDirectory(remoteFullDir))	//���丮�� �������� ������
		{
			//if(FALSE == FtpCreateDirectory(m_hFtpSession, remoteFullDir))//���丮 ������ �õ�
			if (FALSE == CreateRemoteDirectory(remoteFullDir))//���丮 ������ �õ�
				return FALSE;
		}

		TCHAR wzRemoteFile[MAX_PATH] = _T("");
		_stprintf_s(wzRemoteFile, _T("%s\\%s"), remoteFullDir, remoteFile);
		return FtpPutFile(m_hFtpSession, (LPTSTR)localFullPath, (LPTSTR)wzRemoteFile, FTP_TRANSFER_TYPE_BINARY, 0);
	}

	//	remoteFullPath : L"\\server_patch\\2013_10_24\\DCGameServer.exe"
	//	localFullPath : L"D:\\�ٿ�ε�\\2013_10_22_14_18\\DCGameServer.exe"
	BOOL CHisFtp::DownloadFile(const TCHAR* remoteFullPath, const TCHAR* localFullPath)
	{
		//#include <wininet.h>
		//#pragma comment(lib, "wininet")
		if (NULL == m_hInternet || NULL == m_hFtpSession)
			return FALSE;

		//file / dir ���翩��(�������� �ʴ´ٸ�...)
		if (NULL == FindRemoteFile(remoteFullPath))
			return FALSE;

		TCHAR   drive[MAX_PATH] = _T("");
		TCHAR   dir[MAX_PATH] = _T("");
		//TCHAR   fileName[MAX_PATH] = _(T"");
		//TCHAR   ext[MAX_PATH] = _(T"");

		_wsplitpath_s(localFullPath, drive, MAX_PATH, dir, MAX_PATH, NULL, 0, NULL, 0);

		CString strMakeDir;
		strMakeDir.Format(_T("%s\\%s"), drive, dir);
		if (FALSE == CreateLocalDirectory(strMakeDir))
			return FALSE;

		return FtpGetFile(m_hFtpSession, (LPTSTR)remoteFullPath, (LPTSTR)localFullPath, 0, 0, FTP_TRANSFER_TYPE_BINARY, 0);
	}

	//local�� 29 folder �� ������ �޴´�.
	// 29�������� �����ϰ� �ʹٸ�, remoteDir�� 29������ ������ �־�� �Ѵ�.
	// localDir = _T("D:\\Ftp\\workpatch\\PatchVersion\\29")))
	// remoteDir = _T("\\server_patch\\29")
	BOOL CHisFtp::UploadFolder(IN TCHAR* localDir, IN TCHAR* remoteDir)
	{
		std::vector<WIN32_FIND_DATA> fileArray;

		if (FALSE == GetLocalFilesWithSubDir(localDir, fileArray))
			return FALSE;

		for (int i = 0; i < (int)fileArray.size(); ++i)
		{
			//remote�� �����θ� �޾ƿ´�.
			TCHAR* fullpath = fileArray[i].cFileName;

			//fullpath���� localDir + \\ �� ���ֱ� ���� +1�� �����Ͽ���.
			//TCHAR* localDir = _T("D:\\Ftp\\workpatch\\PatchVersion\\29");
			//TCHAR* fullpath = _T("D:\\Ftp\\workpatch\\PatchVersion\\29\\Patch_v21_v1.zip");
			TCHAR* relativeDir = &fullpath[_tcslen(localDir) + 1];

			//directory�̸�...
			if (fileArray[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString dir;
				dir.Format(_T("%s\\%s"), remoteDir, relativeDir);
				CreateRemoteDirectory(dir);
				continue;
			}

			//file�̸�...
			//CString dir;
			//dir.Format(_T("%s\\%s"), remoteDir, relativeDir);
			//UploadFile(fullpath, (TCHAR*)dir.GetString(), relativeDir);
			UploadFile(fullpath, remoteDir, relativeDir);
		}

		return TRUE;
	}

	//remote�� 29 folder �� ������ �޴´�.
	// 29�������� �����ϰ� �ʹٸ�, localDir�� 29������ ������ �־�� �Ѵ�.
	// remoteDir = _T("\\server_patch\\29")
	// localDir = _T("D:\\Ftp\\workpatch\\PatchVersion\\29")))
	BOOL CHisFtp::DownloadFolder(IN TCHAR* remoteDir, IN TCHAR* localDir)
	{
		std::vector<WIN32_FIND_DATA> fileArray;

		if (FALSE == GetRemoteFilesWithSubDir(remoteDir, fileArray))
			return FALSE;

		for (int i = 0; i < (int)fileArray.size(); ++i)
		{
			//remote�� �����θ� �޾ƿ´�.
			TCHAR* fullpath = fileArray[i].cFileName;

			//fullpath���� remoteDir + \\ �� ���ֱ� ���� +1�� �����Ͽ���.
			//TCHAR* remoteDir = _T("\\server_patch");
			//TCHAR* fullpath = _T("\\server_patch\\29\\config\\DtDragon.ini");
			TCHAR* relativeDir = &fullpath[_tcslen(remoteDir) + 1];

			//directory�̸�...
			if (fileArray[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString dir;
				dir.Format(_T("%s\\%s"), localDir, relativeDir);
				CreateLocalDirectory(dir);
				continue;
			}

			//file�̸�...
			CString dir;
			dir.Format(_T("%s\\%s"), localDir, relativeDir);
			DownloadFile(fullpath, dir);
		}

		return TRUE;
	}

	//�������丮 �����Ͽ� ���丮�� �����Ѵ�
	//���� strDirPath�� c:\123\456\789��� c:\, c:\123, c:\123\456, c:\123\456\789 ������ �����Ѵ�
	BOOL CHisFtp::CreateRemoteDirectory(CString strDirPath)
	{
		strDirPath.Replace(_T("\\\\"), _T("\\"));
		if (strDirPath.GetLength() == 0)
			return FALSE;

		if (strDirPath.GetAt(strDirPath.GetLength() - 1) == _T('\\'))//����ڰ� �Է��� ��������� �������� '\'�� �� ������
			strDirPath = strDirPath.Left(strDirPath.GetLength() - 1);//'\'�� ''(����)���� ��ȯ


		BOOL bSuccess = TRUE;

		//strDirPath ���ڿ��� �߰��� �ִ� ���� ����
		//���� c:\123\456\789 ��� c:\, c:\123, c:\123\456 ���� ����
		//remote�� ��� ������ "\\server_patch" �̹Ƿ� �Ǿչ��ڴ� ���� ó���մϴ�. 
		for (int i = 1; i < strDirPath.GetLength(); i++)
		{
			if (strDirPath.GetAt(i) == _T('\\'))
			{
				CString strMakeDir = strDirPath.Left(i);
				//if(_taccess_s(strMakeDir, 0) == ENOENT)//���丮�� �������� ������
				if (FALSE == SetRemoteDirectory((TCHAR*)strMakeDir.GetString()))//���丮�� �������� ������
				{
					//if(_tmkdir(strMakeDir) == ENOENT)//���丮 ������ �õ�
					if (FALSE == FtpCreateDirectory(m_hFtpSession, strMakeDir))//���丮 ������ �õ�
						return FALSE;
				}
			}
		}

		//if(_tmkdir(strDirPath) == ENOENT)//���� ���丮(c:\123\456\789) ����
		if (FALSE == FtpCreateDirectory(m_hFtpSession, strDirPath))//���� ���丮(c:\123\456\789) ����
			return FALSE;

		return TRUE;
	}

	BOOL CHisFtp::CreateLocalDirectory(CString strDirPath)
	{
		return HisUtil::CreateSubDir(strDirPath);
	}

	BOOL CHisFtp::FindRemoteFile(IN const TCHAR* remoteFullPath)
	{
		WIN32_FIND_DATA find_data;
		memset(&find_data, 0, sizeof(WIN32_FIND_DATA));
		HINTERNET hFind = FtpFindFirstFile(m_hFtpSession, remoteFullPath, &find_data, INTERNET_FLAG_RELOAD, NULL);
		if (NULL == hFind)
			return FALSE;

		InternetCloseHandle(hFind);
		return TRUE;
	}

};//..namespace HisUtil {