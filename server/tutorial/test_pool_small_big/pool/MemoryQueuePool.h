#pragma once


#include <queue>
#include <set>
#include <vector>
#include <typeinfo>

namespace HisUtil {


	//////////////////////////////////////////////////////////////////////
	// CMemoryQueuePool 
	//////////////////////////////////////////////////////////////////////

	template<class T>
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
		CMemoryQueuePool(void) : bIsAllocated_(FALSE) ()
			virtual ~CMemoryQueuePool(void)
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
					//NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
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
				while (!memUsed_.empty())
				{
					SAFE_DELETE(memUsed_.front());
					memUsed_.pop();
				}
			}

			{//delete free memory
				while (!memFree_.empty()) {
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


			while (false == memUsed_.empty())
			{
				T* pT = memUsed_.front();
				memUsed_.pop();

				if (IsAllocated())
					memFree_.push(pT);
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
					//CEventLog::Instance().NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
					printf("error : %s\n", e.what());
					return NULL;
				}
			}

			T* pT = memFree_.front();
			memFree_.pop();
			memLeak_.insert(pT);//push �Ǹ鼭 ȸ��ó���˴ϴ�.
			return pT;
		}


		//pool�� �ִ´�.
		bool Push(T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (IsAllocated())
				memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

			memUsed_.push(pT);
			return TRUE;
		}


		//ó�� ��ü�� �����Ѵ�.
		T* Front()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (true == memUsed_.empty())
				return NULL;

			return memUsed_.front();
		}


		//free pool �� �־��ش�.
		// �������� ���� ���� ����ó����
		void Pop()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (true == memUsed_.empty())
				return;

			T* pT = memUsed_.front();
			memUsed_.pop();

			if (IsAllocated())
				memFree_.push(pT);
		}


		//ó�� ��ü�� �����ϰ�, pool ���� ������.
		//Front_Pop() ȣ���Ŀ��� pool���� �����Ƿ� Push�� ���� �־��־�� �Ѵ�.
		//���� : ���������� pool�� �����ϱ� ���� ����մϴ�.
		T* Front_Pop()
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);


			if (true == memUsed_.empty())
				return NULL;

			T* pT = memUsed_.front();
			memUsed_.pop();

			if (IsAllocated())
				memLeak_.insert(pT);//push �Ǹ鼭 ȸ��ó���˴ϴ�.
			return pT;
		}


		INT32 GetUsedMemSize()	{ return (INT32)memUsed_.size(); }
		INT32 GetFreeMemSize()	{ return (INT32)memFree_.size(); }
		INT32 GetLeakMemSize()	{ return (INT32)memLeak_.size(); }
	};

}//namespace HisUtil