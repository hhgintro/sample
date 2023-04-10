// test_crypt_ras.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


#include <vector>
#include <windows.h>

//typedef unsigned __int64 		CRYPTO_T;
typedef unsigned __int32 		CRYPTO_T;

bool isPrime(CRYPTO_T pr)
{
	CRYPTO_T j = (CRYPTO_T)sqrt(pr);
	for (CRYPTO_T i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return false;
	}
	return true;
}

void MakeFile(std::vector<CRYPTO_T>& buff, int fileindex, int BUFF_X, int BUFF_Y, int DIV_Y)
{
	char filename[256] = "";
	sprintf_s(filename, "%08d.txt", fileindex);

	FILE* pf;
	fopen_s(&pf, filename, "w");
	if (pf)
	{
		for (int y = 0; y < BUFF_Y; ++y)
		{
			for (int x = 0; x < BUFF_X; ++x)
			{
				int idx = x + (y*BUFF_X);
				if (buff.size() <= idx)
					goto ___finish;

				char tmp[1000] = "";
				sprintf_s(tmp, "0x%04x,", buff.at(idx));
				fwrite(tmp, strlen(tmp), 1, pf);

				COORD pos = { 0, 4 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("%s", filename);
			}
			char tmp[] = "\n";
			fwrite(tmp, strlen(tmp), 1, pf);
			if (0 == ((y + 1) % DIV_Y))
				fwrite(tmp, strlen(tmp), 1, pf);
		}
	}

	___finish:
	fclose(pf);
}

int main()
{
	//unsigned CRYPTO_T tmp1 = sqrt(9223372036854775807);
	//unsigned CRYPTO_T tmp2 = (unsigned CRYPTO_T)3037000499 * (unsigned CRYPTO_T)3037000499;

	printf("소수를 구하는 중입니다.\n");
	printf("닫지 마세요\n");

	const int BUFF_X = 10;
	const int BUFF_Y = 1000;
	const int DIV_Y = BUFF_Y / 100;//몇칸마다 띄울지

	int fileindex = 0;

	std::vector<CRYPTO_T> buff;
	buff.reserve(BUFF_X * BUFF_Y);

	//0x10000000 : 제곱하면 8byte(0x0100000000000000)이 되니깐 최소값으로 설정하고
	//0xB5000000 : 최대값은 아니지만 충분히 크다고 생각되는 값이므로(0x7FF9000000000000-충분히 큰양수)
	//for (unsigned CRYPTO_T i = 0x10000000; i < 0xB5000000; ++i)
	//for (unsigned CRYPTO_T i = 0x0100000000000000; i < 0xffffffffffffffff; ++i)
	//for (unsigned CRYPTO_T i = 2; i < 2000; ++i)

	for (CRYPTO_T i = 0x1000; i < 0xFFFF; ++i)
	{
		if (true == isPrime(i))
		{
			buff.push_back(i);

			COORD pos = { 0, 3 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("buffer size:%05d\n", buff.size());
			if (BUFF_X * BUFF_Y <= (int)buff.size())
			{
				MakeFile(buff, ++fileindex, BUFF_X, BUFF_Y, DIV_Y);
				buff.clear();
			}
		}
	}

	if (0 < buff.size())
	{
		MakeFile(buff, ++fileindex, BUFF_X, BUFF_Y, DIV_Y);
		buff.clear();
	}

	return 0;
}
