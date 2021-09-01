#pragma once
#include"Object.h"
#include"Astar.h"
class CUnit : public CObject
{
private:
	int fuel;
	int movement;
	int healthPoint;
	int tileIdx;
	int popIdx;

	UNIT_MATCH matchType;
	UNIT_TYPE unitType;
	PLAYER_TYPE playerType;

	bool isActive;
	bool isSelected;
	bool isMove;
	bool moveSetting;
	bool tileRange[TILE_NUM_X * TILE_NUM_Y];
	// 무기를 2종 담을 수 있는 벡터와 그 클래스를 만들 것
public:
	CUnit();
	CUnit(UNIT_TYPE _type, Vec2 _pos, int idx);
	~CUnit();

	HRESULT init();
	void release();
	void update();
	void render();

	void select();
	void move(Vec2 _pos, int idx);
	void wait();
	void floodFill();
	void checkMoveRange(int idx, int cnt);
	bool correctMove(int idx);

	bool getSelected() { return isSelected; }
	bool getActive() { return isActive; }
	bool getMove() { return isMove; }

	void settingByType(UNIT_TYPE type);

	void setPlayerType(PLAYER_TYPE type) { if (playerType == PLAYER_TYPE::NONE) playerType = type; }
	void setActive(bool active) { isActive = active; }
	void setSelected(bool select) { isSelected = select; }
	void setMove(bool move) { isMove = move; }
};