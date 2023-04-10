// test_hisutil_module.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <atltime.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HisUtil::CModule module;
	wprintf(L"path: %s\n", module.GetPathName());
	wprintf(L"app: %s\n", module.GetAppName());
	/*
	CTime createdtime(2016, 5, 20, 10, 56, 00);

	printf("create \t: %lld\n", createdtime.GetTime());
	printf("utc \t: %lld\n", HisUtil::GetUniversalTime());

	struct tm t;
	__time64_t tmp = createdtime.GetTime();
	_localtime64_s(&t, &tmp);

	char buff[100];
	sprintf_s(buff, _countof(buff), "���� ���� �ð� : %d/%02d/%02d %02d:%02d:%02d",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);
	puts(buff);

	_gmtime64_s(&t, &tmp);
	sprintf_s(buff, _countof(buff), "���� ǥ�� �ð� : %d/%02d/%02d %02d:%02d:%02d",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);
	puts(buff);
	*/

	//�׽�Ʈ�� �������� �ӽ� �ð������� �����ϵ��� �Ͽ���.(�ð������� �� ����� �Ѵ�.)
	module.Init(2016, 5, 20, 11, 22, 00);

	while (1){
		Sleep(1000);

		//�����ġ �̵�
		COORD pos = { 0, 5 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		printf("event \t: %lld\n", module.GetEventTime()); //�׽�Ʈ�� ��������
		printf("utc \t: %lld\n", HisUtil::GetUniversalTime());

		module.CheckValid();
	}

	system("pause");
	return 0;
}

