#pragma once
#include"Object.h"
#include"Weapon.h"
#include"Astar.h"
#include"Tile.h"

class CGameManager;
class CUnit : public CObject
{
private:
	int fuel;
	int movement;
	int tileIdx;
	int popIdx;
	float healthPoint;

	UNIT_MATCH matchType;
	UNIT_TYPE unitType;
	PLAYER_TYPE playerType;

	bool isActive;
	bool isSelected;
	bool isMove;
	bool isArrive;
	bool isCapturing;
	bool isAttack;
	bool isRange;
	bool moveSetting;

	bool moveRange[TILE_NUM_X * TILE_NUM_Y];
	bool attackRange[TILE_NUM_X * TILE_NUM_Y];
	bool availRange[TILE_NUM_X * TILE_NUM_Y];
	bool rangeCheck[TILE_NUM_X * TILE_NUM_Y];

	CWeapon* weaponArr[static_cast<int>(WEAPON_NUMBER::END)];

	CGameManager* gameMgr;
public:
	CUnit();
	CUnit(PLAYER_TYPE _player, UNIT_TYPE _type, Vec2 _pos, int idx, CGameManager* mgr);
	~CUnit();

	HRESULT init();
	void release();
	void update();
	void render();

	void wait();
	
	// 이동 관련 함수
	void move(Vec2 _pos, int idx);
	void moveFloodFill();
	void checkMoveRange(int idx, int cnt, int checkfuel);
	bool correctMove(int idx);
	void playMoveSound();
	void stopMoveSound();

	// 공격 관련 함수
	void attackFloodFill();
	void checkAttackRange(int idx, int cnt, CWeapon* useWeapon);
	void rangeFloodFill();
	void checkRange(int idx, int cnt, CWeapon* useWeapon);
	float calculateDamage(CUnit* unit, CTile* tile);
	float weaponDamage(UNIT_TYPE type, WEAPON_NUMBER num);
	bool correctAttack(int idx);
	bool isEnemyInFocus();
	void attack(CUnit* oppositUnit, CTile* oppositTile);
	void damaged(float damage);
	void bulletCount(CUnit* oppositUnit);

	// 점령 관련 함수
	void capture();
	void unCapture();

	// 보급 관련 함수
	void supply();

	void repair();
	
	void weaponSetting(UNIT_TYPE type);

	bool getSelected() { return isSelected; }
	bool getActive() { return isActive; }
	bool getMove() { return isMove; }
	bool getArrive() { return isArrive; }
	bool getRange() { return isRange; }
	int getHP() { return healthPoint; }
	int getFuel() { return fuel; }
	int getAmmo()
	{
		int ammo = 0;
		switch (weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->getWeaponType())
		{
		case WEAPON_TYPE::NONE:
			ammo = 0;
			break;
		case WEAPON_TYPE::M_GUN:
		case WEAPON_TYPE::BAZOOKA:
		case WEAPON_TYPE::CANNON:
			ammo = weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->getAmmo();
			break;
		}
		return ammo;
	}

	UNIT_TYPE getUnitType() { return unitType; }
	PLAYER_TYPE getPlayerType() { return playerType; }
	
	int getTileIdx() { return tileIdx; }

	void settingByType(UNIT_TYPE type);

	void setPlayerType(PLAYER_TYPE type) { if (playerType == PLAYER_TYPE::NONE) playerType = type; }
	void setActive(bool active) { isActive = active; }
	void setSelected(bool select) { isSelected = select; }
	void setMove(bool move) { isMove = move; }
	void setTileIdx(int idx) { tileIdx = idx; }
	void setMoveSetting(bool moveSet) { moveSetting = moveSet; }
	void setArrive(bool arrive) { isArrive = arrive; }
	void setAttack(bool attack) { isAttack = attack; }
	void setRange(bool range) { isRange = range; }
};