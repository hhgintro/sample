#pragma once

//#define _WIN32_WINNT			0x0502	// Try using.. InitializeCriticalSectionAndSpinCount()
//#define WINVER					0x0502
//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

//Header: Declared in Winbase.h include Windows.h.
//Library: Use Kernel32.lib.

/* 사용예
변수 선언
	CCritSecBase cs_

사용
func()
{
	AUTO_LOCK(cs_)
	...
}
..사용예*/

#include <Windows.h>
#include <assert.h>

namespace HisUtil {

	//critical section 을 생성하기만 한다.
	class CCritSecBase
	{
	public:
		//CCritSecBase() {InitializeCriticalSection(&cs_); }
		CCritSecBase(DWORD spincount = 4000)
		{
			__try
			{
				::InitializeCriticalSectionAndSpinCount(&cs_, spincount);
			}
			__except (STATUS_NO_MEMORY == GetExceptionCode())
			{
				assert(!"fail InitializeCriticalSectionAndSpinCount");
			}
		}
		~CCritSecBase()
		{
			DeleteCriticalSection(&cs_);
		}

		inline void Lock()
		{
			__try
			{
				::EnterCriticalSection(&cs_);
				//EXCEPTION_EXECUTE_HANDLER
			}
			__except (STATUS_NO_MEMORY == GetExceptionCode())
			{
				printf("except %x\n", GetExceptionCode());
				assert(!"fail EnterCriticalSection");
			}
		}
		inline void Unlock()
		{
			::LeaveCriticalSection(&cs_);
		}

		//CCritSecBase(DWORD spincount = 2000) { mutex_ = CreateMutex(NULL, FALSE, NULL); }
		//~CCritSecBase() { CloseHandle(mutex_); }

		//inline void Lock()		{ WaitForSingleObject(mutex_, INFINITE); }
		//inline void Unlock()	{ ReleaseMutex(mutex_); }

	private:
		CRITICAL_SECTION cs_;
		//HANDLE mutex_;
	};


	//생성된 critical setion을 이용한다.(lock, unlock)
	//class로 선언함으로 자동 소멸되도록 처리한다.
	class CHisCritSec
	{
	private:
		CCritSecBase* base_;
	public:
		CHisCritSec(CCritSecBase* base) : base_(base) {
			if (base_) base_->Lock();
			//_tprintf(_T("==== lock On ==== LockCount(%d), RecursionCount(%d), OwningThread(%d), LockSemaphore(%d), SpinCount(%d)\n")
			//	, base_->cs_.LockCount, base_->cs_.RecursionCount, base_->cs_.OwningThread, base_->cs_.LockSemaphore, base_->cs_.SpinCount);
		}
		virtual ~CHisCritSec() {
			if (base_) base_->Unlock();
			//_tprintf(_T("==== lock Off ==== LockCount(%d), RecursionCount(%d), OwningThread(%d), LockSemaphore(%d), SpinCount(%d)\n")
			//	, base_->cs_.LockCount, base_->cs_.RecursionCount, base_->cs_.OwningThread, base_->cs_.LockSemaphore, base_->cs_.SpinCount);
		}
	};

#define AUTO_LOCK(a)		CHisCritSec Lock(&a)

}//HisUtil