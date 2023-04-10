#pragma once
/*
���� : 2009.10.19
���� : unicode�� ��ȯ�� �����ϵ��� ����
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
		DEFAULT_ON_BLACK,	//���������� ���(�ణ�帲)
		WHITE_ON_BLACK,		//���������� ���
		RED_ON_BLACK,
		GREEN_ON_BLACK,
		YELLOW_ON_BLACK,
		BLUE_ON_BLACK,
		MAGENTA_ON_BLACK,	//��ȫ
		CYAN_ON_BLACK,		//�ϴ�
		GRAY_ON_BLACK,		//ȸ��
		BLACK_ON_GRAY,		//ȸ�������� ����
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

	const int MAX_INDEX = 3;	//������ 2�̻����� �����ؾ�(���� 3�̻�) )
	const int INIT_POOL_COUNT = 1000;	//log�� ����� pool�� �ʱⰪ



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

		int m_index;	//���Ǵ� m_poolLog �迭�� ���ؽ�
		//Proud::CriticalSection m_cs;		//m_index�� �����Ѵ�.
		HisUtil::CCritSecBase m_cs;			//m_index�� �����Ѵ�.
		HisUtil::CCritSecBase m_csColor;	//consoleâ �÷���� �����Ѵ�.
		//CMemoryQueuePool<int> m_poolLogIndex;
		CMemoryQueuePool<_stLogString> m_poolLog[MAX_INDEX];

		//Proud::String		szPath_
		TCHAR szPath_[MAX_PATH];
		TString szFileName_;

		//HANDLE hConsole_;//�ܼ� handle


		FILE* fp_;
		WORD wLastDay_;
		WORD wLastHour_;

		TIME_T tickLogEvent_;//tick(ms)�������� ���Ͽ� �α׸� ����Ѵ�.
		TIME_T timeLogEvent_;

		BOOL bEnableEventTime_;//�̺�Ʈ �ð��� ������� ����

		BOOL bIsoffDuty_; //���̻� ������ �ʴ´�.

		//xml �� ������ keyword�� �α� ����Ѵ�.
		CMemoryPool<std::string, logParam> mapLogKeyword_;

		//
		CModule m_module;


		//private:
	public:
		void Begin();
		void End();
		void Clear();

	private:

		//���� pool index�� �����´�.
		//bNext : TRUE �̸� ���簪�� �����ϰ� ������ ����Ű�� �ȴ�.
		int GetPoolIndex();
		int NextPoolIndex();

		//���ϸ��� �ܺο��� ������ �� �ֵ��� .h�� �Űܳ��Ҵ�.
		TString& GetLogFileName();

		//�α׸� ����� ���ο� ������ ������?
		BOOL OnMakeNewFile(const SYSTEMTIME& Tm);

		//���� ũ��
		long GetLogFileSize(TString& filename);


	public:
		CEventLog(void);//singleton �ܺο��� ������ ������
	public:
		virtual ~CEventLog(void);

		BOOL LoadXmlLogKeyword(char* filename);
		void SetLogEventTick(TIME_T tick = TIME_MIN(1));//tick(ms)�������� ���Ͽ� �α׸� ����Ѵ�.
		void SetLogEventTime(BOOL bEable);
		void LogEvent(char* keyword, TCHAR* pFormat, ...);
		void SetColor(WORD color);

		void OnWorkerThread(int index);//���������� ������ thread�� ���� �����ð����� ����Ѵ�.

	};

}//namespace HisUtil {

#define LOGEVENT HisUtil::CEventLog::Instance().LogEvent
//�α׸� ���Ͽ� ��Ͻð� ������ ������ �� �ִ�.(default : 0)
#define SET_LOG_EVENT_TICK HisUtil::CEventLog::Instance().SetLogEventTick
//�α��� �ð��� �������(default : 0)
#define ENABLE_LOG_EVENT_TIME HisUtil::CEventLog::Instance().SetLogEventTime
