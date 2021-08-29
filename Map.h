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
	CMap(const char* fileName);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(const char* fileName);

	CTile** getTile() { return tile; }
	vector<CBuilding*> getVecBuilding() { return vecBuilding; }
	void setCameraLink(CCamera* _cam) { cam = _cam; }

	void addBuilding(PLAYER_TYPE type, Vec2 pos, bool factory, bool HQ, int idx);
	void eraseBuilding(int idx);
	void clearBuilding();
};