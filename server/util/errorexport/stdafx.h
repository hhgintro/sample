// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h> //_kbhit(), _getch()

#include <locale.h>//_wsetlocale



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <Windows.h>
#include <string.h>
#include <map>
#include <vector>



#include "../hisutil/hisutil_define.h"

#include "../hisutil/math/math_define.h"
#include "../hisutil/time/time_define.h"
#include "../hisutil/module/Module.h"
#include "../hisutil/etc/string.h"
#include "../hisutil/etc/util.h"

#include "CommentOption.h"
#include "FileLoader.h"


//#ifdef _DEBUG
//	#pragma comment(lib, "../../bin/hisutil/hisutilx64_d.lib")
//#else
//	#pragma comment(lib, "../../bin/hisutil/hisutilx64.lib")
//#endif //_DEBUG
