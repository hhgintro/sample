#pragma once

#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

namespace HisUtil {

#if !defined SAFE_DELETE
#define SAFE_DELETE(p) delete (p); //(p)=NULL;
#endif

	//pool의 정보를 담아올 수 있는 최대 크기
	const int DEFAULT_RESERVED_VECTOR_SIZE = 1000;


	//////////////////////////////////////////////////////////////////////
	// CMemoryMultiSetPool 
	//////////////////////////////////////////////////////////////////////

	template<class T, class COMP>
	class CMemoryMultiSetPool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryMultiSetPool에서 메모리를 할당한 경우
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;


	protected:

		std::multiset<T*, COMP>	memUsed_;	// 현재 사용되는 메모리
		std::queue<T*>	memFree_;	// 사용 대기중인 메모리
		std::set<T*>	memLeak_;	// 회수되지 않는 메모리(create이후 insert 되지 않은 메모리)


	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryMultiSetPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryMultiSetPool(void)
		{
			End();
		}


		// 기본 메모리 풀을 잡음
		void Begin(int size = 1)
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
					e.what();
					//LOGEVENT("HG_RED", _T("error %s"), e.what())
				}
			}
		}

		//메모리 풀을 모두 삭제한다.
		//이 함수는 더이상 pool의 정보가 더이상 사용되지 않음이 보장되어야 한다.
		void End()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			{//delete used memory
				std::multiset<T*, COMP>::iterator it = memUsed_.begin();
				while (it != memUsed_.end())
				{
					if (IsAllocated())
						SAFE_DELETE(*it);

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
						SAFE_DELETE((*it));

					++it;
				}
				memLeak_.clear();
			}
		}

		// 사용 메모리를 모두 지우고 "memFree_"에 반환
		void Clear()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			{//used memory. come back to the free memory
				std::multiset<T*, COMP>::iterator it = memUsed_.begin();
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
		T* Create()
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
					e.what();
					//LOGEVENT("HG_RED", _T("error %s"), e.what())
					return NULL;
				}
			}

			T* pT = memFree_.front();
			memFree_.pop();
			memLeak_.insert(pT);//insert 되면서 회수처리됩니다.
			return pT;
		}

		//pool에 등록합니다.
		bool Insert(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (IsAllocated())
				memLeak_.erase(pT);//create에서 생성된 개체는 leak되지 않고 회수되었습니다.

			memUsed_.insert(pT);
			return TRUE;
		}

		// 이미 사용된(GetFirstData()에서 호출된) 메모리를 반납합니다. "memFree_"에 반환
		void Erase(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (IsAllocated())
			{
				memLeak_.erase(pT);//create에서 생성된 개체는 leak되지 않고 회수되었습니다.
				memFree_.push(pT);
			}
			memUsed_.erase(pT);
		}

		//pool의 begin() 정보를 가져옵니다
		//가져올때 pool에서는 빠집니다.(필요시엔 다시 넣어주셔야 합니다.)
		T* GetFirstData()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (true == memUsed_.empty())
				return NULL;

			T* pT = *memUsed_.begin();
			memUsed_.erase(memUsed_.begin());
			if (IsAllocated())
				memLeak_.insert(pT);//insert 되면서 회수처리됩니다.
			return pT;
		}

		//pool의 정보를 가져온다.
		//  start : 가져온 처음 위치(0부터 시작됩니다.)
		//  cnt : 가져올 개수
		//  funcCompare : 비교를 진행할 함수의 포인터
		//  param : 함수 포인터의 전달 인자
		void GetAllList(std::vector<T*>& vecAll
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


			std::multiset<T*, COMP>::iterator it = memUsed_.begin();
			for (; it != memUsed_.end(); ++it)
			{
				//시작위치부터 가져온다.
				if (++index < start)
					continue;

				//취합할까??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare((*it), param))
						continue;
				}

				vecAll.push_back((*it));

				//지정된 개수 만큼만 담는다.
				if (cnt <= ++count || DEFAULT_RESERVED_VECTOR_SIZE <= count)
					break;
			}
		}


		INT32 GetUsedMemSize() { return (INT32)memUsed_.size(); }	//used pool 개수	
		INT32 GetFreeMemSize() { return (INT32)memFree_.size(); }	//free pool 개수
		INT32 GetLeakMemSize() { return (INT32)memLeak_.size(); }	//leak pool 개수
	};

}//namespace HisUtil