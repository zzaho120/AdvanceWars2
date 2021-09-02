#pragma once
#include"gameNode.h"
#include "MoveUnitCommand.h"
#include "UnitManager.h"
#include "BuildingManager.h"
#include "Unit.h"

class CPlayer : public gameNode
{
private:
	bool isSelected;
	bool isMove;

	PLAYER_TYPE playerType;

	CGameManager* gameMgr;
public:
	CPlayer();
	CPlayer(PLAYER_TYPE player);
	~CPlayer();

	HRESULT init();
	HRESULT init(CGameManager* mgr);
	void release();
	void update();

	void selectUnit();
	void moveUnit();
	void selectFactory();

	void enter();
	void exit();

	PLAYER_TYPE getPlayerType() { return playerType; }
};

