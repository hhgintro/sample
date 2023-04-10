#include "stdafx.h"
#include "FileLoader.h"


CFileLoader::CFileLoader()
	: m_buff(NULL), m_arraycount(-1)
{

	//��θ� �Ǵ� ���ϸ� �ѱ��� ���ԵǸ� ���� ������� �������� �ʴ´�.
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
	m_arraycount = -1;	//�迭�� ������ ����մϴ�.(������)

	//������ ������ enum�� ã�´�.
	char* pos = strstr(GetBuff(), opt.GetEnumSymbol());
	if (NULL == pos)
		return m_arraycount;

	//enum�� ����...
	pos = strstr(GetBuff(), "{");
	if (NULL == pos)
		return m_arraycount;


	//enum�� �ּ��� ã���� true�� �ȴ�.
	//(�� ã�� ��� default ������ ������ �ش�.)
	//bool findcomments = false;

	//���ڿ� ������ ���ƺ���.
	char* seps = "\n";//��ū ������
	char* context = NULL;
	char* token = strtok_s(pos+1, seps, &context);	//���پ� �����ɴϴ�.
	while (token != NULL)
	{
		//enum�� ��...
		//if (NULL != strstr(commentsToken, "MAX_GAME_RESULT"))
		if (NULL != strstr(token, "};"))
			break;
		//printf("line:%s\n", token);

		//===============
		//�ּ��� ã��
		//===============
		if(IsComment(token, opt))
		{
			token = strtok_s(NULL, seps, &context);
			continue;
		}

		//===============
		//enum �� ã��
		//===============
		//enum ���� ���ڱ��̸� ���Ѵ�.
		char* enumToken = strstr(token, "//");

		__int64 tempsize = enumToken - token;
		if (NULL == enumToken)
			tempsize = strlen(token);


		//enum ���� ã�´�.
		char* temp = new char[tempsize+1];
		memcpy(temp, token, tempsize);
		temp[tempsize] = '\0';
		char* data = HisUtil::trim(temp, " ,\t\n");
		if (strlen(data) > 0)
			SetEnumValue(token);

		DELETE_SAFE_ARRAY(temp);


		

		//","�� ó���̸� ������(�������� �ּ� �Ϸ�ó��-��ã������ �ڵ��Է�)
		//__int64 gap = commaToken - commentsToken;

		//�޾ƿ� ���ڿ�
		//commentsToken = commentsToken + strlen(comments);
		//printf("%s\n", temp);

		/* Get next token: */
		token = strtok_s(NULL, seps, &context);
	}//..while( token != NULL )


	return m_arraycount;
}

bool CFileLoader::IsComment(char* token, CCommentOption& opt)
{
	if (NULL != strstr(token, "//") || NULL != strstr(token, "/*"))	// [/*] �� �־ �ּ����� �����Ѵ�.
	{
		char* commentsPos = strstr(token, opt.GetComment());
		if (NULL != commentsPos)
		{
			//�ּ����� �����ΰ��( //1, //2 ), ������ �ּ��� ���̸� ���Ѵ�.
			char* commentsNext = strstr(commentsPos + strlen(opt.GetComment()), "//");

			//�ּ������� �˻��ڵ��� ����("//[kr]�ּ���" ���� "//[kr]")�� ����.
			__int64 tempsize = commentsNext - commentsPos - strlen(opt.GetComment());
			if (NULL == commentsNext)
				tempsize = strlen(commentsPos) - strlen(opt.GetComment());

			char* temp = new char[tempsize + 1];
			memcpy(temp, commentsPos + strlen(opt.GetComment()), tempsize);
			temp[tempsize] = '\0';
			char* data = HisUtil::trim(temp, " ,\t\n");
			//printf("comment(%d):%s\n", arraycount, temp);
			m_pool.insert(std::pair<int, std::string>(m_arraycount, data));
			//findcomments = true;//�ּ��� ã�Ҵ�.
			DELETE_SAFE_ARRAY(temp);
		}
		return true;
	}
	return false;//�ּ����� �ƴϴ�.
}

void CFileLoader::SetEnumValue(char* token)
{
	//findcomments = false;
	//printf("key:%s\n", temp);

	//enum �� ���� ������ ��� (RESULT_OK = 100)
	char* numToken = strstr(token, "=");
	if (NULL == numToken)
	{
		++m_arraycount;
		return;
	}

	char* data = HisUtil::trim(numToken+1, " ,\t\n");//+1 : =�� �������ؼ�.
	if (strlen(data) > 0)
		m_arraycount = atoi(data);
}

//bCS : cs ���� ��������
bool CFileLoader::MakeFile(CCommentOption& opt, TCHAR* path, BOOL bCS)
{
	FILE* file = NULL;//fopen("c:\\mapfile.txt", "at");
	_tfopen_s(&file, path, _T("wt+,ccs=UTF-8"));
	if (NULL == file)
	{
		printf("fail fopen");
		return false;
	}

	////������ ����.
	//_ftprintf(file, L"#pragma once\n\n\n");
	//���ڹ迭�� ����
	//_ftprintf(file, L"static const wchar_t* GameResultCodeString[] = {");
	std::vector<std::wstring>::iterator it = opt.GetStartSyntax().begin();
	while ( it != opt.GetStartSyntax().end())
	{
		_ftprintf(file, (*it).c_str());
		++it;
	}

	{

		//���ù�
		//		/*    0*/		"����",
		//		/*    1*/		"proud ���� ��Ȳ �߻�",
		std::map<int, std::string>::iterator it = m_pool.begin();
		for (; it != m_pool.end(); ++it)
		{
			//std::map<int, std::string>::iterator it = m_pool.find(i);
			//if (it == m_pool.end())
			//{
			//	//�ּ����� ���� ���.
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

	////���ڿ� �迭�� ��
	////_ftprintf(file, L"\n};\n\n\n");
	//_ftprintf(file, L"\n};\n");
	it = opt.GetEndSyntax().begin();
	while (it != opt.GetEndSyntax().end())
	{
		_ftprintf(file, (*it).c_str());
		++it;
	}

	//�迭�� ������ ����մϴ�.
	//_ftprintf(file, L"const int MAX_GAME_RESULT_STRING_COUNT = %d;\n", m_arraycount);

	//fflush (file);
	fclose(file);
	file = NULL;

	return true;
}
