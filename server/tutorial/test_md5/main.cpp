// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



//std::string md5(const std::string strMd5)
//{
//	md5_state_t state;
//	md5_byte_t digest[16];
//	char hex_output[16 * 2 + 1];
//	int di;
//
//	md5_init(&state);
//	md5_append(&state, (const md5_byte_t *)strMd5.c_str(), strMd5.length());
//	md5_finish(&state, digest);
//
//	int size = sizeof(hex_output) + 10;
//
//	for (di = 0; di < 16; ++di)
//		sprintf_s(hex_output + di * 2, 3, "%02x", digest[di]);
//
//	return hex_output;
//}

int main()
{
	//char* tmp = "Hello world";//"3e25960a79dbc69b674cd4ec67a72c62"
	char* tmp = "hello world";//"5eb63bbbe01eeed093cb22bb8f5acdc3"


	HisUtil::md5 md5;
	md5.append(tmp, (int)strlen(tmp));

	std::string buff = md5.GetMd5();
	printf("%s\n", buff.c_str());
	system("pause");
    return 0;
}

