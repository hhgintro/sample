#include "stdafx.h"
#include "Iocp.h"

namespace NetCore {

	CIocp::CIocp(VOID)
		: IocpHandle_(0), owner_(0)
	{
	}

	CIocp::~CIocp(VOID)
	{
		End();
	}

	BOOL CIocp::Begin(VOID)
	{
		IocpHandle_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (0 == IocpHandle_)
			return FALSE;

		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		//return CThread::BeginThread(SystemInfo.dwNumberOfProcessors * 2 + 1);
		return CThread::BeginThread(SystemInfo.dwNumberOfProcessors);
		//return CThread::BeginThread(1);//SystemInfo.dwNumberOfProcessors);// * 2 + 1);
	}

	BOOL CIocp::End(VOID)
	{
		PostQueuedCompletionStatus(IocpHandle_, 0, 0, NULL);

		CThread::EndThread();

		if (IocpHandle_)
			CloseHandle(IocpHandle_);

		return TRUE;
	}

	BOOL CIocp::RegisterSocketToIocp(SOCKET socket, ULONG_PTR completionKey)
	{
		if (0 == socket || 0 == completionKey)
			return FALSE;

		IocpHandle_ = CreateIoCompletionPort((HANDLE)socket, IocpHandle_, completionKey, 0);
		if (0 == IocpHandle_)
			return FALSE;

		return TRUE;
	}

	VOID CIocp::OnWorkerThread(int index)
	{
		BOOL			Successed = FALSE;
		DWORD			NumberOfByteTransfered = 0;
		VOID			*CompletionKey = NULL;
		OVERLAPPED		*Overlapped = NULL;
		OVERLAPPED_EX	*OverlappedEx = NULL;
		VOID			*Object = NULL;

		//srand은 thread마다 별도로 관리
		srand(GetTickCount());

		while (TRUE == IsRunning())
		{
			Successed = GetQueuedCompletionStatus(
				IocpHandle_,
				&NumberOfByteTransfered,
				(PULONG_PTR)&CompletionKey,
				&Overlapped,
				INFINITE);

			if (NULL == CompletionKey || NULL == Overlapped)
				return;

			OverlappedEx = (OVERLAPPED_EX*)Overlapped;
			Object = OverlappedEx->Object;
			if (NULL == Object)
				continue;

			//if(0 == Successed)
			//{
			//	LOGEVENT("HG_RED", _T("==========심각한 오류일지 몰라 GetLastError(%d)"), GetLastError());
			//}

			if (FALSE == Successed || (Successed && 0 == NumberOfByteTransfered))
			{
				if (OverlappedEx->IoType == IO_ACCEPT)		OnIoConnected(Object);
				else										OnIoDisconnected(Object);
				continue;
			}

			switch (OverlappedEx->IoType)
			{
			case IO_READ:
				OnIoRecv(Object, NumberOfByteTransfered);
				break;

			case IO_WRITE:
				OnIoSend(Object, NumberOfByteTransfered);
				break;
			}
		}//..while
	}

};//..namespace NetCore {