#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "UnitManager.h"
#include "BuildingManager.h"

class GameManager : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	CCursor* cursor;
	CUnitManager* unitMgr;
	CBuildingManager* buildingMgr;

public:
	GameManager();
	~GameManager();

	HRESULT init();
	void release();
	void update();
	void render();
};