#include "StdAfx.h"
#include "PathFinder.h"

CPathFinder::CPathFinder()
	: map_(NULL), BOARD_X_COUNT(0), BOARD_Y_COUNT(0), start_(0), end_(0)
	, bIsDiagonal_(TRUE)
{

}

CPathFinder::~CPathFinder()
{
	openboard_.clear();
	closedboard_.clear();
	pathboard_.clear();
	shortpathboard_.clear();
	terrain_.clear();
	postdirect_ = 0;
}

//초기함수 반드시 호출해 줘야 함.
void CPathFinder::Init(_stTerrain** terrain, BOARD_T sizeX, BOARD_T sizeY)
{
	Clear();

//	servertime_ = RandInt(TIME_HOUR(24), TIME_HOUR(72));

	map_ = terrain;

	//map 크기
	BOARD_X_COUNT = sizeX;
	BOARD_Y_COUNT = sizeY;

	////이중배열 동적 할당
	//try
	//{
	//	if(NULL != map_)
	//	{
	//		//할당된 너비 부터 지워야 합니다.
	//		for(BOARDINDEX i=0; i<BOARD_Y_COUNT; ++i)
	//			delete [] map_[i];

	//		delete [] map_;
	//		map_ = NULL;
	//	}


	//	//변경된 map 크기
	//	BOARD_X_COUNT = sizeX;
	//	BOARD_Y_COUNT = sizeY;


	//	map_ = new _stTerrain* [BOARD_Y_COUNT];//높이 할당

	//	for(BOARDINDEX i=0; i<BOARD_Y_COUNT; ++i)
	//	{
	//		map_[i] = new _stTerrain[BOARD_X_COUNT];//너비 할당
	//		//memset(map_[i], 0, sizeof(_stTerrain) * BOARD_X_COUNT);//값을 초기화한다.
	//	}
	//}
	//catch(std::bad_alloc& e)
	//{
	//	printf("%s\n", e.what());
	//	//LOGEVENT("HG_RED", _T("예외처리됨 map_ = new LPVOID*"));
	//	return;
	//}


	m_module.Init(2099, 12, 23, 12, 00, 0);
}

void CPathFinder::Clear()
{
	openboard_.clear();
	closedboard_.clear();
	pathboard_.clear();
	//wall_.clear();
	shortpathboard_.clear();
	postdirect_ = 0;

	//endFake_ = 0;
	FcostFake_ = 2100000000;//그냥 큰수
	HcostFake_ = 2100000000;//그냥 큰수
}

void CPathFinder::ChangeStart(BOARDINDEX board)
{
	start_ = board;
}

void CPathFinder::ChangeStart(BOARD_T x, BOARD_T y)
{
	BOARDINDEX board = XY_TO_BOARDINDEX(x, y);
	if(board == end_)
		return;

	ChangeStart(board);
}

void CPathFinder::ChangeEnd(BOARDINDEX board)
{
	end_ = board;
}

void CPathFinder::ChangeEnd(BOARD_T x, BOARD_T y)
{
	BOARDINDEX board = XY_TO_BOARDINDEX(x, y);
	if(board == start_)
		return;

	ChangeEnd(board);
}

void CPathFinder::AddTerrain(int tterraintype, BOARD_T x, BOARD_T y)
{
	BOARDINDEX board = XY_TO_BOARDINDEX(x, y);
	if(board == start_ || board == end_)
		return;

	if(TRUE == RemoveTerrain(board))
		return;

	terrain_.push_back(board);

	//terrain type
	SetTerrainType(x, y, tterraintype);
}

BOOL CPathFinder::RemoveTerrain(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);

	std::list<BOARDINDEX>::iterator it;
	for(it = terrain_.begin(); it != terrain_.end(); )
	{
		if(board == (*it))
		{
			it = terrain_.erase(it);
			SetTerrainType(x, y, eTerrain_Normal);
			return TRUE;
		}
		else
			++it;
	}
	return FALSE;
}

//시작->목표 도착하면 TRUE 리턴(경로는 pathboard_ 에서 확인) 
BOOL CPathFinder::FindPath(void* object, BOARDINDEX start, BOARDINDEX& end, UINT8 xsize, UINT8 ysize)
{
	if(NULL == map_ || NULL == object)
		return FALSE;

	//모듈 보호
	if(FALSE == m_module.CheckValid())
		return FALSE;


	//기록 초기화
	Clear();

	//시작위치
	ChangeStart(start);

	//3x3의 경우 몸집에 의해 가장 가까운 위치로 자동 설정한다.
	end = GetNearBodyFrame(start, end);
	//목표위치
	ChangeEnd(end);


	////도착지점의 점유상태를 기억하고 있다가 마지막에 점유를 갱신한다.
	//void* destoccupy = GetBoardObject(end);
	//SetBoardObject(end, NULL);//도착지점에 갈수 없으면, 경로검색을 할 수 없다.

	BOOL bFindPath = FALSE;
		//시작위치를 넣는다.
		openboard_.push_back(start);

//int tick = GetTickCount();
//LOGEVENT("HG_CYAN", _T("	%s 길찾기 진입"), ((IBattleObject*)object)->GetNickname().GetString(), GetTickCount() - tick);

		//경로를 찾는다.
		if(TRUE == ArrivedEnd(object, end, xsize, ysize))
		{
			GetShortPath();
			bFindPath = TRUE;
		}
//LOGEVENT("HG_CYAN", _T("	%s 길찾기 소요시간(%d)"), ((IBattleObject*)object)->GetNickname().GetString(), GetTickCount() - tick);
//if(30000 < GetTickCount() - tick)
//{
//	int a = 0;
//	a = 0;
//}

	////시작전 점유상태로 돌려놓는다.
	//SetBoardObject(end, destoccupy);
	return bFindPath;
}

//목표위치에 도착 하면 TRUE 리턴
BOOL CPathFinder::ArrivedEnd(void* object, BOARDINDEX end, UINT8 xsize, UINT8 ysize)
{
	while(FALSE == openboard_.empty())
	{
		BOARDINDEX board = *openboard_.begin();
		openboard_.pop_front();

		//목표위치
		if(board == end_)
			return TRUE;

		AddFrontier(object, board, xsize, ysize);
	}
	return FALSE;
}

//board 주변을 openboard_에 추가한다.
void CPathFinder::AddFrontier(void* object, BOARDINDEX board, UINT8 xsize, UINT8 ysize)
{
	closedboard_.insert(board);

	//주변검색
	BOARD_T x_board = BOARDINDEX_TO_X(board);
	BOARD_T y_board = BOARDINDEX_TO_Y(board);

	for(int i=0; i<DIRECT_MAX; ++i)
	{
		if(FALSE == OnDiagonal(i))
			continue;

		BOARD_T x = x_board;
		BOARD_T y = y_board;

		DIRECT_TYPE direct;

		switch(i)
		{
		case DIRECT_N:	{				y -= 1;		direct = DIRECT_S;		} break;
		case DIRECT_NE:	{	x += 1;		y -= 1;		direct = DIRECT_SW;		} break;
		case DIRECT_E:	{	x += 1;					direct = DIRECT_W;		} break;
		case DIRECT_SE:	{	x += 1;		y += 1;		direct = DIRECT_NW;		} break;
		case DIRECT_S:	{				y += 1;		direct = DIRECT_N;		} break;
		case DIRECT_SW:	{	x -= 1;		y += 1;		direct = DIRECT_NE;		} break;
		case DIRECT_W:	{	x -= 1;					direct = DIRECT_E;		} break;
		case DIRECT_NW: {	x -= 1;		y -= 1;		direct = DIRECT_SE;		} break;
		}

		//닫힌상태이면 무시
		BOARDINDEX tempboard = XY_TO_BOARDINDEX(x,y);
		if(closedboard_.end() != closedboard_.find(tempboard))
			continue;


		//object의 경로의 폭을 체크한다.
		if(TRUE == IsBadFrontier(object, x, y, xsize, ysize))
		{
			closedboard_.insert(tempboard);
			continue;
		}



		//비용계산
		int Gcost = CalculateGcost(direct, tempboard, GetGCost(x_board, y_board));
		int Hcost = GetBoardDistance(tempboard, end_) * 10;
		int Fcost = Gcost + Hcost;


		//처음검색된 영역은 열린상태에 추가한다.
		//이미 열린상태이면...cost 갱신해준다.(비용이 낮을때만)
		//새로운 값이 더 크면 갱신하지 않는다.
		if(FALSE == IsOpenedTerrain(tempboard, Fcost))
			InsertOpenTerrain(tempboard, direct, Fcost, Gcost, Hcost);

	}//..for(int i=0; i<DIRECT_MAX; ++i)
}

//이미 열린상태이면...cost 갱신해준다.(비용이 낮을때만)
//새로운 값이 더 크면 갱신하지 않는다.
//새로운 값이 작으면, 여기서 빼고, 아래(InsertOpenTerrain())에서 다시 넣어 준다.
BOOL CPathFinder::IsOpenedTerrain(BOARDINDEX board, int Fcost)
{
	std::list<BOARDINDEX>::iterator it;
	for(it=openboard_.begin(); it!=openboard_.end(); )
	{
		//이미 열린상태이면...cost 갱신해준다.(비용이 낮을때만)
		if(board == (*it))
		{
			if(GetFCost(*it) <= Fcost)
				return TRUE;//새로운 값이 더크니, 갱신하지 않는다.

			it = openboard_.erase(it);//새로운 값이 작으니, 여기서 빼고, 아래에서 다시 넣어 준다.
			return FALSE;
		}
		else
			++it;
	}

	return FALSE;
}

//처음검색된 영역은 열린상태에 추가한다.
//또는 위(IsOpenedTerrain())에서 재갱신이 필요한 영역을 추가해 준다.
void CPathFinder::InsertOpenTerrain(BOARDINDEX board, int direct, int Fcost, int Gcost, int Hcost)
{
	//setting...new terrain
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);

	SetDirect(x, y, direct);
	SetFCost(x, y, Fcost);
	SetGCost(x, y, Gcost);
	SetHCost(x, y, Hcost);

	//목표거리가 가장가까운것 & 가장짧은 예상경로
	if((Hcost < HcostFake_)
		|| (Hcost == HcostFake_ && Fcost < FcostFake_))
	{
		FcostFake_ = Fcost;
		HcostFake_ = Hcost;
		endFake_ = board;
	}


	std::list<BOARDINDEX>::iterator it;
	for(it=openboard_.begin(); it!=openboard_.end(); ++it)
	{
		if(Fcost <= GetFCost(*it))
			break;
	}

	//if(it != openboard_.end())
	openboard_.insert(it, board);
}

void CPathFinder::GetShortPath()
{
	BOARD_T x = BOARDINDEX_TO_X(end_);
	BOARD_T y = BOARDINDEX_TO_Y(end_);

	//목표위치
	pathboard_.push_front(end_);
	{
		//같은방향인경우 중간 과정을 생략합니다.
		postdirect_ = GetDirect(x, y); //end_ 의 방향을 임의 저장합니다.
		shortpathboard_.push_front(end_);
	}

	while(1)
	{
		int direct = GetDirect(x, y);
		if(FALSE == OnDiagonal(direct))
			continue;

		//현 board에서 방향으로 이전 board를 찾는다.
		switch(direct)
		{
		case DIRECT_N:	{				y -= 1;		} break;
		case DIRECT_NE:	{	x += 1;		y -= 1;		} break;
		case DIRECT_E:	{	x += 1;					} break;
		case DIRECT_SE:	{	x += 1;		y += 1;		} break;
		case DIRECT_S:	{				y += 1;		} break;
		case DIRECT_SW:	{	x -= 1;		y += 1;		} break;
		case DIRECT_W:	{	x -= 1;					} break;
		case DIRECT_NW: {	x -= 1;		y -= 1;		} break;
		}


		//이전 board가 시작위치면...그만 찾는다.
		BOARDINDEX board = XY_TO_BOARDINDEX(x, y);
		if(start_ == board)
			break;

		//pathboard_.push_back(board);
		pathboard_.push_front(board);

		//같은방향인경우 중간 과정을 생략합니다.
		direct = GetDirect(x, y);
		if(postdirect_ != direct)
		{
			postdirect_ = direct;
			shortpathboard_.push_front(board);
		}
	}
	return;
}

int CPathFinder::CalculateGcost(int direct, BOARDINDEX board, int GCost)
{
	int terrain_cost = 0;
	switch(GetTerrainType(board))
	{
	case eTerrain_Start:
	case eTerrain_End:
	case eTerrain_Normal:		terrain_cost = 0;	 break;
	case eTerrain_Water:		terrain_cost = 70;	 break;
	case eTerrain_Swamp:		terrain_cost = 50;	 break;

	default:			terrain_cost = 10000;	break;
	//case eTerrain_Wall:			terrain_cost = 500;	 break;

	}
	//eTerrain_Normal
	//	, eTerrain_Water	//물
	//	, eTerrain_Swamp	//늪
	//	, eTerrain_Wall		//장벽
	//	, eTerrain_Start	//시작위치
	//	, eTerrain_End		//목표위치

	//HG_TODO : 장애물은 비용을 추가한다.
	switch(direct)
	{
	case DIRECT_N:		return 10 + terrain_cost + GCost;
	case DIRECT_NE:		return 14 + terrain_cost + GCost;
	case DIRECT_E:		return 10 + terrain_cost + GCost;
	case DIRECT_SE:		return 14 + terrain_cost + GCost;
	case DIRECT_S:		return 10 + terrain_cost + GCost;
	case DIRECT_SW:		return 14 + terrain_cost + GCost;
	case DIRECT_W:		return 10 + terrain_cost + GCost;
	case DIRECT_NW:		return 14 + terrain_cost + GCost;
	}
	return 0;
}

//두 board 사이의 거리(단위 : BOARDINDEX) -- 행동력과 밀접한 관계
int CPathFinder::GetBoardDistance(BOARDINDEX source, BOARDINDEX target)
{
	BOARD_T x_source = BOARDINDEX_TO_X(source);
	BOARD_T y_source = BOARDINDEX_TO_Y(source);

	BOARD_T x_target = BOARDINDEX_TO_X(target);
	BOARD_T y_target = BOARDINDEX_TO_Y(target);

	//board은 한칸이 거리1이고 대각선 이동은 없기에 간단한 공식으로 거리를 구한다.
	return abs(x_target - x_source) + abs(y_target - y_source);
}

//대각선 이동여부 체크
BOOL CPathFinder::OnDiagonal(int direction)
{
	if(TRUE == bIsDiagonal_)
		return TRUE;
	
	//대각선 이동이 불가능인 경우...대각선을 걸러낸다.
	switch(direction)
	{
	case DIRECT_NW:
	case DIRECT_NE:
	case DIRECT_SW:
	case DIRECT_SE:
		return FALSE;
	}

	return TRUE;
}


//잘못된 좌표
BOOL CPathFinder::IsBadFrontier(void* object, BOARD_T x, BOARD_T y, UINT8 xsize, UINT8 ysize)
{
	//x 사이즈가 3이면 좌우로 1칸이라는 뜻
	UINT8 xgap = xsize / 2;
	UINT8 ygap = ysize / 2;

	for(UINT8 yy=0; yy<ysize; ++yy)
	{
		//중앙에서 위쪽 gap만큼 떨어진 위치에서 시작해서 사이즈만큼 아래로 이동
		BOARD_T ytemp = y - ygap + yy;

		for(UINT8 xx=0; xx<xsize; ++xx)
		{
			//중앙에서 좌측 gap만큼 떨어진 위치에서 시작해서 사이즈만큼 우측으로 이동
			BOARD_T xtemp = x - xgap + xx;

			//잘못된 위치...무시
			if(TRUE == IsBadBoard(xtemp, ytemp))
				return TRUE;

			////타인이 점유중이면...무시
			//if(NULL != GetBoardObject(xtemp, ytemp) && object != GetBoardObject(xtemp, ytemp))
			//	return TRUE;

			//갈수 없는 영역이면...무시
			if(eTerrain_Wall == GetTerrainType(xtemp, ytemp))
				return TRUE;
			
		}//..for(UINT8 xx=0; xx<xsize; ++xx)
	}//..for(UINT8 yy=0; yy<ysize; ++yy)

	return FALSE;
}

//	start : 공격자의 위치
//	end : 몬스터의 위치
BOARDINDEX CPathFinder::GetNearBodyFrame(BOARDINDEX start, BOARDINDEX end)
{
	//가장 가까운 위치가 설정된다.
	BOARDINDEX nearestboard = end;
	int distance = GetBoardDistance(end, start);//임의 큰값 설정

	//타겟위치가 비었다. 이동가능
	void* object = GetBoardObject(end);
	if(NULL == object)
		return end;

	//개체의 몸집이므로 이동가능
	if(object == GetBoardObject(start))
		return end;


	//타겟으로 저정된 개체의 몸집을 확인하여 가장 가까운 위치를 찾는다.
	std::list<BOARDINDEX> openbodyframe;
	std::set<BOARDINDEX> closedbodyframe;


	openbodyframe.push_back(end);

	while(FALSE == openbodyframe.empty())
	{
		BOARDINDEX board = *openbodyframe.begin();
		openbodyframe.pop_front();
	
		////목표위치
		//if(board == end_)
		//	return TRUE;
	
		AddBodyFrame(object, start, board, openbodyframe, closedbodyframe, nearestboard, distance);
	}

	return nearestboard;
}

//몸집을 체크하여 openbodyframe에 추가한다.
//	object : 몸집체크되는 개체
//	start : 공격자의 위치
//	board : 몸집체크되는 위치
//	openbodyframe : open 된 몸집정보
//	closedbodyframe : closed 된 몸집 정보
//	nearestboard : 가장 가까운 위치
//	distance : 가장 가까운 거리
void CPathFinder::AddBodyFrame(void* object, BOARDINDEX start, BOARDINDEX board
							   , std::list<BOARDINDEX>& openbodyframe, std::set<BOARDINDEX>& closedbodyframe
							   , BOARDINDEX& nearestboard, int& distance)
{
	closedbodyframe.insert(board);

	//주변검색
	BOARD_T x_board = BOARDINDEX_TO_X(board);
	BOARD_T y_board = BOARDINDEX_TO_Y(board);

	for(int i=0; i<DIRECT_MAX; ++i)
	{
		//body frame은 대각선 여부에 관계없이 체크되어야 한다.
		//if(FALSE == OnDiagonal(i))
		//	continue;

		BOARD_T x = x_board;
		BOARD_T y = y_board;

		DIRECT_TYPE direct;

		switch(i)
		{
		case DIRECT_N:	{				y -= 1;		direct = DIRECT_S;		} break;
		case DIRECT_NE:	{	x += 1;		y -= 1;		direct = DIRECT_SW;		} break;
		case DIRECT_E:	{	x += 1;					direct = DIRECT_W;		} break;
		case DIRECT_SE:	{	x += 1;		y += 1;		direct = DIRECT_NW;		} break;
		case DIRECT_S:	{				y += 1;		direct = DIRECT_N;		} break;
		case DIRECT_SW:	{	x -= 1;		y += 1;		direct = DIRECT_NE;		} break;
		case DIRECT_W:	{	x -= 1;					direct = DIRECT_E;		} break;
		case DIRECT_NW: {	x -= 1;		y -= 1;		direct = DIRECT_SE;		} break;
		}

		////object의 경로의 폭을 체크한다.
		//if(TRUE == IsBadFrontier(object, x, y, xsize, ysize))
		//	continue;

		//잘못된 위치...무시
		if(TRUE == IsBadBoard(x, y))
			continue;

		//타인이 점유중이면...무시
		if(object != GetBoardObject(x, y))
			continue;


		//닫힌상태이면 무시
		BOARDINDEX tempboard = XY_TO_BOARDINDEX(x,y);
		if(closedbodyframe.end() != closedbodyframe.find(tempboard))
			continue;

		//open상태이면 무시.
		std::list<BOARDINDEX>::iterator it;
		for(it=openbodyframe.begin(); it!=openbodyframe.end(); ++it)
		{
			if(tempboard == *it)
				continue;
		}

		//거리계산
		int cost = GetBoardDistance(tempboard, start);
		if(distance <= cost)//거리가 먼것은 구지 open에 넣어줄 필요 없다.
			continue;

		//가장 가까운 데이타 설정
		nearestboard = tempboard;
		distance = cost;

		//if(it != openboard_.end())
		openbodyframe.push_back(tempboard);

	}//..for(int i=0; i<DIRECT_MAX; ++i)
}

//존재하지 않는 좌표
BOOL CPathFinder::IsBadBoard(BOARD_T x, BOARD_T y)
{
	//잘못된 위치...무시
	if(BOARD_X_COUNT <= x || BOARD_Y_COUNT <= y)
		return TRUE;

	return FALSE;
}
BOOL CPathFinder::IsBadBoard(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return IsBadBoard(x, y);
}
#ifdef _HG_TEST_OBJECT_CHECK_
void* CPathFinder::GetBoardObject(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return NULL;

	return map_[y][x].object_;
}
void* CPathFinder::GetBoardObject(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetBoardObject(x, y);
}
void CPathFinder::SetBoardObject(BOARD_T x, BOARD_T y, void* object, UINT8 xsize, UINT8 ysize)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	//x 사이즈가 3이면 좌우로 1칸이라는 뜻
	UINT8 xgap = xsize / 2;
	UINT8 ygap = ysize / 2;

	for(UINT8 yy=0; yy<ysize; ++yy)
	{
		//중앙에서 위쪽 gap만큼 떨어진 위치에서 시작해서 사이즈만큼 아래로 이동
		BOARD_T ytemp = y - ygap + yy;
		for(UINT8 xx=0; xx<xsize; ++xx)
		{
			//중앙에서 좌측 gap만큼 떨어진 위치에서 시작해서 사이즈만큼 우측으로 이동
			BOARD_T xtemp = x - xgap + xx;
			if(TRUE == IsBadBoard(xtemp, ytemp))
				continue;

			map_[ytemp][xtemp].object_ = object;//자리 등록(NULL이면 해제)
			//printf("map_[%d][%d] = %x\n", ytemp, xtemp, object);
		}//..for(UINT8 xx=0; xx<xsize; ++xx)
	}//..for(UINT8 yy=0; yy<ysize; ++yy)
}
void CPathFinder::SetBoardObject(BOARDINDEX board, void* object, UINT8 xsize, UINT8 ysize)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetBoardObject(x, y, object, xsize, ysize);
}
#endif //_HG_TEST_OBJECT_CHECK_

UINT8 CPathFinder::GetTerrainType(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return 0;

	return map_[y][x].terraintype_;
}
UINT8 CPathFinder::GetTerrainType(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetTerrainType(x, y);
}
void CPathFinder::SetTerrainType(BOARD_T x, BOARD_T y, UINT8 terraintype)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	map_[y][x].terraintype_ = terraintype;
}
void CPathFinder::SetTerrainType(BOARDINDEX board, UINT8 terraintype)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetTerrainType(x, y, terraintype);
}


UINT8 CPathFinder::GetDirect(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return 0;

	return map_[y][x].direct_;
}
UINT8 CPathFinder::GetDirect(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetDirect(x, y);
}
void CPathFinder::SetDirect(BOARD_T x, BOARD_T y, UINT8 direct)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	map_[y][x].direct_ = direct;
}
void CPathFinder::SetDirect(BOARDINDEX board, UINT8 direct)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetDirect(x, y, direct);
}

int CPathFinder::GetFCost(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return 0;

	return map_[y][x].Fcost_;
}
int CPathFinder::GetFCost(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetFCost(x, y);
}
void CPathFinder::SetFCost(BOARD_T x, BOARD_T y, int Fcost)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	map_[y][x].Fcost_ = Fcost;
}
void CPathFinder::SetFCost(BOARDINDEX board, int Fcost)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetFCost(x, y, Fcost);
}


int CPathFinder::GetGCost(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return 0;

	return map_[y][x].Gcost_;
}
int CPathFinder::GetGCost(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetGCost(x, y);
}
void CPathFinder::SetGCost(BOARD_T x, BOARD_T y, int Gcost)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	map_[y][x].Gcost_ = Gcost;
}
void CPathFinder::SetGCost(BOARDINDEX board, int Gcost)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetGCost(x, y, Gcost);
}


int CPathFinder::GetHCost(BOARD_T x, BOARD_T y)
{
	if(TRUE == IsBadBoard(x, y))
		return 0;

	return map_[y][x].Hcost_;
}
int CPathFinder::GetHCost(BOARDINDEX board)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	return GetHCost(x, y);
}
void CPathFinder::SetHCost(BOARD_T x, BOARD_T y, int Hcost)
{
	if(TRUE == IsBadBoard(x, y))
		return;

	map_[y][x].Hcost_ = Hcost;
}
void CPathFinder::SetHCost(BOARDINDEX board, int Hcost)
{
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);
	SetHCost(x, y, Hcost);
}