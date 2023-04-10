// Zipper.h: interface for the CZipper class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


#include "zlib/zip.h"

struct Z_FileInfo
{
	int nFileCount;
	int nFolderCount;
	DWORD dwUncompressedSize;
};

class CZipper  
{
public:
	CZipper(LPCTSTR szFilePath = NULL, LPCTSTR szRootFolder = NULL, bool bAppend = FALSE);
	virtual ~CZipper();

	// simple interface
	static bool ZipFile(LPCTSTR szFilePath); // saves as same name with .zip
	static bool ZipFolder(LPCTSTR szFilePath, bool bIgnoreFilePath); // saves as same name with .zip
	
	// works with prior opened zip
	bool AddFileToZip(LPCTSTR szFilePath, bool bIgnoreFilePath = FALSE);
	//bool AddFileToZip(LPCTSTR szFilePath, LPCTSTR szRelFolderPath); // replaces path info from szFilePath with szFolder
	bool AddFolderToZip(LPCTSTR szFolderPath, bool bIgnoreFilePath = FALSE);

	// extended interface
	bool OpenZip(LPCTSTR szFilePath, LPCTSTR szRootFolder = NULL, bool bAppend = FALSE);
	bool CloseZip(); // for multiple reuse
	void GetFileInfo(Z_FileInfo& info);
	
protected:
	zipFile m_uzFile;
	TCHAR m_szRootFolder[MAX_PATH + 1];
	Z_FileInfo m_info;

protected:
	void PrepareSourcePath(LPTSTR szPath);
};
