#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "UnitManager.h"
#include "BuildingManager.h"

class CGameManager : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	CCursor* cursor;
	CUnitManager* unitMgr;
	CBuildingManager* buildingMgr;

public:
	CGameManager();
	~CGameManager();

	HRESULT init();
	void release();
	void update();
	void render();
};