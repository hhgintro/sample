#include "stdafx.h"
#include "Service.h"


namespace HisUtil {



	BOOL LaunchService(LPCTSTR servicename)
	{
		SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (NULL == hSCM)
			return FALSE;

		SC_HANDLE hService = ::OpenService(hSCM, servicename, SERVICE_ALL_ACCESS);
		if (NULL == hService)
		{
			//NOTIFY_SYSTEM_LOG("HG_RED", _T(" service(%s) 서비스 OPEN 실패"), servicename);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}

		if (FALSE == ::StartService(hService, NULL, NULL))
		{
			//NOTIFY_SYSTEM_LOG("HG_RED", _T(" service(%s) 서비스 시작 실패"), servicename);
			::CloseServiceHandle(hService);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}

		//NOTIFY_SYSTEM_LOG("HG_YELLOW", _T(" service(%s) 서비스 시작 되었습니다."), servicename);
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return TRUE;
	}

	BOOL ShutdownService(LPCTSTR servicename)
	{
		SERVICE_STATUS status;
		DWORD dwStartTime = GetTickCount();
		DWORD dwBytesNeeded = 0;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (NULL == hSCM)
			return FALSE;

		SC_HANDLE hService = ::OpenService(hSCM, servicename, SERVICE_ALL_ACCESS);
		if (NULL == hService)
		{
			//NOTIFY_SYSTEM_LOG("HG_RED", _T(" service(%s) 서비스 OPEN 실패"), servicename);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}

		if (FALSE == ::ControlService(hService, SERVICE_CONTROL_STOP, &status))
		{
			//NOTIFY_SYSTEM_LOG("HG_RED", _T(" service(%s) 서비스 Stop 실패"), servicename);
			::CloseServiceHandle(hService);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}


		// Wait for the service to stop
		while (status.dwCurrentState != SERVICE_STOPPED)
		{

			Sleep(status.dwWaitHint);
			if (!QueryServiceStatusEx(
				hService	,                     // handle to service 
				SC_STATUS_PROCESS_INFO,         // information level
				(LPBYTE)&status,             // address of structure
				sizeof(SERVICE_STATUS_PROCESS), // size of structure
				&dwBytesNeeded))              // size needed if buffer is too small
			{
				//return GetLastError();
				//NOTIFY_SYSTEM_LOG("HG_RED", _T("error GetLastError(%d)"), GetLastError());
				::CloseServiceHandle(hService);
				::CloseServiceHandle(hSCM);
				return FALSE;
			}

			if (status.dwCurrentState == SERVICE_STOPPED)
				break;

			if (GetTickCount() - dwStartTime > TIME_SEC(30))
			{
				//return ERROR_TIMEOUT;
				//NOTIFY_SYSTEM_LOG("HG_RED", _T("error TIERROR_TIMEOUT : 강종처리해 봅니다."));
				::CloseServiceHandle(hService);
				::CloseServiceHandle(hSCM);

				//프로세스 강제 종료
				//char taskkill[MAX_PATH] = "";
				//sprintf(taskkill, "taskkill /f /im %s", Proud::StringW2A(servicename));
				//system(taskkill);
				return KillProcess(servicename);
			}
		}

		//NOTIFY_SYSTEM_LOG("HG_YELLOW", _T(" service(%s) 서비스 중지 되었습니다."), servicename);
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return TRUE;
	}

	//TRUE 이면 서비스 실행중...
	BOOL ServiceStatus(LPCTSTR servicename)
	{
		SERVICE_STATUS status;
		DWORD dwBytesNeeded = 0;

		SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (NULL == hSCM)
			return FALSE;

		SC_HANDLE hService = ::OpenService(hSCM, servicename, SERVICE_ALL_ACCESS);
		if (NULL == hService)
		{
			//NOTIFY_SYSTEM_LOG("HG_RED", _T(" service(%s) 서비스 OPEN 실패"), servicename);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}

		if (!QueryServiceStatusEx(
			hService,                     // handle to service 
			SC_STATUS_PROCESS_INFO,         // information level
			(LPBYTE)&status,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // size needed if buffer is too small
		{
			//return GetLastError();
			//NOTIFY_SYSTEM_LOG("HG_RED", _T("error GetLastError(%d)"), GetLastError());
			::CloseServiceHandle(hService);
			::CloseServiceHandle(hSCM);
			return FALSE;
		}

		if (status.dwCurrentState != SERVICE_RUNNING)
			return FALSE;

		return TRUE;
	}

	/**
	* #include <Tlhelp32.h> // KillProcess
	* 해당 프로세스를 찾아 죽입니다.
	* 작업관리자에 나타나는 모든 프로세스를 죽일 수 있습니다
	* 죽일 프로세스는 ProcessName 입니다 파라미터로 받으셔도 무방
	* 아래함수에서      if(TerminateProcess(hProcess, 0))
	*                             GetExitCodeProcess(hProcess, &Code);
	* 이 두 부분을 삭제후 활용하시면 현재 띄어잇는 프로세스를 찾기용으로
	* 함수를 수정도 가능합니다.
	* 출처 : http://blog.naver.com/mazester/60018070698
	*/
	BOOL KillProcess(LPCTSTR servicename)
	{
		HANDLE         hProcessSnap = NULL;
		DWORD          Return = FALSE;
		PROCESSENTRY32 pe32 = { 0 };

		CString ProcessName;
		ProcessName.Format(_T("%s.exe"), servicename);
		ProcessName.MakeLower();

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
			return (hProcessSnap != 0 ? TRUE : FALSE);
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hProcessSnap, &pe32))
		{
			DWORD Code = 0;
			DWORD dwPriorityClass;
			do {
				HANDLE hProcess;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				dwPriorityClass = GetPriorityClass(hProcess);
				CString Temp = pe32.szExeFile;
				Temp.MakeLower();
				if (Temp == ProcessName)
				{
					if (TerminateProcess(hProcess, 0))
						GetExitCodeProcess(hProcess, &Code);
					else
						return GetLastError();
				}
				CloseHandle(hProcess);
			} while (Process32Next(hProcessSnap, &pe32));
			Return = TRUE;
		}
		else
			Return = FALSE;
		CloseHandle(hProcessSnap);
		return Return;
	}


};//..namespace HisUtil {
