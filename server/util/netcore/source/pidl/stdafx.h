// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma warning(disable : 4996)	//_CRT_SECURE_NO_DEPRECATE	�����(strcpy --> strcpy_s)


//#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <stdlib.h>
#include <winsock2.h>	//	-- Lib : Winmm.lib
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <sql.h>
#include <sqlext.h>
#include <comdef.h>
//#include <Mmsystem.h>	//timeGetTime() -- Lib : Winmm.lib
#include <dbghelp.h>	//dump ���ϻ���
#include <assert.h>
#include <time.h>
#include <string>
#include <locale.h>		//::setlocale()
#include <winnt.h>		//interlock�Լ�