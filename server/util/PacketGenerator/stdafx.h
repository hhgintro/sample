// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma warning(disable : 4996)	//_CRT_SECURE_NO_DEPRECATE	경고무시(strcpy --> strcpy_s)


//#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */

#include <string>

// STL
#include <list>			//std::list
#include <vector>
#include <map>
#include <queue>

#include <locale.h>
//#include "../../../common/define/type.h"
//#include "../../../common/define/common.h"

//#include "../../../common/HisUtil/HisUtil.h"
//#include "../../../common/HisUtil/Timer.h"
//#include "../../../common/HisUtil/unicode.h"

#include "../hisutil/hisutil_define.h"

#include "../hisutil/module/module.h"
#include "../hisutil/etc/string.h"
#include "../hisutil/math/math_define.h"
#include "../hisutil/thread/HisCritSec.h"
#include "../hisutil/thread/Singleton.h"
#include "../hisutil/time/time_define.h"

#include "../hisutil/thread/Thread.h"

#include "../hisutil/pool/MemoryPool.inl"
#include "../hisutil/pool/MemoryQueuePool.inl"
#include "../hisutil/eventlog/eventlog.h"

#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"


//#ifdef _DEBUG
//#	pragma comment(lib, "../../../bin/LibHisUtil_D.lib")
//#	pragma comment(lib, "../../../bin/tinyXml_D.lib")
//#else
//#	pragma comment(lib, "../../../bin/LibHisUtil.lib")
//#	pragma comment(lib, "../../../bin/tinyXml.lib")
//#endif //_DEBUG
