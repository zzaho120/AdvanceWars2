#pragma once
#include"Object.h"
#include"Weapon.h"
#include"Astar.h"

class CMap;
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

	CWeapon* weaponArr[static_cast<int>(WEAPON_NUMBER::END)];

	CMap* map;
public:
	CUnit();
	CUnit(PLAYER_TYPE _player, UNIT_TYPE _type, Vec2 _pos, int idx, CMap* _map);
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
	
	void weaponSetting(UNIT_TYPE type);

	bool getSelected() { return isSelected; }
	bool getActive() { return isActive; }
	bool getMove() { return isMove; }
	UNIT_TYPE getUnitType() { return unitType; }
	
	int getTileIdx() { return tileIdx; }

	void settingByType(UNIT_TYPE type);

	void setPlayerType(PLAYER_TYPE type) { if (playerType == PLAYER_TYPE::NONE) playerType = type; }
	void setActive(bool active) { isActive = active; }
	void setSelected(bool select) { isSelected = select; }
	void setMove(bool move) { isMove = move; }
	void setTileIdx(int idx) { tileIdx = idx; }
	void setMoveSetting(bool moveSet) { moveSetting = moveSet; }
};