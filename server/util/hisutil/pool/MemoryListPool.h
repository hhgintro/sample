#pragma once

#include <list>
#include <queue>
#include <set>
#include <vector>
//#include <typeinfo>


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
	// CMemoryListPool 
	//////////////////////////////////////////////////////////////////////

	template<typename T>
	class CMemoryListPool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryListPool에서 메모리를 할당한 경우
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;


	protected:

		std::list<T*>	memUsed_;	// 현재 사용되는 메모리
		std::queue<T*>	memFree_;	// 현재 사용되지 않는 메모리
		std::set<T*>	memLeak_;	// 회수되지 않는 메모리(create이후 insert 되지 않은 메모리)

	protected:
		bool IsAllocated() { return bIsAllocated_; }


	public:
		CMemoryListPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryListPool(void)
		{
			End();
		}


		// 기본 메모리 풀을 잡음
		void Begin(int size = 1);

		//메모리 풀을 모두 삭제한다.
		void End();

		// 사용 메모리를 모두 지우고 "memFree_"에 반환
		void Clear();

		// 개체를 생성한다.
		T* Create();

		////pool에 등록합니다.
		bool Insert(T* pT, BOOL(*funcCompare)(T*, T*) = NULL);

		//// key에 해당하는 사용되는 메모리에서 지우고 "memFree_"에 반환
		void Erase(T* pT);

		//// 키로 데이터를 찾아라.
		//T* Find(K key);

		//pool의 정보를 가져온다.
		//  start : 가져온 처음 위치(0부터 시작됩니다.)
		//  cnt : 가져올 개수
		//  funcCompare : 비교를 진행할 함수의 포인터
		//  param : 함수 포인터의 전달 인자
		void GetAllList(std::vector<T>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL);

		//pool의 정보를 역순으로 가져온다.
		//  start : 가져온 처음 위치( 0 부터 시작됩니다.)
		//  cnt : 가져올 개수
		//  funcCompare : 비교를 진행할 함수의 포인터
		//  param : 함수 포인터의 전달 인자
		void GetAllReverseList(std::vector<T>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL);


		int GetUsedMemSize()	{ return (int)memUsed_.size(); }	//used pool 개수	
		int GetFreeMemSize()	{ return (int)memFree_.size(); }	//free pool 개수
		int GetLeakMemSize()	{ return (int)memLeak_.size(); }	//leak pool 개수
	};


}//namespace HisUtil
