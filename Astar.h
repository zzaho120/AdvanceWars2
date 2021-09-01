#pragma once
#include"singleton.h"

struct aStarTile
{
	bool walkable;		//�������� �ֳ�	
	bool listOn;		//openList�� �߰��Ǿ����� ����
	int F, G, H;
	aStarTile* parent;	//�θ� Ÿ�� �ּ�
	TILE_TYPE type;		//Ÿ�ϼӼ�
	ENVIRONMENT_TYPE envirType;
	int tileIdx;
	Vec2 pos;
};

class CMap;
class CAstar : public Singleton<CAstar>
{
private:
	aStarTile tile[TILE_NUM_X * TILE_NUM_Y];
	vector<aStarTile*> openList;
	vector<aStarTile*> closeList;
	stack<int> pathList;

	UNIT_TYPE curUnitType;
	
	int startIdx;
	int endIdx;

	int Cg;
	int lastIdx;
	int closeIdx;

	bool isArrive;

	CMap* map;
public:
	CAstar();
	~CAstar();

	HRESULT init();
	HRESULT init(CMap* map);
	void release();
	void update();

	void tileInitializing();//��ġ�� �Ӽ��� �°� �ʱ�ȭ
	void addOpenList();	//���¸���Ʈ �߰�
	void caculateH();		//���¸���Ʈ�� Ÿ�� H�� ���
	void caculateF();		//���¸���Ʈ�� Ÿ�� F�� ���
	void addCloseList();	//���� ���� F������ Ŭ���� ����Ʈ�� �߰�
	void checkArrive();	//�����ߴ��� ���� üũ

	void setStartEnd(int startIdx, int endIdx, UNIT_TYPE type);
	void setPath(aStarTile* tile);
	void checkGValue(int idx);

	stack<int> getRoadList() { return pathList; }
	aStarTile* getAstarTile() { return tile; }

	void erasePathList() { if (!pathList.empty()) pathList.pop(); }
};