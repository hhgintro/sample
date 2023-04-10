#pragma once

/*=====================================================
	사용되지 않는 가짜 CLASS
=====================================================*/
//class CZoneManager : public CThread<CZoneManager>, public Singleton<CZoneManager>
class CZoneManager : public CTempZoneManager, public Singleton<CZoneManager>
{
public:
	CZoneManager() {}
	~CZoneManager() {}

};

