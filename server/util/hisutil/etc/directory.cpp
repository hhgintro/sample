#include "stdafx.h"

#include <tchar.h>

namespace HisUtil
{

	//하위 디렉토리 모두 삭제
	///* 이게 더 좋아...한방이다..^^
	#include "shellapi.h"
	void DeleteFolder(char* szDirectory)

	{
		SHFILEOPSTRUCTA FileOp = {0};//쉘 구조체 

		FileOp.hwnd = NULL;
		FileOp.wFunc = FO_DELETE;//지우고 
		FileOp.pFrom = szDirectory;//인자로 받은 폴더

		FileOp.pTo = NULL;//복사할때 사용
		FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI ;//화면에 메세지 표시 않함

		//뭔지 알고 싶으시면 지우고 해보세요
		FileOp.fAnyOperationsAborted = false;//나머진 뭔지 모르겠네요
		FileOp.hNameMappings = NULL;
		FileOp.lpszProgressTitle = NULL;

		SHFileOperationA(&FileOp);//구조체를 실행
	}
	//*/


	//위에꺼 서라..한방이더라...ㅋㅋ
	void DeleteFolder(const TCHAR* lpFolder)
	{
		WIN32_FIND_DATA	FindData;
		HANDLE			FindHandle;
		TCHAR temp1[MAX_PATH];
		UINT lpFolder_Len;

		if(lpFolder==NULL || *lpFolder=='\0')
			return;

		lpFolder_Len = static_cast<UINT>(_tcslen(lpFolder));
		if(lpFolder[lpFolder_Len-1]=='\\')
		{
			_tprintf_s(temp1, "%s*.*", lpFolder);
		}
		else
		{
			_tprintf_s(temp1, "%s\\*.*", lpFolder);
		}

		FindHandle=FindFirstFile(temp1, &FindData);
		if(INVALID_HANDLE_VALUE!=FindHandle)
		{
			while(1)
			{
				if(lpFolder[lpFolder_Len-1]=='\\')
				{
					_tprintf_s(temp1, "%s%s", lpFolder, FindData.cFileName);
				}
				else
				{
					_tprintf_s(temp1, "%s\\%s", lpFolder, FindData.cFileName);
				}
				if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//Dir
					if(_tcscmp(FindData.cFileName, _T("."))==0)
					{
						//.    -->> skip
					}
					else if(_tcscmp(FindData.cFileName, _T(".."))==0)
					{
						//..   -->> skip
					}
					else
					{
						DeleteFolder(temp1);
						if((FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)||
							(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
						{
							SetFileAttributes(temp1, FILE_ATTRIBUTE_NORMAL);
						}
						RemoveDirectory(temp1);
					}
				}
				else
				{
					//File
					if((FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)||
						(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
					{
						SetFileAttributes(temp1, FILE_ATTRIBUTE_NORMAL);
					}
					DeleteFile(temp1);
				}
				if(!FindNextFile(FindHandle, &FindData))
				{
					break;
				}
			}
		}
		FindClose(FindHandle);

		SetFileAttributes(lpFolder, FILE_ATTRIBUTE_NORMAL);
		RemoveDirectory(lpFolder);
	}

	HisUtil::TString replaceString(HisUtil::TString subject, const HisUtil::TString& search, const HisUtil::TString& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	//하위디렉토리 포함하여 디렉토리를 생성한다
	//가령 dirpath가 c:\123\456\789라면 c:\, c:\123, c:\123\456, c:\123\456\789 폴더를 생성한다
	BOOL CreateSubDir(const TCHAR* dirpath)
	{
		TCHAR dir[MAX_PATH] = _T("");

		for (int i = 0; i < _tcslen(dirpath); ++i)
		{
			if ('/' == dirpath[i] || '\\' == dirpath[i])
			{
				_tcsncpy_s(dir, dirpath, i + 1);

				if (_taccess_s(dir, 0) == ENOENT)//디렉토리가 존재하지 않으면
				{
					if (_tmkdir(dir) == ENOENT)//디렉토리 생성을 시도
						return FALSE;
				}
			}
		}

		//경로 끝에 슬래쉬('/' or '\\')가 없은 경우
		if (_taccess_s(dirpath, 0) == ENOENT)//디렉토리가 존재하지 않으면
		{
			if (_tmkdir(dirpath) == ENOENT)//디렉토리 생성을 시도
				return FALSE;
		}
		return TRUE;
	}


#include <io.h>
	// 0 : 디렉토리면 0 반환
	// 1 : 파일
	// -1 : 파일 또는 디렉토리가 없으면 -1 반환
	int isFileOrDir(TCHAR* path)
	{
		_tfinddatai64_t c_file;
		intptr_t hFile;
		int result;


		if ((hFile = _tfindfirsti64(path, &c_file)) == -1L)
			result = -1; // 파일 또는 디렉토리가 없으면 -1 반환
		else
			if (c_file.attrib & _A_SUBDIR)
				result = 0; // 디렉토리면 0 반환
			else
				result = 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환


		_findclose(hFile);

		return result;
	}


};//..namespace HisUtil
