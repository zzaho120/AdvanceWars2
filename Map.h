#pragma once
#include "gameNode.h"
#include "Tile.h"

class CCamera;
class CBuilding;
class CMap : public gameNode
{
private:
	CTile* tile[TILE_NUM_X * TILE_NUM_Y];
	CCamera* cam;

	vector<CBuilding*> vecBuilding;
	vector<CBuilding*>::iterator iterBuilding;

	bool isDebug;
public:
	CMap();
	CMap(Vec2 startPos, Vec2 size);
	CMap(CMap* copy);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	CTile** getTile() { return tile; }
	void setCameraLink(CCamera* _cam) { cam = _cam; }

	void addBuilding(PLAYER_TYPE type, Vec2 pos, bool factory, bool HQ, int idx);
	void eraseBuilding(int idx);
};

