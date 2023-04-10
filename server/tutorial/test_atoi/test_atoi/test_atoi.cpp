// test_atoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <stdlib.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, -84, -104, -80, -28, -78, 124, -73, -56, -71, 20, -68, -84, -64, 68, -59, 0, 0, 0, 5, 6, 31, -123, 119, 65, 100, 0 };

	int pos = 0;
	int rank = buf[pos];
	pos += 8;//rank가 8byte값으로 넘어온다.

	std::wstring name = ((wchar_t*)&buf[pos]);
	pos += 19;//name 길이 19(db에서 최대길이)

	char Gender = buf[pos];
	pos += 1;//gender 길이

	char Age = buf[pos];
	pos += 1;//age 길이

	float PlayTime = (float)buf[pos];
	pos += 4;//playtime 길이

	int Score = buf[pos];
	pos += 4;//score 길이


	system("pause");
	return 0;
}