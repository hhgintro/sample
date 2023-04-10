#include "stdafx.h"
#include "FileLoader.h"


CFileLoader::CFileLoader()
	: m_buff(NULL), m_arraycount(-1)
{

	//경로명 또는 파일명에 한글이 포함되면 파일 입출력이 동작하지 않는다.
	_wsetlocale(LC_ALL, L"");//#include <locale.h>
}


CFileLoader::~CFileLoader()
{
	DELETE_SAFE_ARRAY(m_buff);
}


bool CFileLoader::LoadEnumFile(TCHAR* path)
{

	int ttt = 0;
	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
	_tfopen_s(&file, path, _T("rt"));
	if (NULL == file)
		return false;

	fseek(file, 0, SEEK_END);   // non-portable
	int size = ftell(file);
	m_buff = new char[size];
	memset(m_buff, 0, size);

	////wchar_t strError[BUFF_SIZE+1];
	//char strError[BUFF_SIZE+1];
	//memset(&strError, 0, );

	fseek(file, 0, SEEK_SET);   // non-portable
	fread(m_buff, 1, size, file);
	fclose(file);
	return true;
}



int CFileLoader::Tokenize(CCommentOption& opt)
{
	m_arraycount = -1;	//배열의 개수를 기록합니다.(대조용)

	//정보를 가져올 enum을 찾는다.
	char* pos = strstr(GetBuff(), opt.GetEnumSymbol());
	if (NULL == pos)
		return m_arraycount;

	//enum의 시작...
	pos = strstr(GetBuff(), "{");
	if (NULL == pos)
		return m_arraycount;


	//enum의 주석을 찾으면 true가 된다.
	//(못 찾은 경우 default 값으로 설정해 준다.)
	//bool findcomments = false;

	//문자열 끝까지 돌아보자.
	char* seps = "\n";//토큰 구분자
	char* context = NULL;
	char* token = strtok_s(pos+1, seps, &context);	//한줄씩 가져옵니다.
	while (token != NULL)
	{
		//enum의 끝...
		//if (NULL != strstr(commentsToken, "MAX_GAME_RESULT"))
		if (NULL != strstr(token, "};"))
			break;
		//printf("line:%s\n", token);

		//===============
		//주석문 찾기
		//===============
		if(IsComment(token, opt))
		{
			token = strtok_s(NULL, seps, &context);
			continue;
		}

		//===============
		//enum 값 찾기
		//===============
		//enum 값의 문자길이를 구한다.
		char* enumToken = strstr(token, "//");

		__int64 tempsize = enumToken - token;
		if (NULL == enumToken)
			tempsize = strlen(token);


		//enum 값를 찾는다.
		char* temp = new char[tempsize+1];
		memcpy(temp, token, tempsize);
		temp[tempsize] = '\0';
		char* data = HisUtil::trim(temp, " ,\t\n");
		if (strlen(data) > 0)
			SetEnumValue(token);

		DELETE_SAFE_ARRAY(temp);


		

		//","가 처음이면 시작임(이전꺼는 주석 완료처리-못찾았으면 자동입력)
		//__int64 gap = commaToken - commentsToken;

		//받아올 문자열
		//commentsToken = commentsToken + strlen(comments);
		//printf("%s\n", temp);

		/* Get next token: */
		token = strtok_s(NULL, seps, &context);
	}//..while( token != NULL )


	return m_arraycount;
}

bool CFileLoader::IsComment(char* token, CCommentOption& opt)
{
	if (NULL != strstr(token, "//") || NULL != strstr(token, "/*"))	// [/*] 만 있어도 주석으로 간주한다.
	{
		char* commentsPos = strstr(token, opt.GetComment());
		if (NULL != commentsPos)
		{
			//주석문이 이중인경우( //1, //2 ), 앞쪽을 주석의 길이를 구한다.
			char* commentsNext = strstr(commentsPos + strlen(opt.GetComment()), "//");

			//주석문앞의 검색코드의 길이("//[kr]주석문" 에서 "//[kr]")는 뺀다.
			__int64 tempsize = commentsNext - commentsPos - strlen(opt.GetComment());
			if (NULL == commentsNext)
				tempsize = strlen(commentsPos) - strlen(opt.GetComment());

			char* temp = new char[tempsize + 1];
			memcpy(temp, commentsPos + strlen(opt.GetComment()), tempsize);
			temp[tempsize] = '\0';
			char* data = HisUtil::trim(temp, " ,\t\n");
			//printf("comment(%d):%s\n", arraycount, temp);
			m_pool.insert(std::pair<int, std::string>(m_arraycount, data));
			//findcomments = true;//주석문 찾았다.
			DELETE_SAFE_ARRAY(temp);
		}
		return true;
	}
	return false;//주석문이 아니다.
}

void CFileLoader::SetEnumValue(char* token)
{
	//findcomments = false;
	//printf("key:%s\n", temp);

	//enum 에 값을 설정한 경우 (RESULT_OK = 100)
	char* numToken = strstr(token, "=");
	if (NULL == numToken)
	{
		++m_arraycount;
		return;
	}

	char* data = HisUtil::trim(numToken+1, " ,\t\n");//+1 : =는 빼기위해서.
	if (strlen(data) > 0)
		m_arraycount = atoi(data);
}

//bCS : cs 파일 생성유무
bool CFileLoader::MakeFile(CCommentOption& opt, TCHAR* path, BOOL bCS)
{
	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
	_tfopen_s(&file, path, _T("wt+,ccs=UTF-8"));
	if (NULL == file)
	{
		printf("fail fopen");
		return false;
	}

	////파일의 시작.
	//_ftprintf(file, L"#pragma once\n\n\n");
	//문자배열의 시작
	//_ftprintf(file, L"static const wchar_t* GameResultCodeString[] = {");
	std::vector<std::wstring>::iterator it = opt.GetStartSyntax().begin();
	while ( it != opt.GetStartSyntax().end())
	{
		_ftprintf(file, (*it).c_str());
		++it;
	}

	{

		//예시문
		//		/*    0*/		"성공",
		//		/*    1*/		"proud 예외 상황 발생",
		std::map<int, std::string>::iterator it = m_pool.begin();
		for (; it != m_pool.end(); ++it)
		{
			//std::map<int, std::string>::iterator it = m_pool.find(i);
			//if (it == m_pool.end())
			//{
			//	//주석문이 없는 경우.
			//	fprintf(file, "\n\t/*%5d*/\t\tL\"%s\",", i, "(not found)");
			//	continue;
			//}

			TCHAR wzBuf[4096] = _T("");
			HisUtil::CA2W(CP_ACP, (*it).second.c_str(), wzBuf, sizeof(wzBuf));

			if (TRUE == bCS) {
				//fprintf(file, "\n\t/*%5d*/\t\t\"%s\",", (*it).first, (*it).second.c_str());
				_ftprintf(file, _T("\n\t\t\tGameResultCodeString.Add(%u, \"(%u) %s\");"), (*it).first, (*it).first, wzBuf);
			} else {
				//fprintf(file, "\n\t/*%5d*/\t\tL\"%s\",", (*it).first, (*it).second.c_str());
				_ftprintf(file, _T("\n\t\tGameResultCodeString.insert(std::pair<int, std::wstring>(%u, L\"(%u) %s\"));"), (*it).first, (*it).first, wzBuf);
			}
		}

	}

	////문자열 배열의 끝
	////_ftprintf(file, L"\n};\n\n\n");
	//_ftprintf(file, L"\n};\n");
	it = opt.GetEndSyntax().begin();
	while (it != opt.GetEndSyntax().end())
	{
		_ftprintf(file, (*it).c_str());
		++it;
	}

	//배열의 개수를 기록합니다.
	//_ftprintf(file, L"const int MAX_GAME_RESULT_STRING_COUNT = %d;\n", m_arraycount);

	//fflush (file);
	fclose(file);
	file = NULL;

	return true;
}
