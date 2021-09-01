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

	bool isDebug;
public:
	CMap();
	CMap(Vec2 startPos, Vec2 size);
	CMap(const char* fileName);
	CMap(const char* fileName, CCamera* camera);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(const char* fileName);

	CTile** getTile() { return tile; }
	void setCameraLink(CCamera* _cam) { cam = _cam; }
};