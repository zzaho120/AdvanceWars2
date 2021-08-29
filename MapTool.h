#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
class CMapTool : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	Vec2 cursor;

	bool isToolMode;
public:
	CMapTool();
	~CMapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
	void setMap();

	void tileDirectionSet();

	void riverSetting(int tileNum);
	int checkRiver(int tileNum, DIRECTION direction);
	
	void roadSetting(int tileNum);
	int checkRoad(int tileNum, DIRECTION direction);

	void seaSetting(int tileNum);
	int checkSea(int tileNum, DIRECTION direction);
	void seaTileSet(int tileNum, int seaType);

	void setEnvirType(int tileNum, ENVIRONMENT_TYPE environment, ROTATE_TYPE rotate);

	void setBuilding(int tileNum, BUILDING_TYPE building, PLAYER_TYPE player);
	void setHQ(int tileNum, PLAYER_TYPE player);

	bool save(const char* fileName);
	bool load(const char* fileName);

	// 옵저버 패턴 구현 전
	//void subscribe(CObject* obj);
	//void unsubscribe(CObject* obj);
};