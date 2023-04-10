#pragma once

//#define _WIN32_WINNT			0x0502	// Try using.. InitializeCriticalSectionAndSpinCount()
//#define WINVER					0x0502
//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

//Header: Declared in Winbase.h include Windows.h.
//Library: Use Kernel32.lib.

/* ��뿹
���� ����
	CCritSecBase cs_

���
func()
{
	AUTO_LOCK(cs_)
	...
}
..��뿹*/

#include <Windows.h>
#include <assert.h>
#include <new>

namespace HisUtil {

	//critical section �� �����ϱ⸸ �Ѵ�.
	class CCritSecBase
	{
	public:
		//CCritSecBase() {InitializeCriticalSection(&cs_); }
		CCritSecBase(DWORD spincount = 4000);
		~CCritSecBase();


		//�̹� CRITICAL_SECTION �� ������ �����尡 �ٽ� EnterCriticalSection ���� �װ��� �����Ϸ��� �ϴ°�� �������� �Ѿ��.
		//	�׷��� �ѹ� LeaveCriticalSection ���� CRITICAL_SECTION �� ������ ���� �ٽ�LeaveCriticalSection �� ȣ���ϸ�,
		//	�� �������� �ʴ� �����忡�� LeaveCriticalSection �� ȣ���ϸ� ������ EnterCriticalSection ȣ��ÿ� deadlock �� �߻��Ѵ�.
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


	//������ critical setion�� �̿��Ѵ�.(lock, unlock)
	//class�� ���������� �ڵ� �Ҹ�ǵ��� ó���Ѵ�.
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
