#pragma once

#include "MemoryPool.h"

namespace HisUtil {

	// 기본 메모리 풀을 잡음
	template<class K, class T, class CONTAINER>
	//template<class C>
	void CMemoryPool<K, T, CONTAINER>::Begin(int size = 1)
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
				//CEventLog::Instance().LogEvent("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
				printf("error : %s\n", e.what());
			}
		}
	}

	//메모리 풀을 모두 삭제한다.
	//이 함수는 더이상 pool의 정보가 더이상 사용되지 않음이 보장되어야 한다.
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::End()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//delete used memory
			CONTAINER::iterator it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (IsAllocated())
					SAFE_DELETE((*it).second);

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
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Clear()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//used memory. come back to the free memory
			CONTAINER::iterator it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (IsAllocated())
					memFree_.push((*it).second);

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
	template<typename K, typename T, typename CONTAINER>
	//template<typename C>
	T* CMemoryPool<K, T, CONTAINER>::Create()
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
		memLeak_.insert(pT);//insert 되면서 회수처리됩니다.
		return pT;
	}


	//pool에 등록합니다.
	template<class K, class T, class CONTAINER>
	BOOL CMemoryPool<K, T, CONTAINER>::Insert(K key, T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		if (IsAllocated())
			memLeak_.erase(pT);//create에서 생성된 개체는 leak되지 않고 회수되었습니다.

		//case 1. key가 등록되어 있다면 무시한다.
		if (memUsed_.find(key) != memUsed_.end())
		{
			//key값이 등록되어 있다면 FALSE 리턴
			//CEventLog::Instance().LogEvent("HG_RED", _T(" Duplicate insert key(0x%016x) [%s]")
			//	, key, Proud::StringA2W(typeid(this).name()));
			//printf(" Duplicate insert key(0x%016x) [%s]\n", key, typeid(this).name());
				
			//GetValue : wstring을 키로 사용할 경우...출력을 위해
			std::cout << _T(" Duplicate insert key(") << GetValue(key) << _T(") : ") << typeid(this).name() << std::endl;

			////	printf(" Duplicate insert key(0x%016x) [%s]\n", key, typeid(this).name());
			////	printf(" Duplicate insert key(%s) [%s]\n", key, typeid(this).name());
			//std::stringstream out;
			////std::cout << " Duplicate insert key(" << key << ") : " << typeid(this).name() << std::endl;
			//out << " Duplicate insert key(" << key << ") : " << typeid(this).name();
			////std::cout << out.str() << std::endl;
			//String str(out.str().c_str());
			//wprintf(L"%s\n", str.w_str());
			////HG_TODO : cout/wprintf 도 모두 되는데. CEventLog는 왜 안될까?
			////CEventLog::Instance().LogEvent("HG_RED", (WCHAR*)str.w_str());

			//회수 처리합니다.
			if (IsAllocated())
				memFree_.push(pT);

			return FALSE;
		}


		memUsed_.insert(std::make_pair(key, pT));
		return TRUE;
	}


	// key에 해당하는 사용되는 메모리에서 지우고 "memFree_"에 반환
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Erase(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
		it = memUsed_.find(key);
		if (it != memUsed_.end())
		{
			if (IsAllocated())
				memFree_.push((*it).second);

			it = memUsed_.erase(it);
		}
	}

	// "memFree_"에 반환
	// memFree_는 중복을 체크하지 않습니다.그러니 중복반환이 되지 않도록 각별히 주의해 주세요
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Erase(T* pT)
	{
		AUTO_LOCK(cs_);

		memLeak_.erase(pT);//회수되는 경우.
		memFree_.push(pT);
	}

	// key에 해당하는 사용되는 메모리를 지우고, "memFree_"에 반환하지 않는다.
	// 즉. 다른 pool로 이전을 하기 위한 목적임(다른 pool은 당연히 IsAllocated()가 true상태여야 한다)
	// 다른 pool에서는 insert()를 통해 넣어주면 된다.
	// 사용후 반환은 Erase(T* pT)를 호출하세요( 이거 아님-Erase(K key))
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Pop(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
		it = memUsed_.find(key);
		if (it != memUsed_.end())
		{
			T* pT = (*it).second;
			memUsed_.erase(it);
			return pT;
		}
		return NULL;
	}

	// 맨앞에 사용되는 메모리를 지우고, "memFree_"에 반환하지 않는다.
	// 즉. 다른 pool로 이전을 하기 위한 목적임(다른 pool은 당연히 IsAllocated()가 true상태여야 한다)
	// 다른 pool에서는 insert()를 통해 넣어주면 된다.
	// 사용후 반환은 Erase(T* pT)를 호출하세요( 이거 아님-Erase(K key))
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Pop()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it = memUsed_.begin();
		if (it != memUsed_.end())
		{
			T* pT = (*it).second;
			memUsed_.erase(it);
			return pT;
		}
		return NULL;
	}

	// 키로 데이터를 찾아라.
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Find(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
		it = memUsed_.find(key);
		if (it != memUsed_.end())
			return (*it).second;
		return NULL;
	}

	//pool의 정보를 가져온다.
	//  start : 가져온 처음 위치(0부터 시작됩니다.)
	//  cnt : 가져올 개수
	//  funcCompare : 비교를 진행할 함수의 포인터
	//  param : 함수 포인터의 전달 인자
	//
	//	예시:
	//		BOOL IS_BIG(AAA* a, void* val)
	//		{
	//			return (a->a > (int)val);
	//		}
	//		std::vector<AAA*> vecAll;
	//		pool.GetAllList(vecAll, 0, 3, IS_BIG, (void*)2);
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::GetAllList(
		::std::vector<T*>& vecAll
		, INT32 start = 0
		, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
		, BOOL(*funcCompare)(T*, void*) = NULL
		, void* param = NULL)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		vecAll.reserve(cnt);

		INT32 index = -1;
		INT32 count = 0;

		//저장하고 있는 개수보다 크면 가져올 것이 없다.
		// 저장된 데이타가 1개이고, start 1 이면...
		// start는 0 이 처음데이타이므로 가져올 것이 없다.
		//( start가 0 이면 데이타를 하나 가져올 수 있다.)
		if (GetUsedMemSize() <= start)
			return;


		CONTAINER::iterator it = memUsed_.begin();
		for (; it != memUsed_.end(); ++it)
		{
			//시작위치부터 가져온다.
			if (++index < start)
				continue;

			//취합할까??
			if (NULL != funcCompare)
			{
				if (FALSE == funcCompare(it->second, param))
					continue;
			}

			vecAll.push_back(it->second);

			//지정된 개수 만큼만 담는다.
			if (cnt <= ++count)
				break;
		}
	}

	//pool의 정보를 역순으로 가져온다.
	//  start : 가져온 처음 위치( 0 부터 시작됩니다.)
	//  cnt : 가져올 개수
	//  funcCompare : 비교를 진행할 함수의 포인터
	//  param : 함수 포인터의 전달 인자
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::GetAllReverseList(
		::std::vector<T*>& vecAll
		, INT32 start = 0
		, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
		, BOOL(*funcCompare)(T*, void*) = NULL
		, void* param = NULL)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		vecAll.reserve(cnt);

		INT32 index = -1;
		INT32 count = 0;

		//저장하고 있는 개수보다 크면 가져올 것이 없다.
		// 저장된 데이타가 1개이고, start 1 이면...
		// start는 0 이 처음데이타이므로 가져올 것이 없다.
		//( start가 0 이면 데이타를 하나 가져올 수 있다.)
		if (GetUsedMemSize() <= start)
			return;

		CONTAINER::reverse_iterator it = memUsed_.rbegin();
		for (; it != memUsed_.rend(); ++it)
		{
			//시작위치부터 가져온다.
			if (++index < start)
				continue;

			//취합할까??
			if (NULL != funcCompare)
			{
				if (FALSE == funcCompare(it->second, param))
					continue;
			}

			vecAll.push_back(it->second);

			//지정된 개수 만큼만 담는다.
			if (++count >= cnt)
				break;
		}
	}

}//namespace HisUtil