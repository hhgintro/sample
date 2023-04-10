#include "stdafx.h"
#include "ServiceRegister.h"

//#define __FILE_LOG__

#ifdef __FILE_LOG__
FILE* pf = NULL;
//char * path = "D:\\work\\TestService\\x64\\Debug\\log.txt";
char * path = "log.txt";
#endif //__FILE_LOG__


void LOG(char* format, ...)
{
#ifdef __FILE_LOG__
	va_list	arg;
	int		count;

	char buff[1024] = "";

	va_start(arg, format);
	//count = _vsntprintf_s(format, arg);
	count = _vsnprintf_s(buff, 1024, format, arg);
	va_end(arg);

	fopen_s(&pf, path, "a");
	fwrite(buff, 1, strlen(buff), pf);
	fclose(pf);
#endif //__FILE_LOG__
}

namespace HisUtil {

	CServiceRegister::GAMELOOP CServiceRegister::m_GameMain;
	SERVICE_STATUS_HANDLE CServiceRegister::m_ssh;
	bool CServiceRegister::m_bRunedServiceMain = false;

	CServiceRegister::CServiceRegister()
	{
	}


	CServiceRegister::~CServiceRegister()
	{
	}

	void CServiceRegister::Run( /*const char* ServiceName, */GAMELOOP GameMain)
	{
		LOG("start RegisterService()\n");
		m_GameMain = GameMain;
		SERVICE_TABLE_ENTRY ServiceEntry[] = { { /*const_cast<char*>( ServiceName )*/_T(""), ServiceMain }, { NULL, NULL } };

		StartServiceCtrlDispatcher(ServiceEntry);
		if (false == m_bRunedServiceMain)
		{
			LOG("  if (false == m_bRunedServiceMain)\n");

			// SCM을 통하지 않고 직접 실행했을 경우(디버깅)를 위해.
			(*m_GameMain)();
		}
		LOG("end RegisterService()\n");
	}

	BOOL CServiceRegister::Register(TCHAR* cmd, TCHAR* servicename)
	{
		if (NULL == cmd)	return FALSE;

		BOOL result = FALSE;
		if (0 == _tcscmp(cmd, _T("-install")))			result = Install(servicename);
		else if (0 == _tcscmp(cmd, _T("-uninstall")))	result = Uninstall(servicename);
		else											return FALSE;

		if (TRUE == result)		_tprintf_s(_T("success %s(fileName:%s)\n"), cmd, servicename);
		else					_tprintf_s(_T("fail %s(fileName:%s)\n"), cmd, servicename);
		return TRUE;
	}

	void __stdcall CServiceRegister::ServiceMain(DWORD Argc, TCHAR** Argv)
	{
		LOG("  start ServiceMain()\n");
		m_bRunedServiceMain = true;

		m_ssh = RegisterServiceCtrlHandler(Argv[0], CtrlHandler);

		if (NULL == m_ssh)
		{
			LOG("  end if (NULL == m_ssh)\n");
			return;
		}

		SERVICE_STATUS status = { SERVICE_WIN32_OWN_PROCESS, SERVICE_PAUSE_PENDING, SERVICE_ACCEPT_STOP /*| SERVICE_ACCEPT_PAUSE_CONTINUE*/, 0, 0, 0, 0 };
		SetServiceStatus(m_ssh, &status);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// 초기화.... 기타 설정들...
		////TCHAR WorkingPath[MAX_PATH + 1] = _T("");
		////GetModulePath(WorkingPath);
		////SetCurrentDirectory(WorkingPath);
		//TCHAR   drive[MAX_PATH];
		//TCHAR   dir[MAX_PATH];
		//_wsplitpath_s(Argv[0], drive, MAX_PATH, dir, MAX_PATH, NULL, 0, NULL, 0);

		//TCHAR WorkingPath1[MAX_PATH] = _T("");
		//_stprintf_s(WorkingPath1, MAX_PATH, _T("%s%s"), drive, dir);
		//SetCurrentDirectory(WorkingPath1);
		/// 초기화 끝
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////1///////////////////////////////////////////////////

		status.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(m_ssh, &status);

		//게임 메인 루프
		(*m_GameMain)();
		LOG("  end ServiceMain()\n");
	}

	void __stdcall CServiceRegister::CtrlHandler(DWORD Code)
	{
		LOG("    start CtrlHandler()\n");
		SERVICE_STATUS status = { SERVICE_WIN32_OWN_PROCESS, SERVICE_RUNNING, SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE, 0, 0, 0, 0 };
		switch (Code)
		{
		case SERVICE_CONTROL_PAUSE:
			status.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			status.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:
			status.dwCurrentState = SERVICE_STOPPED;
			break;
		case SERVICE_CONTROL_INTERROGATE:
			status.dwCurrentState = SERVICE_CONTROL_INTERROGATE;
			break;
		}

		SetServiceStatus(m_ssh, &status);
		LOG("    end CtrlHandler()\n");
	}

	BOOL CServiceRegister::Install(LPCTSTR serviceName)
	{
		//LOG("start Install()\n");
		TCHAR		FileFullPath[MAX_PATH] = _T("");
		SC_HANDLE	schSCManager = NULL;
		SC_HANDLE	schService = NULL;

		if (!serviceName)
		{
			_tprintf_s(_T("servicename is NULL"));
			return FALSE;
		}

		//FileFullPath[0] = '"';
		//GetModuleFileName(NULL, FileFullPath + 1, MAX_PATH - 1);
		//_tcscat_s(FileFullPath, MAX_PATH, _T("\""));
		GetModuleFileName(NULL, FileFullPath, MAX_PATH);

		schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (!schSCManager)
		{
			int result = GetLastError();
			_tprintf_s(_T("fail OpenSCManager(%d)"), result);
			return FALSE;
		}

		//SERVICE_AUTO_START	//자동
		//SERVICE_DEMAND_START	//수동	
		//SERVICE_BOOT_START	//(fail)드라이버 서브스만 유효
		//SERVICE_SYSTEM_START	//(fail)드라이버 서브스만 유효
		schService = CreateService(schSCManager,
			serviceName,
			serviceName,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			FileFullPath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

		if (!schService)
		{
			CloseServiceHandle(schSCManager);
			_tprintf_s(_T("fail CreateService()"));
			return FALSE;
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);

		return TRUE;
	}

	BOOL CServiceRegister::Uninstall(LPCTSTR serviceName)
	{
		//LOG("start Uninstall()\n");
		SC_HANDLE schSCManager = NULL;
		SC_HANDLE schService = NULL;

		if (!serviceName)
			return FALSE;

		schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (!schSCManager)
			return FALSE;

		schService = OpenService(schSCManager, serviceName, DELETE);
		if (!schService)
		{
			CloseServiceHandle(schSCManager);
			return FALSE;
		}

		if (!DeleteService(schService))
		{
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);

			return FALSE;
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);

		return TRUE;
	}

};//..namespace HisUtil {
