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
#include <vector>

#include <iostream>
#include <string>


#include "../../../common/errorcode/ErrorCode.h"

#include "../../util/tinyxml/tinyxml.h"

#include "../../util/hisutil/hisutil_define.h"

#include "../../util/hisutil/etc/string.h"

#include "../../util/hisutil/time/time_define.h"
#include "../../util/hisutil/math/math_define.h"

#include "../../util/hisutil/module/module.h"

#include "../../util/hisutil/thread/HisCritSec.h"
#include "../../util/hisutil/thread/Thread.h"
#include "../../util/hisutil/thread/Singleton.h"

#include "../../util/hisutil/pool/MemoryPool.inl"
#include "../../util/hisutil/pool/MemoryQueuePool.inl"

#include "../../util/hisutil/eventlog/eventlog.h"

#include "../../util/hisutil/db/db_define.h"
#include "../../util/hisutil/db/db_define.h"
//#include "../../util/hisutil/db/ado.h"
#include "../../util/hisutil/db/SPBase.h"
#include "../../util/hisutil/db/BaseDBManager.h"

#include "sp_mysql.h"
#include "sp_mssql.h"