// test_hisutil_thread.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{

	char* str0 = "abc��abc";

	HisUtil::CT2U8 strUtf8(str0);

	printf("%s -> %s\n", str0, strUtf8.GetUTF8().c_str());


	system("pause");
	return 0;
}

