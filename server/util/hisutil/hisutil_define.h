#pragma once

//#include <atlbase.h>
//#include <windows.h>

#define IN
#define OUT
#define INOUT


typedef	UINT64		TIME_T;		//단위:ms, GetTickCount64() 로 체크합니다.
typedef	UINT64		TIME_SEC_T;	//단위:s, GetUniversalTime()로 체크합니다.(DB에서 가져오는 시간을 관리하기 위해)

typedef UINT16		GAME_RESULT;



//시간관련
#define TIME_S_SEC(n)					(n)				//(단위:s) n 초
#define TIME_S_MIN(n)					(n*60)			//(단위:s) n 분
#define TIME_S_HOUR(n)					(n*3600)		//(단위:s) n 시간
#define TIME_S_DAY(n)					(n*86400)		//(단위:s) n 일(INT32일 경우 최대 24일까지만 가능)
#define TIME_S_YEAR(n)					(n*‭31536000‬)	//(단위:s) n 년


#define TIME_MSEC(n)					(n)				//(단위:ms) ms
#define TIME_SEC(n)						(n*1000)		//(단위:ms) n 초
#define TIME_MIN(n)						(n*60000)		//(단위:ms) n 분
#define TIME_HOUR(n)					(n*3600000)		//(단위:ms) n 시간
#define TIME_DAY(n)						(n*86400000)	//(단위:ms) n 일(INT32일 경우 최대 24일까지만 가능)
#define TIME_YEAR(n)					(n*‭31536000‬000)	//(단위:ms) n 년


#define ISNULL_WCHAR(p)					(((p).IsNull()) ? L"" : (p))
#define ISNULL_CHAR(p)					(((p).IsNull()) ? "" : (p))
#define ISNULL_VALUE(p)					(((p).IsNull()) ? 0 : (p))

//#define ISNULL_LUA_CHAR(p)			((NULL==(p)) ? "" : (p))

//비트연산
#define ADD_BIT_FLAG(state, value)		(state |= value)
#define SUB_BIT_FLAG(state, value)		(state ^= value)
#define CHECK_BIT_FLAG(state, value)	(value == (state & value))

#define SHIFT_L(y, x)					(y << x)
#define SHIFT_L_1(x)					SHIFT_L(1, (x-1))


#define DELETE_SAFE(p)					if(p) { delete p; p=NULL;}
#define DELETE_SAFE_ARRAY(p)			if(p) { delete [] p; p=NULL;}
#define FREE_SAFE(p)					if(p) { p.Free();}

//#define BOARDINDEX_TO_X(pos)			((pos) & 0x00FF)
//#define BOARDINDEX_TO_Y(pos)			(((pos) & 0xFF00) >> 8)
//#define XY_TO_BOARDINDEX(x,y)			((x & 0x00FF) | (y << 8))
#define BOARDINDEX_TO_X(pos)			((pos) & 0x0F)
#define BOARDINDEX_TO_Y(pos)			(((pos) & 0xF0) >> 4)
#define XY_TO_BOARDINDEX(x,y)			((x & 0x0F) | ((y) << 4))

#define MAKEINT64(a, b)					((((INT64)(a)) & 0xffffffff) << 32 | (((INT32)(b)) & 0xffffffff))


const int MAX_IP_LENGTH = 16;	//xxx.xxx.xxx.xxx

