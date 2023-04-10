#pragma once

//#define _HG_TEST_OBJECT_CHECK_

typedef UINT32		BOARDINDEX;
typedef UINT16		BOARD_T;	//BOARDINDEX 의 크기의 반.

#define BOARDINDEX_TO_X		LOWORD
#define BOARDINDEX_TO_Y		HIWORD
#define XY_TO_BOARDINDEX	MAKELONG



enum DIRECT_TYPE
{
	DIRECT_N
	, DIRECT_NE
	, DIRECT_E
	, DIRECT_SE
	, DIRECT_S
	, DIRECT_SW
	, DIRECT_W
	, DIRECT_NW
	, DIRECT_MAX
};


enum TERARIN_TYPE
{
	eTerrain_Normal
	, eTerrain_Water	//물
	, eTerrain_Swamp	//늪
	, eTerrain_Wall		//장벽

	, eTerrain_Max
};


struct _stTerrain
{
	_stTerrain()
#ifdef _HG_TEST_OBJECT_CHECK_
		: object_(NULL), terraintype_(0), direct_(0), Fcost_(0), Gcost_(0), Hcost_(0) {}
#else
		: terraintype_(0), direct_(0), Fcost_(0), Gcost_(0), Hcost_(0) {}
#endif //_HG_TEST_OBJECT_CHECK_

	_stTerrain& operator = (const _stTerrain& rhs)
	{
		if(this == &rhs)	return *this;

#ifdef _HG_TEST_OBJECT_CHECK_
		object_			= rhs.object_;
#endif //_HG_TEST_OBJECT_CHECK_

		terraintype_	= rhs.terraintype_;
		direct_			= rhs.direct_;
		Fcost_			= rhs.Fcost_;
		Gcost_			= rhs.Gcost_;
		Hcost_			= rhs.Hcost_;
		return *this;
	}

#ifdef _HG_TEST_OBJECT_CHECK_
	void* object_; //점유정보
#endif //_HG_TEST_OBJECT_CHECK_

	UINT8 terraintype_;//타일종류(평지,물,늪,장벽,등등)
	UINT8 direct_;	//방향(시작위치방향)
	int Fcost_;		//F = G + H
	int Gcost_;		//소비 비용
	int Hcost_;		//목표거리 비용
};
