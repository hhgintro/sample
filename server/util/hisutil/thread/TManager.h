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
	DATA m_invalidValue; 		// 검색에 실패한경우가 발생했을때 리턴해줄 값이다.

	Proud::CriticalSection m_cs;
	//CCritSecBase csT_;

public:
	TManager(DATA invalidValue) 
		: m_invalidValue(invalidValue)	// invalid value 를 미리 설정해놓고 필요할때 리턴한다.
		// DATA의 치완 연산자를 미리 정의해 줘야 한다. -ozzywow-
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

	// note : 단일쓰레드 환경에서는 레퍼런스를 리턴해도 안전하지만
	// 멀티쓰레드 환경에서는 레퍼런스를 리턴하는것은 위험하기 때문에 객체를 리턴하도록 했다. -ozzywow-
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

