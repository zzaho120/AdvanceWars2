#pragma once
#include"gameNode.h"
#include "UnitManager.h"
#include "BuildingManager.h"
#include "Unit.h"

class CPlayer : public gameNode
{
private:
	bool isUnitSelect;
	bool isOnUI;
	bool isMove;

	int money;
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
	
	void playerInput();

	void selectUnit();
	void moveUnit();
	void viewFactory();
	void viewOption();

	void enter();
	void exit();

	PLAYER_TYPE getPlayerType() { return playerType; }
	bool getOnUI() { return isOnUI; }
	int getMoney() { return money; }

	void setUnitSelect(bool select) { isUnitSelect = select; }
	void setOnUI(bool select) { isOnUI = select; }
	void setMove(bool move) { isMove = move; }
	void setMoney(int _money) { money = _money; }
};

