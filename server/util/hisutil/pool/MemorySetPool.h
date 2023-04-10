#pragma once

#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

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
	// CMemorySetPool 
	//////////////////////////////////////////////////////////////////////

	template<class T>
	class CMemorySetPool
	{
	private:
		bool bIsAllocated_;			//true : CMemorySetPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;


	protected:

		std::set<T*>	memUsed_;	// ���� ���Ǵ� �޸�
		std::queue<T*>	memFree_;	// ��� ������� �޸�
		std::set<T*>	memLeak_;	// ȸ������ �ʴ� �޸�(create���� insert ���� ���� �޸�)


	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemorySetPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemorySetPool(void)
		{
			End();
		}


		// �⺻ �޸� Ǯ�� ����
		void Begin(int size = 1);

		//�޸� Ǯ�� ��� �����Ѵ�.
		//�� �Լ��� ���̻� pool�� ������ ���̻� ������ ������ ����Ǿ�� �Ѵ�.
		void End();

		// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
		void Clear();

		// ��ü�� �����Ѵ�.
		T* Create();

		//pool�� ����մϴ�.
		bool Insert(T* pT);

		T* Find(T& rT);
		void Erase(T& rT);

		// �̹� ����(GetFirstData()���� ȣ���) �޸𸮸� �ݳ��մϴ�. "memFree_"�� ��ȯ
		void Erase(T* pT);

		//pool�� begin() ������ �����ɴϴ�
		//�����ö� pool������ �����ϴ�.(�ʿ�ÿ� �ٽ� �־��ּž� �մϴ�.)
		T* GetFirstData();

		//pool�� ������ �����´�.
		//  start : ������ ó�� ��ġ(0���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllList(std::vector<T*>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL );


		INT32 GetUsedMemSize() { return (INT32)memUsed_.size(); }	//used pool ����	
		INT32 GetFreeMemSize() { return (INT32)memFree_.size(); }	//free pool ����
		INT32 GetLeakMemSize() { return (INT32)memLeak_.size(); }	//leak pool ����
	};

}//namespace HisUtil