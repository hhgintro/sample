// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//
#include <winsock2.h>	//	-- Lib : Ws2_32.lib, Winmm.lib (windows.h보다 먼저선언해야 "재정의 오류" 없다)
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <ws2tcpip.h>	// inet_ntop

#include <windows.h>
//#include <signal.h>

#include "../../../../common/errorcode/ErrorCode.h"
#include "../../../../common/errorcode/ErrorServer.h"

#include "../../../util/tinyxml/tinyxml.h"

#include "../../../util/hisutil/hisutil_include.h"
//
//#include "../../../util/hisutil/etc/string.h"
//#include "../../../util/hisutil/file/ParamBase.h"
//
//#include "../../../util/hisutil/math/math_define.h"
//#include "../../../util/hisutil/time/time_define.h"
//#include "../../../util/hisutil/module/module.h"
//#include "../../../util/hisutil/minidump/CrashHandler.h"
//#include "../../../util/hisutil/db/db_define.h"
//
//#include "../../../util/hisutil/service/ServiceRegister.h"
//
//#include "../../../util/hisutil/thread/HisCritSec.h"
//#include "../../../util/hisutil/thread/Thread.h"
//#include "../../../util/hisutil/thread/Singleton.h"
//
//
//#include "../../../util/hisutil/msg/msg.h"
//
//#include "../../../util/hisutil/pool/MemoryPool.h"
//#include "../../../util/hisutil/pool/MemoryQueuePool.h"
//
//#include "../../../util/hisutil/log/eventlog.h"
//
//
//#include "../../../util/hisutil/crypt/crypto.h"
//#include "../../../util/hisutil/file/IniLoader.h"

#include "../../../util/netcore/netcore/netcore_include.h"


#include "../../../common/type.h"
#include "../../../common/struct.h"

#include "../common/struct.h"

#include "../pidl/pidl/M2_Protocol.h"
#include "../pidl/pidl/M2_Structure.h"
#include "../pidl/pidl/M2_RecvPacket.h"
#include "../pidl/pidl/M2_SendPacket.h"



#include "Param.h"
#include "Server.h"
#include "world.h"


#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Mswsock.lib")
