// server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>

#include "../../../util/hisutil/iocp/SimpleIocp.h"

#define SERVER_PORT        3500

int _tmain(int argc, _TCHAR* argv[])
{
	HisUtil::CSimpleIocp iocp;
	if (FALSE == iocp.Begin(SERVER_PORT))
		return 0;

	while (1)
	{
		Sleep(1000);
	}

	return 0;
}
