#include "stdafx.h"
#include "HisCritSec.h"

namespace HisUtil {

	//critical section �� �����ϱ⸸ �Ѵ�.
	//class CCritSecBase
	CCritSecBase::CCritSecBase(DWORD spincount/*4000*/)
		: invalid_(false)
	{
		//__try __except�� �Ҹ��ڰ� �ִ� class������ ����� �� ���ٳ�.
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

	//�̹� CRITICAL_SECTION �� ������ �����尡 �ٽ� EnterCriticalSection ���� �װ��� �����Ϸ��� �ϴ°�� �������� �Ѿ��.
	//	�׷��� �ѹ� LeaveCriticalSection ���� CRITICAL_SECTION �� ������ ���� �ٽ�LeaveCriticalSection �� ȣ���ϸ�,
	//	�� �������� �ʴ� �����忡�� LeaveCriticalSection �� ȣ���ϸ� ������ EnterCriticalSection ȣ��ÿ� deadlock �� �߻��Ѵ�.
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


	//������ critical setion�� �̿��Ѵ�.(lock, unlock)
	//class�� ���������� �ڵ� �Ҹ�ǵ��� ó���Ѵ�.
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
