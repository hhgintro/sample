#pragma once
#include "PathDefine.h"

class CPathFinder
{
private:
	//terrain
	_stTerrain** map_;

	BOOL bIsDiagonal_;	//�밢�� �̵�(�˻�) ���� ����
	UINT8 postdirect_;	//shortpathboard_ �� ����ϱ� ���� ���������� ����մϴ�.

	int FcostFake_;		//F = G + H
	//int Gcost_;		//�Һ� ���
	int HcostFake_;		//��ǥ�Ÿ� ���


	CModuleManager m_module;
public:

	BOARDINDEX BOARD_X_COUNT;	//���� ������
	BOARDINDEX BOARD_Y_COUNT;	//���� ������

	BOARDINDEX start_;	//������ġ
	//std::vector<BOARDINDEX> start_;	//������ġ
	BOARDINDEX end_;		//��ǥ��ġ
	BOARDINDEX endFake_;	//��ǥ��ġ(end_ ��ġ�� ���� ������ ��ġ)



	std::list<BOARDINDEX> openboard_;//��������(Fcost�� ���� ������ ���ĵȴ�.)
	std::set<BOARDINDEX> closedboard_;//��������
	std::list<BOARDINDEX> pathboard_;//��ǥ->���� ���
	std::list<BOARDINDEX> shortpathboard_;//��ǥ->���� ���(���������� ��� �߰� board�� ������)
	std::list<BOARDINDEX> terrain_;//�ܺο��� Draw�� ���� terrain list�� ������ �����Ѵ�.(����,��ǥ��ġ�� ����)
	



public:
	CPathFinder();
	~CPathFinder();

	//�ʱ��Լ�(init()) �ݵ�� ȣ���� ��� ��.
	void Init(_stTerrain** terrain, BOARD_T sizeX, BOARD_T sizeY);
	void Clear();


	void ChangeStart(BOARDINDEX board);	//������ġ
	void ChangeStart(BOARD_T x, BOARD_T y);	//������ġ
	void ChangeEnd(BOARDINDEX board);	//��ǥ��ġ
	void ChangeEnd(BOARD_T x, BOARD_T y);	//��ǥ��ġ
	void AddTerrain(int tterraintype, BOARD_T x, BOARD_T y);//terrain(wall, water, swamp)
	BOOL RemoveTerrain(BOARDINDEX board);//terrain(wall, water, swamp)

	
	//����->��ǥ �����ϸ� TRUE ����(��δ� pathboard_ ���� Ȯ��)
	//object : �̵��Ϸ��� ��ü(3x3)�� ��� �ڽ��� ������ ���� �̵��Ұ����� ������.
	BOOL FindPath(void* object, BOARDINDEX start, BOARDINDEX& end, UINT8 xsize=1, UINT8 ysize=1);

	//�߸��� ��ǥ
	BOOL IsBadFrontier(void* object, BOARD_T x, BOARD_T y, UINT8 xsize, UINT8 ysize);

	//Ÿ������ ������ ��ü�� ������ Ȯ���Ͽ� ���� ����� ��ġ�� ã�´�.
	BOARDINDEX GetNearBodyFrame(BOARDINDEX start, BOARDINDEX end);

	//�������� �ʴ� ��ǥ
	BOOL IsBadBoard(BOARD_T x, BOARD_T y);
	BOOL IsBadBoard(BOARDINDEX board);

	//�밢�� �˻�
	BOOL GetIsDiagonal() { return bIsDiagonal_; }
	void SetIsDiagonal(BOOL diagonal) { bIsDiagonal_ = diagonal; }

	//�� board ������ �Ÿ�(���� : BOARDINDEX) -- �ൿ�°� ������ ����
	int GetBoardDistance(BOARDINDEX source, BOARDINDEX target);


#ifdef _HG_TEST_OBJECT_CHECK_
	//��ü����
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
	//����
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

	//��ǥ��ġ�� ���� �ϸ� TRUE ����
	BOOL ArrivedEnd(void* object, BOARDINDEX end, UINT8 xsize=1, UINT8 ysize=1);

	//board �ֺ��� openboard_�� �߰��Ѵ�.
	void AddFrontier(void* object, BOARDINDEX board, UINT8 xsize=1, UINT8 ysize=1);

	//������ üũ�Ͽ� openbodyframe�� �߰��Ѵ�.
	void AddBodyFrame(void* object, BOARDINDEX start, BOARDINDEX board
		, std::list<BOARDINDEX>& openbodyframe, std::set<BOARDINDEX>& closedbodyframe
		, BOARDINDEX& nearestboard, int& distance);

	//�̹� ���������̸�...cost �������ش�.(����� ��������)
	//���ο� ���� �� ũ�� �������� �ʴ´�.
	//���ο� ���� ������, ���⼭ ����, �Ʒ�(InsertOpenTerrain())���� �ٽ� �־� �ش�.
	BOOL IsOpenedTerrain(BOARDINDEX board, int Fcost);

	//ó���˻��� ������ �������¿� �߰��Ѵ�.
	//�Ǵ� ��(IsOpenedTerrain())���� �簻���� �ʿ��� ������ �߰��� �ش�.
	void InsertOpenTerrain(BOARDINDEX board, int direct, int Fcost, int Gcost, int Hcost);

	//������ġ -> ��ǥ��ġ�� ��θ� �����´�.
	void GetShortPath();

	//direct : ������ġ ����
	//board : ���� ��ġ
	//GCost : ���� ��ġ������ GCost
	int CalculateGcost(int direct, BOARDINDEX board, int GCost);

	//�밢�� �̵����� üũ
	BOOL OnDiagonal(int direction);

};