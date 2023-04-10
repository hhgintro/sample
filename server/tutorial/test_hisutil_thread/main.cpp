// test_hisutil_thread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

class MyThread : public HisUtil::CThread
{
	void OnWorkerThread(int index)
	{
		int tick = GetTickCount() + 100 * (index + 1);

		_tprintf(_T("thread(%d) is running\n"), index);
		while(TRUE == IsRunning())
		{
			Sleep(1);
			if(tick < GetTickCount())
				break;

			//if (0 == (index % 2)) {
			//	int* p = m_pool.Create();
			//	*p = index;
			//	m_pool.Push(p);
			//}
			//else {
			//	m_pool.Front();
			//	m_pool.Pop();
			//}

			Sleep(10000000);

			
		}
		_tprintf(_T("thread(%d) is stopped\n"), index);
	}

	//HisUtil::CMemoryQueuePool<int> m_pool;
};

int _tmain(int argc, _TCHAR* argv[])
{
	while(1)
	{
		MyThread thread;
		thread.BeginThread(8);
		//thread.KillThread();
		thread.EndThread();

		Sleep(2000);
	}

	//int pos = 0;
	//while (1)
	//{
	//	Sleep(3000);
	//	printf("main thread is running\n");

	//	if (++pos == 2)
	//	{
	//		thread.EndThread();
	//	}
	//	else if (pos > 3)
	//	{
	//		break;
	//	}
	//}

	printf("main thread is stopped\n");
	system("pause");
	return 0;
}

