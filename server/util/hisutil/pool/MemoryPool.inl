#pragma once

#include "MemoryPool.h"

namespace HisUtil {

	// �⺻ �޸� Ǯ�� ����
	template<class K, class T, class CONTAINER>
	//template<class C>
	void CMemoryPool<K, T, CONTAINER>::Begin(int size = 1)
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
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::End()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//delete used memory
			CONTAINER::iterator it = memUsed_.begin();
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
					SAFE_DELETE((T*)(*it));

				++it;
			}
			memLeak_.clear();
		}
	}

	// ��� �޸𸮸� ��� ����� "memFree_"�� ��ȯ
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Clear()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		{//used memory. come back to the free memory
			CONTAINER::iterator it = memUsed_.begin();
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
	template<typename K, typename T, typename CONTAINER>
	//template<typename C>
	T* CMemoryPool<K, T, CONTAINER>::Create()
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
	template<class K, class T, class CONTAINER>
	BOOL CMemoryPool<K, T, CONTAINER>::Insert(K key, T* pT)
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
			//printf(" Duplicate insert key(0x%016x) [%s]\n", key, typeid(this).name());
				
			//GetValue : wstring�� Ű�� ����� ���...����� ����
			std::cout << _T(" Duplicate insert key(") << GetValue(key) << _T(") : ") << typeid(this).name() << std::endl;

			////	printf(" Duplicate insert key(0x%016x) [%s]\n", key, typeid(this).name());
			////	printf(" Duplicate insert key(%s) [%s]\n", key, typeid(this).name());
			//std::stringstream out;
			////std::cout << " Duplicate insert key(" << key << ") : " << typeid(this).name() << std::endl;
			//out << " Duplicate insert key(" << key << ") : " << typeid(this).name();
			////std::cout << out.str() << std::endl;
			//String str(out.str().c_str());
			//wprintf(L"%s\n", str.w_str());
			////HG_TODO : cout/wprintf �� ��� �Ǵµ�. CEventLog�� �� �ȵɱ�?
			////CEventLog::Instance().LogEvent("HG_RED", (WCHAR*)str.w_str());

			//ȸ�� ó���մϴ�.
			if (IsAllocated())
				memFree_.push(pT);

			return FALSE;
		}


		memUsed_.insert(std::make_pair(key, pT));
		return TRUE;
	}


	// key�� �ش��ϴ� ���Ǵ� �޸𸮿��� ����� "memFree_"�� ��ȯ
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Erase(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
		it = memUsed_.find(key);
		if (it != memUsed_.end())
		{
			if (IsAllocated())
				memFree_.push((*it).second);

			it = memUsed_.erase(it);
		}
	}

	// "memFree_"�� ��ȯ
	// memFree_�� �ߺ��� üũ���� �ʽ��ϴ�.�׷��� �ߺ���ȯ�� ���� �ʵ��� ������ ������ �ּ���
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::Erase(T* pT)
	{
		AUTO_LOCK(cs_);

		memLeak_.erase(pT);//ȸ���Ǵ� ���.
		memFree_.push(pT);
	}

	// key�� �ش��ϴ� ���Ǵ� �޸𸮸� �����, "memFree_"�� ��ȯ���� �ʴ´�.
	// ��. �ٸ� pool�� ������ �ϱ� ���� ������(�ٸ� pool�� �翬�� IsAllocated()�� true���¿��� �Ѵ�)
	// �ٸ� pool������ insert()�� ���� �־��ָ� �ȴ�.
	// ����� ��ȯ�� Erase(T* pT)�� ȣ���ϼ���( �̰� �ƴ�-Erase(K key))
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Pop(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
		it = memUsed_.find(key);
		if (it != memUsed_.end())
		{
			T* pT = (*it).second;
			memUsed_.erase(it);
			return pT;
		}
		return NULL;
	}

	// �Ǿտ� ���Ǵ� �޸𸮸� �����, "memFree_"�� ��ȯ���� �ʴ´�.
	// ��. �ٸ� pool�� ������ �ϱ� ���� ������(�ٸ� pool�� �翬�� IsAllocated()�� true���¿��� �Ѵ�)
	// �ٸ� pool������ insert()�� ���� �־��ָ� �ȴ�.
	// ����� ��ȯ�� Erase(T* pT)�� ȣ���ϼ���( �̰� �ƴ�-Erase(K key))
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Pop()
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it = memUsed_.begin();
		if (it != memUsed_.end())
		{
			T* pT = (*it).second;
			memUsed_.erase(it);
			return pT;
		}
		return NULL;
	}

	// Ű�� �����͸� ã�ƶ�.
	template<class K, class T, class CONTAINER>
	T* CMemoryPool<K, T, CONTAINER>::Find(K key)
	{
		//Proud::CriticalSectionLock lock(cs_, true);
		AUTO_LOCK(cs_);

		CONTAINER::iterator it;
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
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::GetAllList(
		::std::vector<T*>& vecAll
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


		CONTAINER::iterator it = memUsed_.begin();
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
	template<class K, class T, class CONTAINER>
	void CMemoryPool<K, T, CONTAINER>::GetAllReverseList(
		::std::vector<T*>& vecAll
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

		CONTAINER::reverse_iterator it = memUsed_.rbegin();
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

}//namespace HisUtil