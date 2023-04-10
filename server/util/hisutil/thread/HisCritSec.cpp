#include "stdafx.h"
#include "HisCritSec.h"

namespace HisUtil {

	//critical section 을 생성하기만 한다.
	//class CCritSecBase
	CCritSecBase::CCritSecBase(DWORD spincount/*4000*/)
		: invalid_(false)
	{
		//__try __except는 소멸자가 있는 class에서는 사용할 수 없다네.
		//__try
		//{
		//	::InitializeCriticalSectionAndSpinCount(&cs_, spincount);
		//}
		//__except (STATUS_NO_MEMORY == GetExceptionCode())
		//{
		//	assert(!"fail InitializeCriticalSectionAndSpinCount");
		//}
		try
		{
			//::InitializeCriticalSectionAndSpinCount(&cs_, spincount);
			InitializeCriticalSection(&cs_);
			invalid_ = true;
			//m_lockCounter = 0;
			//m_dwThreadId = 0;
		}
		catch (std::bad_alloc& e)
		{
			printf("except %s\n", e.what());
			assert(!"fail EnterCriticalSection");
		}
	}

	CCritSecBase::~CCritSecBase()
	{
		//assert(0 == m_lockCounter);
		invalid_ = false;
		::DeleteCriticalSection(&cs_);
	}

	//이미 CRITICAL_SECTION 을 소유한 스레드가 다시 EnterCriticalSection 으로 그것을 소유하려고 하는경우 에러없이 넘어간다.
	//	그러나 한번 LeaveCriticalSection 으로 CRITICAL_SECTION 을 해제한 다음 다시LeaveCriticalSection 을 호출하면,
	//	즉 소유하지 않는 스레드에서 LeaveCriticalSection 을 호출하면 다음번 EnterCriticalSection 호출시에 deadlock 이 발생한다.
	void CCritSecBase::Lock()
	{
		if (false == invalid_)	return;
		//if (0 == InterlockedCompareExchange((PLONG)&m_lockCounter, 1, 0))//if(!IsCurrentThreadLocked())
		//{

			try
			{
				::EnterCriticalSection(&cs_);
				//printf("::EnterCriticalSection(%d)\n", GetCurrentThreadId());
				//printf("lcokcnt(%d),recursion(%d),own(%d)\n", cs_.LockCount, cs_.RecursionCount, cs_.OwningThread);
				//InterlockedExchange((PLONG)&m_dwThreadId, (LONG)GetCurrentThreadId());
				//InterlockedIncrement((PLONG)&m_lockCounter);
				//++m_lockCounter;
				//EXCEPTION_EXECUTE_HANDLER
			}
			catch (std::bad_alloc& e)
			{
				printf("except %s\n", e.what());
				assert(!"fail EnterCriticalSection");
			}
		//}
	}
	void CCritSecBase::Unlock()
	{
		if (false == invalid_)	return;
		//if (1 == InterlockedCompareExchange((PLONG)&m_lockCounter, 0, 1))//if(!IsCurrentThreadLocked())
		{
			//--m_lockCounter;
			//assert(0 <= m_lockCounter);
			//InterlockedExchange((PLONG)&m_dwThreadId, (LONG)0);
			//InterlockedDecrement((PLONG)&m_lockCounter);

			//printf("::LeaveCriticalSection(%d)\n\n", GetCurrentThreadId());
			::LeaveCriticalSection(&cs_);
			//printf("lcokcnt(%d),recursion(%d),own(%d)\n", cs_.LockCount, cs_.RecursionCount, cs_.OwningThread);
		}
	}


	//생성된 critical setion을 이용한다.(lock, unlock)
	//class로 선언함으로 자동 소멸되도록 처리한다.
	//class CHisCritSec

	CHisCritSec::CHisCritSec(CCritSecBase& base)
		: base_(base)
	{
		//if (!IsCurrentThreadLocked())
		{
			//if (base_)	base_->Lock();
			base_.Lock();
			//InterlockedExchange((PLONG)&m_dwThreadId, (LONG)GetCurrentThreadId());
		}
		//_tprintf(_T("==== lock On ==== LockCount(%d), RecursionCount(%d), OwningThread(%d), LockSemaphore(%d), SpinCount(%d)\n")
		//	, base_->cs_.LockCount, base_->cs_.RecursionCount, base_->cs_.OwningThread, base_->cs_.LockSemaphore, base_->cs_.SpinCount);
	}
	CHisCritSec::~CHisCritSec()
	{
		//if (IsCurrentThreadLocked())
		{
			//InterlockedExchange((PLONG)&m_dwThreadId, (LONG)0);
			//if (base_)
			//{
			//	base_->Unlock();
			//	base_ = NULL;
			//}
			base_.Unlock();
		}
		//_tprintf(_T("==== lock Off ==== LockCount(%d), RecursionCount(%d), OwningThread(%d), LockSemaphore(%d), SpinCount(%d)\n")
		//	, base_->cs_.LockCount, base_->cs_.RecursionCount, base_->cs_.OwningThread, base_->cs_.LockSemaphore, base_->cs_.SpinCount);
	}

}//HisUtil
