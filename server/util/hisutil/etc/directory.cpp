#include "stdafx.h"

#include <tchar.h>

namespace HisUtil
{

	//���� ���丮 ��� ����
	///* �̰� �� ����...�ѹ��̴�..^^
	#include "shellapi.h"
	void DeleteFolder(char* szDirectory)

	{
		SHFILEOPSTRUCTA FileOp = {0};//�� ����ü 

		FileOp.hwnd = NULL;
		FileOp.wFunc = FO_DELETE;//����� 
		FileOp.pFrom = szDirectory;//���ڷ� ���� ����

		FileOp.pTo = NULL;//�����Ҷ� ���
		FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI ;//ȭ�鿡 �޼��� ǥ�� ����

		//���� �˰� �����ø� ����� �غ�����
		FileOp.fAnyOperationsAborted = false;//������ ���� �𸣰ڳ׿�
		FileOp.hNameMappings = NULL;
		FileOp.lpszProgressTitle = NULL;

		SHFileOperationA(&FileOp);//����ü�� ����
	}
	//*/


	//������ ����..�ѹ��̴���...����
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

	//�������丮 �����Ͽ� ���丮�� �����Ѵ�
	//���� dirpath�� c:\123\456\789��� c:\, c:\123, c:\123\456, c:\123\456\789 ������ �����Ѵ�
	BOOL CreateSubDir(const TCHAR* dirpath)
	{
		TCHAR dir[MAX_PATH] = _T("");

		for (int i = 0; i < _tcslen(dirpath); ++i)
		{
			if ('/' == dirpath[i] || '\\' == dirpath[i])
			{
				_tcsncpy_s(dir, dirpath, i + 1);

				if (_taccess_s(dir, 0) == ENOENT)//���丮�� �������� ������
				{
					if (_tmkdir(dir) == ENOENT)//���丮 ������ �õ�
						return FALSE;
				}
			}
		}

		//��� ���� ������('/' or '\\')�� ���� ���
		if (_taccess_s(dirpath, 0) == ENOENT)//���丮�� �������� ������
		{
			if (_tmkdir(dirpath) == ENOENT)//���丮 ������ �õ�
				return FALSE;
		}
		return TRUE;
	}


#include <io.h>
	// 0 : ���丮�� 0 ��ȯ
	// 1 : ����
	// -1 : ���� �Ǵ� ���丮�� ������ -1 ��ȯ
	int isFileOrDir(TCHAR* path)
	{
		_tfinddatai64_t c_file;
		intptr_t hFile;
		int result;


		if ((hFile = _tfindfirsti64(path, &c_file)) == -1L)
			result = -1; // ���� �Ǵ� ���丮�� ������ -1 ��ȯ
		else
			if (c_file.attrib & _A_SUBDIR)
				result = 0; // ���丮�� 0 ��ȯ
			else
				result = 1; // �׹��� ���� "�����ϴ� ����"�̱⿡ 1 ��ȯ


		_findclose(hFile);

		return result;
	}


};//..namespace HisUtil
