// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <windows.h>
#include <string>

#include "../../tinyxml/tinyxml.h"

#include "../../hisutil/hisutil_define.h"

#include "../../hisutil/etc/string.h"
#include "../../hisutil/time/time_define.h"
#include "../../hisutil/math/math_define.h"
#include "../../hisutil/module/module.h"
#include "../../hisutil/thread/HisCritSec.h"
#include "../../hisutil/thread/Thread.h"
#include "../../hisutil/thread/Singleton.h"
#include "../../hisutil/pool/MemoryPool.h"
#include "../../hisutil/pool/MemoryQueuePool.h"
#include "../../hisutil/log/eventlog.h"