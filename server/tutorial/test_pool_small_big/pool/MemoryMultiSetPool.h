#pragma once

#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

namespace HisUtil {

#if !defined SAFE_DELETE
#define SAFE_DELETE(p) delete (p); //(p)=NULL;
#endif

	//pool�� ������ ��ƿ� �� �ִ� �ִ� ũ��
	const int DEFAULT_RESERVED_VECTOR_SIZE = 1000;


	//////////////////////////////////////////////////////////////////////
	// CMemoryMultiSetPool 
	//////////////////////////////////////////////////////////////////////

	template<class T, class COMP>
	class CMemoryMultiSetPool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryMultiSetPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;


	protected:

		std::multiset<T*, COMP>	memUsed_;	// ���� ���Ǵ� �޸�
		std::queue<T*>	memFree_;	// ��� ������� �޸�
		std::set<T*>	memLeak_;	// ȸ������ �ʴ� �޸�(create���� insert ���� ���� �޸�)


	protected:
		bool IsAllocated() { return bIsAllocated_; }

	public:
		CMemoryMultiSetPool(void) : bIsAllocated_(FALSE) {}
		virtual ~CMemoryMultiSetPool(void)
		{
			End();
		}


		// �⺻ �޸� Ǯ�� ����
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

		//�޸� Ǯ�� ��� �����Ѵ�.
		//�� �Լ��� ���̻� pool�� ������ ���̻� ������ ������ ����Ǿ�� �Ѵ�.
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

		// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
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

		// ��ü�� �����Ѵ�.
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
					memLeak_.insert(pT);//insert �Ǹ鼭 ȸ��ó���˴ϴ�.
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
			memLeak_.insert(pT);//insert �Ǹ鼭 ȸ��ó���˴ϴ�.
			return pT;
		}

		//pool�� ����մϴ�.
		bool Insert(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (IsAllocated())
				memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

			memUsed_.insert(pT);
			return TRUE;
		}

		// �̹� ����(GetFirstData()���� ȣ���) �޸𸮸� �ݳ��մϴ�. "memFree_"�� ��ȯ
		void Erase(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (IsAllocated())
			{
				memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.
				memFree_.push(pT);
			}
			memUsed_.erase(pT);
		}

		//pool�� begin() ������ �����ɴϴ�
		//�����ö� pool������ �����ϴ�.(�ʿ�ÿ� �ٽ� �־��ּž� �մϴ�.)
		T* GetFirstData()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (true == memUsed_.empty())
				return NULL;

			T* pT = *memUsed_.begin();
			memUsed_.erase(memUsed_.begin());
			if (IsAllocated())
				memLeak_.insert(pT);//insert �Ǹ鼭 ȸ��ó���˴ϴ�.
			return pT;
		}

		//pool�� ������ �����´�.
		//  start : ������ ó�� ��ġ(0���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
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

			//�����ϰ� �ִ� �������� ũ�� ������ ���� ����.
			// ����� ����Ÿ�� 1���̰�, start 1 �̸�...
			// start�� 0 �� ó������Ÿ�̹Ƿ� ������ ���� ����.
			//( start�� 0 �̸� ����Ÿ�� �ϳ� ������ �� �ִ�.)
			if ((INT32)GetUsedMemSize() <= start)
				return;


			std::multiset<T*, COMP>::iterator it = memUsed_.begin();
			for (; it != memUsed_.end(); ++it)
			{
				//������ġ���� �����´�.
				if (++index < start)
					continue;

				//�����ұ�??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare((*it), param))
						continue;
				}

				vecAll.push_back((*it));

				//������ ���� ��ŭ�� ��´�.
				if (cnt <= ++count || DEFAULT_RESERVED_VECTOR_SIZE <= count)
					break;
			}
		}


		INT32 GetUsedMemSize() { return (INT32)memUsed_.size(); }	//used pool ����	
		INT32 GetFreeMemSize() { return (INT32)memFree_.size(); }	//free pool ����
		INT32 GetLeakMemSize() { return (INT32)memLeak_.size(); }	//leak pool ����
	};

}//namespace HisUtil