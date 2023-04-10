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

	//pool�� ������ ��ƿ� �� �ִ� �ִ� ũ��
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
		bool bIsAllocated_;			//true : CMemoryPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;

	protected:
		CONTAINER			memUsed_;	// ���� ���Ǵ� �޸�
		::std::queue<T*>	memFree_;	// ��� ������� �޸�
		::std::set<T*>		memLeak_;	// ȸ������ �ʴ� �޸�(create���� insert ���� ���� �޸�)

	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryPool(void)
		{
			End();
		}


		// �⺻ �޸� Ǯ�� ����
		//template<class C>
		void Begin(int size = 1);

		//�޸� Ǯ�� ��� �����Ѵ�.
		//�� �Լ��� ���̻� pool�� ������ ���̻� ������ ������ ����Ǿ�� �Ѵ�.
		void End();

		// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
		void Clear();


		// ��ü�� �����Ѵ�.
		//template<class C>
		T* Create();

		//pool�� ����մϴ�.
		BOOL Insert(K key, T* pT);

		// key�� �ش��ϴ� ���Ǵ� �޸𸮿��� ����� "memFree_"�� ��ȯ
		void Erase(K key);

		// "memFree_"�� ��ȯ
		// memFree_�� �ߺ��� üũ���� �ʽ��ϴ�.�׷��� �ߺ���ȯ�� ���� �ʵ��� ������ ������ �ּ���
		void Erase(T* pT);

		// key�� �ش��ϴ� ���Ǵ� �޸𸮸� �����, "memFree_"�� ��ȯ���� �ʴ´�.
		// ��. �ٸ� pool�� ������ �ϱ� ���� ������(�ٸ� pool�� �翬�� IsAllocated()�� true���¿��� �Ѵ�)
		// �ٸ� pool������ insert()�� ���� �־��ָ� �ȴ�.
		// ����� ��ȯ�� Erase(T* pT)�� ȣ���ϼ���( �̰� �ƴ�-Erase(K key))
		T* Pop(K key);

		// �Ǿտ� ���Ǵ� �޸𸮸� �����, "memFree_"�� ��ȯ���� �ʴ´�.
		// ��. �ٸ� pool�� ������ �ϱ� ���� ������(�ٸ� pool�� �翬�� IsAllocated()�� true���¿��� �Ѵ�)
		// �ٸ� pool������ insert()�� ���� �־��ָ� �ȴ�.
		// ����� ��ȯ�� Erase(T* pT)�� ȣ���ϼ���( �̰� �ƴ�-Erase(K key))
		T* Pop();

		// Ű�� �����͸� ã�ƶ�.
		T* Find(K key);

		//pool�� ������ �����´�.
		//  start : ������ ó�� ��ġ(0���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		//
		//	����:
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

		//pool�� ������ �������� �����´�.
		//  start : ������ ó�� ��ġ( 0 ���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllReverseList(::std::vector<T*>& vecAll
							, INT32 start = 0
							, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
							, BOOL(*funcCompare)(T*, void*) = NULL
							, void* param = NULL);

		//insert()�� key���� ���(�����)�ϱ� ���� �뵵
		INT32 GetValue(INT32 val) { return val; }
		UINT32 GetValue(UINT32 val) { return val; }
		INT64 GetValue(INT64 val) { return val; }
		UINT64 GetValue(UINT64 val) { return val; }
		const char* GetValue(std::string val) { return val.c_str(); }
		const wchar_t* GetValue(std::wstring val) { return val.c_str(); }
		//..//insert()�� key���� ���(�����)�ϱ� ���� �뵵

		INT32 GetUsedMemSize() { AUTO_LOCK(cs_); return (INT32)memUsed_.size(); }	//used pool ����	
		INT32 GetFreeMemSize() { AUTO_LOCK(cs_); return (INT32)memFree_.size(); }	//free pool ����
		INT32 GetLeakMemSize() { AUTO_LOCK(cs_); return (INT32)memLeak_.size(); }	//leak pool ����
	};

}//namespace HisUtil