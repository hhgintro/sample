// test_hisutil_module.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <atltime.h>


#include <windows.h>
#include <iostream>   
#include <process.h>

#include "CriticalSectionEx.h"
// /*
double score = 0.0;


HANDLE threads[10];

CRITICAL_SECTION score_mutex;

#define HIS_LOCK
//#define OTHER_LOCK

const int LOOP_COUNT = 10;
const int THREAD_COUNT = 100;

BaseLock *pLock;


unsigned int __stdcall MyThread(void *data)
{
	for (int i = 0; i < LOOP_COUNT; ++i)
	{
#ifdef HIS_LOCK
		HisUtil::CHisCritSec Lock((HisUtil::CCritSecBase*)data);
		score = score + 1.0;
#elif defined OTHER_LOCK
		LockObj lock(pLock);
		score = score + 1.0;
#else
		EnterCriticalSection(&score_mutex);
		//while (!TryEnterCriticalSection(&score_mutex)) {}
		score = score + 1.0;
		LeaveCriticalSection(&score_mutex);
#endif
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//CRITICAL_SECTION sscs_;
	//::InitializeCriticalSectionAndSpinCount(&sscs_, 0);

	//INT64 val = 0;

	//printf("%d\n", InterlockedCompareExchange((PLONG)&val, 0, 1));
	//printf("%d\n", InterlockedCompareExchange((PLONG)&val, 1, 0));
	//system("pause");
	//return 0;


	{
#ifdef HIS_LOCK
		HisUtil::CCritSecBase cs_(0);
#elif defined OTHER_LOCK
		pLock = new CriticalSectionEx();
#else
		InitializeCriticalSection(&score_mutex);
#endif
		for (int loop = 0; loop < THREAD_COUNT; loop++)
		{
#ifdef HIS_LOCK
			threads[loop] = (HANDLE)_beginthreadex(NULL, 0, MyThread, &cs_, 0, NULL);
#elif defined OTHER_LOCK
			threads[loop] = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, NULL);
#else
			threads[loop] = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, NULL);
#endif
		}

		WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

#ifdef HIS_LOCK
#elif defined OTHER_LOCK
#else
		DeleteCriticalSection(&score_mutex);
#endif
	}

	printf("score:%f\n", score);

	//::DeleteCriticalSection(&sscs_);

	system("pause");
	return 0;
}

// */

/*
#define THREADCOUNT 100
BaseLock *pLock;

unsigned int __stdcall MyThread(void *data)
{
	BOOL bContinue = TRUE;

	while (bContinue)
	{
		LockObj lock(pLock);
		printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
		bContinue = FALSE;
		break;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("Example"));

	HANDLE aThread[THREADCOUNT];
	//DWORD ThreadID;
	int i;


	pLock = new CriticalSectionEx();

	// Create worker threads

	for (i = 0; i < THREADCOUNT; i++)
	{
		aThread[i] = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, NULL);
		//aThread[i] = CreateThread(
		//	NULL,       // default security attributes
		//	0,          // default stack size
		//	(LPTHREAD_START_ROUTINE)ThreadProc,
		//	NULL,       // no thread function arguments
		//	0,          // default creation flags
		//	&ThreadID); // receive thread identifier

		if (aThread[i] == NULL)
		{
			printf("CreateThread error: %d\n", GetLastError());
			return 1;
		}
	}

	// Wait for all threads to terminate

	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// Close thread and semaphore handles

	for (i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[i]);

	delete pLock;

	system("pause");
	return 0;
}
*/