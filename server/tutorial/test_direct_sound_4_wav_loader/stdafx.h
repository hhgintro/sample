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

#include "../../util/hisutil/pool/MemoryPool.inl"
#include "../../util/hisutil/pool/MemoryQueuePool.inl"

#include "../../util/hisound/sound/DispatchSound.h"
#include "../../util/hisound/sound/SoundCapture.h"

#include "./sound/DispatchCapture.h"

#ifdef DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "../../bin/hisound/hisoundDebugx64.lib")
	#else
		#pragma comment(lib, "../../bin/hisound/hisoundDebugx86.lib")
	#endif //.._WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "../../bin/hisound/hisoundReleasex64.lib")
	#else
		#pragma comment(lib, "../../bin/hisound/hisoundReleasex86.lib")
	#endif //.._WIN64
#endif //..DEEBUG

