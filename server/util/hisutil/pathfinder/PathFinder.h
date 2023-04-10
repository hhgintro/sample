#pragma once
#include "PathDefine.h"

class CPathFinder
{
private:
	//terrain
	_stTerrain** map_;

	BOOL bIsDiagonal_;	//대각선 이동(검색) 가능 여부
	UINT8 postdirect_;	//shortpathboard_ 를 기록하기 위해 이전방향을 기억합니다.

	int FcostFake_;		//F = G + H
	//int Gcost_;		//소비 비용
	int HcostFake_;		//목표거리 비용


	CModuleManager m_module;
public:

	BOARDINDEX BOARD_X_COUNT;	//가로 사이즈
	BOARDINDEX BOARD_Y_COUNT;	//세로 사이즈

	BOARDINDEX start_;	//시작위치
	//std::vector<BOARDINDEX> start_;	//시작위치
	BOARDINDEX end_;		//목표위치
	BOARDINDEX endFake_;	//목표위치(end_ 위치에 갈수 없을때 위치)



	std::list<BOARDINDEX> openboard_;//열린상태(Fcost가 낮은 순서로 정렬된다.)
	std::set<BOARDINDEX> closedboard_;//닫힌상태
	std::list<BOARDINDEX> pathboard_;//목표->시작 경로
	std::list<BOARDINDEX> shortpathboard_;//목표->시작 경로(같은방향인 경우 중간 board는 생략됨)
	std::list<BOARDINDEX> terrain_;//외부에서 Draw를 위해 terrain list를 별도로 관리한다.(시작,목표위치는 제외)
	



public:
	CPathFinder();
	~CPathFinder();

	//초기함수(init()) 반드시 호출해 줘야 함.
	void Init(_stTerrain** terrain, BOARD_T sizeX, BOARD_T sizeY);
	void Clear();


	void ChangeStart(BOARDINDEX board);	//시작위치
	void ChangeStart(BOARD_T x, BOARD_T y);	//시작위치
	void ChangeEnd(BOARDINDEX board);	//목표위치
	void ChangeEnd(BOARD_T x, BOARD_T y);	//목표위치
	void AddTerrain(int tterraintype, BOARD_T x, BOARD_T y);//terrain(wall, water, swamp)
	BOOL RemoveTerrain(BOARDINDEX board);//terrain(wall, water, swamp)

	
	//시작->목표 도착하면 TRUE 리턴(경로는 pathboard_ 에서 확인)
	//object : 이동하려는 개체(3x3)인 경우 자신의 몸집에 의해 이동불가현상 때문에.
	BOOL FindPath(void* object, BOARDINDEX start, BOARDINDEX& end, UINT8 xsize=1, UINT8 ysize=1);

	//잘못된 좌표
	BOOL IsBadFrontier(void* object, BOARD_T x, BOARD_T y, UINT8 xsize, UINT8 ysize);

	//타겟으로 저정된 개체의 몸집을 확인하여 가장 가까운 위치를 찾는다.
	BOARDINDEX GetNearBodyFrame(BOARDINDEX start, BOARDINDEX end);

	//존재하지 않는 좌표
	BOOL IsBadBoard(BOARD_T x, BOARD_T y);
	BOOL IsBadBoard(BOARDINDEX board);

	//대각선 검색
	BOOL GetIsDiagonal() { return bIsDiagonal_; }
	void SetIsDiagonal(BOOL diagonal) { bIsDiagonal_ = diagonal; }

	//두 board 사이의 거리(단위 : BOARDINDEX) -- 행동력과 밀접한 관계
	int GetBoardDistance(BOARDINDEX source, BOARDINDEX target);


#ifdef _HG_TEST_OBJECT_CHECK_
	//개체정보
	void* GetBoardObject(BOARD_T x, BOARD_T y);
	void* GetBoardObject(BOARDINDEX board);
	void SetBoardObject(BOARD_T x, BOARD_T y, void* object, UINT8 xsize=1, UINT8 ysize=1);
	void SetBoardObject(BOARDINDEX board, void* object, UINT8 xsize=1, UINT8 ysize=1);
#endif //_HG_TEST_OBJECT_CHECK_

	//terrain type
	UINT8 GetTerrainType(BOARD_T x, BOARD_T y);
	UINT8 GetTerrainType(BOARDINDEX board);
	void SetTerrainType(BOARD_T x, BOARD_T y, UINT8 terraintype);
	void SetTerrainType(BOARDINDEX board, UINT8 terraintype);
	//방향
	UINT8 GetDirect(BOARD_T x, BOARD_T y);
	UINT8 GetDirect(BOARDINDEX board);
	void SetDirect(BOARD_T x, BOARD_T y, UINT8 direct);
	void SetDirect(BOARDINDEX board, UINT8 direct);

	//F cost
	int GetFCost(BOARD_T x, BOARD_T y);;
	int GetFCost(BOARDINDEX board);
	void SetFCost(BOARD_T x, BOARD_T y, int Fcost);
	void SetFCost(BOARDINDEX board, int Fcost);
	//G cost
	int GetGCost(BOARD_T x, BOARD_T y);;
	int GetGCost(BOARDINDEX board);
	void SetGCost(BOARD_T x, BOARD_T y, int Gcost);
	void SetGCost(BOARDINDEX board, int Gcost);
	//H cost
	int GetHCost(BOARD_T x, BOARD_T y);;
	int GetHCost(BOARDINDEX board);
	void SetHCost(BOARD_T x, BOARD_T y, int Hcost);
	void SetHCost(BOARDINDEX board, int Hcost);


private:

	//목표위치에 도착 하면 TRUE 리턴
	BOOL ArrivedEnd(void* object, BOARDINDEX end, UINT8 xsize=1, UINT8 ysize=1);

	//board 주변을 openboard_에 추가한다.
	void AddFrontier(void* object, BOARDINDEX board, UINT8 xsize=1, UINT8 ysize=1);

	//몸집을 체크하여 openbodyframe에 추가한다.
	void AddBodyFrame(void* object, BOARDINDEX start, BOARDINDEX board
		, std::list<BOARDINDEX>& openbodyframe, std::set<BOARDINDEX>& closedbodyframe
		, BOARDINDEX& nearestboard, int& distance);

	//이미 열린상태이면...cost 갱신해준다.(비용이 낮을때만)
	//새로운 값이 더 크면 갱신하지 않는다.
	//새로운 값이 작으면, 여기서 빼고, 아래(InsertOpenTerrain())에서 다시 넣어 준다.
	BOOL IsOpenedTerrain(BOARDINDEX board, int Fcost);

	//처음검색된 영역은 열린상태에 추가한다.
	//또는 위(IsOpenedTerrain())에서 재갱신이 필요한 영역을 추가해 준다.
	void InsertOpenTerrain(BOARDINDEX board, int direct, int Fcost, int Gcost, int Hcost);

	//시작위치 -> 목표위치의 경로를 가져온다.
	void GetShortPath();

	//direct : 시작위치 방향
	//board : 현재 위치
	//GCost : 이전 위치까지의 GCost
	int CalculateGcost(int direct, BOARDINDEX board, int GCost);

	//대각선 이동여부 체크
	BOOL OnDiagonal(int direction);

};