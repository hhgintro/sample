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

//�ʱ��Լ� �ݵ�� ȣ���� ��� ��.
void CPathFinder::Init(_stTerrain** terrain, BOARD_T sizeX, BOARD_T sizeY)
{
	Clear();

//	servertime_ = RandInt(TIME_HOUR(24), TIME_HOUR(72));

	map_ = terrain;

	//map ũ��
	BOARD_X_COUNT = sizeX;
	BOARD_Y_COUNT = sizeY;

	////���߹迭 ���� �Ҵ�
	//try
	//{
	//	if(NULL != map_)
	//	{
	//		//�Ҵ�� �ʺ� ���� ������ �մϴ�.
	//		for(BOARDINDEX i=0; i<BOARD_Y_COUNT; ++i)
	//			delete [] map_[i];

	//		delete [] map_;
	//		map_ = NULL;
	//	}


	//	//����� map ũ��
	//	BOARD_X_COUNT = sizeX;
	//	BOARD_Y_COUNT = sizeY;


	//	map_ = new _stTerrain* [BOARD_Y_COUNT];//���� �Ҵ�

	//	for(BOARDINDEX i=0; i<BOARD_Y_COUNT; ++i)
	//	{
	//		map_[i] = new _stTerrain[BOARD_X_COUNT];//�ʺ� �Ҵ�
	//		//memset(map_[i], 0, sizeof(_stTerrain) * BOARD_X_COUNT);//���� �ʱ�ȭ�Ѵ�.
	//	}
	//}
	//catch(std::bad_alloc& e)
	//{
	//	printf("%s\n", e.what());
	//	//LOGEVENT("HG_RED", _T("����ó���� map_ = new LPVOID*"));
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
	FcostFake_ = 2100000000;//�׳� ū��
	HcostFake_ = 2100000000;//�׳� ū��
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

//����->��ǥ �����ϸ� TRUE ����(��δ� pathboard_ ���� Ȯ��) 
BOOL CPathFinder::FindPath(void* object, BOARDINDEX start, BOARDINDEX& end, UINT8 xsize, UINT8 ysize)
{
	if(NULL == map_ || NULL == object)
		return FALSE;

	//��� ��ȣ
	if(FALSE == m_module.CheckValid())
		return FALSE;


	//��� �ʱ�ȭ
	Clear();

	//������ġ
	ChangeStart(start);

	//3x3�� ��� ������ ���� ���� ����� ��ġ�� �ڵ� �����Ѵ�.
	end = GetNearBodyFrame(start, end);
	//��ǥ��ġ
	ChangeEnd(end);


	////���������� �������¸� ����ϰ� �ִٰ� �������� ������ �����Ѵ�.
	//void* destoccupy = GetBoardObject(end);
	//SetBoardObject(end, NULL);//���������� ���� ������, ��ΰ˻��� �� �� ����.

	BOOL bFindPath = FALSE;
		//������ġ�� �ִ´�.
		openboard_.push_back(start);

//int tick = GetTickCount();
//LOGEVENT("HG_CYAN", _T("	%s ��ã�� ����"), ((IBattleObject*)object)->GetNickname().GetString(), GetTickCount() - tick);

		//��θ� ã�´�.
		if(TRUE == ArrivedEnd(object, end, xsize, ysize))
		{
			GetShortPath();
			bFindPath = TRUE;
		}
//LOGEVENT("HG_CYAN", _T("	%s ��ã�� �ҿ�ð�(%d)"), ((IBattleObject*)object)->GetNickname().GetString(), GetTickCount() - tick);
//if(30000 < GetTickCount() - tick)
//{
//	int a = 0;
//	a = 0;
//}

	////������ �������·� �������´�.
	//SetBoardObject(end, destoccupy);
	return bFindPath;
}

//��ǥ��ġ�� ���� �ϸ� TRUE ����
BOOL CPathFinder::ArrivedEnd(void* object, BOARDINDEX end, UINT8 xsize, UINT8 ysize)
{
	while(FALSE == openboard_.empty())
	{
		BOARDINDEX board = *openboard_.begin();
		openboard_.pop_front();

		//��ǥ��ġ
		if(board == end_)
			return TRUE;

		AddFrontier(object, board, xsize, ysize);
	}
	return FALSE;
}

//board �ֺ��� openboard_�� �߰��Ѵ�.
void CPathFinder::AddFrontier(void* object, BOARDINDEX board, UINT8 xsize, UINT8 ysize)
{
	closedboard_.insert(board);

	//�ֺ��˻�
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

		//���������̸� ����
		BOARDINDEX tempboard = XY_TO_BOARDINDEX(x,y);
		if(closedboard_.end() != closedboard_.find(tempboard))
			continue;


		//object�� ����� ���� üũ�Ѵ�.
		if(TRUE == IsBadFrontier(object, x, y, xsize, ysize))
		{
			closedboard_.insert(tempboard);
			continue;
		}



		//�����
		int Gcost = CalculateGcost(direct, tempboard, GetGCost(x_board, y_board));
		int Hcost = GetBoardDistance(tempboard, end_) * 10;
		int Fcost = Gcost + Hcost;


		//ó���˻��� ������ �������¿� �߰��Ѵ�.
		//�̹� ���������̸�...cost �������ش�.(����� ��������)
		//���ο� ���� �� ũ�� �������� �ʴ´�.
		if(FALSE == IsOpenedTerrain(tempboard, Fcost))
			InsertOpenTerrain(tempboard, direct, Fcost, Gcost, Hcost);

	}//..for(int i=0; i<DIRECT_MAX; ++i)
}

//�̹� ���������̸�...cost �������ش�.(����� ��������)
//���ο� ���� �� ũ�� �������� �ʴ´�.
//���ο� ���� ������, ���⼭ ����, �Ʒ�(InsertOpenTerrain())���� �ٽ� �־� �ش�.
BOOL CPathFinder::IsOpenedTerrain(BOARDINDEX board, int Fcost)
{
	std::list<BOARDINDEX>::iterator it;
	for(it=openboard_.begin(); it!=openboard_.end(); )
	{
		//�̹� ���������̸�...cost �������ش�.(����� ��������)
		if(board == (*it))
		{
			if(GetFCost(*it) <= Fcost)
				return TRUE;//���ο� ���� ��ũ��, �������� �ʴ´�.

			it = openboard_.erase(it);//���ο� ���� ������, ���⼭ ����, �Ʒ����� �ٽ� �־� �ش�.
			return FALSE;
		}
		else
			++it;
	}

	return FALSE;
}

//ó���˻��� ������ �������¿� �߰��Ѵ�.
//�Ǵ� ��(IsOpenedTerrain())���� �簻���� �ʿ��� ������ �߰��� �ش�.
void CPathFinder::InsertOpenTerrain(BOARDINDEX board, int direct, int Fcost, int Gcost, int Hcost)
{
	//setting...new terrain
	BOARD_T x = BOARDINDEX_TO_X(board);
	BOARD_T y = BOARDINDEX_TO_Y(board);

	SetDirect(x, y, direct);
	SetFCost(x, y, Fcost);
	SetGCost(x, y, Gcost);
	SetHCost(x, y, Hcost);

	//��ǥ�Ÿ��� ���尡���� & ����ª�� ������
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

	//��ǥ��ġ
	pathboard_.push_front(end_);
	{
		//���������ΰ�� �߰� ������ �����մϴ�.
		postdirect_ = GetDirect(x, y); //end_ �� ������ ���� �����մϴ�.
		shortpathboard_.push_front(end_);
	}

	while(1)
	{
		int direct = GetDirect(x, y);
		if(FALSE == OnDiagonal(direct))
			continue;

		//�� board���� �������� ���� board�� ã�´�.
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


		//���� board�� ������ġ��...�׸� ã�´�.
		BOARDINDEX board = XY_TO_BOARDINDEX(x, y);
		if(start_ == board)
			break;

		//pathboard_.push_back(board);
		pathboard_.push_front(board);

		//���������ΰ�� �߰� ������ �����մϴ�.
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
	//	, eTerrain_Water	//��
	//	, eTerrain_Swamp	//��
	//	, eTerrain_Wall		//�庮
	//	, eTerrain_Start	//������ġ
	//	, eTerrain_End		//��ǥ��ġ

	//HG_TODO : ��ֹ��� ����� �߰��Ѵ�.
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

//�� board ������ �Ÿ�(���� : BOARDINDEX) -- �ൿ�°� ������ ����
int CPathFinder::GetBoardDistance(BOARDINDEX source, BOARDINDEX target)
{
	BOARD_T x_source = BOARDINDEX_TO_X(source);
	BOARD_T y_source = BOARDINDEX_TO_Y(source);

	BOARD_T x_target = BOARDINDEX_TO_X(target);
	BOARD_T y_target = BOARDINDEX_TO_Y(target);

	//board�� ��ĭ�� �Ÿ�1�̰� �밢�� �̵��� ���⿡ ������ �������� �Ÿ��� ���Ѵ�.
	return abs(x_target - x_source) + abs(y_target - y_source);
}

//�밢�� �̵����� üũ
BOOL CPathFinder::OnDiagonal(int direction)
{
	if(TRUE == bIsDiagonal_)
		return TRUE;
	
	//�밢�� �̵��� �Ұ����� ���...�밢���� �ɷ�����.
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


//�߸��� ��ǥ
BOOL CPathFinder::IsBadFrontier(void* object, BOARD_T x, BOARD_T y, UINT8 xsize, UINT8 ysize)
{
	//x ����� 3�̸� �¿�� 1ĭ�̶�� ��
	UINT8 xgap = xsize / 2;
	UINT8 ygap = ysize / 2;

	for(UINT8 yy=0; yy<ysize; ++yy)
	{
		//�߾ӿ��� ���� gap��ŭ ������ ��ġ���� �����ؼ� �����ŭ �Ʒ��� �̵�
		BOARD_T ytemp = y - ygap + yy;

		for(UINT8 xx=0; xx<xsize; ++xx)
		{
			//�߾ӿ��� ���� gap��ŭ ������ ��ġ���� �����ؼ� �����ŭ �������� �̵�
			BOARD_T xtemp = x - xgap + xx;

			//�߸��� ��ġ...����
			if(TRUE == IsBadBoard(xtemp, ytemp))
				return TRUE;

			////Ÿ���� �������̸�...����
			//if(NULL != GetBoardObject(xtemp, ytemp) && object != GetBoardObject(xtemp, ytemp))
			//	return TRUE;

			//���� ���� �����̸�...����
			if(eTerrain_Wall == GetTerrainType(xtemp, ytemp))
				return TRUE;
			
		}//..for(UINT8 xx=0; xx<xsize; ++xx)
	}//..for(UINT8 yy=0; yy<ysize; ++yy)

	return FALSE;
}

//	start : �������� ��ġ
//	end : ������ ��ġ
BOARDINDEX CPathFinder::GetNearBodyFrame(BOARDINDEX start, BOARDINDEX end)
{
	//���� ����� ��ġ�� �����ȴ�.
	BOARDINDEX nearestboard = end;
	int distance = GetBoardDistance(end, start);//���� ū�� ����

	//Ÿ����ġ�� �����. �̵�����
	void* object = GetBoardObject(end);
	if(NULL == object)
		return end;

	//��ü�� �����̹Ƿ� �̵�����
	if(object == GetBoardObject(start))
		return end;


	//Ÿ������ ������ ��ü�� ������ Ȯ���Ͽ� ���� ����� ��ġ�� ã�´�.
	std::list<BOARDINDEX> openbodyframe;
	std::set<BOARDINDEX> closedbodyframe;


	openbodyframe.push_back(end);

	while(FALSE == openbodyframe.empty())
	{
		BOARDINDEX board = *openbodyframe.begin();
		openbodyframe.pop_front();
	
		////��ǥ��ġ
		//if(board == end_)
		//	return TRUE;
	
		AddBodyFrame(object, start, board, openbodyframe, closedbodyframe, nearestboard, distance);
	}

	return nearestboard;
}

//������ üũ�Ͽ� openbodyframe�� �߰��Ѵ�.
//	object : ����üũ�Ǵ� ��ü
//	start : �������� ��ġ
//	board : ����üũ�Ǵ� ��ġ
//	openbodyframe : open �� ��������
//	closedbodyframe : closed �� ���� ����
//	nearestboard : ���� ����� ��ġ
//	distance : ���� ����� �Ÿ�
void CPathFinder::AddBodyFrame(void* object, BOARDINDEX start, BOARDINDEX board
							   , std::list<BOARDINDEX>& openbodyframe, std::set<BOARDINDEX>& closedbodyframe
							   , BOARDINDEX& nearestboard, int& distance)
{
	closedbodyframe.insert(board);

	//�ֺ��˻�
	BOARD_T x_board = BOARDINDEX_TO_X(board);
	BOARD_T y_board = BOARDINDEX_TO_Y(board);

	for(int i=0; i<DIRECT_MAX; ++i)
	{
		//body frame�� �밢�� ���ο� ������� üũ�Ǿ�� �Ѵ�.
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

		////object�� ����� ���� üũ�Ѵ�.
		//if(TRUE == IsBadFrontier(object, x, y, xsize, ysize))
		//	continue;

		//�߸��� ��ġ...����
		if(TRUE == IsBadBoard(x, y))
			continue;

		//Ÿ���� �������̸�...����
		if(object != GetBoardObject(x, y))
			continue;


		//���������̸� ����
		BOARDINDEX tempboard = XY_TO_BOARDINDEX(x,y);
		if(closedbodyframe.end() != closedbodyframe.find(tempboard))
			continue;

		//open�����̸� ����.
		std::list<BOARDINDEX>::iterator it;
		for(it=openbodyframe.begin(); it!=openbodyframe.end(); ++it)
		{
			if(tempboard == *it)
				continue;
		}

		//�Ÿ����
		int cost = GetBoardDistance(tempboard, start);
		if(distance <= cost)//�Ÿ��� �հ��� ���� open�� �־��� �ʿ� ����.
			continue;

		//���� ����� ����Ÿ ����
		nearestboard = tempboard;
		distance = cost;

		//if(it != openboard_.end())
		openbodyframe.push_back(tempboard);

	}//..for(int i=0; i<DIRECT_MAX; ++i)
}

//�������� �ʴ� ��ǥ
BOOL CPathFinder::IsBadBoard(BOARD_T x, BOARD_T y)
{
	//�߸��� ��ġ...����
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

	//x ����� 3�̸� �¿�� 1ĭ�̶�� ��
	UINT8 xgap = xsize / 2;
	UINT8 ygap = ysize / 2;

	for(UINT8 yy=0; yy<ysize; ++yy)
	{
		//�߾ӿ��� ���� gap��ŭ ������ ��ġ���� �����ؼ� �����ŭ �Ʒ��� �̵�
		BOARD_T ytemp = y - ygap + yy;
		for(UINT8 xx=0; xx<xsize; ++xx)
		{
			//�߾ӿ��� ���� gap��ŭ ������ ��ġ���� �����ؼ� �����ŭ �������� �̵�
			BOARD_T xtemp = x - xgap + xx;
			if(TRUE == IsBadBoard(xtemp, ytemp))
				continue;

			map_[ytemp][xtemp].object_ = object;//�ڸ� ���(NULL�̸� ����)
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