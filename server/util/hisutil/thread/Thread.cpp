#include "stdafx.h"
#include "Thread.h"

namespace HisUtil {

	CThread::CThread()
		: m_hStartEvent(NULL), m_hDestoryEvent(NULL), m_bIsRunning(FALSE)
	{
	}

	CThread::~CThread()
	{
		//m_hStartEvent
		if(NULL == m_hStartEvent)
		{
			CloseHandle(m_hStartEvent);
			m_hStartEvent = NULL;
			//_tprintf(_T("CloseHandle(m_hStartEvent)\n"));
		}

		//m_hDestoryEvent
		if(NULL == m_hDestoryEvent)
		{
			CloseHandle(m_hDestoryEvent);
			m_hDestoryEvent = NULL;
			//_tprintf(_T("CloseHandle(m_hDestoryEvent)\n"));
		}

		//m_vecWorkerThread
		for (int i=0; i<(int)m_vecWorkerThread.size(); ++i)
		{
			CloseHandle(m_vecWorkerThread[i]);
			m_vecWorkerThread[i] = NULL;
			//_tprintf(_T("CloseHandle(m_vecWorkerThread[%d])\n"), i);
		}
		m_vecWorkerThread.clear();
	}

	//nThreadCount�� MAXIMUM_WAIT_OBJECTS(64)�� �ʰ��ؼ� ������ �� �����ϴ�.
	BOOL CThread::BeginThread(int nThreadCount/*1*/)
	{
		//_tprintf(_T("create event(m_hStartEvent)\n"));
		m_hStartEvent = CreateEvent(0, FALSE, FALSE, 0);
		if (m_hStartEvent == NULL)
		{
			EndThread();
			return FALSE;
		}

		//_tprintf(_T("create event(m_hDestoryEvent)\n"));
		m_hDestoryEvent = CreateEvent(0, FALSE, FALSE, 0);
		if (m_hDestoryEvent == NULL)
		{
			EndThread();
			return FALSE;
		}

		//��� ��ȣ
		if(FALSE == m_module.CheckValid())
			return TRUE;

		//thread ����
		m_bIsRunning = TRUE;
		//printf("************************ BEGIN THREAD: %p\n", this);

		//nThreadCount�� MAXIMUM_WAIT_OBJECTS(64)�� �ʰ��ؼ� ������ �� �����ϴ�.
		//�ʰ��� ���. WaitForMultipleObjects���� WAIT_FAILED�� �����մϴ�.
		if (nThreadCount > MAXIMUM_WAIT_OBJECTS)
			nThreadCount = MAXIMUM_WAIT_OBJECTS;

		for (int i = 0; i < nThreadCount; ++i)
		{
			//_tprintf(_T("_beginthreadex(%d)\n"), i);
			stParam param(this, i);
			HANDLE WorkerThread = (HANDLE)::_beginthreadex(NULL, 0, _Thread, &param, 0, NULL);
			//if(NULL == WorkerThread)
			//{
			//	//_tprintf(_T("Error thread (%d)���� ���� : errno %d <errno.h>�� error code ���� ����\n"), i, errno);
			//	continue;
			//}
			m_vecWorkerThread.push_back(WorkerThread);
			//_tprintf(_T("(0x%p)BeginThread (0x%x)\n"), this, WorkerThread);
			////LOGEVENT("HG_CYAN", _T("(0x%x)BeginThread (0x%x)\n"), this, WorkerThread);	//���⼭ LOGEVENT �� �۵�����

			WaitForSingleObject(m_hStartEvent, INFINITE);
		}

		return TRUE;
	}

	//void CThread::KillThread()
	//{
	//	m_bIsRunning = FALSE;

	//	EndThread();
	//}
	
	void CThread::EndThread()
	{
		if (FALSE == m_bIsRunning)
			return;
		m_bIsRunning = FALSE;	//�� FALSE�� �Ǿ�� Thread�� while���� �����մϴ�.
		//printf("************************ END THREAD: %p\n", this);

		HANDLE buff[64] = {0, };
		for (size_t i=0; i<m_vecWorkerThread.size(); ++i)
			buff[i] = m_vecWorkerThread[i];

		////_tprintf(_T("(0x%p)EndThread waiting[0x%x]... \n"), this, buff[0]);
		//LOGEVENT("HG_CYAN", _T("(0x%p)EndThread waiting[0x%x]..."), this, buff[0]);

		//INFINITE ���� �����ϸ� CEventSelect::OnWorkerThread()�� WaitForMultipleObjects���� hold���¶� ������� �ʴ´�.
		//DWORD ret = WaitForMultipleObjects((DWORD)m_vecWorkerThread.size(), buff, TRUE, INFINITE);
		DWORD ret = WaitForMultipleObjects((DWORD)m_vecWorkerThread.size(), buff, TRUE, END_THREAD_WAIT_TIME);// INFINITE);
		////_tprintf(_T("WaitForMultipleObjects(%x/%x)\n"), ret, GetLastError());
		//LOGEVENT("HG_CYAN", _T("WaitForMultipleObjects(%x/%x)"), ret, GetLastError());

		//HG[2021.03.04]TerminateThread()���� �ƹ��͵� �ȵȴ�. ��������.
		//if (WAIT_TIMEOUT == ret) {
		//	for (size_t i = 0; i < m_vecWorkerThread.size(); ++i)
		//		TerminateThread(m_vecWorkerThread[i], 0xFE);
		//}

		for (size_t i=0; i<m_vecWorkerThread.size(); ++i)
		{
			CloseHandle(m_vecWorkerThread[i]);
			m_vecWorkerThread[i] = NULL;
			//_tprintf(_T("CloseHandle(m_vecWorkerThread[%d])\n"), i);
		}
		m_vecWorkerThread.clear();

		//WaitForSingleObject(m_hDestoryEvent, INFINITE);
		////_tprintf(_T("(0x%p)EndThread()\n"), this);
		//LOGEVENT("HG_CYAN", _T("(0x%p)EndThread()"), this);
	}

	void CThread::OnThread(int index)
	{
		//_tprintf(_T("\tstart Thread[%d]\n"), index);
		SetEvent(m_hStartEvent);
		OnWorkerThread(index);
		////SetEvent(m_hDestoryEvent);
		//_tprintf(_T("\tend Thread[%d]\n"), index);
	}

	unsigned int CALLBACK CThread::_Thread(void* lpParam)
	{
		stParam* parm = (stParam*)lpParam;
		if(NULL == parm || NULL == parm->m_object)
			return 0;

		parm->m_object->OnThread(parm->m_index);
		//_tprintf(_T("(0x%x)_thread finished\n"), parm->m_object);
		return 0;
	}

};//..namespace HisUtil {
