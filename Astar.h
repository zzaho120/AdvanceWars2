#pragma once
#include"Tile.h"
#include"gameNode.h"

struct AstarTile 
{
	bool isWalkable;
	bool isListOn;
	bool isOnlyInfry;
	Vec2 pos;
	int idx;
	int valueF, valueG, valueH;

	ENVIRONMENT_TYPE EnvirType;
	ASTAR_TYPE tileType;
	UNIT_TYPE unitType;

	AstarTile* parent;
};

class CAstar : public gameNode
{
private:
	AstarTile tile[TILE_NUM_X * TILE_NUM_Y];
	vector<AstarTile*> openList;
	vector<AstarTile*> closeList;

	ASTAR_STATE astarState;
	Vec2 startPos;
	Vec2 endPos;
	int lastIdx;

	int Cidx, Cg;
public:
	CAstar();
	CAstar(CTile** _tile, Vec2 start, Vec2 end);
	~CAstar();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileInit();
	void addOpenList();
	void visit(int tileNum);
	void caculateH();
	void caculateF();
	void addCloseList();
	void checkArrive();
};

