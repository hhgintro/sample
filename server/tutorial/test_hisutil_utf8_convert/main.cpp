// test_hisutil_thread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{

	char* str0 = "abc가abc";

	HisUtil::CT2U8 strUtf8(str0);

	printf("%s -> %s\n", str0, strUtf8.GetUTF8().c_str());


	system("pause");
	return 0;
}

