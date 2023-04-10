#pragma once

//#include <Windows.h>
#include <time.h>

// ** 이전합니다. **
//hisutil_define.h 로 이동하였습니다.
////시간관련
//#define TIME_S_SEC(n)	(n)				//(단위:s) n 초
//#define TIME_S_MIN(n)	(n*60)			//(단위:s) n 분
//#define TIME_S_HOUR(n)	(n*3600)		//(단위:s) n 시간
//#define TIME_S_DAY(n)	(n*86400)		//(단위:s) n 일(INT32일 경우 최대 24일까지만 가능)
//#define TIME_S_YEAR(n)	(n*‭31536000‬)	//(단위:s) n 년
//
//
//#define TIME_MSEC(n)	(n)				//(단위:ms) ms
//#define TIME_SEC(n)		(n*1000)		//(단위:ms) n 초
//#define TIME_MIN(n)		(n*60000)		//(단위:ms) n 분
//#define TIME_HOUR(n)	(n*3600000)		//(단위:ms) n 시간
//#define TIME_DAY(n)		(n*86400000)	//(단위:ms) n 일(INT32일 경우 최대 24일까지만 가능)
//#define TIME_YEAR(n)	(n*‭31536000‬000)	//(단위:ms) n 년
//
//typedef	UINT64			TIME_T;		//단위:ms, GetTickCount64() 로 체크합니다.
//typedef	UINT64			TIME_SEC_T;	//단위:s, GetUniversalTime()로 체크합니다.(DB에서 가져오는 시간을 관리하기 위해)


namespace HisUtil {


	struct _stTime
	{
		//2013-02-21 17:48:49
		UINT16 m_year;
		UINT8 m_month;
		UINT8 m_day;
		UINT8 m_hour;
		UINT8 m_min;
		UINT8 m_sec;

		_stTime()
			: m_year(0), m_month(0), m_day(0), m_hour(0), m_min(0), m_sec(0) {}
		_stTime(UINT16 year, UINT8 month, UINT8 day, UINT8 hour, UINT8 min, UINT8 sec)
			: m_year(year), m_month(month), m_day(day), m_hour(hour), m_min(min), m_sec(sec) {}

		void clear()
		{
			m_year = 0, m_month = 0, m_day = 0, m_hour = 0, m_min = 0, m_sec = 0;
		}
	};


	/*일정시간동안 변수가 유효하다고 설정합니다.*/
	/*user서버에서 retemoDB가 유효한지에서 판단합니다.*/
	template<class T>
	struct _stTimeValidVariable
	{
		T m_val;
		TIME_T m_msec;//(단위:ms)

		void Set(T val, TIME_T msec) { m_val = val; m_msec = msec; }

		//	m_msec가 0 인 경우 TRUE (무한대 설정이 필요)
		//	cur < m_msec 인 경우 TRUE
		BOOL IsValid(TIME_T cur) { return (0 == m_msec || cur < m_msec); }

		_stTimeValidVariable& operator = (const _stTimeValidVariable& rhs)
		{
			m_val = rhs.m_val;
			m_msec = rhs.m_msec;
			return *this;
		}
	};
	//namespace Proud{
	//	template<class T>
	//	inline CMessage& operator>>(Proud::CMessage &msg, _stTimeValidVariable<T> &b)
	//	{
	//		msg >> b.m_retmoeS
	//			>> b.m_retmoeX
	//			;
	//		return msg;
	//	}
	//	template<class T>
	//	inline CMessage& operator<<(Proud::CMessage &msg, const _stTimeValidVariable<T> &b)
	//	{
	//		msg << b.m_retmoeS
	//			<< b.m_retmoeX
	//			;
	//		return msg;
	//	}
	//	template<class T>
	//	inline void AppendTextOut(String &a, _stTimeValidVariable<T> &b) {}
	//};


	inline TIME_T GetUniversalTime()
	{
		// 세계 표준 시간(UTC) 반환
		__time64_t now;
		return _time64(&now);
		//================================================
		// CTime / _time64 는 세계 표준 시간을 리턴한다.
		// 사용에 따라
		// 로컬이면 _localtime64_s()
		// UTCdlaus _gmtime64_s() 로 확인할 수 있다.
		//================================================

		//struct tm t;
		//char buff[100];

		//// UTC를 국가 시간으로 변환
		//_localtime64_s(&t, &now);
		//// 1970년 1월 1일 0시를 기준.
		//sprintf_s(buff, _countof(buff), "현재 국가 시간 : %d/%02d/%02d %02d:%02d:%02d",
		//	t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		//	t.tm_hour, t.tm_min, t.tm_sec);
		//puts(buff);


		//_gmtime64_s(&t, &now);
		//sprintf_s(buff, _countof(buff), "세계 표준 시간 : %d/%02d/%02d %02d:%02d:%02d",
		//	t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		//	t.tm_hour, t.tm_min, t.tm_sec);
		//puts(buff);
	}

	//length : buff의 _countof(buff)을 입력합니다.(주의 : sizeof(buff)는 다른영역을 침범할 수 있습니다.)
	inline TCHAR* GetLocalTime(TCHAR* buff, int length)
	{
		struct tm t;

		// UTC를 국가 시간으로 변환
		__time64_t now = GetUniversalTime();
		_localtime64_s(&t, &now);

		// 1970년 1월 1일 0시를 기준.
		//sprintf_s(buff, _countof(buff), "현재 국가 시간 : %d/%02d/%02d %02d:%02d:%02d",
		_stprintf_s(buff, length, _T("현재 국가 시간 : %d/%02d/%02d %02d:%02d:%02d"),
			t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
			t.tm_hour, t.tm_min, t.tm_sec);
		//puts(buff);

		return buff;
	}

	//length : buff의 _countof(buff)을 입력합니다.(주의 : sizeof(buff)는 다른영역을 침범할 수 있습니다.)
	inline TCHAR* GetUtcTime(TCHAR* buff, int length)
	{
		struct tm t;

		// UTC를 국가 시간으로 변환
		__time64_t now = GetUniversalTime();
		_gmtime64_s(&t, &now);

		// 1970년 1월 1일 0시를 기준.
		//sprintf_s(buff, _countof(buff), "세계 표준 시간 : %d/%02d/%02d %02d:%02d:%02d",
		_stprintf_s(buff, length, _T("세계 표준 시간 : %d/%02d/%02d %02d:%02d:%02d"),
			t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
			t.tm_hour, t.tm_min, t.tm_sec);
		//puts(buff);

		return buff;
	}

	//s64Sec : 이전에 저장된 Tick(ms)
	//s64CheckTick : 체크 주기(ms)
	//return : 체크주기를 오버한 경우 현재시간을 갱신후 true리턴, 아니면 fales
	inline BOOL TimerChecker64(TIME_T& s64Sec, const TIME_T s64CheckTick)
	{
		TIME_T current = ::GetTickCount64();
		if (current < s64Sec + s64CheckTick)
			return FALSE;

		s64Sec = current;
		return TRUE;
	}

	//========================================================
	//정밀한 시간 측정을 목적으로 사용합니다.
	//#include <windows.h>
	inline double TimeCounter()
	{
		LARGE_INTEGER start;
		QueryPerformanceCounter(&start);
		return (double)start.QuadPart;
	}

	//start : 체크시작시간( TimerCounter()의 값 )
	//unit : 단위 ( 1.0:초, 1*10^3:ms 1*10^6:us 1*10^9:ns )
	inline double TimeCounterChecker(double start, double unit = 1.0)
	{
		static LARGE_INTEGER freq;

		static bool bIsCheckecFrequncy = false;
		if (false == bIsCheckecFrequncy)
		{
			if (0 == QueryPerformanceFrequency(&freq))
				return 0;
			if (0 == freq.QuadPart)
				return 0;

			bIsCheckecFrequncy = true;
		}

		double end = TimeCounter();

		//소요시간
		return (end - start) * unit / freq.QuadPart;
	}
	//========================================================


	//문자를 시간으로 변환
	inline time_t Time4String(const TCHAR* date)
	{
		//예시
		//CTime next(HisUtil::TimeForString(_T("2022-01-25")));
		//CTime next += CTimeSpan(1, 0, 0, 0); // +1일

		//date 형식 : _T("%4d-%2d-%2d %2d:%2d:%2d")
		int year = 0, month = 0, day = 0, hour = 0, minute = 0, sec = 0;
		_stscanf_s(date, _T("%04d-%02d-%02d %02d:%02d:%02d"), &year, &month, &day, &hour, &minute, &sec);

		struct tm t;
		memset(&t, 0, sizeof(t));
		t.tm_year	= year - 1900;
		t.tm_mon	= month - 1;
		t.tm_mday	= day;
		return mktime(&t);
	}

};//..namespace HisUtil {
