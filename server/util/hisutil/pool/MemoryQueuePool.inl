#pragma once

#include "MemoryQueuePool.h"

namespace HisUtil {


	// �⺻ �޸� Ǯ�� ����
	template<typename T>
	//template<typename C>
	void CMemoryQueuePool<T>::Begin(int size = 1)
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
	template<class T>
	void CMemoryQueuePool<T>::End()
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
					SAFE_DELETE((T*)(*it));

				++it;
			}
			memLeak_.clear();
		}
	}

	// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
	template<class T>
	void CMemoryQueuePool<T>::Clear()
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
	template<class T>
	//template<typename C>
	T* CMemoryQueuePool<T>::Create()
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


	//use pool�� �ִ´�.(free pool�� �������� Release�� ����ض�.)
	template<class T>
	bool CMemoryQueuePool<T>::Push(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (IsAllocated())
			memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

		memUsed_.push(pT);
		return TRUE;
	}


	//ó�� ��ü�� �����Ѵ�.
	template<class T>
	T* CMemoryQueuePool<T>::Front()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (true == memUsed_.empty())
			return NULL;

		return memUsed_.front();
	}


	//free pool �� �־��ش�.
	// �������� ���� ���� ����ó����
	template<class T>
	void CMemoryQueuePool<T>::Pop()
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
	//Front_Pop() ȣ���Ŀ��� pool���� �����Ƿ� Push �Ǵ� Release�� ���� �־��־�� �Ѵ�.
	//���� : ���������� pool�� �����ϱ� ���� ����մϴ�.
	template<class T>
	T* CMemoryQueuePool<T>::Front_Pop()
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

	//free pool�� �ִ´�.(use pool�� �������� Push�� ����ض�.)
	template<class T>
	bool CMemoryQueuePool<T>::Release(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (IsAllocated())
			memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

		memFree_.push(pT);
		return TRUE;
	}

}//namespace HisUtil