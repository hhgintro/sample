// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include <windows.h>
#include <atlbase.h>
#include <memory>
#include <mmsystem.h>
#include <dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Winmm.lib")

#include "../hisutil/thread/HisCritSec.h"
#include "../hisutil/thread/Singleton.h"

#include "../hisutil/pool/MemoryPool.inl"
#include "../hisutil/pool/MemoryQueuePool.inl"
