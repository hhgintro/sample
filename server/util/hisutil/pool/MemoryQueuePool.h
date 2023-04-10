#pragma once


#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

namespace HisUtil {

#if !defined SAFE_DELETE
#define SAFE_DELETE(p) delete (p); (p)=NULL;
#endif

	//////////////////////////////////////////////////////////////////////
	// CMemoryQueuePool 
	//////////////////////////////////////////////////////////////////////

	template<typename T>
	class CMemoryQueuePool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryPool에서 메모리를 할당한 경우
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;

	protected:
		//std::map<K, T*>	memUsed_;	// 현재 사용되는 메모리
		std::queue<T*>	memUsed_;	// 현재 사용되는 메모리
		std::queue<T*>	memFree_;	// 사용 대기중인 메모리
		std::set<T*>	memLeak_;	// 회수되지 않는 메모리(create이후 insert 되지 않은 메모리)

	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryQueuePool(void) : bIsAllocated_(false) {}
		virtual ~CMemoryQueuePool(void)
		{
			End();
		}


		// 기본 메모리 풀을 잡음
		//template<typename C>
		void Begin(int size = 1);

		//메모리 풀을 모두 삭제한다.
		void End();

		// 사용 메모리를 모두 지우고 "memFree_"에 반환
		void Clear();


		// 개체를 생성한다.
		//template<typename C>
		T* Create();

		//use pool에 넣는다.(free pool에 넣을때는 Release를 사용해라.)
		bool Push(T* pT);

		//처음 개체에 접근한다.
		T* Front();


		//free pool 에 넣어준다.
		// 생성되지 않은 경우는 무시처리됨
		void Pop();


		//처음 개체에 접근하고, pool 에서 빼진다.
		//Front_Pop() 호출후에는 pool에서 빼지므로 Push 또는 Release를 통해 넣어주어야 한다.
		//목적 : 순차적으로 pool에 접근하기 위해 사용합니다.
		T* Front_Pop();

		//free pool에 넣는다.(use pool에 넣을때는 Push를 사용해라.)
		bool Release(T* pT);


		INT32 GetUsedMemSize()  { AUTO_LOCK(cs_); return (INT32)memUsed_.size(); }	//used pool 개수	
		INT32 GetFreeMemSize()	{ AUTO_LOCK(cs_); return (INT32)memFree_.size(); }
		INT32 GetLeakMemSize()	{ AUTO_LOCK(cs_); return (INT32)memLeak_.size(); }
	};

}//namespace HisUtil