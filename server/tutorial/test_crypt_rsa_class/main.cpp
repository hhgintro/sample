// test_crypt_ras.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


//typedef unsigned char		CONVERT_T;
const int CONVERT_T = 3;//한번에 암호화 할 수 있는 byte수

int main()
{
	//▶ 키 생성
	//1. 서로다른 소수 p와 q를 선택하고
	//2. 이들의 곱 n = pq를 계산한다.
	//3. phi( φ(n) = (p - 1)(q - 1) )를 구한다.

	HisUtil::CCryptoRSA crypto;
	crypto.Begin(0x1003, 0x100f);
	//crypto.Begin(0xffef, 0xfff1);
	//crypto.Begin(0xfff1);

	//crypto.set_n(0x00000000005b2bf3);
	//crypto.set_e(0x0000000000000065);
	//crypto.set_d(0x00000000000904fd);

	//char형 배열을 처리하기 때문에 255를 넘을 이유는 없을듯.
	//CRYPTO_T tmp = 0xc8434241;// 165000;// 5000;// 255;// 5;
	HisUtil::CRYPTO_T tmp = 0xFFFFFF;// 0xc843;// 165000;// 5000;// 255;// 5;

	//▶ encrypt
	HisUtil::CRYPTO_T C = crypto.Encrypt(tmp);
	printf("encrypt : 0x%x\n", C);

	//▶ decrypt
	HisUtil::CRYPTO_T D = crypto.Decrypt(C);
	printf("decrypt : 0x%x\n", D);

	//for (CRYPTO_T i = 0x2000; i < 0xFFFFffff; ++i)
	//{
	//	//▶ encrypt
	//	CRYPTO_T C = crypto.Encrypt(i);
	//	//▶ decrypt
	//	CRYPTO_T D = crypto.Decrypt(C);
	//	if (i!=D)
	//		printf("0x%x ", i);
	//}


#if 0
	const int max_buffer = 100;
	CRYPTO_T m[max_buffer] = { 0, }, en[max_buffer] = { 0, };
	//char msg[max_buffer] = "ABCDEFGHJIKLMNOPQRSTUVWXYZ(황현기abcdefghjiklmnopqrstuvwxyz0123456789";
	char msg[max_buffer] = "AB황현기ab";
	char after[max_buffer] = "";

	int size = 0;
	for (int i = 0; i < (int)strlen(msg); i += CONVERT_T)
	{
		//m[size] = (*(CONVERT_T*)(msg + i));
		memcpy(&m[size], msg + i, CONVERT_T);
		++size;
	}
	//encrypt
	for (int i = 0; i < size; ++i)
	{
		en[i] = crypto.Encrypt(m[i]);
		printf("%c", en[i]);
	}
	printf("\n");

	int pos = 0;
	//decrypt
	for (int i = 0; i < size; ++i)
	{
		CRYPTO_T tmp = crypto.Decrypt(en[i]);
		pos = i * CONVERT_T;
		memcpy(&after[pos], &tmp, CONVERT_T);
	}
	//after[pos] = '\0';
	printf("%s\n", after);
#else
	const int max_buffer = 100;

	char msg[max_buffer] = "AB황현기ab";
	char en[max_buffer] = "";
	char after[max_buffer] = "";
	int size = (int)strlen(msg);
	int ensize = 0, aftersize = 0;

	crypto.Encrypt(msg, size, en, ensize);
	crypto.Decrypt(en, ensize, after, aftersize);

	printf("CryptoRAS: %s\n", after);
	printf("\n");




	char en1[max_buffer] = "";
	char after1[max_buffer] = "";

	HisUtil::CCrypto::Encrypt((unsigned char*)msg, size, (unsigned char*)en1);
	HisUtil::CCrypto::Decrypt((unsigned char*)en1, size, (unsigned char*)after1);
	printf("Crypto : %s\n", after1);

	//0~255범위 변환 체크(정상 확인됨)
	for (int i = 0; i < 256; ++i)
	{
		unsigned char m1 = (unsigned char)i;
		unsigned char a1 = 0, b1 = 0;

		HisUtil::CCrypto::Encrypt((unsigned char*)&m1, 1, (unsigned char*)&a1);
		HisUtil::CCrypto::Decrypt((unsigned char*)&a1, 1, (unsigned char*)&b1);

		//여기에 하나라도 걸리면...안되지요.
		if (m1 != b1)
			printf("%d ", m1);

	}
	printf("\n");

#endif

	system("pause");
	return 0;
}
