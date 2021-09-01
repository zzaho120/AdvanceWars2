#pragma once
#include"singleton.h"

struct aStarTile
{
	bool walkable;		//지나갈수 있냐	
	bool listOn;		//openList에 추가되었는지 여부
	int F, G, H;
	aStarTile* parent;	//부모 타일 주소
	TILE_TYPE type;		//타일속성
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

	void tileInitializing();//배치후 속성에 맞게 초기화
	void addOpenList();	//오픈리스트 추가
	void caculateH();		//오픈리스트내 타일 H값 계산
	void caculateF();		//오픈리스트내 타일 F값 계산
	void addCloseList();	//가장 작은 F선택후 클로즈 리스트에 추가
	void checkArrive();	//도착했는지 여부 체크

	void setStartEnd(int startIdx, int endIdx, UNIT_TYPE type);
	void setPath(aStarTile* tile);
	void checkGValue(int idx);

	stack<int> getRoadList() { return pathList; }
	aStarTile* getAstarTile() { return tile; }

	void erasePathList() { if (!pathList.empty()) pathList.pop(); }
};