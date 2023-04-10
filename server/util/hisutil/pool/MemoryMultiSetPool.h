#pragma once

#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

namespace HisUtil {

#if !defined SAFE_DELETE
#define SAFE_DELETE(p) delete (p); (p)=NULL;
#endif

	//pool의 정보를 담아올 수 있는 최대 크기
	//const int DEFAULT_RESERVED_VECTOR_SIZE = 1000;
#if !defined DEFAULT_RESERVED_VECTOR_SIZE
#define DEFAULT_RESERVED_VECTOR_SIZE	1000
#endif


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
		void Begin(int size = 1);

		//메모리 풀을 모두 삭제한다.
		//이 함수는 더이상 pool의 정보가 더이상 사용되지 않음이 보장되어야 한다.
		void End();

		// 사용 메모리를 모두 지우고 "memFree_"에 반환
		void Clear();

		// 개체를 생성한다.
		T* Create();

		//pool에 등록합니다.
		bool Insert(T* pT);

		// 이미 사용된(GetFirstData()에서 호출된) 메모리를 반납합니다. "memFree_"에 반환
		void Erase(T* pT);

		//pool의 begin() 정보를 가져옵니다
		//가져올때 pool에서는 빠집니다.(필요시엔 다시 넣어주셔야 합니다.)
		T* GetFirstData();

		//pool의 정보를 가져온다.
		//  start : 가져온 처음 위치(0부터 시작됩니다.)
		//  cnt : 가져올 개수
		//  funcCompare : 비교를 진행할 함수의 포인터
		//  param : 함수 포인터의 전달 인자
		void GetAllList(std::vector<T*>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL );


		INT32 GetUsedMemSize() { return (INT32)memUsed_.size(); }	//used pool 개수	
		INT32 GetFreeMemSize() { return (INT32)memFree_.size(); }	//free pool 개수
		INT32 GetLeakMemSize() { return (INT32)memLeak_.size(); }	//leak pool 개수
	};

}//namespace HisUtil