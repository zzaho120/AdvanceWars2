#pragma once
#include "gameNode.h"
#include "Tile.h"

class CEnvironmnet;
class CBuilding;
class CMap : public gameNode
{
private:
	CTile* tileMap[TILE_NUM_X * TILE_NUM_Y];
	vector<CBuilding*> vecBuilding;
	vector<CBuilding*>::iterator iterBuilding;
	
	/*리스트 배경오브젝

	리스트 빌딩 

		빌딩
			타일인덱스*/
public:
	CMap();
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();
};

