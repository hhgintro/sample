// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#pragma warning(disable : 4996)	//_CRT_SECURE_NO_DEPRECATE	경고무시(strcpy --> strcpy_s)
#pragma warning(disable : 4099)	//warning LNK4099: 'vc90.pdb' PDB를 '../../../bin/netcore_d.lib' 또는

//#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <stdlib.h>
#include <winsock2.h>	//	-- Lib : Winmm.lib
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <process.h>    /* _beginthread, _endthread */
#include <sql.h>
#include <sqlext.h>

#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>

#include <dbghelp.h>	//dump 파일생성
#include <assert.h>

#include <time.h>		//_time64()




#include "../../../../../common/errorcode/ErrorCode.h"
#include "../../../../../common/errorcode/ErrorServer.h"

#include "../../../hisutil/hisutil_include.h"


#include "../../netcore/netcore_include.h"

#include "../../../../common/struct.h"
