#include "stdafx.h"
#include "CrashHandler.h"

#include <new.h>		//_set_new_handler
#include <eh.h>			//set_terminate
#include <process.h>	//_beginthreadex
#include <signal.h>

#ifndef _AddressOfReturnAddress

// Taken from: http://msdn.microsoft.com/en-us/library/s975zw7k(VS.71).aspx
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// _ReturnAddress and _AddressOfReturnAddress should be prototyped before use 
EXTERNC void * _AddressOfReturnAddress(void);
EXTERNC void * _ReturnAddress(void);

#endif 

namespace HisUtil
{
	MINIDUMP_TYPE CCrashHandler::m_dumptype = MiniDumpNormal;
	TCHAR CCrashHandler::m_szAppName[MAX_PATH] = { 0, };
	TCHAR CCrashHandler::m_szLogFile[MAX_PATH] = { 0, };


	CCrashHandler::CCrashHandler(LPCTSTR szProjectPath, LPCTSTR szAppName, MINIDUMP_TYPE dumptype/*MiniDumpWithFullMemory*/)
	{
		//MINIDUMP_TYPE
		m_dumptype = dumptype;

		//appname
		//m_szAppName = new TCHAR[MAX_PATH];
		_stprintf_s(m_szAppName, MAX_PATH, _T("%s\\%s"), szProjectPath, szAppName);

		//// Log/ 폴더 생성
		//TCHAR szPath[MAX_PATH] = {0, };
		//_stprintf_s(szPath, MAX_PATH, _T("%s%s\\"), szProjectPath, _T("Log"));
		//::CreateDirectory(szPath,0);// Log/ 폴더 생성

		//// ./log/server
		////m_szLogFile = new TCHAR[MAX_PATH];
		//_stprintf_s(m_szLogFile, MAX_PATH, _T("%s%s"), szPath, szAppName);


		Log2File(_T("===== minidump init ====="));


		SetProcessExceptionHandlers();
		SetThreadExceptionHandlers();
	}

	CCrashHandler::~CCrashHandler()
	{
	}

	void CCrashHandler::SetProcessExceptionHandlers()
	{
		Log2File(_T("    SetProcessExceptionHandlers()"));
		// Install top-level SEH handler
		SetUnhandledExceptionFilter(SehHandler);

		// Catch pure virtual function calls.
		// Because there is one _purecall_handler for the whole process, 
		// calling this function immediately impacts all threads. The last 
		// caller on any thread sets the handler. 
		// http://msdn.microsoft.com/en-us/library/t296ys27.aspx
		_set_purecall_handler(PureCallHandler);

		// Catch new operator memory allocation exceptions
		_set_new_handler(NewHandler);

		// Catch invalid parameter exceptions.
		_set_invalid_parameter_handler(InvalidParameterHandler);

		// Set up C++ signal handlers

		_set_abort_behavior(_CALL_REPORTFAULT, _CALL_REPORTFAULT);

		// Catch an abnormal program termination
		signal(SIGABRT, SigabrtHandler);

		// Catch illegal instruction handler
		signal(SIGINT, SigintHandler);

		// Catch a termination request
		signal(SIGTERM, SigtermHandler);

	}

	void CCrashHandler::SetThreadExceptionHandlers()
	{
		Log2File(_T("    SetThreadExceptionHandlers()"));

		// Catch terminate() calls. 
		// In a multithreaded environment, terminate functions are maintained 
		// separately for each thread. Each new thread needs to install its own 
		// terminate function. Thus, each thread is in charge of its own termination handling.
		// http://msdn.microsoft.com/en-us/library/t6fk7h29.aspx
		set_terminate(TerminateHandler);

		// Catch unexpected() calls.
		// In a multithreaded environment, unexpected functions are maintained 
		// separately for each thread. Each new thread needs to install its own 
		// unexpected function. Thus, each thread is in charge of its own unexpected handling.
		// http://msdn.microsoft.com/en-us/library/h46t5b69.aspx  
		set_unexpected(UnexpectedHandler);

		// Catch a floating point error
		typedef void(*sigh)(int);
		signal(SIGFPE, (sigh)SigfpeHandler);

		// Catch an illegal instruction
		signal(SIGILL, SigillHandler);

		// Catch illegal storage access errors
		signal(SIGSEGV, SigsegvHandler);

	}

	// The following code gets exception pointers using a workaround found in CRT code.
	void CCrashHandler::GetExceptionPointers(DWORD dwExceptionCode,
		EXCEPTION_POINTERS** ppExceptionPointers)
	{
		// The following code was taken from VC++ 8.0 CRT (invarg.c: line 104)

		EXCEPTION_RECORD ExceptionRecord;
		CONTEXT ContextRecord;
		memset(&ContextRecord, 0, sizeof(CONTEXT));

#ifdef _X86_

		__asm {
			mov dword ptr[ContextRecord.Eax], eax
				mov dword ptr[ContextRecord.Ecx], ecx
				mov dword ptr[ContextRecord.Edx], edx
				mov dword ptr[ContextRecord.Ebx], ebx
				mov dword ptr[ContextRecord.Esi], esi
				mov dword ptr[ContextRecord.Edi], edi
				mov word ptr[ContextRecord.SegSs], ss
				mov word ptr[ContextRecord.SegCs], cs
				mov word ptr[ContextRecord.SegDs], ds
				mov word ptr[ContextRecord.SegEs], es
				mov word ptr[ContextRecord.SegFs], fs
				mov word ptr[ContextRecord.SegGs], gs
				pushfd
				pop[ContextRecord.EFlags]
		}

		ContextRecord.ContextFlags = CONTEXT_CONTROL;
#pragma warning(push)
#pragma warning(disable:4311)
		ContextRecord.Eip = (ULONG)_ReturnAddress();
		ContextRecord.Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
		ContextRecord.Ebp = *((ULONG *)_AddressOfReturnAddress() - 1);


#elif defined (_IA64_) || defined (_AMD64_)

		/* Need to fill up the Context in IA64 and AMD64. */
		RtlCaptureContext(&ContextRecord);

#else  /* defined (_IA64_) || defined (_AMD64_) */

		ZeroMemory(&ContextRecord, sizeof(ContextRecord));

#endif  /* defined (_IA64_) || defined (_AMD64_) */

		ZeroMemory(&ExceptionRecord, sizeof(EXCEPTION_RECORD));

		ExceptionRecord.ExceptionCode = dwExceptionCode;
		ExceptionRecord.ExceptionAddress = _ReturnAddress();

		///

		EXCEPTION_RECORD* pExceptionRecord = new EXCEPTION_RECORD;
		memcpy(pExceptionRecord, &ExceptionRecord, sizeof(EXCEPTION_RECORD));
		CONTEXT* pContextRecord = new CONTEXT;
		memcpy(pContextRecord, &ContextRecord, sizeof(CONTEXT));

		*ppExceptionPointers = new EXCEPTION_POINTERS;
		(*ppExceptionPointers)->ExceptionRecord = pExceptionRecord;
		(*ppExceptionPointers)->ContextRecord = pContextRecord;
	}

	void CCrashHandler::ExceptionHandler(EXCEPTION_POINTERS* pExcPtrs)
	{
		if (pExcPtrs->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
		{
			Log2File(_T("쓰레드 생성(EXCEPTION_STACK_OVERFLOW)"));

			// 덤프 찍기용 쓰레드 하나 생성해 주고
			HANDLE hThread = (HANDLE)::_beginthreadex(NULL, 0, CreateMiniDump, pExcPtrs, 0, NULL);
			// 생성 쓰레드가 덤프 끝날 때까지 기다린다
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
			Log2File(_T("쓰레드 정상종료\n\n"));
			return;
		}

		// 스택 오버플로우가 없는 일반적인 경우의 덤프 처리
		CreateMiniDump(pExcPtrs);
	}

	// This method creates minidump of the process
	unsigned int CCrashHandler::CreateMiniDump(void* param)
	{
		Log2File(_T("===== minidump start ====="));

		EXCEPTION_POINTERS* pExcPtrs = (EXCEPTION_POINTERS*)param;

		HMODULE hDbgHelp = NULL;
		HANDLE hFile = NULL;
		MINIDUMP_EXCEPTION_INFORMATION mei;
		MINIDUMP_CALLBACK_INFORMATION mci;

		// Load dbghelp.dll
		Log2File(_T("Load dbghelp.dll"));
		hDbgHelp = LoadLibrary(_T("dbghelp.dll"));
		if (hDbgHelp == NULL)
		{
			// Error - couldn't load dbghelp.dll
			Log2File(_T("DBGHELP.DLL not found"));
			return EXCEPTION_CONTINUE_SEARCH;
		}

		//system time
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);	 //현재시간 획득	

		//덤프 파일 이름 설정 
		TCHAR szDumpPath[_MAX_PATH] = { 0, };
		_sntprintf_s(szDumpPath, MAX_PATH, _TRUNCATE, _T("%s-%04d-%02d-%02d %02d_%02d_%02d(%03d).dmp")
			, m_szAppName
			, systemTime.wYear
			, systemTime.wMonth
			, systemTime.wDay
			, systemTime.wHour
			, systemTime.wMinute
			, systemTime.wSecond
			, systemTime.wMilliseconds);


		// Create the minidump file
		Log2File(_T("create the dump file"));
		hFile = CreateFile(
			szDumpPath,
			GENERIC_WRITE,
			FILE_SHARE_WRITE,//0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			// Couldn't create file
			Log2File(_T("Failed to create dump file '%s' (error %d)"), szDumpPath, GetLastError());
			return EXCEPTION_CONTINUE_SEARCH;
		}

		// Write minidump to the file
		mei.ThreadId = GetCurrentThreadId();
		mei.ExceptionPointers = pExcPtrs;
		mei.ClientPointers = FALSE;
		mci.CallbackRoutine = NULL;
		mci.CallbackParam = NULL;

		typedef BOOL(WINAPI *LPMINIDUMPWRITEDUMP)(
			HANDLE hProcess,
			DWORD ProcessId,
			HANDLE hFile,
			MINIDUMP_TYPE DumpType,
			CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
			CONST PMINIDUMP_USER_STREAM_INFORMATION UserEncoderParam,
			CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

		LPMINIDUMPWRITEDUMP pfnMiniDumpWriteDump =
			(LPMINIDUMPWRITEDUMP)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
		if (!pfnMiniDumpWriteDump)
		{
			// Bad MiniDumpWriteDump function
			Log2File(_T("not found MiniDumpWriteDump()"));
			return EXCEPTION_CONTINUE_SEARCH;
		}
		Log2File(_T("loading MiniDumpWriteDump()"));


		HANDLE hProcess = GetCurrentProcess();
		DWORD dwProcessId = GetCurrentProcessId();

		BOOL bWriteDump = pfnMiniDumpWriteDump(
			hProcess,
			dwProcessId,
			hFile,
			m_dumptype,
			&mei,
			NULL,
			&mci);

		if (!bWriteDump)
		{
			// Error writing dump.
			Log2File(_T("Failed to save dump file to '%s' (error %d)"), szDumpPath, GetLastError());
			return EXCEPTION_CONTINUE_SEARCH;
		}
		Log2File(_T("Saved dump file to '%s'"), szDumpPath);
		Log2File(_T("===== minidump end ====="));

		// Close file
		CloseHandle(hFile);

		// Unload dbghelp.dll
		FreeLibrary(hDbgHelp);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Structured exception handler
	LONG WINAPI CCrashHandler::SehHandler(PEXCEPTION_POINTERS pExceptionPtrs)
	{
		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

		// Unreacheable code  
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// CRT terminate() call handler
	void __cdecl CCrashHandler::TerminateHandler()
	{
		// Abnormal program termination (terminate() function was called)

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);
	}

	// CRT unexpected() call handler
	void __cdecl CCrashHandler::UnexpectedHandler()
	{
		// Unexpected error (unexpected() function was called)

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);
	}

	// CRT Pure virtual method call handler
	void __cdecl CCrashHandler::PureCallHandler()
	{
		// Pure virtual function call

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}


	// CRT invalid parameter handler
	void __cdecl CCrashHandler::InvalidParameterHandler(
		const wchar_t* expression,
		const wchar_t* function,
		const wchar_t* file,
		unsigned int line,
		uintptr_t pReserved)
	{
		pReserved;

		// Invalid parameter exception

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT new operator fault handler
	int __cdecl CCrashHandler::NewHandler(size_t)
	{
		// 'new' operator memory allocation exception

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

		// Unreacheable code
		return 0;
	}

	// CRT SIGABRT signal handler
	void CCrashHandler::SigabrtHandler(int)
	{
		// Caught SIGABRT C++ signal

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT SIGFPE signal handler
	void CCrashHandler::SigfpeHandler(int /*code*/, int subcode)
	{
		// Floating point exception (SIGFPE)

		EXCEPTION_POINTERS* pExceptionPtrs = (PEXCEPTION_POINTERS)_pxcptinfoptrs;

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT sigill signal handler
	void CCrashHandler::SigillHandler(int)
	{
		// Illegal instruction (SIGILL)

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT sigint signal handler
	void CCrashHandler::SigintHandler(int)
	{
		// Interruption (SIGINT)

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT SIGSEGV signal handler
	void CCrashHandler::SigsegvHandler(int)
	{
		// Invalid storage access (SIGSEGV)

		PEXCEPTION_POINTERS pExceptionPtrs = (PEXCEPTION_POINTERS)_pxcptinfoptrs;

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	// CRT SIGTERM signal handler
	void CCrashHandler::SigtermHandler(int)
	{
		// Termination request (SIGTERM)

		// Retrieve exception information
		EXCEPTION_POINTERS* pExceptionPtrs = NULL;
		GetExceptionPointers(0, &pExceptionPtrs);

		// Write minidump file
		ExceptionHandler(pExceptionPtrs);

		// Terminate process
		TerminateProcess(GetCurrentProcess(), 1);

	}

	void CCrashHandler::Log2File(TCHAR* logmsg, ...)
	{
		return;//로그찍다 보니 덤프가 안남더라.

		TCHAR szLog[MAX_LOG_SIZE] = _T("");

		va_list	pArg;
		va_start(pArg, logmsg);
		_vstprintf_s(szLog, MAX_LOG_SIZE, logmsg, pArg);
		va_end(pArg);


		TCHAR filename[MAX_PATH] = _T("");
		_stprintf_s(filename, MAX_PATH, _T("%s_Dump.log"), m_szLogFile);

		FILE *fp = NULL;
		_tfopen_s(&fp, filename, _T("at"));
		if (NULL != fp)
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			_ftprintf_s(fp, _T("[%02d_%02d_%02d %02d:%02d:%02d]  %s\n"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, szLog);
			fclose(fp);
			fp = NULL;
		}

	}

};//namespace HisUtil