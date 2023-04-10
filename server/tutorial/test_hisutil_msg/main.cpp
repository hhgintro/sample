// MasterServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


#include <windows.h>

void test_MsgPack()
{
	char char_a[10] = { 0, };
	wchar_t wchar_a[10] = { 0, };
	int int_a[10] = { 0, };
	memset(char_a, 1, sizeof(char_a));
	memset(wchar_a, 2, sizeof(wchar_a));
	memset(int_a, 9, sizeof(int_a));
	printf("char size : %d\n", sizeof(char_a));
	printf("wchar size : %d\n", sizeof(wchar_a));
	printf("int_a size : %d\n", sizeof(int_a));

	char out_char_a[10] = { 0, };
	wchar_t out_wchar_a[10] = { 0, };
	wchar_t out_int_a[10] = { 0, };

	char* pchar = out_char_a;
	wchar_t* pwchar = out_wchar_a;
	wchar_t* pint = out_int_a;

	//memcpy_s(pchar, 10, char_a, 10);
	//memcpy_s(pwchar, 20, wchar_a, 18);
	HisUtil::CMsg msg;
	msg
		//<< char_a
		//<< wchar_a
		<< HisUtil::CMsgPack(char_a, sizeof(char_a))
		<< HisUtil::CMsgPack(wchar_a, sizeof(wchar_a))
		<< HisUtil::CMsgPack(int_a, sizeof(int_a))
		;

	msg
		//>> out_char_a
		//>> out_wchar_a
		>> HisUtil::CMsgPack(out_char_a, sizeof(out_char_a))
		>> HisUtil::CMsgPack(out_wchar_a, sizeof(out_wchar_a))
		>> HisUtil::CMsgPack(out_int_a, sizeof(out_int_a))
		;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//test_MsgPack();
	//test_Vector();

	system("pause");
	return 0;

}
