#pragma once
/*
수정 : 2009.10.19
내용 : unicode로 변환이 가능하도록 적용
*/

//#include "../thread/Singleton.h"

//#include <string>
//#include "../pool/MemoryPool.h"
//#include "../pool/MemoryQueuePool.h"

//#include "../thread/Thread.h"
//#include "../pool/MemoryQueuePool.h"
//#include "../module/Module.h"

//#if defined _UNICODE
//#define TString std::wstring
////#define TString Proud::String
//#else
//#define TString std::string
////#define TString Proud::StringA
//#endif

namespace HisUtil {



	//color
	enum COLOR_ID
	{
		DEFAULT_ON_BLACK,	//검은바탕에 흰색(약간흐림)
		WHITE_ON_BLACK,		//검은바탕에 흰색
		RED_ON_BLACK,
		GREEN_ON_BLACK,
		YELLOW_ON_BLACK,
		BLUE_ON_BLACK,
		MAGENTA_ON_BLACK,	//분홍
		CYAN_ON_BLACK,		//하늘
		GRAY_ON_BLACK,		//회색
		BLACK_ON_GRAY,		//회색바탕에 검정
		BLACK_ON_WHITE,
		RED_ON_WHITE,
		GREEN_WHITE,
		YELLOW_ON_WHITE,
		BLUE_ON_WHITE,
		MAGENTA_ON_WHITE,
		CYAN_ON_WHITE,
		WHITE_ON_WHITE,
	};

	const int MAX_LOG_SIZE = 4096;
	const long MAX_LOG_FILE_SIZE = 2 * 1024000; //2M

	const int MAX_INDEX = 3;	//무조건 2이상으로 설정해야(권장 3이상) )
	const int INIT_POOL_COUNT = 1000;	//log를 기록할 pool의 초기값



	class CEventLog : public CThread, public CSingleton<CEventLog>
	{
		struct logParam {
			int console;	//console
			int file;		//file
			int debug;		//OutputDebugString
			int url;		//url
			int color;

			logParam() : console(0), file(0), debug(0), url(0), color(0) {}
		};

		struct _stLogString {
			TString m_msg;

			void Clear() { m_msg.clear(); }
		};


	private:

		int m_index;	//사용되는 m_poolLog 배열의 인텍스
		//Proud::CriticalSection m_cs;		//m_index를 관리한다.
		HisUtil::CCritSecBase m_cs;			//m_index를 관리한다.
		HisUtil::CCritSecBase m_csColor;	//console창 컬러출력 관리한다.
		//CMemoryQueuePool<int> m_poolLogIndex;
		CMemoryQueuePool<_stLogString> m_poolLog[MAX_INDEX];

		//Proud::String		szPath_
		TCHAR szPath_[MAX_PATH];
		TString szFileName_;

		//HANDLE hConsole_;//콘솔 handle


		FILE* fp_;
		WORD wLastDay_;
		WORD wLastHour_;

		TIME_T tickLogEvent_;//tick(ms)간격으로 파일에 로그를 기록한다.
		TIME_T timeLogEvent_;

		BOOL bEnableEventTime_;//이벤트 시간을 기록하지 유무

		BOOL bIsoffDuty_; //더이상 일하지 않는다.

		//xml 에 설정된 keyword만 로그 기록한다.
		CMemoryPool<std::string, logParam> mapLogKeyword_;

		//
		CModule m_module;


		//private:
	public:
		void Begin();
		void End();
		void Clear();

	private:

		//현재 pool index를 가져온다.
		//bNext : TRUE 이면 현재값을 리턴하고 다음을 가리키게 된다.
		int GetPoolIndex();
		int NextPoolIndex();

		//파일명을 외부에서 지정할 수 있도록 .h로 옮겨놓았다.
		TString& GetLogFileName();

		//로그를 기록할 새로운 파일을 만들까요?
		BOOL OnMakeNewFile(const SYSTEMTIME& Tm);

		//파일 크기
		long GetLogFileSize(TString& filename);


	public:
		CEventLog(void);//singleton 외부에서 생성을 막고자
	public:
		virtual ~CEventLog(void);

		BOOL LoadXmlLogKeyword(char* filename);
		void SetLogEventTick(TIME_T tick = TIME_MIN(1));//tick(ms)간격으로 파일에 로그를 기록한다.
		void SetLogEventTime(BOOL bEable);
		void LogEvent(char* keyword, TCHAR* pFormat, ...);
		void SetColor(WORD color);

		void OnWorkerThread(int index);//파일저정은 별도의 thread를 돌려 일정시간마다 기록한다.

	};

}//namespace HisUtil {

#define LOGEVENT HisUtil::CEventLog::Instance().LogEvent
//로그를 파일에 기록시간 간격을 설정할 수 있다.(default : 0)
#define SET_LOG_EVENT_TICK HisUtil::CEventLog::Instance().SetLogEventTick
//로그의 시간을 기록유무(default : 0)
#define ENABLE_LOG_EVENT_TIME HisUtil::CEventLog::Instance().SetLogEventTime
