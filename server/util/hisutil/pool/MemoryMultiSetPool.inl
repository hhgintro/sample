#pragma once

#include "MemoryMultiSetPool.h"

namespace HisUtil {

	// �⺻ �޸� Ǯ�� ����
	template<class T, class COMP>
	void CMemoryMultiSetPool<T, COMP>::Begin(int size = 1)
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
	template<class T, class COMP>
	void CMemoryMultiSetPool<T, COMP>::End()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		{//delete used memory
			std::multiset<T*, COMP>::iterator it = memUsed_.begin();
			while (it != memUsed_.end())
			{
				if (IsAllocated())
					SAFE_DELETE((T*)(*it));

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
					SAFE_DELETE((T*)(*it));

				++it;
			}
			memLeak_.clear();
		}
	}

	// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
	template<class T, class COMP>
	void CMemoryMultiSetPool<T, COMP>::Clear()
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
	template<class T, class COMP>
	T* CMemoryMultiSetPool<T, COMP>::Create()
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
	template<class T, class COMP>
	bool CMemoryMultiSetPool<T, COMP>::Insert(T* pT)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);


		if (IsAllocated())
			memLeak_.erase(pT);//create���� ������ ��ü�� leak���� �ʰ� ȸ���Ǿ����ϴ�.

		memUsed_.insert(pT);
		return TRUE;
	}

	// �̹� ����(GetFirstData()���� ȣ���) �޸𸮸� �ݳ��մϴ�. "memFree_"�� ��ȯ
	template<class T, class COMP>
	void CMemoryMultiSetPool<T, COMP>::Erase(T* pT)
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
	template<class T, class COMP>
	T* CMemoryMultiSetPool<T, COMP>::GetFirstData()
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
	template<class T, class COMP>
	void CMemoryMultiSetPool<T,COMP>::GetAllList(
		std::vector<T*>& vecAll
		, INT32 start					/*0*/
		, INT32 cnt						/*DEFAULT_RESERVED_VECTOR_SIZE*/
		, BOOL(*funcCompare)(T*, void*) /*NULL*/
		, void* param					/*NULL*/ )
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

			vecAll.push_back(*it);

			//������ ���� ��ŭ�� ��´�.
			if (cnt <= ++count || DEFAULT_RESERVED_VECTOR_SIZE <= count)
				break;
		}
	}

}//namespace HisUtil