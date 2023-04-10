#include "stdafx.h"
#include "eventlog.h"

#include <locale.h>		//::setlocale()

namespace HisUtil {

	CEventLog::CEventLog(void)
		: fp_(NULL)
	{
		//#include <locale.h>		//::setlocale()
		_tsetlocale(LC_ALL, _T("Korean"));//�ܼ�â�� �����ڵ� ���ڸ� ����ϱ� ����

		//::AllocConsole(); //�ָܼ�� �Ҵ�
		//hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);	//������ �ܼ��� �ڵ鰪�� ��´�.

		Begin();
		Clear();
	}

	CEventLog::~CEventLog(void)
	{
		End();
		::FreeConsole();
	}

	void CEventLog::Begin()
	{
		try
		{
			TCHAR logpath[MAX_PATH] = _T("");
			_stprintf_s(logpath, _T("%s\\Log\\"), m_module.GetPathName());
			//���� ���� : log ���� �Ʒ� server ������ ������� CreateDirectory()�� 2�� ȣ���Ͽ��� �Ѵ�.
			::CreateDirectory(logpath, 0);// Log/ ���� ����

			//m_module.GetConfigFileName(projectpath, _T("\\"), szPath_);
			//memset(szPath_, 0, sizeof(szPath_));
			_stprintf_s(szPath_, _T("%s%s"), logpath, m_module.GetAppName());
			::CreateDirectory(szPath_, 0);// Log/Server/ ���� ����

			GetLogFileName();

			//xml
			TCHAR xmlpath[MAX_PATH] = _T("");
			_stprintf_s(xmlpath, _T("%sconfig\\logConfig.xml"), m_module.GetPathName());
			char filename[MAX_PATH];
			HisUtil::CW2A(CP_ACP, xmlpath, filename, _countof(filename));
			if (FALSE == LoadXmlLogKeyword(filename))
			{
				printf_s("fail LoadXmlLogKeyword(%s)\n", filename);
				//_tprintf_s(_T("fail LoadXmlLogKeyword(%s)\n"), xmlpath);
			}



			for (int i = 0; i < MAX_INDEX; ++i)
				m_poolLog[i].Begin(INIT_POOL_COUNT);

			//m_poolLogIndex.Begin(MAX_INDEX);



			//SYSTEM_INFO SystemInfo;
			//GetSystemInfo(&SystemInfo);
			//log�� �ϳ��� thread���� ó���մϴ�.
			CThread::BeginThread(1);//SystemInfo.dwNumberOfProcessors);
		}
		catch (std::exception& src)
		{
			src;
		}
	}

	void CEventLog::End()
	{
		//Proud::CriticalSectionLock(m_cs, true);
		try
		{
			bIsoffDuty_ = TRUE;

			//���⿡���� �����̸��� �ٽ� �������� �ʰ�
			//������ ��ϵ� ������ ����Ѵ�.(��¥�� ������ ���翡..)
			_tfopen_s(&fp_, szFileName_.c_str(), _T("at"));
			if (NULL != fp_)
			{
				////HisUtil::LogUrl(URL_LOG_NORMAL, "HG_GRAY", " Log ����Ʈ ���� : %d", listLogs_.size())
				//for(LOGLIST_ITERATOR it = listLogs_.begin(); it != listLogs_.end(); ++it) {
				//	_ftprintf(fp_, (*it).c_str());
				//}
				//listLogs_.clear();
				int index = GetPoolIndex();
				_stLogString* pool = m_poolLog[index].Front();
				while (NULL != pool)
				{
					//_tprintf(_T("%s\n"), pool->m_msg.c_str());
					_ftprintf(fp_, pool->m_msg.c_str());
					m_poolLog[index].Pop();

					pool = m_poolLog[index].Front();
				}

				//fflush (fp_);
				fclose(fp_);
				fp_ = NULL;
			}

			for (int i = 0; i < MAX_INDEX; ++i)
				m_poolLog[i].End();

			//m_poolLogIndex.End();

			CThread::EndThread();
		}
		catch (std::exception& src)
		{
			src;
		}
	}

	void CEventLog::Clear()
	{
		m_index = 0;

		//memset(szPath_, 0, sizeof(szPath_));
		if (NULL != fp_)
		{
			fclose(fp_);
			fp_ = NULL;
		}

		wLastDay_ = 0;
		wLastHour_ = 0;

		tickLogEvent_ = TIME_SEC(1);	// default time
		timeLogEvent_ = 0;

		bEnableEventTime_ = FALSE;

		bIsoffDuty_ = FALSE;

		//listLogs_.clear();
		for (int i = 0; i < MAX_INDEX; ++i)
			m_poolLog[i].Clear();
	}

	//bNext : TRUE �̸� ���簪�� �����ϰ� ������ ����Ű�� �ȴ�.
	int CEventLog::GetPoolIndex()
	{
		//Proud::CriticalSectionLock(m_cs, true);
		AUTO_LOCK(m_cs);

		return m_index; //���簪
		//return *m_poolLogIndex.Front();
	}
	int CEventLog::NextPoolIndex()
	{
		//Proud::CriticalSectionLock(m_cs, true);
		AUTO_LOCK(m_cs);

		int index = m_index;
		m_index = (m_index + 1) % MAX_INDEX;//����� pool�� �������� ������ �ش�.
		return index;//���簪
	}


	//���ϸ��� �ܺο��� ������ �� �ֵ��� .h�� �Űܳ��Ҵ�.
	TString& CEventLog::GetLogFileName()
	{
		SYSTEMTIME Tm;
		GetLocalTime(&Tm);

		if (FALSE == OnMakeNewFile(Tm))
			return szFileName_;

		TCHAR filename[MAX_PATH] = _T("");
		_stprintf_s(filename, MAX_PATH, _T("%s\\LogEvent%04d%02d%02d %02dh%02dm%02ds.log"), szPath_, Tm.wYear, Tm.wMonth, Tm.wDay, Tm.wHour, Tm.wMinute, Tm.wSecond);

		return szFileName_ = filename;
	}


	//�α׸� ����� ���ο� ������ ������?
	BOOL CEventLog::OnMakeNewFile(const SYSTEMTIME& Tm)
	{
		//�����ִ� ũ��.
		if (MAX_LOG_FILE_SIZE < GetLogFileSize(szFileName_))
			return TRUE;

		if (wLastDay_ == Tm.wDay && wLastHour_ == Tm.wHour)//�ð��� �α� ���
			return FALSE;//don't

		wLastDay_ = Tm.wDay;
		wLastHour_ = Tm.wHour;
		return TRUE;//make new file
	}

	//���� ũ��
	long CEventLog::GetLogFileSize(TString& filename)
	{
		long file_size = 0;
		FILE *fp = NULL;
		_tfopen_s(&fp, filename.c_str(), _T("r"));
		if (fp == NULL)
			return -1;

		fseek(fp, 0l, SEEK_END);    // �������� ��ġ�� ������ �ű��
		file_size = ftell(fp);                // �������� ��ġ�� ����
		fclose(fp);
		return file_size;
	}

	void CEventLog::SetLogEventTick(TIME_T tick)
	{
		//AUTO_LOCK(csLog_);//CThreadSync Sync

		tickLogEvent_ = tick;
	}

	void CEventLog::SetLogEventTime(BOOL bEable)
	{
		bEnableEventTime_ = bEable;
	}

	void CEventLog::LogEvent(char* keyword, TCHAR* pFormat, ...)
	{
		//~~~
		//return;

		TCHAR szLog[MAX_LOG_SIZE] = _T("");
		TCHAR szMsg[MAX_LOG_SIZE] = _T("");

		if (MAX_LOG_SIZE <= _tcslen(pFormat))
			return;

		//��� ��ȣ
		if (FALSE == m_module.CheckValid())
			return;


		//try
		{
			//Proud::CriticalSectionLock(m_cs, true);

			if (TRUE == bIsoffDuty_)
				return;

			logParam* par = mapLogKeyword_.Find(keyword);
			if (NULL == par)
			{
				//printf_s("*** you need to check key(%s) on logConfig.xml ***\n", keyword);
				return;
			}

			va_list	pArg;
			va_start(pArg, pFormat);
			_vstprintf_s(szLog, MAX_LOG_SIZE, pFormat, pArg);
			va_end(pArg);



			SYSTEMTIME Tm;
			GetLocalTime(&Tm);

			//�α׿� �ð��� �������� �ʴ´�.(�̹� szLog�� ���Ե� ����϶�)
			if(TRUE == bEnableEventTime_)
				_stprintf_s(szMsg, MAX_LOG_SIZE, _T("[%02d:%02d:%02d.%03d]  %s\n"), Tm.wHour, Tm.wMinute, Tm.wSecond, Tm.wMilliseconds, szLog);
			else
				_stprintf_s(szMsg, MAX_LOG_SIZE, _T("%s\n"), szLog);


			//�ܼ�â
			if (par->console)
			{
				AUTO_LOCK(m_csColor);//���� �����Ѵ�� �� �����±���.

				SetColor(par->color);
				_tprintf(szMsg);
				SetColor(DEFAULT_ON_BLACK);//�ʱ�ȭ(black)
			}

			//Debug string
			if (par->debug)
				OutputDebugString(szMsg);

			//file
			if (par->file)
			{
				int index = GetPoolIndex();
				_stLogString* log = m_poolLog[index].Create();
				log->Clear();
				log->m_msg = szMsg;
				m_poolLog[index].Push(log);
			}
		}
		//catch (std::exception& src)
		//{
		//	printf("exception : %s\n", src.what());
		//}
	}


	// ���Ӽ��� ������
	void CEventLog::OnWorkerThread(int index)
	{
		try
		{
			while (TRUE == IsRunning())
			{
				Sleep(1);

				if (timeLogEvent_ <= GetTickCount64())
				{
					//Proud::CriticalSectionLock(m_cs, true);
					timeLogEvent_ = GetTickCount64() + tickLogEvent_;


					//if(listLogs_.size() <= 0)
					//int index = GetPoolIndex();
					int index = NextPoolIndex();//����� pool�� �������� �����ϰ� ���簪�� �޾ƿ´�.
					_stLogString* log = m_poolLog[index].Front();
					if (NULL == log)
						continue;
					//NextPoolIndex();//����� pool�� �������� ������ �ش�.


					TString& filename = GetLogFileName();
					_tfopen_s(&fp_, filename.c_str(), _T("at"));
					if (NULL != fp_)
					{
						//for(LOGLIST_ITERATOR it = listLogs_.begin(); it != listLogs_.end(); ++it)
						//	_ftprintf(fp_, (*it).c_str());

						//listLogs_.clear();
						while (NULL != log)
						{
							//_tprintf(_T("%s\n"), pool->m_msg.c_str());
							_ftprintf(fp_, log->m_msg.c_str());
							log->Clear();

							m_poolLog[index].Pop();
							log = m_poolLog[index].Front();
						}

						//fflush (fp_);
						fclose(fp_);
						fp_ = NULL;
					}
				}//..if(timeLogEvent_ <= GetTickCount64())
			}//..while(TRUE == IsRunning())

			//�׽�Ʈ��(Delay�� �߻��ϱ� ����)
			//printf("thread finished\n");
			//Sleep(TIME_SEC(10));
		}
		catch (std::exception& src)
		{
			src;
		}
	}

	BOOL CEventLog::LoadXmlLogKeyword(char* filename)
	{
		//�缳���Ҷ� �����Ѵ�.
		mapLogKeyword_.Clear();

		///* xml �׽�Ʈ
		TiXmlDocument doc;
		if (false == doc.LoadFile(filename))
		{
			//bool result = doc.LoadFile(filename);
			return FALSE;
		}
		//XmlTest( "Entity with one digit.", result, true )

		TiXmlElement* root = doc.FirstChildElement("Log");
		if (root)
		{
			TiXmlElement* elem = doc.FirstChildElement()->FirstChildElement();
			while (elem)
			{
				logParam* par = mapLogKeyword_.Create();
				par->console = atoi(elem->Attribute("console"));
				par->file = atoi(elem->Attribute("file"));
				par->debug = atoi(elem->Attribute("debug"));
				par->color = atoi(elem->Attribute("color"));

				//printf("%s console=%s file=%s dubug=%s color=%s\n"
				//	, elem->Value()
				//	, elem->Attribute( "console" )
				//	, elem->Attribute( "file" )
				//	, elem->Attribute( "debug" )
				//	, elem->Attribute( "color" ))

				mapLogKeyword_.Insert(std::string(elem->Value()), par);
				elem = elem->NextSiblingElement();
			}
		}
		return TRUE;
	}

	void CEventLog::SetColor(WORD color)
	{
		WORD attribute = 0;

		switch (color)
		{
		case DEFAULT_ON_BLACK:		// White on Black
			attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case WHITE_ON_BLACK:		// White on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case RED_ON_BLACK:			// Red on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_RED;
			break;
		case GREEN_ON_BLACK:		// Green on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
			break;
		case YELLOW_ON_BLACK:		// Yellow on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
			break;
		case BLUE_ON_BLACK:			// Blue on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
			break;
		case MAGENTA_ON_BLACK:		// Magenta on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
			break;
		case CYAN_ON_BLACK:			// Cyan on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case GRAY_ON_BLACK:			// Gray on Black
			attribute = FOREGROUND_INTENSITY;
			break;
		case BLACK_ON_GRAY:			// Black on Gray
			attribute = BACKGROUND_INTENSITY | BACKGROUND_INTENSITY;
			break;
		case BLACK_ON_WHITE:        // Black on White
			attribute = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
			break;
		case RED_ON_WHITE:			// Red on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED;
			break;
		case GREEN_WHITE:			// Green on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN;
			break;
		case YELLOW_ON_WHITE:		// Yellow on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
			break;
		case BLUE_ON_WHITE:			// Blue on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE;
			break;
		case MAGENTA_ON_WHITE:		// Magenta on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE;
			break;
		case CYAN_ON_WHITE:			// Cyan on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case WHITE_ON_WHITE:		// White on White
			attribute = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		default:					// White on Black
			attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute);
	}

}//namespace HisUtil {
