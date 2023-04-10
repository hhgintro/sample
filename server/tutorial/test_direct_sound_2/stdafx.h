// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>


// TODO: reference additional headers your program requires here

#include <windows.h>
#include <atlbase.h>
#include <memory>
#include <dsound.h>
//#include <afx.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Winmm.lib")


#include "../../util/hisutil/thread/HisCritSec.h"
#include "../../util/hisutil/thread/Singleton.h"

#include "../../util/hisutil/pool/MemoryPool.h"
#include "../../util/hisutil/pool/MemoryQueuePool.h"

