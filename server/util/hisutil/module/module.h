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
		//������Ʈ ��θ� �����ɴϴ�.
		TCHAR* GetPathName() { return m_pathName; }
		//�������ϸ�(.exe �� ���ŵ�)
		TCHAR* GetAppName() { return m_appName; }

		//�̺�Ʈ ���۽ð�(�׽�Ʈ ������)
		TIME_SEC_T GetEventTime() { return m_eventtime; }

	private:
		void GetProjectPathName();


	private:
		TIME_SEC_T m_eventtime;	//�̺�Ʈ�ð�(����:s)

		TCHAR m_pathFull[MAX_PATH];
		TCHAR m_pathName[MAX_PATH];
		TCHAR m_appName[MAX_PATH];
	};

}//namespace HisUtil