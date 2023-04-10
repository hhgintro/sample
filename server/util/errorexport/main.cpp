#include "stdafx.h"


const int BUFF_SIZE = 100000;

//void GetProjectPathName(TCHAR* pathName, TCHAR* appName)
//{
//	if(NULL == pathName || NULL == appName)
//		return;
//
//	TCHAR FullPath[MAX_PATH];
//	INT64 nPathLength = 0, nFileNameLength = 0;
//	TCHAR *FirstIdx = NULL, *SecIdx = NULL;
//
//	/*
//	D:\DigitalFrog\work\delphinia_Union\bin\MasterServer.exe
//	\MasterServer
//	*/
//	nPathLength = GetModuleFileName(NULL, FullPath, sizeof(FullPath));
//	FirstIdx = _tcsrchr (FullPath, _T('\\'));
//	nPathLength = (FirstIdx - FullPath);//  * sizeof(TCHAR);//unicode
//
//	SecIdx = _tcsstr (FullPath, _T(".exe"));//���μ�����
//	nFileNameLength = (SecIdx - FirstIdx - 1) * sizeof(TCHAR);//unicode
//	//nFileNameLength = (SecIdx) * sizeof(TCHAR);//unicode
//
//	//���������� �����Ǵ� ���� ��ġ�� ������ �ش�.
//	memcpy( pathName, FullPath, (nPathLength + 1) * sizeof(TCHAR));
//
//	memcpy( appName, FullPath + (nPathLength + 1), nFileNameLength);
//	//appName
//}

BOOL LoadErrorFile(WCHAR* filename, char* errorcode, int size)
{
	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
	_tfopen_s(&file, filename, _T("rt"));
	if(NULL == file)
		return FALSE;

	//fseek(file, 0, SEEK_END);   // non-portable
	//size = ftell(file);

	////wchar_t strError[BUFF_SIZE+1];
	//char strError[BUFF_SIZE+1];
	//memset(&strError, 0, );

	fread(errorcode, size, 1, file);
	fclose(file);
	return TRUE;
}

int Tokenize(FILE* file, char* errorcode, char* format, BOOL bLua)
{
	int arraycount = 0;	//�迭�� ������ ����մϴ�.(������)

	//strstr()�Լ��� ȣ���ϸ� ������ �ջ�ǹǷ� 2ȸ�̻� tokenize()�� ȣ���� �� ���
	//���纻�� ���� ����մϴ�.
	char temperrorcode[BUFF_SIZE+1];
	memcpy(temperrorcode, errorcode, sizeof(temperrorcode));

	//������ ������ enum�� ã�´�.
	char* pos = strstr(temperrorcode, "enum GameResultCode");
	if(NULL == pos)
		return arraycount;

	//���ڿ� ������ ���ƺ���.
	char* seps = "\n";//��ū ������
	char* context = NULL;
	char* token = strtok_s(pos, seps, &context);
	while( token != NULL )
	{
		/* While there are tokens in "string" */
		//printf( " %s\n ", token );
		char* temp = strstr(token, "//");
		if(NULL == temp)
		{
			/* Get next token: */
			token = strtok_s(NULL, seps, &context);
			continue;
		}

		//====================================
		//�̹� �ּ�ó���� ���� ���ܽ�Ų��.
		/*	����
			//Reserve_00002,        //using for proud
		*/
		__int64 gap = temp - token;
		if(gap < 4)	// 4: �׳� ������...
		{
			/* Get next token: */
			token = strtok_s(NULL, seps, &context);
			continue;
		}

		//====================================



		//lua�� 1���� �迭�� ���۵Ǿ�...0(����)�� ���� �־��ݴϴ�.
		if(0 != arraycount || FALSE == bLua)
		{
			// + 2 : ���ڿ� �տ�"//" �κ��� ������ �ֱ� ���� �־���.
			fprintf(file, format, arraycount, temp + 2);// (L") + ���ڿ� + (",)
		}
		++arraycount;

		//��..
		if(NULL != strstr(temp, "MAX_GAME_RESULT"))
			break;


		/* Get next token: */
		token = strtok_s(NULL, seps, &context);
	}//..while( token != NULL )

	return arraycount;
}

//void MakeErrorString(char* errorcode, TCHAR* errorStringFile)
//{
//	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
//	_tfopen_s(&file, errorStringFile, _T("wt"));
//	if(NULL == file)
//	{
//		_tprintf(_T("fail fopen"));
//		return;
//	}
//
//	//������ ����.
//	_ftprintf(file, L"#pragma once\n\n\n");
//
//	//�������� ���.
//	//_ftprintf(file, L"//%s\n", errorCodeFile);
//	//_ftprintf(file, L"//%s\n\n\n", errorStringFile);
//
//
//	//���ڹ迭�� ����
//	_ftprintf(file, L"static const wchar_t* GameResultCodeString[] = {");
//	{
//		
//		//���ù�
//		//		/*    0*/		"����",
//		//		/*    1*/		"proud ���� ��Ȳ �߻�",
//		int arraycount = Tokenize(file, errorcode, "\n\t/*%5d*/\t\tL\"%s\",", FALSE);
//
//		//���ڿ� �迭�� ��
//		_ftprintf(file, L"\n};\n\n\n");
//
//		//�迭�� ������ ����մϴ�.
//		_ftprintf(file, L"const int MAX_GAME_RESULT_STRING_COUNT = %d;\n", arraycount);
//	}
//
//	//fflush (file);
//	fclose(file);
//	file = NULL;
//
//}
//
//void MakeErrorLua(char* errorcode, TCHAR* errorLuaFile)
//{
//	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
//	_tfopen_s(&file, errorLuaFile, _T("wt"));
//	if(NULL == file)
//	{
//		_tprintf(_T("fail fopen"));
//		return;
//	}
//
//	//������ ����.
//	//_ftprintf(file, L"#pragma once\n\n\n");
//
//	//�������� ���.
//	//_ftprintf(file, L"//%s\n", errorCodeFile);
//	//_ftprintf(file, L"//%s\n\n\n", errorStringFile);
//
//
//	//���ڹ迭�� ����
//	_ftprintf(file, L"ErrorStringInfo = {}");
//	{
//		int arraycount = Tokenize(file, errorcode, "\nErrorStringInfo[%d] = \"%s\"", TRUE);
//
//		//int lenth = errorcode.GetLength();
//		WCHAR* tokens = L"'\n'";//��ū ������
//
//
//		//int index = errorcode.Find(L"enum GameResultCode");//������ ������ enum�� ã�´�.
//		//int index_old = index;
//
//		//Proud::String resToken;//�����޽��� ��´�.
//
//		//int arraycount = 0;	//�迭�� ������ ����մϴ�.(������)
//
//		//int posArray = -1;//�迭�� ��ġ������ Ȱ��ȴ�.
//		//while(0 <= index)
//		//{
//		//	index = errorcode.Find(tokenComment, index) + _tcslen(tokenComment);//������ ������ enum�� ã�´�.(+2 : "//"�� �����ϱ� ����)
//		//	if(-1 == index)
//		//		break;
//
//		//	//���ڱ� �� ������ ����ų��???
//		//	if(index < index_old)
//		//		break;
//
//		//	//�缳��
//		//	index_old = index;
//
//		//	//�Ʒ���
//		//	//MAX_GAME_RESULT ���ڿ��� ���� �ľ��մϴ�.
//		//	//if(GAME_RESULT_COUNT < ++posArray)//�迭�� ��ġ������ Ȱ��ȴ�.
//		//	//	break;
//
//		//	resToken = errorcode.Tokenize(tokens, index);
//		//	if(-1 == index)
//		//		break;
//
//
//		//	wchar_t temp[4096] = L"";
//		//	int length = (resToken.GetLength() * 2);
//		//	memcpy(temp, resToken.GetString(), length);
//		//	//_tcscpy_s(temp, length, resToken.GetString());
//		//	//printf("%d = %s\n", posArray, Proud::StringW2A(resToken).GetString());
//
//		//	//lua�� 1���� �迭�� ���۵Ǽ�...0(����)�� ���� �־��ݴϴ�.
//		//	if(0 < arraycount)
//		//		_ftprintf(file, L"\nErrorStringInfo[%d] = \"%s\"", arraycount, temp);	// (L") + ���ڿ� + (",)
//		//	++arraycount;
//
//		//	//���ڿ��� ��.
//		//	if(0 == resToken.Compare(L"MAX_GAME_RESULT"))
//		//		break;
//		//}
//
//		//���ڿ� �迭�� ��
//		_ftprintf(file, L"\n\n\nfunction GetErrorStringInfo( index )");
//		_ftprintf(file, L"\n\treturn ErrorStringInfo[index]");
//		_ftprintf(file, L"\nend");
//
//		_ftprintf(file, L"\n\nfunction GetErrorStringCount()");
//		_ftprintf(file, L"\n\treturn table.count( ErrorStringInfo )");
//		_ftprintf(file, L"\nend");
//	}
//
//	//fflush (file);
//	fclose(file);
//	file = NULL;
//
//}


void help()
{
	//����μ� : ../pidl/X2G.txt -path ../../common/pidl/

	//�������� + xml��� + ��������(X2B.txt) + ������
	_tprintf(_T("\n�ؽ�Ʈ(*.txt) ������ �������� ����ü�� �Լ��� �����մϴ�.\n\n"));
	_tprintf(_T("ErrorExport	[source] [-path ���] [-cs] [-lang ���]\n"));
	_tprintf(_T("    source     ErrorCode.h ���ϰ��.\n"));
	_tprintf(_T("    path		���� ��°��(default:������)\n"));
	_tprintf(_T("    -cs        cs ������ �����մϴ�.\n"));
	_tprintf(_T("    -lang		���(default:kr, en, jp)\n"));
	//system("pause");
}

BOOL parserArgment(int argc, _TCHAR* argv[], TCHAR** source, TCHAR** target, BOOL& bCS, TCHAR** lang)
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == _T('-'))
		{
			//target ��ΰ� �ִٸ�
			if (0 == _tcscmp(argv[i], _T("-path")))
			{
				if (++i < argc)
				{
					*target = argv[i];
					continue;
				}
			}
			else if (0 == _tcscmp(argv[i], _T("-lang")))
			{
				if (++i < argc)
				{
					*lang = argv[i];
					continue;
				}
			}
			else if (0 == _tcscmp(argv[i], _T("-cs")))
			{
				bCS = TRUE;
				continue;
			}
			else
			{
				//�������� �ʴ� �ɼ�
				//help();
				return FALSE;
			}
		}
		else if (0 == _tcscmp(argv[i], _T("/?")))
		{
			//help();
			return FALSE;
		}

		*source = argv[i];
	}

	return TRUE;
}

//#include "../../common/errorcode/ErrorCode.h"
int _tmain(int argc, WCHAR* argv[], WCHAR* envp[])
{
	_wsetlocale(LC_ALL, L"");//#include <locale.h>

	TCHAR* target = _T(".");//������(".")
	TCHAR* source = NULL;
	BOOL bCS = FALSE;	//cs ���ϻ�������
	TCHAR* lang = _T("kr");

	//pidl�� NULLüũ�� parserArgment()���Ŀ� ������ �ش�.
	if (FALSE == parserArgment(argc, argv, &source, &target, bCS, &lang) || NULL == source)
	{
		help();
		return 0;
	}

	HisUtil::CModule m_module;

	TCHAR* projectPath = m_module.GetPathName();
	TCHAR errorCodeFile[MAX_PATH] = _T("");
	TCHAR errorStringFile[MAX_PATH] = _T("");
	{
		//ErrorCode.h �������
		_stprintf_s(errorCodeFile, _T("%s"), HisUtil::GetAppendPath(projectPath, source).c_str());
		//ErrorString.h �������
		//_stprintf_s(errorStringFile, _T("%s"), HisUtil::GetAppendPath(projectPath, target).c_str());
	}

	//��θ� �Ǵ� ���ϸ� �ѱ��� ���ԵǸ� ���� ������� �������� �ʴ´�.
	_wsetlocale(LC_ALL, L"");//#include <locale.h>

	//��� ��ȣ
	if(FALSE == m_module.CheckValid())
		return 0;


	CFileLoader loader;
	loader.LoadEnumFile(errorCodeFile);

	char commentLang[MAX_PATH] = "";
	sprintf_s(commentLang, "//[%s]", HisUtil::String(lang).c_str());

	CCommentOption opt;
	opt.SetEnumSymbol("enum GameResultCode");
	opt.SetComment(commentLang);
	loader.Tokenize(opt);


	TCHAR temp[MAX_PATH] = _T("");

	//bCS = false;
	{
		opt.ClearSyntax();
	
		opt.AddStartSyntax(_T("#pragma once\n#include <map>\n\n\n"));
		//opt.AddStartSyntax(_T("static const wchar_t* GameResultCodeString_[] = {"));
		//opt.AddEndSyntax(_T("\n};\n"));

		_stprintf_s(temp, _T("namespace GameResult_%s {"), lang);
		opt.AddStartSyntax(temp);
		opt.AddStartSyntax(_T("\n\tstd::map<int, std::wstring> GameResultCodeString;"));
		opt.AddStartSyntax(_T("\n\n\tstatic void LoadGameResultString()\n\t{"));
		opt.AddEndSyntax(_T("\n\t}\n"));

		opt.AddEndSyntax(_T("\n\tstatic const WCHAR* GetGameResultString(int result) {"));
		opt.AddEndSyntax(_T("\n\t\tif (0 == GameResultCodeString.size())"));
		opt.AddEndSyntax(_T("\n\t\t\tLoadGameResultString();"));

		opt.AddEndSyntax(_T("\n\n\t\tstd::map<int, std::wstring>::iterator it = GameResultCodeString.find(result);"));
		opt.AddEndSyntax(_T("\n\t\tif (it != GameResultCodeString.end())"));
		opt.AddEndSyntax(_T("\n\t\t\treturn (*it).second.c_str();"));
		opt.AddEndSyntax(_T("\n\t\treturn L\"\";\n\t}\n} //namespace GameResult {"));

		//ErrorString.h �������
		_stprintf_s(errorStringFile, _T("%s\\ErrorString_%s.h"), HisUtil::GetAppendPath(projectPath, target).c_str(), lang);
		loader.MakeFile(opt, errorStringFile, FALSE);
	}

	if (TRUE == bCS) {
		//���ù�
		//string[] weekDays2 = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		opt.ClearSyntax();

		//opt.AddStartSyntax("#pragma once\n\n\n");
		opt.AddStartSyntax(_T("\nusing System.Collections.Generic;"));
		opt.AddStartSyntax(_T("\n\nnamespace CSampleClient {"));
		_stprintf_s(temp, _T("\n\tstatic public class GameResult_%s\n\t{"), lang);
		opt.AddStartSyntax(temp);

		opt.AddStartSyntax(_T("\n\t\tstatic Dictionary<int, string> GameResultCodeString = new Dictionary<int, string>();"));
		opt.AddStartSyntax(_T("\n\n\t\tstatic void LoadGameResultString()\n\t\t{"));
		opt.AddEndSyntax(_T("\n\t\t}\t\t\n"));

		opt.AddEndSyntax(_T("\n\t\tstatic public string GetGameResultString(int result) {"));
		opt.AddEndSyntax(_T("\n\t\t\tif (0 == GameResultCodeString.Count)"));
		opt.AddEndSyntax(_T("\n\t\t\t\tLoadGameResultString();"));

		opt.AddEndSyntax(_T("\n\n\t\t\tif (GameResultCodeString.ContainsKey(result))"));
		opt.AddEndSyntax(_T("\n\t\t\t\treturn GameResultCodeString[result];"));
		opt.AddEndSyntax(_T("\n\t\t\treturn \"\";\n\t\t}\n\t}\n}"));

		//ErrorString.h �������
		_stprintf_s(errorStringFile, _T("%s\\ErrorString_%s.cs"), HisUtil::GetAppendPath(projectPath, target).c_str(), lang);
		loader.MakeFile(opt, errorStringFile, bCS);
	}

	//system("pause");
	return 0;
}
