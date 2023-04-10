#pragma once

#include <string>
#include <iostream>	//std::cout
//#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

//#include "../thread/HisCritSec.h"

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
	// CMemoryPool 
	//////////////////////////////////////////////////////////////////////

	//CONTAINER : std::map or std::unordered_map, etc
	template<class K, class T, class CONTAINER=std::unordered_map<K,T*> >
	class CMemoryPool// public IMemoryPool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryPool에서 메모리를 할당한 경우
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;

	protected:
		CONTAINER			memUsed_;	// 현재 사용되는 메모리
		::std::queue<T*>	memFree_;	// 사용 대기중인 메모리
		::std::set<T*>		memLeak_;	// 회수되지 않는 메모리(create이후 insert 되지 않은 메모리)

	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryPool(void)
		{
			End();
		}


		// 기본 메모리 풀을 잡음
		//template<class C>
		void Begin(int size = 1);

		//메모리 풀을 모두 삭제한다.
		//이 함수는 더이상 pool의 정보가 더이상 사용되지 않음이 보장되어야 한다.
		void End();

		// 사용 메모리를 모두 지우고 "memFree_"에 반환
		void Clear();


		// 개체를 생성한다.
		//template<class C>
		T* Create();

		//pool에 등록합니다.
		BOOL Insert(K key, T* pT);

		// key에 해당하는 사용되는 메모리에서 지우고 "memFree_"에 반환
		void Erase(K key);

		// "memFree_"에 반환
		// memFree_는 중복을 체크하지 않습니다.그러니 중복반환이 되지 않도록 각별히 주의해 주세요
		void Erase(T* pT);

		// key에 해당하는 사용되는 메모리를 지우고, "memFree_"에 반환하지 않는다.
		// 즉. 다른 pool로 이전을 하기 위한 목적임(다른 pool은 당연히 IsAllocated()가 true상태여야 한다)
		// 다른 pool에서는 insert()를 통해 넣어주면 된다.
		// 사용후 반환은 Erase(T* pT)를 호출하세요( 이거 아님-Erase(K key))
		T* Pop(K key);

		// 맨앞에 사용되는 메모리를 지우고, "memFree_"에 반환하지 않는다.
		// 즉. 다른 pool로 이전을 하기 위한 목적임(다른 pool은 당연히 IsAllocated()가 true상태여야 한다)
		// 다른 pool에서는 insert()를 통해 넣어주면 된다.
		// 사용후 반환은 Erase(T* pT)를 호출하세요( 이거 아님-Erase(K key))
		T* Pop();

		// 키로 데이터를 찾아라.
		T* Find(K key);

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
		void GetAllList(::std::vector<T*>& vecAll
						, INT32 start = 0
						, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
						, BOOL(*funcCompare)(T*, void*) = NULL
						, void* param = NULL);

		//pool의 정보를 역순으로 가져온다.
		//  start : 가져온 처음 위치( 0 부터 시작됩니다.)
		//  cnt : 가져올 개수
		//  funcCompare : 비교를 진행할 함수의 포인터
		//  param : 함수 포인터의 전달 인자
		void GetAllReverseList(::std::vector<T*>& vecAll
							, INT32 start = 0
							, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
							, BOOL(*funcCompare)(T*, void*) = NULL
							, void* param = NULL);

		//insert()시 key값을 출력(디버깅)하기 위한 용도
		INT32 GetValue(INT32 val) { return val; }
		UINT32 GetValue(UINT32 val) { return val; }
		INT64 GetValue(INT64 val) { return val; }
		UINT64 GetValue(UINT64 val) { return val; }
		const char* GetValue(std::string val) { return val.c_str(); }
		const wchar_t* GetValue(std::wstring val) { return val.c_str(); }
		//..//insert()시 key값을 출력(디버깅)하기 위한 용도

		INT32 GetUsedMemSize() { AUTO_LOCK(cs_); return (INT32)memUsed_.size(); }	//used pool 개수	
		INT32 GetFreeMemSize() { AUTO_LOCK(cs_); return (INT32)memFree_.size(); }	//free pool 개수
		INT32 GetLeakMemSize() { AUTO_LOCK(cs_); return (INT32)memLeak_.size(); }	//leak pool 개수
	};

}//namespace HisUtil