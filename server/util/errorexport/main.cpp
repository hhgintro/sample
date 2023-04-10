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
//	SecIdx = _tcsstr (FullPath, _T(".exe"));//프로세스명
//	nFileNameLength = (SecIdx - FirstIdx - 1) * sizeof(TCHAR);//unicode
//	//nFileNameLength = (SecIdx) * sizeof(TCHAR);//unicode
//
//	//실행파일이 구동되는 폴더 위치만 전달해 준다.
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
	int arraycount = 0;	//배열의 개수를 기록합니다.(대조용)

	//strstr()함수를 호출하면 원본이 손상되므로 2회이상 tokenize()을 호출할 수 없어서
	//복사본을 만들어서 사용합니다.
	char temperrorcode[BUFF_SIZE+1];
	memcpy(temperrorcode, errorcode, sizeof(temperrorcode));

	//정보를 가져올 enum을 찾는다.
	char* pos = strstr(temperrorcode, "enum GameResultCode");
	if(NULL == pos)
		return arraycount;

	//문자열 끝까지 돌아보자.
	char* seps = "\n";//토큰 구분자
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
		//이미 주석처리된 경우는 제외시킨다.
		/*	예시
			//Reserve_00002,        //using for proud
		*/
		__int64 gap = temp - token;
		if(gap < 4)	// 4: 그냥 감으로...
		{
			/* Get next token: */
			token = strtok_s(NULL, seps, &context);
			continue;
		}

		//====================================



		//lua는 1부터 배열이 시작되어...0(성공)은 빼고 넣어줍니다.
		if(0 != arraycount || FALSE == bLua)
		{
			// + 2 : 문자열 앞에"//" 부분은 제거해 주기 위해 넣었다.
			fprintf(file, format, arraycount, temp + 2);// (L") + 문자열 + (",)
		}
		++arraycount;

		//끝..
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
//	//파일의 시작.
//	_ftprintf(file, L"#pragma once\n\n\n");
//
//	//참조파일 경로.
//	//_ftprintf(file, L"//%s\n", errorCodeFile);
//	//_ftprintf(file, L"//%s\n\n\n", errorStringFile);
//
//
//	//문자배열의 시작
//	_ftprintf(file, L"static const wchar_t* GameResultCodeString[] = {");
//	{
//		
//		//예시문
//		//		/*    0*/		"성공",
//		//		/*    1*/		"proud 예외 상황 발생",
//		int arraycount = Tokenize(file, errorcode, "\n\t/*%5d*/\t\tL\"%s\",", FALSE);
//
//		//문자열 배열의 끝
//		_ftprintf(file, L"\n};\n\n\n");
//
//		//배열의 개수를 기록합니다.
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
//	//파일의 시작.
//	//_ftprintf(file, L"#pragma once\n\n\n");
//
//	//참조파일 경로.
//	//_ftprintf(file, L"//%s\n", errorCodeFile);
//	//_ftprintf(file, L"//%s\n\n\n", errorStringFile);
//
//
//	//문자배열의 시작
//	_ftprintf(file, L"ErrorStringInfo = {}");
//	{
//		int arraycount = Tokenize(file, errorcode, "\nErrorStringInfo[%d] = \"%s\"", TRUE);
//
//		//int lenth = errorcode.GetLength();
//		WCHAR* tokens = L"'\n'";//토큰 구분자
//
//
//		//int index = errorcode.Find(L"enum GameResultCode");//정보를 가져올 enum을 찾는다.
//		//int index_old = index;
//
//		//Proud::String resToken;//오류메시지 담는다.
//
//		//int arraycount = 0;	//배열의 개수를 기록합니다.(대조용)
//
//		//int posArray = -1;//배열의 위치값으로 활용된다.
//		//while(0 <= index)
//		//{
//		//	index = errorcode.Find(tokenComment, index) + _tcslen(tokenComment);//정보를 가져올 enum을 찾는다.(+2 : "//"를 생략하기 위해)
//		//	if(-1 == index)
//		//		break;
//
//		//	//갑자기 왜 앞쪽을 가리킬까???
//		//	if(index < index_old)
//		//		break;
//
//		//	//재설정
//		//	index_old = index;
//
//		//	//아래쪽
//		//	//MAX_GAME_RESULT 문자열로 끝을 파악합니다.
//		//	//if(GAME_RESULT_COUNT < ++posArray)//배열의 위치값으로 활용된다.
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
//		//	//lua는 1부터 배열이 시작되서...0(성공)은 빼고 넣어줍니다.
//		//	if(0 < arraycount)
//		//		_ftprintf(file, L"\nErrorStringInfo[%d] = \"%s\"", arraycount, temp);	// (L") + 문자열 + (",)
//		//	++arraycount;
//
//		//	//문자열의 끝.
//		//	if(0 == resToken.Compare(L"MAX_GAME_RESULT"))
//		//		break;
//		//}
//
//		//문자열 배열의 끝
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
	//명령인수 : ../pidl/X2G.txt -path ../../common/pidl/

	//실행파일 + xml경로 + 프로토콜(X2B.txt) + 저장경로
	_tprintf(_T("\n텍스트(*.txt) 정보로 프로토콜 구조체와 함수를 생성합니다.\n\n"));
	_tprintf(_T("ErrorExport	[source] [-path 경로] [-cs] [-lang 언어]\n"));
	_tprintf(_T("    source     ErrorCode.h 파일경로.\n"));
	_tprintf(_T("    path		파일 출력경로(default:현재경로)\n"));
	_tprintf(_T("    -cs        cs 파일을 생성합니다.\n"));
	_tprintf(_T("    -lang		언어(default:kr, en, jp)\n"));
	//system("pause");
}

BOOL parserArgment(int argc, _TCHAR* argv[], TCHAR** source, TCHAR** target, BOOL& bCS, TCHAR** lang)
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == _T('-'))
		{
			//target 경로가 있다면
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
				//존재하지 않는 옵션
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

	TCHAR* target = _T(".");//현재경로(".")
	TCHAR* source = NULL;
	BOOL bCS = FALSE;	//cs 파일생성유무
	TCHAR* lang = _T("kr");

	//pidl의 NULL체크는 parserArgment()이후에 진행해 준다.
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
		//ErrorCode.h 생성경로
		_stprintf_s(errorCodeFile, _T("%s"), HisUtil::GetAppendPath(projectPath, source).c_str());
		//ErrorString.h 생성경로
		//_stprintf_s(errorStringFile, _T("%s"), HisUtil::GetAppendPath(projectPath, target).c_str());
	}

	//경로명 또는 파일명에 한글이 포함되면 파일 입출력이 동작하지 않는다.
	_wsetlocale(LC_ALL, L"");//#include <locale.h>

	//모듈 보호
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

		//ErrorString.h 생성경로
		_stprintf_s(errorStringFile, _T("%s\\ErrorString_%s.h"), HisUtil::GetAppendPath(projectPath, target).c_str(), lang);
		loader.MakeFile(opt, errorStringFile, FALSE);
	}

	if (TRUE == bCS) {
		//예시문
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

		//ErrorString.h 생성경로
		_stprintf_s(errorStringFile, _T("%s\\ErrorString_%s.cs"), HisUtil::GetAppendPath(projectPath, target).c_str(), lang);
		loader.MakeFile(opt, errorStringFile, bCS);
	}

	//system("pause");
	return 0;
}
