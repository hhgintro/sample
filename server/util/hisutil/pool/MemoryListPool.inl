#pragma once

#include "MemoryListPool.h"


namespace HisUtil {

	// 기본 메모리 풀을 잡음
	template<class T>
	void CMemoryListPool<T>::Begin(int size = 1)
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
				//NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), e.what());
				printf("error : %s\n", e.what());
			}
		}
	}

	//메모리 풀을 모두 삭제한다.
	template<class T>
	void CMemoryListPool<T>::End()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//delete used memory
			std::list<T*>::iterator it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (IsAllocated())
					SAFE_DELETE((*it));

				++it;
			}
			memUsed_.clear();
		}

		{//delete free memory
			while (!memFree_.empty())
			{
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
	void CMemoryListPool<T>::Clear()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//used memory. come back to the free memory
			std::list<T*>::iterator it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (IsAllocated())
					memFree_.push((*it));

				++it;
			}
			memUsed_.clear();
		}

		{//delete leak memory
			std::set<T*>::iterator it = memLeak_.begin();
			while (it != memLeak_.end())
			{
				if (IsAllocated())
					memFree_.push((*it));

				++it;
			}
			memLeak_.clear();
		}
	}

	// 개체를 생성한다.
	template<class T>
	T* CMemoryListPool<T>::Create()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		bIsAllocated_ = TRUE;

		if (memFree_.empty())
		{
			try
			{
				return new T;
			}
			catch (std::bad_alloc& e)
			{
				//LOGEVENT("HG_RED", _T("error %s"), e.what())
				printf("error : %s\n", e.what());
				return NULL;
			}
		}

		T* pT = memFree_.front();
		memFree_.pop();
		return pT;
	}

	////pool에 등록합니다.
	template<class T>
	bool CMemoryListPool<T>::Insert(T* pT, BOOL(*funcCompare)(T*, T*) = NULL)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		if (true == memUsed_.empty())
		{
			memUsed_.push_back(pT);
			return true;
		}

		//함수 포인터가 설정되어 있다면...
		if (NULL != funcCompare)
		{
			std::list<T*>::iterator it = memUsed_.begin();
			for (; it != memUsed_.end(); ++it)
			{
				//방금 추가되는 데이타가 이전꺼보다 작은값일경우에 앞에 넣어준다
				if (TRUE == funcCompare(pT, (*it)))
				{
					memUsed_.insert(it, pT);
					return true;
				}//..if(RUE == funcCompare(pT, (*it)))
			}//..for(; it != memUsed_.end(); ++it)
		}//..if(NULL != funcCompare)

		//맨마지막에 넣어준다.
		memUsed_.push_back(pT);
		return TRUE;
	}

	//// key에 해당하는 사용되는 메모리에서 지우고 "memFree_"에 반환
	template<class T>
	void CMemoryListPool<T>::Erase(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		std::list<T*>::iterator it;
		it = memUsed_.begin();
		while (it != memUsed_.end())
		{
			if (*it == pT)
			{
				it = memUsed_.erase(it);
				break;
			}
			++it;
		}
	}

	//// 키로 데이터를 찾아라.
	//T* Find(K key);

	//pool의 정보를 가져온다.
	//  start : 가져온 처음 위치(0부터 시작됩니다.)
	//  cnt : 가져올 개수
	//  funcCompare : 비교를 진행할 함수의 포인터
	//  param : 함수 포인터의 전달 인자
	template<class T>
	void CMemoryListPool<T>::GetAllList(
		std::vector<T*>& vecAll
		, INT32 start = 0
		, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
		, BOOL(*funcCompare)(T*, void*) = NULL
		, void* param = NULL)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		vecAll.reserve(DEFAULT_RESERVED_VECTOR_SIZE);


		INT32 index = -1;
		INT32 count = 0;

		//저장하고 있는 개수보다 크면 가져올 것이 없다.
		// 저장된 데이타가 1개이고, start 1 이면...
		// start는 0 이 처음데이타이므로 가져올 것이 없다.
		//( start가 0 이면 데이타를 하나 가져올 수 있다.)
		if ((INT32)GetUsedMemSize() <= start)
			return;


		std::list<T*>::iterator it = memUsed_.begin();
		for (; it != memUsed_.end(); ++it)
		{
			//시작위치부터 가져온다.
			if (++index < start)
				continue;

			//취합할까??
			if (NULL != funcCompare)
			{
				if (FALSE == funcCompare(*it, param))
					continue;
			}

			vecAll.push_back(*it);

			//지정된 개수 만큼만 담는다.
			if (cnt <= ++count || DEFAULT_RESERVED_VECTOR_SIZE <= count)
				break;
		}
	}

	//pool의 정보를 역순으로 가져온다.
	//  start : 가져온 처음 위치( 0 부터 시작됩니다.)
	//  cnt : 가져올 개수
	//  funcCompare : 비교를 진행할 함수의 포인터
	//  param : 함수 포인터의 전달 인자
	template<class T>
	void CMemoryListPool<T>::GetAllReverseList(
		std::vector<T*>& vecAll
		, INT32 start = 0
		, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
		, BOOL(*funcCompare)(T*, void*) = NULL
		, void* param = NULL)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		vecAll.reserve(DEFAULT_RESERVED_VECTOR_SIZE);

		INT32 index = -1;
		INT32 count = 0;

		//저장하고 있는 개수보다 크면 가져올 것이 없다.
		// 저장된 데이타가 1개이고, start 1 이면...
		// start는 0 이 처음데이타이므로 가져올 것이 없다.
		//( start가 0 이면 데이타를 하나 가져올 수 있다.)
		if ((INT32)GetUsedMemSize() <= start)
			return;

		std::list<T*>::reverse_iterator it = memUsed_.rbegin();
		for (; it != memUsed_.rend(); ++it)
		{
			//시작위치부터 가져온다.
			if (++index < start)
				continue;

			//취합할까??
			if (NULL != funcCompare)
			{
				if (FALSE == funcCompare(*it, param))
					continue;
			}

			vecAll.push_back(*it);

			//지정된 개수 만큼만 담는다.
			if (++count >= cnt)
				break;
		}
	}


}//namespace HisUtil
