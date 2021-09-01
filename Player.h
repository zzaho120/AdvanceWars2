#pragma once
#include"gameNode.h"
#include"MoveUnitCommand.h"
#include "UnitManager.h"
#include "BuildingManager.h"
#include"Unit.h"

class CCursor;
class CMap;
class CPlayer : public gameNode
{
private:
	CUnitManager* unitMgr;
	CBuildingManager* buildingMgr;

	CCommand* command;
	CUnit* curUnit;

	bool isMove;

	PLAYER_TYPE playerType;

	CCursor* cursor;
	CMap* map;
public:
	CPlayer();
	CPlayer(PLAYER_TYPE player, CCursor* _cursor, CMap* _map);
	~CPlayer();

	HRESULT init();
	void release();
	void update();
	void render();

	void addUnitToMgr(UNIT_TYPE type);
	void selectUnit();
	void moveUnit();

	void enter();
	void exit();

	PLAYER_TYPE getPlayerType() { return playerType; }
};

