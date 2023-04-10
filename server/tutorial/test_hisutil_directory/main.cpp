// test_hisutil_db.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"



int _tmain(int argc, _TCHAR* argv[])
{
	//printf("result:%d\n", _tmkdir(_T("c://__test1")));		//success
	//printf("result:%d\n", _tmkdir(_T("c://__test2//")));	//success
	//printf("result:%d\n", _tmkdir(_T("c:\\\\__test3")));	//success
	//printf("result:%d\n", _tmkdir(_T("c://\\__test4\\")));	//success
	////printf("result:%d\n", _tmkdir(_T("//__test0001")));		//fail
	//printf("result:%d\n", _tmkdir(_T(".//__test0002")));	//success
	//printf("result:%d\n", _tmkdir(_T("__test0003")));	//success

	//TCHAR path[] = L"D:\work\test\2016.07.02\server\sample\test_hisutil_directory/\\123\\/456/\\/789";
	TCHAR path[] = L"./\\123\\/456/\\/789";
	//TCHAR path[] = L"123";

	printf("result(1 is success):%d\n", HisUtil::CreateSubDir(path));
	system("pause");
	return 0;
}
