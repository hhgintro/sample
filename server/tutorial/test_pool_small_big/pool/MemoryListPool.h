#pragma once

#include <list>
#include <queue>
#include <set>
#include <vector>
//#include <typeinfo>


namespace HisUtil {

	const int DEFAULT_RESERVED_VECTOR_SIZE = 1000;

	//////////////////////////////////////////////////////////////////////
	// CMemoryListPool 
	//////////////////////////////////////////////////////////////////////

	template<class T>
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
					//NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), e.what());
					printf("error : %s\n", e.what());
				}
			}
		}

		//�޸� Ǯ�� ��� �����Ѵ�.
		void End()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			{//delete used memory
				std::list<T*>::iterator it = memUsed_.begin();
				while (it != memUsed_.end())
				{
					if (IsAllocated())
						SAFE_DELETE((*it));

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
				std::list<T*>::iterator it = memUsed_.begin();
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
					return new T;
				}
				catch (std::bad_alloc& e)
				{
					//LOGEVENT("HG_RED", _T("error %s"), e.what())
					printf("error : %s\n", e.what());
					return NULL;
				}
			}

			T* pT = memFree_.front();
			memFree_.pop();
			return pT;
		}

		////pool�� ����մϴ�.
		bool Insert(T* pT, BOOL(*funcCompare)(T*, T*) = NULL)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			if (true == memUsed_.empty())
			{
				memUsed_.push_back(pT);
				return true;
			}

			//�Լ� �����Ͱ� �����Ǿ� �ִٸ�...
			if (NULL != funcCompare)
			{
				std::list<T*>::iterator it = memUsed_.begin();
				for (; it != memUsed_.end(); ++it)
				{
					//��� �߰��Ǵ� ����Ÿ�� ���������� �������ϰ�쿡 �տ� �־��ش�
					if (TRUE == funcCompare(pT, (*it)))
					{
						memUsed_.insert(it, pT);
						return true;
					}//..if(RUE == funcCompare(pT, (*it)))
				}//..for(; it != memUsed_.end(); ++it)
			}//..if(NULL != funcCompare)

			//�Ǹ������� �־��ش�.
			memUsed_.push_back(pT);
			return TRUE;
		}

		//// key�� �ش��ϴ� ���Ǵ� �޸𸮿��� ����� "memFree_"�� ��ȯ
		void Erase(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			std::list<T*>::iterator it;
			it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (*it == pT)
				{
					it = memUsed_.erase(it);
					break;
				}
				++it;
			}
		}

		//// Ű�� �����͸� ã�ƶ�.
		//T* Find(K key);

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


			std::list<T*>::iterator it = memUsed_.begin();
			for (; it != memUsed_.end(); ++it)
			{
				//������ġ���� �����´�.
				if (++index < start)
					continue;

				//�����ұ�??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare(*it, param))
						continue;
				}

				vecAll.push_back(*it);

				//������ ���� ��ŭ�� ��´�.
				if (cnt <= ++count || DEFAULT_RESERVED_VECTOR_SIZE <= count)
					break;
			}
		}

		//pool�� ������ �������� �����´�.
		//  start : ������ ó�� ��ġ( 0 ���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllReverseList(std::vector<T*>& vecAll
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

			std::list<T*>::reverse_iterator it = memUsed_.rbegin();
			for (; it != memUsed_.rend(); ++it)
			{
				//������ġ���� �����´�.
				if (++index < start)
					continue;

				//�����ұ�??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare(*it, param))
						continue;
				}

				vecAll.push_back(*it);

				//������ ���� ��ŭ�� ��´�.
				if (++count >= cnt)
					break;
			}
		}


		int GetUsedMemSize()	{ return (int)memUsed_.size(); }	//used pool ����	
		int GetFreeMemSize()	{ return (int)memFree_.size(); }	//free pool ����
		int GetLeakMemSize()	{ return (int)memLeak_.size(); }	//leak pool ����
	};


}//namespace HisUtil
