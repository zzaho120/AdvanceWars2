#pragma once
#include"gameNode.h"
#include "Camera.h"
#include "Map.h"
#include "UnitManager.h"
#include "MoveUnitCommand.h"
class CTestGame : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	Vec2 cursor;
	int cursorIdx;

	CUnitManager* unitMgr;
	CUnit* curUnit;
	CCommand* command;

	bool isSelected;
	bool isMove;
public:
	CTestGame();
	~CTestGame();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();

	void addUnitToMgr(UNIT_TYPE type);
	void unitSelect();
	void unitMove();
};