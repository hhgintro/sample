#pragma once

/*=====================================================
	������ �ʴ� ��¥ CLASS
=====================================================*/
//class CZoneManager : public CThread<CZoneManager>, public Singleton<CZoneManager>
class CZoneManager : public CTempZoneManager, public Singleton<CZoneManager>
{
public:
	CZoneManager() {}
	~CZoneManager() {}

};

