// Zipper.cpp: implementation of the CZipper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Zipper.h"

#include "zlib/zip.h"
#include "zlib/iowin32.h"
#include "../shared/filemisc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const UINT BUFFERSIZE = 2048;

CZipper::CZipper(LPCTSTR szFilePath, LPCTSTR szRootFolder, bool bAppend) : m_uzFile(0)
{
	CloseZip();

	if (szFilePath)
		OpenZip(szFilePath, szRootFolder, bAppend);
}

CZipper::~CZipper()
{
	CloseZip();
}

bool CZipper::CloseZip()
{
	int nRet = m_uzFile ? zipClose(m_uzFile, NULL) : ZIP_OK;

	m_uzFile = NULL;
	m_szRootFolder[0] = 0;
	ZeroMemory(&m_info, sizeof(m_info));

	return (nRet == ZIP_OK);
}

void CZipper::GetFileInfo(Z_FileInfo& info)
{
	info = m_info;
}

// simple interface
//형식 : L"d:\\svn_diff.txt"
bool CZipper::ZipFile(LPCTSTR szFilePath)
{
	DWORD dwAttr = GetFileAttributes(szFilePath);
	if (dwAttr == 0xffffffff
		|| FILE_ATTRIBUTE_DIRECTORY == (dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return false;

	// make zip path
	TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
	_tsplitpath_s(szFilePath, szDrive, _MAX_DRIVE, szFolder, MAX_PATH, szName, _MAX_FNAME, NULL, 0);

	TCHAR szZipPath[MAX_PATH];
	_tmakepath_s(szZipPath, MAX_PATH, szDrive, szFolder, szName, _T("zip"));

	CZipper zip;
	if (zip.OpenZip(szZipPath, NULL, false))
		return zip.AddFileToZip(szFilePath, false);

	return FALSE;
}

//형식 : L"d:\\svn_diff"
bool CZipper::ZipFolder(LPCTSTR szFilePath, bool bIgnoreFilePath)
{
	DWORD dwAttr = GetFileAttributes(szFilePath);
	if (dwAttr == 0xffffffff
		|| FILE_ATTRIBUTE_DIRECTORY != (dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return false;

	// make zip path
	TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
	_tsplitpath_s(szFilePath, szDrive, _MAX_DRIVE, szFolder, MAX_PATH, szName, _MAX_FNAME, NULL, 0);

	TCHAR szZipPath[MAX_PATH];
	_tmakepath_s(szZipPath, MAX_PATH, szDrive, szFolder, szName, _T("zip"));

	CZipper zip;

	TCHAR szRootFolder[MAX_PATH] = _T("");
	_tcscpy_s(szRootFolder, MAX_PATH, szFilePath);
	//strcat(szRootFolder, "\\");

	if (zip.OpenZip(szZipPath, szRootFolder, FALSE))
		return zip.AddFolderToZip(szFilePath, bIgnoreFilePath);

	return FALSE;
}
	
// works with prior opened zip
bool CZipper::AddFileToZip(LPCTSTR szFilePath, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	// we don't allow paths beginning with '..\' because this would be outside
	// the root folder
	if (!bIgnoreFilePath && _tcsstr(szFilePath, _T("..\\")) == szFilePath)
		return false;

	//TRACE ("CZipper::AddFileToZip(%s)\n", szFilePath);

	bool bFullPath = (_tcschr(szFilePath, _T(':')) != NULL);

	// if the file is relative then we need to append the root before opening
	TCHAR szFullFilePath[MAX_PATH];
	
	lstrcpy(szFullFilePath, szFilePath);
	PrepareSourcePath(szFullFilePath);

	// if the file is a fullpath then remove the root path bit
	TCHAR szFileName[MAX_PATH] = _T("");

	if (bIgnoreFilePath)
	{
		TCHAR szName[_MAX_FNAME], szExt[_MAX_EXT];
		_tsplitpath_s(szFilePath, NULL, 0, NULL, 0, szName, _MAX_FNAME, szExt, _MAX_EXT);

		_tmakepath_s(szFileName, MAX_PATH, NULL, NULL, szName, szExt);
	}
	else if (bFullPath)
	{
		//// check the root can be found
		//if (0 != _strnicmp(szFilePath, m_szRootFolder, lstrlen(m_szRootFolder)))
		//	return false;

		// else
		lstrcpy(szFileName, szFilePath + lstrlen(m_szRootFolder));
	}
	else // relative path
	{
		// if the path begins with '.\' then remove it
		if (_tcsstr(szFilePath, _T(".\\")) == szFilePath)
			lstrcpy(szFileName, szFilePath + 2);
		else
			lstrcpy(szFileName, szFilePath);
	}

	// save file attributes
	zip_fileinfo zfi;

	zfi.internal_fa = 0;
	zfi.external_fa = ::GetFileAttributes(szFilePath);
	
	// save file time
	SYSTEMTIME st;

	GetLastModified(szFullFilePath, st, TRUE);

	zfi.dosDate = 0;
	zfi.tmz_date.tm_year = st.wYear;
	zfi.tmz_date.tm_mon = st.wMonth - 1;
	zfi.tmz_date.tm_mday = st.wDay;
	zfi.tmz_date.tm_hour = st.wHour;
	zfi.tmz_date.tm_min = st.wMinute;
	zfi.tmz_date.tm_sec = st.wSecond;
	
	// load input file
	HANDLE hInputFile = ::CreateFile(szFullFilePath, 
									GENERIC_READ,
									0,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_READONLY,
									NULL);

	if (hInputFile == INVALID_HANDLE_VALUE)
		return FALSE;

	int nRet = zipOpenNewFileInZip(m_uzFile, 
									Proud::StringW2A(szFileName),
									&zfi, 
									NULL, 
									0,
									NULL,
									0, 
									NULL,
									Z_DEFLATED,
									Z_DEFAULT_COMPRESSION);

	if (nRet == ZIP_OK)
	{
		m_info.nFileCount++;

		// read the file and output to zip
		char pBuffer[BUFFERSIZE];
		DWORD dwBytesRead = 0, dwFileSize = 0;

		while (nRet == ZIP_OK && ::ReadFile(hInputFile, pBuffer, BUFFERSIZE, &dwBytesRead, NULL))
		{
			dwFileSize += dwBytesRead;

			if (dwBytesRead)
				nRet = zipWriteInFileInZip(m_uzFile, pBuffer, dwBytesRead);
			else
				break;
		}

		m_info.dwUncompressedSize += dwFileSize;
	}

	zipCloseFileInZip(m_uzFile);
	::CloseHandle(hInputFile);

	return (nRet == ZIP_OK);
}

//bool CZipper::AddFileToZip(LPCTSTR szFilePath, LPCTSTR szRelFolderPath)
//{
//	if (!m_uzFile)
//		return FALSE;
//
//	// szRelFolderPath cannot contain drive info
//	if (szRelFolderPath && strchr(szRelFolderPath, ':'))
//		return FALSE;
//
//	// if the file is relative then we need to append the root before opening
//	char szFullFilePath[MAX_PATH];
//	
//	lstrcpy(szFullFilePath, szFilePath);
//	PrepareSourcePath(szFullFilePath);
//
//	// save file attributes and time
//	zip_fileinfo zfi;
//
//	zfi.internal_fa = 0;
//	zfi.external_fa = ::GetFileAttributes(szFilePath);
//	
//	// save file time
//	SYSTEMTIME st;
//
//	GetLastModified(szFullFilePath, st, TRUE);
//
//	zfi.dosDate = 0;
//	zfi.tmz_date.tm_year = st.wYear;
//	zfi.tmz_date.tm_mon = st.wMonth - 1;
//	zfi.tmz_date.tm_mday = st.wDay;
//	zfi.tmz_date.tm_hour = st.wHour;
//	zfi.tmz_date.tm_min = st.wMinute;
//	zfi.tmz_date.tm_sec = st.wSecond;
//
//	// load input file
//	HANDLE hInputFile = ::CreateFile(szFullFilePath, 
//									GENERIC_READ,
//									0,
//									NULL,
//									OPEN_EXISTING,
//									FILE_ATTRIBUTE_READONLY,
//									NULL);
//
//	if (hInputFile == INVALID_HANDLE_VALUE)
//		return FALSE;
//
//	// strip drive info off filepath
//	char szName[_MAX_FNAME], szExt[_MAX_EXT];
//	_splitpath(szFilePath, NULL, NULL, szName, szExt);
//
//	// prepend new folder path 
//	char szFileName[MAX_PATH];
//	_makepath(szFileName, NULL, szRelFolderPath, szName, szExt);
//
//	// open the file in the zip making sure we remove any leading '\'
//	int nRet = zipOpenNewFileInZip(m_uzFile, 
//									szFileName + (szFileName[0] == '\\' ? 1 : 0),
//									&zfi, 
//									NULL, 
//									0,
//									NULL,
//									0, 
//									NULL,
//									Z_DEFLATED,
//									Z_DEFAULT_COMPRESSION);
//
//	if (nRet == ZIP_OK)
//	{
//		m_info.nFileCount++;
//
//		// read the file and output to zip
//		char pBuffer[BUFFERSIZE];
//		DWORD dwBytesRead = 0, dwFileSize = 0;
//
//		while (nRet == ZIP_OK && ::ReadFile(hInputFile, pBuffer, BUFFERSIZE, &dwBytesRead, NULL))
//		{
//			dwFileSize += dwBytesRead;
//
//			if (dwBytesRead)
//				nRet = zipWriteInFileInZip(m_uzFile, pBuffer, dwBytesRead);
//			else
//				break;
//		}
//
//		m_info.dwUncompressedSize += dwFileSize;
//	}
//
//	zipCloseFileInZip(m_uzFile);
//	::CloseHandle(hInputFile);
//
//	return (nRet == ZIP_OK);
//}

bool CZipper::AddFolderToZip(LPCTSTR szFolderPath, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	m_info.nFolderCount++;

	// if the path is relative then we need to append the root before opening
	TCHAR szFullPath[MAX_PATH];
	
	lstrcpy(szFullPath, szFolderPath);
	PrepareSourcePath(szFullPath);

	// always add folder first
	// save file attributes
	zip_fileinfo zfi;
	
	zfi.internal_fa = 0;
	zfi.external_fa = ::GetFileAttributes(szFullPath);
	
	SYSTEMTIME st;
	
	GetLastModified(szFullPath, st, TRUE);
	
	zfi.dosDate = 0;
	zfi.tmz_date.tm_year = st.wYear;
	zfi.tmz_date.tm_mon = st.wMonth - 1;
	zfi.tmz_date.tm_mday = st.wDay;
	zfi.tmz_date.tm_hour = st.wHour;
	zfi.tmz_date.tm_min = st.wMinute;
	zfi.tmz_date.tm_sec = st.wSecond;
	
	// if the folder is a fullpath then remove the root path bit
	TCHAR szFolderName[MAX_PATH] = _T("");
	
	if (bIgnoreFilePath)
	{
		_tsplitpath_s(szFullPath, NULL, 0, NULL, 0, szFolderName, MAX_PATH, NULL, 0);
	}
	else
	{
		// check the root can be found
		if (0 != _tcsncicmp(szFullPath, m_szRootFolder, lstrlen(m_szRootFolder)))
			return false;
		
		// else
		lstrcpy(szFolderName, szFullPath + lstrlen(m_szRootFolder));
	}
	
	// folders are denoted by a trailing '\\'
	lstrcat(szFolderName, _T("\\"));
	
	// open the file in the zip making sure we remove any leading '\'
	int nRet = zipOpenNewFileInZip(m_uzFile, 
		Proud::StringW2A(szFolderName),
		&zfi, 
		NULL, 
		0,
		NULL,
		0, 
		NULL,
		Z_DEFLATED,
		Z_DEFAULT_COMPRESSION);
	
	zipCloseFileInZip(m_uzFile);

	// build searchspec
	TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
	_tsplitpath_s(szFullPath, szDrive, _MAX_DRIVE, szFolder, MAX_PATH, szName, _MAX_FNAME, NULL, 0);
	lstrcat(szFolder, szName);

	TCHAR szSearchSpec[MAX_PATH];
	_tmakepath_s(szSearchSpec, MAX_PATH, szDrive, szFolder, _T("*"), _T("*"));

	WIN32_FIND_DATA finfo;
	HANDLE hSearch = FindFirstFile(szSearchSpec, &finfo);

	if (hSearch != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			if (finfo.cFileName[0] != '.') // ".", ".."
			{
				TCHAR szItem[MAX_PATH];
				_tmakepath_s(szItem, MAX_PATH, szDrive, szFolder, finfo.cFileName, NULL);
				
				if (finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					AddFolderToZip(szItem, bIgnoreFilePath);
				}
				else 
					AddFileToZip(szItem, bIgnoreFilePath);
			}
		} 
		while (FindNextFile(hSearch, &finfo));
		
		FindClose(hSearch);
	}

	return TRUE;
}

// extended interface
bool CZipper::OpenZip(LPCTSTR szFilePath, LPCTSTR szRootFolder, bool bAppend)
{
	CloseZip();

	if (!szFilePath || !lstrlen(szFilePath))
		return false;

	// convert szFilePath to fully qualified path 
	TCHAR szFullPath[MAX_PATH];

	if (!GetFullPathName(szFilePath, MAX_PATH, szFullPath, NULL))
		return false;

	// zipOpen will fail if bAppend is TRUE and zip does not exist
	if (bAppend && ::GetFileAttributes(szFullPath) == 0xffffffff)
		bAppend = false;

	m_uzFile = zipOpen(Proud::StringW2A(szFullPath), bAppend ? 1 : 0);

	if (m_uzFile)
	{
		if (!szRootFolder)
		{
			TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH];
			_tsplitpath_s(szFullPath, szDrive, _MAX_DRIVE, szFolder, MAX_PATH, NULL, 0, NULL, 0);

			_tmakepath_s(m_szRootFolder, MAX_PATH, szDrive, szFolder, NULL, NULL);
		}
		else if (lstrlen(szRootFolder))
		{
			//_makepath(m_szRootFolder, NULL, szRootFolder, "", NULL);
			_tcscpy_s(m_szRootFolder, MAX_PATH, szRootFolder);
		}
	}

	return (m_uzFile != NULL);
}

void CZipper::PrepareSourcePath(LPTSTR szPath)
{
	bool bFullPath = (_tcschr(szPath, ':') != NULL);

	// if the file is relative then we need to append the root before opening
	if (!bFullPath)
	{
		TCHAR szTemp[MAX_PATH];
		lstrcpy(szTemp, szPath);

		_tmakepath_s(szPath, MAX_PATH, NULL, m_szRootFolder, szTemp, NULL);
	}
}
