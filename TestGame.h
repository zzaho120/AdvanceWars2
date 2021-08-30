#pragma once
#include"gameNode.h"
#include "Camera.h"
#include "Map.h"
#include "UnitManager.h"
class CTestGame : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	Vec2 cursor;
	CUnitManager* unitMgr;
public:
	CTestGame();
	~CTestGame();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();

	void addUnitToMgr(UNIT_TYPE type);
};