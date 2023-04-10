#pragma once


#include <map>
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
	// CMemoryPool 
	//////////////////////////////////////////////////////////////////////

	template<class K, class T>
	class CMemoryPool// public IMemoryPool
	{
	private:
		bool bIsAllocated_;			//true : CMemoryPool���� �޸𸮸� �Ҵ��� ���
		//Proud::CriticalSection cs_;
		CCritSecBase cs_;

	protected:
		::std::map<K, T*>	memUsed_;	// ���� ���Ǵ� �޸�
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
					//CEventLog::Instance().LogEvent("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
					printf("error : %s\n", e.what());
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
				std::map<K, T*>::iterator it = memUsed_.begin();
				while (it != memUsed_.end())
				{
					if (IsAllocated())
						SAFE_DELETE((*it).second);

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
				std::map<K, T*>::iterator it = memUsed_.begin();
				while (it != memUsed_.end())
				{
					if (IsAllocated())
						memFree_.push((*it).second);

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
					//CEventLog::Instance().NOTIFY_SYSTEM_LOG("HG_RED", _T("error %s"), Proud::StringA2W(e.what()));
					printf("error : %s\n", e.what());
					return NULL;
				}
			}

			T* pT = memFree_.front();
			memFree_.pop();
			memLeak_.insert(pT);//insert �Ǹ鼭 ȸ��ó���˴ϴ�.
			return pT;
		}


		//pool�� ����մϴ�.
		BOOL Insert(K key, T* pT)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			if (IsAllocated())
				memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

			//case 1. key�� ��ϵǾ� �ִٸ� �����Ѵ�.
			if (memUsed_.find(key) != memUsed_.end())
			{
				//key���� ��ϵǾ� �ִٸ� FALSE ����
				//CEventLog::Instance().LogEvent("HG_RED", _T(" Duplicate insert key(0x%016x) [%s]")
				//	, key, Proud::StringA2W(typeid(this).name()));
				printf(" Duplicate insert key(0x%016x) [%s]\n", key, typeid(this).name());

				//ȸ�� ó���մϴ�.
				if (IsAllocated())
					memFree_.push(pT);

				return FALSE;
			}

			memUsed_.insert(std::make_pair(key, pT));
			return TRUE;
		}


		// key�� �ش��ϴ� ���Ǵ� �޸𸮿��� ����� "memFree_"�� ��ȯ
		void Erase(K key)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			std::map<K, T*>::iterator it;
			it = memUsed_.find(key);
			if (it != memUsed_.end())
			{
				if (IsAllocated())
					memFree_.push((*it).second);

				it = memUsed_.erase(it);
			}
		}

		// key�� �ش��ϴ� ���Ǵ� �޸𸮸� �����, "memFree_"�� ��ȯ���� �ʴ´�.
		// ��. �ٸ� pool�� ������ �ϱ� ���� ������(�ٸ� pool�� �翬�� IsAllocated()�� true���¿��� �Ѵ�)
		// �ٸ� pool������ insert()�� ���� �־��ָ� �ȴ�.
		T* Pop(K key)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			std::map<K, T*>::iterator it;
			it = memUsed_.find(key);
			if (it != memUsed_.end())
			{
				T* pT = (*it).second;
				memUsed_.erase(it);
				return pT;
			}
			return NULL;
		}


		// Ű�� �����͸� ã�ƶ�.
		T* Find(K key)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			std::map<K, T*>::iterator it;
			it = memUsed_.find(key);
			if (it != memUsed_.end())
				return (*it).second;
			return NULL;
		}

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
			, void* param = NULL)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			vecAll.reserve(cnt);

			INT32 index = -1;
			INT32 count = 0;

			//�����ϰ� �ִ� �������� ũ�� ������ ���� ����.
			// ����� ����Ÿ�� 1���̰�, start 1 �̸�...
			// start�� 0 �� ó������Ÿ�̹Ƿ� ������ ���� ����.
			//( start�� 0 �̸� ����Ÿ�� �ϳ� ������ �� �ִ�.)
			if (GetUsedMemSize() <= start)
				return;


			std::map<K, T*>::iterator it = memUsed_.begin();
			for (; it != memUsed_.end(); ++it)
			{
				//������ġ���� �����´�.
				if (++index < start)
					continue;

				//�����ұ�??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare(it->second, param))
						continue;
				}

				vecAll.push_back(it->second);

				//������ ���� ��ŭ�� ��´�.
				if (cnt <= ++count)
					break;
			}
		}

		//pool�� ������ �������� �����´�.
		//  start : ������ ó�� ��ġ( 0 ���� ���۵˴ϴ�.)
		//  cnt : ������ ����
		//  funcCompare : �񱳸� ������ �Լ��� ������
		//  param : �Լ� �������� ���� ����
		void GetAllReverseList(::std::vector<T*>& vecAll
			, INT32 start = 0
			, INT32 cnt = DEFAULT_RESERVED_VECTOR_SIZE
			, BOOL(*funcCompare)(T*, void*) = NULL
			, void* param = NULL)
		{
			//Proud::CriticalSectionLock lock(cs_, true);
			AUTO_LOCK(cs_);

			vecAll.reserve(cnt);

			INT32 index = -1;
			INT32 count = 0;

			//�����ϰ� �ִ� �������� ũ�� ������ ���� ����.
			// ����� ����Ÿ�� 1���̰�, start 1 �̸�...
			// start�� 0 �� ó������Ÿ�̹Ƿ� ������ ���� ����.
			//( start�� 0 �̸� ����Ÿ�� �ϳ� ������ �� �ִ�.)
			if (GetUsedMemSize() <= start)
				return;

			std::map<K, T*>::reverse_iterator it = memUsed_.rbegin();
			for (; it != memUsed_.rend(); ++it)
			{
				//������ġ���� �����´�.
				if (++index < start)
					continue;

				//�����ұ�??
				if (NULL != funcCompare)
				{
					if (FALSE == funcCompare(it->second, param))
						continue;
				}

				vecAll.push_back(it->second);

				//������ ���� ��ŭ�� ��´�.
				if (++count >= cnt)
					break;
			}
		}


		INT32 GetUsedMemSize() { return (INT32)memUsed_.size(); }	//used pool ����	
		INT32 GetFreeMemSize() { return (INT32)memFree_.size(); }	//free pool ����
		INT32 GetLeakMemSize() { return (INT32)memLeak_.size(); }	//leak pool ����
	};

}//namespace HisUtil