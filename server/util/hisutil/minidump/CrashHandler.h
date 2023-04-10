#pragma once
#include <DbgHelp.h>

namespace HisUtil
{

	class CCrashHandler
	{
	public:

		// Constructor
		CCrashHandler(LPCTSTR szProjectPath, LPCTSTR szAppName, MINIDUMP_TYPE dumptype = MiniDumpWithFullMemory);

		// Destructor
		virtual ~CCrashHandler();

		// Sets exception handlers that work on per-process basis
		void SetProcessExceptionHandlers();

		// Installs C++ exception handlers that function on per-thread basis
		void SetThreadExceptionHandlers();

		// Collects current process state.
		static void GetExceptionPointers(
			DWORD dwExceptionCode,
			EXCEPTION_POINTERS** pExceptionPointers);

		// This method creates minidump of the process
		static void ExceptionHandler(EXCEPTION_POINTERS* pExcPtrs);
		static unsigned int __stdcall CreateMiniDump(void* param);

		/* Exception handler functions. */

		static LONG WINAPI SehHandler(PEXCEPTION_POINTERS pExceptionPtrs);
		static void __cdecl TerminateHandler();
		static void __cdecl UnexpectedHandler();

		static void __cdecl PureCallHandler();

		static void __cdecl InvalidParameterHandler(const wchar_t* expression,
			const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved);

		static int __cdecl NewHandler(size_t);

		static void SigabrtHandler(int);
		static void SigfpeHandler(int /*code*/, int subcode);
		static void SigintHandler(int);
		static void SigillHandler(int);
		static void SigsegvHandler(int);
		static void SigtermHandler(int);


		static void Log2File(TCHAR* logmsg, ...);


	private:
		static MINIDUMP_TYPE m_dumptype;
		static TCHAR m_szAppName[MAX_PATH];

		//TCHAR szPath_[MAX_PATH];
		static TCHAR m_szLogFile[MAX_PATH];

	};


};//namespace HisUtil