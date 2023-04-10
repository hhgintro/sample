#pragma once

namespace HisUtil {

	class CModule
	{
	public:
		CModule(void);
		~CModule(void);

		void Init(UINT16 year, UINT8 month, UINT8 day, UINT8 hour, UINT8 min, UINT8 sec);

		BOOL CheckValid();


		TCHAR* GetPathFull() { return m_pathFull; }
		//프로젝트 경로를 가져옵니다.
		TCHAR* GetPathName() { return m_pathName; }
		//실행파일명(.exe 는 제거됨)
		TCHAR* GetAppName() { return m_appName; }

		//이벤트 시작시간(테스트 목적임)
		TIME_SEC_T GetEventTime() { return m_eventtime; }

	private:
		void GetProjectPathName();


	private:
		TIME_SEC_T m_eventtime;	//이벤트시간(단위:s)

		TCHAR m_pathFull[MAX_PATH];
		TCHAR m_pathName[MAX_PATH];
		TCHAR m_appName[MAX_PATH];
	};

}//namespace HisUtil