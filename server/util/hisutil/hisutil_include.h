#pragma once

//#include <atlbase.h>
#include <windows.h>
//#include <tchar.h>

#include <Tlhelp32.h> // KillProcess
#include <atlstr.h>	//ATL::CString

#include <wininet.h>	//HINTERNET( CHisFtp ) && "wininet.lib"



#include "hisutil_define.h"


#include "module/module.h"
#include "etc/string.h"
#include "etc/net.h"
#include "etc/directory.h"
#include "etc/util.h"
#include "db/db_define.h"
#include "file/ParamBase.h"
#include "cpu/CPU.h"

#include "math/math_define.h"
#include "time/time_define.h"
#include "minidump/CrashHandler.h"
#include "db/dbconnect.h"
#include "db/SPBase.h"

#include "service/Service.h"
#include "service/ServiceRegister.h"

#include "thread/HisCritSec.h"
#include "thread/HisMutex.h"
#include "thread/Thread.h"
#include "thread/Singleton.h"

#include "ftp/HisFtp.h"

#include "msg/msg.h"
#include "msg/msgpack.h"

#include "pool/MemoryPool.inl"
#include "pool/MemoryQueuePool.inl"
#include "pool/MemoryMultiSetPool.inl"
#include "pool/MemorySetPool.inl"

#include "db/BaseDBManager.h"

#include "eventlog/eventlog.h"

#include "utf8/ConvertUTF8.h"
#include "utf8/ConvertUtil.h"

#include "crypt/crypto.h"
#include "crypt/aes/Encrypt.h"