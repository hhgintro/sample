#pragma once

#include <hash_map>
//#include "HisCritSec.h"

using namespace stdext;

template<typename KEY, class DATA>
class TManager
{
public:
	typedef hash_map<KEY, DATA>					SDataMap;
	typename typedef SDataMap::iterator			SDataMap_it;
	typename typedef SDataMap::const_iterator	SDataMap_cit;
	typename typedef SDataMap::value_type		SDataMap_vt;


protected:
	SDataMap mapData_;
	DATA m_invalidValue; 		// �˻��� �����Ѱ�찡 �߻������� �������� ���̴�.

	Proud::CriticalSection m_cs;
	//CCritSecBase csT_;

public:
	TManager(DATA invalidValue) 
		: m_invalidValue(invalidValue)	// invalid value �� �̸� �����س��� �ʿ��Ҷ� �����Ѵ�.
		// DATA�� ġ�� �����ڸ� �̸� ������ ��� �Ѵ�. -ozzywow-
	{		
		mapData_.clear() ;
	}
	virtual ~TManager()
	{
		Release();
	}

public:
	void Release()
	{
		//AUTO_LOCK(csT_);
		Proud::CriticalSectionLock(m_cs, true);
		mapData_.clear();
	}

	bool Insert(KEY Key, DATA Data)
	{
		//AUTO_LOCK(csT_);
		Proud::CriticalSectionLock(m_cs, true);

		if(mapData_.find(Key) == mapData_.end()) 
		{
			mapData_.insert(SDataMap_vt(Key, Data));
			return true ;
		}		
		return false ;
	}

	void Erase(KEY Key)
	{
		//AUTO_LOCK(csT_);
		Proud::CriticalSectionLock(m_cs, true);

		SDataMap_it it = mapData_.find(Key);
		mapData_.erase(it);
	}

	// note : ���Ͼ����� ȯ�濡���� ���۷����� �����ص� ����������
	// ��Ƽ������ ȯ�濡���� ���۷����� �����ϴ°��� �����ϱ� ������ ��ü�� �����ϵ��� �ߴ�. -ozzywow-
	DATA Find(KEY Key)
	{
		//AUTO_LOCK(csT_);
		Proud::CriticalSectionLock(m_cs, true);

		SDataMap_it it = mapData_.find(Key);
		if(it != mapData_.end()) 
		{
			return  (*it).second;
		}	
		return m_invalidValue ;
	}

	size_t GetSize()
	{
		return mapData_.size();
	}

	SDataMap& GetContainer()
	{
		return mapData_;
	}
};

