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

	//pool�� ������ ��ƿ� �� �ִ� �ִ� ũ��
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
		bool bIsAllocated_;			//true : CMemoryListPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;


	protected:

		std::list<T*>	memUsed_;	// ���� ���Ǵ� �޸�
		std::queue<T*>	memFree_;	// ���� ������ �ʴ� �޸�
		std::set<T*>	memLeak_;	// ȸ������ �ʴ� �޸�(create���� insert ���� ���� �޸�)

	protected:
		bool IsAllocated() { return bIsAllocated_; }


	public:
		CMemoryListPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryListPool(void)
		{
			End();
		}


		// �⺻ �޸� Ǯ�� ����
		void Begin(int size = 1);

		//�޸� Ǯ�� ��� �����Ѵ�.
		void End();

		// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
		void Clear();

		// ��ü�� �����Ѵ�.
		T* Create();

		////pool�� ����մϴ�.
		bool Insert(T* pT, BOOL(*funcCompare)(T*, T*) = NULL);

		//// key�� �ش��ϴ� ���Ǵ� �޸𸮿��� ����� "memFree_"�� ��ȯ
		void Erase(T* pT);

		//// Ű�� �����͸� ã�ƶ�.
		//T* Find(K key);

		//pool�� ������ �����´�.
		//  start : ������ ó�� ��ġ(0���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllList(std::vector<T>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL);

		//pool�� ������ �������� �����´�.
		//  start : ������ ó�� ��ġ( 0 ���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllReverseList(std::vector<T>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL);


		int GetUsedMemSize()	{ return (int)memUsed_.size(); }	//used pool ����	
		int GetFreeMemSize()	{ return (int)memFree_.size(); }	//free pool ����
		int GetLeakMemSize()	{ return (int)memLeak_.size(); }	//leak pool ����
	};


}//namespace HisUtil
