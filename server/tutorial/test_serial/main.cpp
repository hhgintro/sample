// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SerialEx.h"

BYTE msg1[] = { 0xFE, 0xFE, 0x20, 0x00, 0x01 };
BYTE msg2[] = { 0xFE, 0xFE, 0x10, 0x00, 0x00 };

void test()
{

}
int main(int argc, char* argv[])
{
	test();

	int port = 3;
	if (argc >= 2)	port = atoi(argv[1]);

	CSerialEx serial;
	serial.Create(port, CBR_115200, 8, 0, 0);
	serial.Open();

	TCHAR buf[1024] = _T("");
	while (1)
	{
		Sleep(1);

		_fputts(_T("전송할 메시지를 입력하세요(q to quit) : \n"), stdout);
		_fgetts(buf, sizeof(buf), stdin);

		if (!_tcscmp(buf, _T("q\n")))
			break;

		//_tprintf(buf);
		serial.Write((LPSTR)msg1, sizeof(msg1));
		serial.Write((LPSTR)msg2, sizeof(msg2));
	}

	system("pause");
    return 0;
}

