#pragma once

#include <Windows.h>
#include <process.h>	//_beginthreadex

#include <errno.h>
#include <vector>

//#include "..\\module\\ModuleManager.h"


namespace HisUtil {

	//INFINITE ���� �����ϸ� CEventSelect::OnWorkerThread()�� WaitForMultipleObjects���� hold���¶� ������� �ʴ´�.
	const DWORD END_THREAD_WAIT_TIME = TIME_SEC(3);	

	//template<class T>
	class CThread
	{
		//thread�� ���� ����
		struct stParam
		{
			stParam(CThread* object, int index)
			{
				m_object = object;
				m_index = index;
			}

			CThread* m_object;
			int m_index;
		};

	private:

		std::vector<HANDLE>	m_vecWorkerThread;
		HANDLE m_hStartEvent;
		HANDLE m_hDestoryEvent;
	
		//while���� ������ ���� �����ϱ� �ٶ��ϴ�.(Thread ����ó���� ���ؼ�)
		//while(TRUE == IsRunning()) {}
		BOOL m_bIsRunning;

		CModule m_module;

	public:

		CThread();
		virtual ~CThread();

		virtual BOOL BeginThread(int nThreadCount = 1);
		//virtual void KillThread();
		virtual void EndThread();

		virtual void OnThread(int index);
		static unsigned int CALLBACK _Thread(void* lpParam);

		BOOL IsRunning() { return m_bIsRunning;}

		//while���� ������ ���� �����ϱ� �ٶ��ϴ�.(Thread ����ó���� ���ؼ�)
		//while(TRUE == IsRunning()) {}
		virtual void OnWorkerThread(int index) = 0;
	};
};//..namespace HisUtil {
