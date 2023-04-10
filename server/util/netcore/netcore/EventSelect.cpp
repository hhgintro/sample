#include "stdafx.h"
#include "EventSelect.h"

namespace NetCore {

	VOID CEventSelect::OnWorkerThread(int index)
	{
		WSANETWORKEVENTS	NetworkEvents;
		DWORD				EventID = 0;
		//DWORD				Result	= 0;
		//HANDLE				ThreadEvents[2] = { DestroyEventHandle_, mSelectEventHandle };
		HANDLE				ThreadEvents[1] = { mSelectEventHandle };

		//srand은 thread마다 별도로 관리
		srand(GetTickCount());

		while (TRUE == IsRunning()) {
			////EventID = ::WaitForMultipleObjects(2, ThreadEvents, FALSE, INFINITE);
			//EventID = ::WaitForMultipleObjects(1, ThreadEvents, FALSE, INFINITE);
			EventID = ::WaitForMultipleObjects(1, ThreadEvents, FALSE, TIME_MSEC(500));
			switch (EventID) {
				//case WAIT_OBJECT_0:
				//	return;

				//case WAIT_OBJECT_0 + 1:
			case WAIT_OBJECT_0:
			{
				EventID = WSAEnumNetworkEvents(socket_, mSelectEventHandle, &NetworkEvents);
				if (EventID == SOCKET_ERROR) {
					LOGEVENT("Network_Base_Core_Error", _T("failed EVENT error"));
					break;
				}

				if (NetworkEvents.lNetworkEvents & FD_CONNECT)
				{
					if (NetworkEvents.iErrorCode[FD_CONNECT_BIT])
					{
						LOGEVENT("Network_Base_Core_Error", _T("failed connection"));
						OnIoDisconnected();
						break;
					}

					OnIoConnected();
				}
				if (NetworkEvents.lNetworkEvents & FD_WRITE)
				{
					OnIoSend();//100% 신뢰불가
				}
				if (NetworkEvents.lNetworkEvents & FD_READ)
				{
					OnIoRecv();
				}
				if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					OnIoDisconnected();

					if (NetworkEvents.iErrorCode[FD_CLOSE_BIT])
					{
						LOGEVENT("Network_Base_Core_Error", _T("You were disconnected by server"));
						break;
					}
				}
			}//..case WAIT_OBJECT_0 + 1:
			break;

			default:	//WAIT_TIMEOUT
				break;
			}//..switch (EventID) {
		}//..while (TRUE == IsRunning()) {

		LOGEVENT("Network_Base_Core_Info", _T("finished CEventSelect::OnWorkerThread(%d)"), index);
	}

	CEventSelect::CEventSelect(VOID)
		: mSelectEventHandle(0), socket_(0)//, ClientEvent_(0)
	{
	}

	CEventSelect::~CEventSelect(VOID)
	{
	}

	BOOL CEventSelect::Begin(SOCKET socket)
	{
		if (!socket)
			return FALSE;

		if (socket_)
			return FALSE;

		socket_ = socket;

		mSelectEventHandle = WSACreateEvent();
		if (mSelectEventHandle == WSA_INVALID_EVENT)
		{
			End();
			return FALSE;
		}

		DWORD Result = WSAEventSelect(socket, mSelectEventHandle, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
		if (Result == SOCKET_ERROR)
		{
			End();
			return FALSE;
		}

		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		//if (FALSE == CThread::BeginThread(SystemInfo.dwNumberOfProcessors * 2 + 1))
		if (FALSE == CThread::BeginThread(1))	//thread 수를 늘이면, udp packet num의 충돌이 발생한다.
		{
			End();
			return FALSE;
		}

		return TRUE;
	}

	BOOL CEventSelect::End(VOID)
	{
		if (!socket_)
			return FALSE;

		LOGEVENT("Session_Base_Info", _T("# EventSelect END"));
		CThread::EndThread();

		closesocket(socket_);
		socket_ = NULL;
		WSACloseEvent(mSelectEventHandle);
		mSelectEventHandle = NULL;

		return TRUE;
	}

};//..namespace NetCore {