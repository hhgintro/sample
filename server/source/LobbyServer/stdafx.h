// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//
#include <winsock2.h>	//	-- Lib : Ws2_32.lib, Winmm.lib (windows.h���� ���������ؾ� "������ ����" ����)
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <ws2tcpip.h>	// inet_ntop

#include <windows.h>
//#include <signal.h>

#include "../../../common/errorcode/ErrorCode.h"
#include "../../../common/errorcode/ErrorServer.h"

#include "../../util/tinyxml/tinyxml.h"

#include "../../util/hisutil/hisutil_include.h"


#include "../../util/netcore/netcore/netcore_include.h"


#include "../../common/type.h"
#include "../../common/struct.h"

#include "./Param.h"
#include "./Server.h"
#include "./MasterClient.h"
#include "./world.h"


#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Mswsock.lib")



#ifdef _DEBUG
#	pragma comment(lib, "../../bin/hisutil/hisutilDebugx64.lib")
#	pragma comment(lib, "../../bin/netcore/netcoreDebugx64.lib")
#	pragma comment(lib, "../../bin/tinyxml/tinyxmlDebugx64.lib")
#else
#	pragma comment(lib, "../../bin/hisutil/hisutilReleasex64.lib")
#	pragma comment(lib, "../../bin/netcore/netcoreReleasex64.lib")
#	pragma comment(lib, "../../bin/tinyxml/tinyxmlReleasex64.lib")
#endif //_DEBUG
