#pragma once
#include "gameNode.h"
#include "Tile.h"

class CEnvironment;
class CBuilding;
class CMap : public gameNode
{
private:
	CTile* tile[TILE_NUM_X * TILE_NUM_Y];

	vector<CBuilding*> vecBuilding;
	vector<CBuilding*>::iterator iterBuilding;

	vector<CEnvironment*> vecEnvironment;
	vector<CEnvironment*>::iterator iterEnvironment;

	bool isDebug;
public:
	CMap();
	CMap(Vec2 startPos, Vec2 size);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	CTile** getTile() { return tile; }
};

