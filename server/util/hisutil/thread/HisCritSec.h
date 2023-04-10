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
#include <new>

namespace HisUtil {

	//critical section 을 생성하기만 한다.
	class CCritSecBase
	{
	public:
		//CCritSecBase() {InitializeCriticalSection(&cs_); }
		CCritSecBase(DWORD spincount = 4000);
		~CCritSecBase();


		//이미 CRITICAL_SECTION 을 소유한 스레드가 다시 EnterCriticalSection 으로 그것을 소유하려고 하는경우 에러없이 넘어간다.
		//	그러나 한번 LeaveCriticalSection 으로 CRITICAL_SECTION 을 해제한 다음 다시LeaveCriticalSection 을 호출하면,
		//	즉 소유하지 않는 스레드에서 LeaveCriticalSection 을 호출하면 다음번 EnterCriticalSection 호출시에 deadlock 이 발생한다.
		inline void Lock();
		inline void Unlock();

	private:
		CRITICAL_SECTION cs_;
		bool invalid_;
		//HANDLE mutex_;
		//int m_lockCounter;
		//DWORD volatile m_dwThreadId;

		friend class CHisCritSec;
	};


	//생성된 critical setion을 이용한다.(lock, unlock)
	//class로 선언함으로 자동 소멸되도록 처리한다.
	class CHisCritSec
	{
	private:
		CCritSecBase& base_;
		//DWORD volatile m_dwThreadId;
	public:
		CHisCritSec(CCritSecBase& base);
		~CHisCritSec();
	};

}//HisUtil

#define AUTO_LOCK(a)		HisUtil::CHisCritSec Lock(a)
