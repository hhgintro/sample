// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma warning(disable : 4996)	//_CRT_SECURE_NO_DEPRECATE	경고무시(strcpy --> strcpy_s)


//#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
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
#include <dbghelp.h>	//dump 파일생성
#include <assert.h>
#include <time.h>
#include <string>
#include <locale.h>		//::setlocale()
#include <winnt.h>		//interlock함수