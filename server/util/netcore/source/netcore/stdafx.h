// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#pragma warning(disable : 4996)	//_CRT_SECURE_NO_DEPRECATE	�����(strcpy --> strcpy_s)
#pragma warning(disable : 4099)	//warning LNK4099: 'vc90.pdb' PDB�� '../../../bin/netcore_d.lib' �Ǵ�

//#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <stdlib.h>
#include <winsock2.h>	//	-- Lib : Winmm.lib
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <process.h>    /* _beginthread, _endthread */
#include <sql.h>
#include <sqlext.h>

#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>

#include <dbghelp.h>	//dump ���ϻ���
#include <assert.h>

#include <time.h>		//_time64()




#include "../../../../../common/errorcode/ErrorCode.h"
#include "../../../../../common/errorcode/ErrorServer.h"

#include "../../../hisutil/hisutil_include.h"


#include "../../netcore/netcore_include.h"

#include "../../../../common/struct.h"
