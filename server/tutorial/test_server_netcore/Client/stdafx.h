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
#include <ws2tcpip.h>	// inet_ntop
#include <process.h>    /* _beginthread, _endthread */
#include <sql.h>
#include <sqlext.h>

#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>

#include <dbghelp.h>	//dump ���ϻ���
#include <assert.h>

#include "../../../../common/errorcode/ErrorCode.h"
#include "../../../../common/errorcode/ErrorServer.h"

#include "../../../util/tinyxml/tinyxml.h"

#include "../../../util/hisutil/hisutil_define.h"

#include "../../../util/hisutil/etc/string.h"
#include "../../../util/hisutil/etc/net.h"

#include "../../../util/hisutil/math/math_define.h"
#include "../../../util/hisutil/time/time_define.h"
#include "../../../util/hisutil/module/module.h"

#include "../../../util/hisutil/thread/HisCritSec.h"
#include "../../../util/hisutil/thread/Thread.h"
#include "../../../util/hisutil/thread/Singleton.h"

#include "../../../util/hisutil/msg/msg.h"

#include "../../../util/hisutil/pool/MemoryPool.inl"
#include "../../../util/hisutil/pool/MemoryQueuePool.inl"

#include "../../../util/hisutil/eventlog/eventlog.h"


#include "../../../util/hisutil/crypt/crypto.h"

#include "../../../util/netcore/netcore/netcore_include.h"



#include "../../../common/type.h"
#include "../../../common/struct.h"


#include "./GameClient.h"

#include "./clientworld.h"


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "Winmm.lib")

//
//#ifdef _DEBUG
//#	pragma comment(lib, "../../../bin/netcore_d.lib")
//#else
//#	pragma comment(lib, "../../../bin/netcore.lib")
//#endif //_DEBUG
//
////#pragma comment(lib, "../../../bin/Lua.lib")
//
