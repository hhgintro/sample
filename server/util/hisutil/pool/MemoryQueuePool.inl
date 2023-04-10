#pragma once

#include "MemoryQueuePool.h"

namespace HisUtil {


	// 기본 메모리 풀을 잡음
	template<typename T>
	//template<typename C>
	void CMemoryQueuePool<T>::Begin(int size = 1)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		bIsAllocated_ = TRUE;

		for (int i = 0; i < size; ++i)
		{
			try
			{
				memFree_.push(new T);
			}
			catch (std::bad_alloc& e)
			{
				//NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
				printf("error : %s\n", e.what());
			}
		}
	}

	//메모리 풀을 모두 삭제한다.
	template<class T>
	void CMemoryQueuePool<T>::End()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		{//delete used memory
			while (!memUsed_.empty())
			{
				SAFE_DELETE(memUsed_.front());
				memUsed_.pop();
			}
		}

		{//delete free memory
			while (!memFree_.empty()) {
				SAFE_DELETE(memFree_.front());
				memFree_.pop();
			}
		}

		{//delete leak memory
			std::set<T*>::iterator it = memLeak_.begin();
			while (it != memLeak_.end())
			{
				if (IsAllocated())
					SAFE_DELETE((T*)(*it));

				++it;
			}
			memLeak_.clear();
		}
	}

	// 사용 메모리를 모두 지우고 "memFree_"에 반환
	template<class T>
	void CMemoryQueuePool<T>::Clear()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		while (false == memUsed_.empty())
		{
			T* pT = memUsed_.front();
			memUsed_.pop();

			if (IsAllocated())
				memFree_.push(pT);
		}
	}


	// 개체를 생성한다.
	template<class T>
	//template<typename C>
	T* CMemoryQueuePool<T>::Create()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		bIsAllocated_ = TRUE;

		if (memFree_.empty())
		{
			try
			{
				//return new T;
				T* pT = new T;
				memLeak_.insert(pT);//insert 되면서 회수처리됩니다.
				return pT;
			}
			catch (std::bad_alloc& e)
			{
				//CEventLog::Instance().NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
				printf("error : %s\n", e.what());
				return NULL;
			}
		}

		T* pT = memFree_.front();
		memFree_.pop();
		memLeak_.insert(pT);//push 되면서 회수처리됩니다.
		return pT;
	}


	//use pool에 넣는다.(free pool에 넣을때는 Release를 사용해라.)
	template<class T>
	bool CMemoryQueuePool<T>::Push(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (IsAllocated())
			memLeak_.erase(pT);//create에서 생성된 개체는 leak되지 않고 회수되었습니다.

		memUsed_.push(pT);
		return TRUE;
	}


	//처음 개체에 접근한다.
	template<class T>
	T* CMemoryQueuePool<T>::Front()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (true == memUsed_.empty())
			return NULL;

		return memUsed_.front();
	}


	//free pool 에 넣어준다.
	// 생성되지 않은 경우는 무시처리됨
	template<class T>
	void CMemoryQueuePool<T>::Pop()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (true == memUsed_.empty())
			return;

		T* pT = memUsed_.front();
		memUsed_.pop();

		if (IsAllocated())
			memFree_.push(pT);
	}


	//처음 개체에 접근하고, pool 에서 빼진다.
	//Front_Pop() 호출후에는 pool에서 빼지므로 Push 또는 Release를 통해 넣어주어야 한다.
	//목적 : 순차적으로 pool에 접근하기 위해 사용합니다.
	template<class T>
	T* CMemoryQueuePool<T>::Front_Pop()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (true == memUsed_.empty())
			return NULL;

		T* pT = memUsed_.front();
		memUsed_.pop();

		if (IsAllocated())
			memLeak_.insert(pT);//push 되면서 회수처리됩니다.
		return pT;
	}

	//free pool에 넣는다.(use pool에 넣을때는 Push를 사용해라.)
	template<class T>
	bool CMemoryQueuePool<T>::Release(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (IsAllocated())
			memLeak_.erase(pT);//create에서 생성된 개체는 leak되지 않고 회수되었습니다.

		memFree_.push(pT);
		return TRUE;
	}

}//namespace HisUtil