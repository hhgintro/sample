// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#if !defined WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif


// TODO: reference additional headers your program requires here
#include <atlbase.h>
#include <Windows.h>


#include "../../../common/errorcode/ErrorServer.h"
#include "../../../common/errorcode/ErrorCode.h"

#include "../tinyxml/tinyxml.h"

#include "hisutil_include.h"



//
//#ifdef _DEBUG
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2010\\Debug\\ProudNetCommon.lib")
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2010\\Debug\\ProudNetServer.lib")
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2010\\Debug\\ProudNetClient.lib")
//#else
//
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2012\\Release\\ProudNetCommon.lib")
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2012\\Release\\ProudNetServer.lib")
//#pragma comment(lib, "..\\ProudNet\\lib\\x64\\VS2012\\Release\\ProudNetClient.lib")
//#endif //_DEBUG
