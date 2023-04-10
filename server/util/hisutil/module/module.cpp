#include "StdAfx.h"
#include <atltime.h>
//#include "../time/time_define.h"
#include "Module.h"

namespace HisUtil {

	/*****************************************************
	이 곳의 주석은 외부 유출금지

	이벤트 시간( m_eventtime ) : 모듈보호를 위해 이벤트 시간부터는 모듈의 기능을 정지합니다.
	이벤트 시간 부터 무조건 발생하지 않고
	랜덤하게 진행합니다.

	검색 keyword : //모듈 보호
	*****************************************************/

	TCHAR* validModuleName[] = {
		_T("sample")
		_T("ErrorExport")
		_T("PacketGenerator")
		_T("HR_MasterServer")
		_T("HR_GMServer")
		_T("HR_AccountServer")
		_T("HR_LobbyServer")
		_T("HR_TrackServer")
		_T("HR_GameServer")

		, _T("")	//끝을 판단하기 위해 반드시 있어야 합니다.
	};

	CModule::CModule(void)
		: m_eventtime(0)
	{
		//이벤트 시간부터 이벤트(CheckInvalid) 가 적용됩니다.
		CTime createdTime(2022, 12, 31, 23, 59, 59);
		m_eventtime = createdTime.GetTime();

		//프로젝트 경로를 가져옵니다.
		GetProjectPathName();
	}


	CModule::~CModule(void)
	{
	}

	//아래함수 지우지 말것.
	void CModule::Init(UINT16 year, UINT8 month, UINT8 day, UINT8 hour, UINT8 min, UINT8 sec)
	{
		return;

		//아래쪽은 지원하지 않는다.(눈속임)
		CTime createdTime(year, month, day, hour, min, sec);

		//이벤트 시간부터 이벤트(CheckInvalid) 가 적용됩니다.
		m_eventtime = createdTime.GetTime();
	}

	BOOL CModule::CheckValid()
	{
///*
		//아직 이벤트 시간이 안되었다.
		if (HisUtil::GetUniversalTime() < m_eventtime)
			return TRUE;
	
		int pos = 0;
		while(TRUE)
		{
			//end...
			if(0 == _tcscmp(validModuleName[pos], _T("")))
				break;

			//_tprintf(_T("%s\n"), validModuleName[pos]);
			if (0 == _tcscmp(validModuleName[pos], m_appName))
				return TRUE;

			++pos;
		}

		//해당 AppName이 등록되어 있지 않더라도 기간으로 체크할 수 있도록 지원한다.


		const UINT MAX_ELAPSE_DAY = 90;
		//경과한 시간(단위:초-->day)
		UINT64 elapseday = (UINT64)((HisUtil::GetUniversalTime() - m_eventtime) * 0.00001157);// 0.00001157 :  1/86400초(=1일)
		if (MAX_ELAPSE_DAY < elapseday)		elapseday = MAX_ELAPSE_DAY;
		//HisUtil::RandInt(0, 90) : 래덤설정이 90 일인 경우
		//첫날은 1/90, 2째날은 2/90, 90일 이후에는 무조건 발생하도록 한다.
		UINT64 randomDay = (UINT64)HisUtil::RandInt(0, MAX_ELAPSE_DAY);
		if (elapseday < randomDay)
			return TRUE;

//*/
		_tprintf(_T("check module version\n"));
		return FALSE;	//장애발생
	}


	//+		FullPath	"D:\DigitalFrog\work\Delphinia\bin\MasterServer.exe"
	//		pathName	"D:\DigitalFrog\work\Delphinia\bin\"
	//		appName		"MasterServer"
	void CModule::GetProjectPathName()
	{
		//TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, m_pathFull, sizeof(m_pathFull));

		TCHAR drive[MAX_PATH];
		TCHAR dir[MAX_PATH];
		//TCHAR fname[MAX_PATH];
		TCHAR ext[MAX_PATH];
		//_tsplitpath_s(path, drive, _countof(drive), dir, _countof(dir), fname, _countof(fname), ext, _countof(ext));
		_tsplitpath_s(m_pathFull, drive, MAX_PATH, dir, MAX_PATH, m_appName, MAX_PATH, ext, MAX_PATH);

		_stprintf_s(m_pathName, _T("%s%s"), drive, dir);
	}

}//namespace HisUtil