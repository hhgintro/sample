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
		bool bIsAllocated_;			//true : CMemoryPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;

	protected:
		//std::map<K, T*>	memUsed_;	// ���� ���Ǵ� �޸�
		std::queue<T*>	memUsed_;	// ���� ���Ǵ� �޸�
		std::queue<T*>	memFree_;	// ��� ������� �޸�
		std::set<T*>	memLeak_;	// ȸ������ �ʴ� �޸�(create���� insert ���� ���� �޸�)

	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryQueuePool(void) : bIsAllocated_(false) {}
		virtual ~CMemoryQueuePool(void)
		{
			End();
		}


		// �⺻ �޸� Ǯ�� ����
		//template<typename C>
		void Begin(int size = 1);

		//�޸� Ǯ�� ��� �����Ѵ�.
		void End();

		// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
		void Clear();


		// ��ü�� �����Ѵ�.
		//template<typename C>
		T* Create();

		//use pool�� �ִ´�.(free pool�� �������� Release�� ����ض�.)
		bool Push(T* pT);

		//ó�� ��ü�� �����Ѵ�.
		T* Front();


		//free pool �� �־��ش�.
		// �������� ���� ���� ����ó����
		void Pop();


		//ó�� ��ü�� �����ϰ�, pool ���� ������.
		//Front_Pop() ȣ���Ŀ��� pool���� �����Ƿ� Push �Ǵ� Release�� ���� �־��־�� �Ѵ�.
		//���� : ���������� pool�� �����ϱ� ���� ����մϴ�.
		T* Front_Pop();

		//free pool�� �ִ´�.(use pool�� �������� Push�� ����ض�.)
		bool Release(T* pT);


		INT32 GetUsedMemSize()  { AUTO_LOCK(cs_); return (INT32)memUsed_.size(); }	//used pool ����	
		INT32 GetFreeMemSize()	{ AUTO_LOCK(cs_); return (INT32)memFree_.size(); }
		INT32 GetLeakMemSize()	{ AUTO_LOCK(cs_); return (INT32)memLeak_.size(); }
	};

}//namespace HisUtil