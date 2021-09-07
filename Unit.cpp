#include "framework.h"
#include "GameManager.h"
#include "Unit.h"
#include "Map.h"

CUnit::CUnit() :
	CObject(), fuel(0),
	movement(0), healthPoint(1), tileIdx(0),
	matchType(UNIT_MATCH::NONE), isActive(false),
	unitType(UNIT_TYPE::NONE), isSelected(false),
	isCapturing(false), isMove(false), isAttack(false)
{
	weaponSetting(unitType);
}

CUnit::CUnit(PLAYER_TYPE _player, UNIT_TYPE _type, Vec2 _pos, int idx, CGameManager* mgr) :
	CObject(_pos, { TILE_SIZE_X, TILE_SIZE_Y }), tileIdx(idx),
	unitType(_type), isActive(false), isArrive(false), healthPoint(10),
	isSelected(false), isMove(false), moveSetting(false), isCapturing(false), isAttack(false),
	gameMgr(mgr), playerType(_player), isRange(false)
{
	memset(moveRange, 0, sizeof(moveRange));
	settingByType(unitType);
	weaponSetting(unitType);
}


CUnit::~CUnit()
{
}

HRESULT CUnit::init()
{
	if (playerType == PLAYER_TYPE::PLAYER1)
	{
		switch (unitType)
		{
		case UNIT_TYPE::INFANTRY:
			ANIMATION->start("infry_idle_red_on");
			ANIMATION->start("infry_idle_red_off");
			ANIMATION->start("infry_move_left_red");
			break;
		case UNIT_TYPE::MECH:
			ANIMATION->start("mech_idle_red_on");
			ANIMATION->start("mech_idle_red_off");
			ANIMATION->start("mech_move_left_red");
			break;
		case UNIT_TYPE::TANK:
			ANIMATION->start("tank_idle_red_on");
			ANIMATION->start("tank_idle_red_off");
			ANIMATION->start("tank_move_left_red");
			break;
		case UNIT_TYPE::ARTILLERY:
			ANIMATION->start("artil_idle_red_on");
			ANIMATION->start("artil_idle_red_off");
			ANIMATION->start("artil_move_left_red");
			break;
		case UNIT_TYPE::APC:
			ANIMATION->start("APC_idle_red_on");
			ANIMATION->start("APC_idle_red_off");
			ANIMATION->start("APC_move_left_red");
			break;
		}
	}
	else if (playerType == PLAYER_TYPE::PLAYER2)
	{
		switch (unitType)
		{
		case UNIT_TYPE::INFANTRY:
			ANIMATION->start("infry_idle_blue_on");
			ANIMATION->start("infry_idle_blue_off");
			ANIMATION->start("infry_move_left_blue");
			break;
		case UNIT_TYPE::MECH:
			ANIMATION->start("mech_idle_blue_on");
			ANIMATION->start("mech_idle_blue_off");
			ANIMATION->start("mech_move_left_blue");
			break;
		case UNIT_TYPE::TANK:
			ANIMATION->start("tank_idle_blue_on");
			ANIMATION->start("tank_idle_blue_off");
			ANIMATION->start("tank_move_left_blue");
			break;
		case UNIT_TYPE::ARTILLERY:
			ANIMATION->start("artil_idle_blue_on");
			ANIMATION->start("artil_idle_blue_off");
			ANIMATION->start("artil_move_left_blue");
			break;
		case UNIT_TYPE::APC:
			ANIMATION->start("APC_idle_blue_on");
			ANIMATION->start("APC_idle_blue_off");
			ANIMATION->start("APC_move_left_blue");
			break;
		}
	}

	return S_OK;
}

void CUnit::release()
{
}

void CUnit::update()
{
	if (isSelected)
		attackFloodFill();
}

void CUnit::render()
{
	if (isSelected && !isMove)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			for (int j = 0; j < TILE_NUM_X; j++)
			{
				if (!moveRange[i * TILE_NUM_X + j]) continue;

				int left = 35 + j % TILE_NUM_X * TILE_SIZE_X - TILE_SIZE_X / 2;
				int top = 35 + i % TILE_NUM_Y * TILE_SIZE_Y - TILE_SIZE_Y / 2;
				IMAGE->alphaRender("move_range", getMapDC(), left, top, 200);

			}
		}
	}

	if (isSelected && isAttack)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			for (int j = 0; j < TILE_NUM_X; j++)
			{
				if (!attackRange[i * TILE_NUM_X + j]) continue;

				int left = 35 + j % TILE_NUM_X * TILE_SIZE_X - TILE_SIZE_X / 2;
				int top = 35 + i % TILE_NUM_Y * TILE_SIZE_Y - TILE_SIZE_Y / 2;
				IMAGE->alphaRender("attack_range", getMapDC(), left, top, 200);
			}
		}
	}

	if (!isSelected && isRange)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			for (int j = 0; j < TILE_NUM_X; j++)
			{
				if (!availRange[i * TILE_NUM_X + j]) continue;

				int left = 35 + j % TILE_NUM_X * TILE_SIZE_X - TILE_SIZE_X / 2;
				int top = 35 + i % TILE_NUM_Y * TILE_SIZE_Y - TILE_SIZE_Y / 2;
				IMAGE->alphaRender("attack_range", getMapDC(), left, top, 200);
			}
		}
	}

	if (!isSelected)
	{
		if (playerType == PLAYER_TYPE::PLAYER1)
		{
			switch (unitType)
			{
			case UNIT_TYPE::NONE:
				break;
			case UNIT_TYPE::INFANTRY:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_red_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_red_off"));
				break;
			case UNIT_TYPE::MECH:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_red_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_red_off"));
				break;
			case UNIT_TYPE::TANK:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_red_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_red_off"));
				break;
			case UNIT_TYPE::ARTILLERY:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_red_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_red_off"));
				break;
			case UNIT_TYPE::APC:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_red_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_red_off"));
				break;
			}
		}
		else if (playerType == PLAYER_TYPE::PLAYER2)
		{
			switch (unitType)
			{
			case UNIT_TYPE::NONE:
				break;
			case UNIT_TYPE::INFANTRY:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_blue_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_blue_off"));
				break;
			case UNIT_TYPE::MECH:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_blue_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_blue_off"));
				break;
			case UNIT_TYPE::TANK:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_blue_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_blue_off"));
				break;
			case UNIT_TYPE::ARTILLERY:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_blue_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_blue_off"));
				break;
			case UNIT_TYPE::APC:
				if (isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_blue_on"));
				else if (!isActive)
					img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_blue_off"));
				break;
			}
		}
		
	}
	else
	{
		if (playerType == PLAYER_TYPE::PLAYER1)
		{
			switch (unitType)
			{
			case UNIT_TYPE::NONE:
				break;
			case UNIT_TYPE::INFANTRY:
				IMAGE->findImage("infantry_move")->aniRender(getMapDC(), pos.x - 24, pos.y - 32, ANIMATION->findAnimation("infry_move_left_red"));
				break;
			case UNIT_TYPE::MECH:
				IMAGE->findImage("mech_move")->aniRender(getMapDC(), pos.x - 24, pos.y - 32, ANIMATION->findAnimation("infry_move_left_red"));
				break;
			case UNIT_TYPE::TANK:
				IMAGE->findImage("tank_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_red"));
				break;
			case UNIT_TYPE::ARTILLERY:
				IMAGE->findImage("artillery_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_red"));
				break;
			case UNIT_TYPE::APC:
				IMAGE->findImage("APC_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_red"));
				break;
			}
		}
		if (playerType == PLAYER_TYPE::PLAYER2)
		{
			switch (unitType)
			{
			case UNIT_TYPE::NONE:
				break;
			case UNIT_TYPE::INFANTRY:
				IMAGE->findImage("infantry_move")->aniRender(getMapDC(), pos.x - 24, pos.y - 32, ANIMATION->findAnimation("infry_move_left_blue"));
				break;
			case UNIT_TYPE::MECH:
				IMAGE->findImage("mech_move")->aniRender(getMapDC(), pos.x - 24, pos.y - 32, ANIMATION->findAnimation("infry_move_left_blue"));
				break;
			case UNIT_TYPE::TANK:
				IMAGE->findImage("tank_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_blue"));
				break;
			case UNIT_TYPE::ARTILLERY:
				IMAGE->findImage("artillery_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_blue"));
				break;
			case UNIT_TYPE::APC:
				IMAGE->findImage("APC_move")->aniRender(getMapDC(), pos.x - 12, pos.y - 32, ANIMATION->findAnimation("infry_move_left_blue"));
				break;
			}
		}
	}

	if (isCapturing)
		IMAGE->frameRender("unit_status_mark", getMapDC(), pos.x, pos.y + 39, 1, static_cast<int>(playerType));
	if (healthPoint < 10)
		IMAGE->frameRender("unit_hp", getMapDC(), pos.x + 39, pos.y + 39, static_cast<int>(floor(healthPoint)) - 1, 0);
}

void CUnit::move(Vec2 _pos, int idx)
{
	if (!moveSetting)
	{
		ASTAR->erasePathList();
		ASTAR->setStartEnd(tileIdx, idx, unitType);
		ASTAR->update();
		popIdx = ASTAR->getRoadList().top();
		moveSetting = true;
	}


	CTile** tile = gameMgr->getMap()->getTile();
	if (pos == getLeftTopVec2(tile[popIdx]->getPos(), TILE_SIZE))
	{
		ASTAR->erasePathList();
		fuel--;
		if (!ASTAR->getRoadList().empty())
		{
			popIdx = ASTAR->getRoadList().top();
		}
		else if(!isArrive)
			isArrive = true;
	}
	if (pos.x < getLeftTopVec2(tile[popIdx]->getPos(), TILE_SIZE).x)
	{
		pos.x += UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.x > getLeftTopVec2(tile[popIdx]->getPos(), TILE_SIZE).x)
	{
		pos.x -= UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.y < getLeftTopVec2(tile[popIdx]->getPos(), TILE_SIZE).y)
	{
		pos.y += UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.y > getLeftTopVec2(tile[popIdx]->getPos(), TILE_SIZE).y)
	{
		pos.y -= UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
}

void CUnit::wait()
{
	isActive = false;
	isSelected = false;
	isMove = false;
	moveSetting = false;
}

void CUnit::moveFloodFill()
{
	int cnt = 0;
	int checkFuel = fuel;
	memset(moveRange, 0, sizeof(moveRange));
	if (isSelected && !isMove)
	{
		if (tileIdx % 30 > 0 || tileIdx % 30 < 29 || tileIdx > 29 || tileIdx < 579)
		{
			moveRange[tileIdx] = true;

			if (tileIdx % 30 > 0) checkMoveRange(tileIdx - 1, cnt, checkFuel);
			if (tileIdx % 30 < 29) checkMoveRange(tileIdx + 1, cnt, checkFuel);
			if (tileIdx > 29) checkMoveRange(tileIdx + 30, cnt, checkFuel);
			if (tileIdx < 579) checkMoveRange(tileIdx - 30, cnt, checkFuel);
		}
	}
}

void CUnit::attackFloodFill()
{
	int cnt = 0;
	CWeapon* useWeapon = weaponArr[0]->getMaxRange() >= weaponArr[1]->getMaxRange() ? weaponArr[0] : weaponArr[1];
	memset(attackRange, 0, sizeof(attackRange));
	memset(rangeCheck, 0, sizeof(rangeCheck));

	if (tileIdx % 30 > 0 || tileIdx % 30 < 29 || tileIdx > 29 || tileIdx < 579)
	{
		attackRange[tileIdx] = false;
		availRange[tileIdx] = true;
		if (tileIdx % 30 > 0) checkAttackRange(tileIdx - 1, cnt, useWeapon);
		if (tileIdx % 30 < 29) checkAttackRange(tileIdx + 1, cnt, useWeapon);
		if (tileIdx > 29) checkAttackRange(tileIdx - 30, cnt, useWeapon);
		if (tileIdx < 579) checkAttackRange(tileIdx + 30, cnt, useWeapon);
	}

}

void CUnit::rangeFloodFill()
{
	int cnt = 0;
	CWeapon* useWeapon = weaponArr[0]->getMaxRange() >= weaponArr[1]->getMaxRange() ? weaponArr[0] : weaponArr[1];

	memset(availRange, 0, sizeof(availRange));
	memset(rangeCheck, 0, sizeof(rangeCheck));

	if (tileIdx % 30 > 0 || tileIdx % 30 < 29 || tileIdx > 29 || tileIdx < 579)
	{
		availRange[tileIdx] = false;
		rangeCheck[tileIdx] = true;
		if (tileIdx % 30 > 0) checkRange(tileIdx - 1, cnt, useWeapon);
		if (tileIdx % 30 < 29) checkRange(tileIdx + 1, cnt, useWeapon);
		if (tileIdx > 29) checkRange(tileIdx - 30, cnt, useWeapon);
		if (tileIdx < 579) checkRange(tileIdx + 30, cnt, useWeapon);
	}
}

void CUnit::checkMoveRange(int idx, int cnt, int checkFuel)
{
	if (idx % 30 > 0 || idx % 30 < 29 || idx > 29 || idx < 579)
	{
		bool isUnit = gameMgr->getMap()->getTile()[idx]->getUnitType() != UNIT_TYPE::NONE;
		bool isOppsitPlayer = false;

		for (int i = 0; i < gameMgr->getUnitMgr()->getVecUnit().size(); i++)
		{
			if (gameMgr->getUnitMgr()->getVecUnit()[i]->getTileIdx() == idx)
				isOppsitPlayer = gameMgr->getUnitMgr()->getVecUnit()[i]->getPlayerType() != playerType;
		}

		if (isUnit && isOppsitPlayer) return;

		bool isEnoughFuel = checkFuel > 0;

		if (!isEnoughFuel) return;

		ENVIRONMENT_TYPE curTile = gameMgr->getMap()->getTile()[idx]->getTileType();
		bool isOnlyInfry = (curTile == ENVIRONMENT_TYPE::MOUNTAIN) ||
			(curTile == ENVIRONMENT_TYPE::RIVER_3WAYS) ||
			(curTile == ENVIRONMENT_TYPE::RIVER_4WAYS) ||
			(curTile == ENVIRONMENT_TYPE::RIVER_LINE) ||
			(curTile == ENVIRONMENT_TYPE::RIVER_CURVE);
		bool isSea = (curTile == ENVIRONMENT_TYPE::SEA_2WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_3WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_4WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_5WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_6WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_7WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_8WAYS) ||
			(curTile == ENVIRONMENT_TYPE::SEA_HORIZONTAL00) ||
			(curTile == ENVIRONMENT_TYPE::SEA_HORIZONTAL01) ||
			(curTile == ENVIRONMENT_TYPE::SEA_HORIZONTAL02) ||
			(curTile == ENVIRONMENT_TYPE::SEA_VERTICAL00) ||
			(curTile == ENVIRONMENT_TYPE::SEA_VERTICAL01) ||
			(curTile == ENVIRONMENT_TYPE::SEA_VERTICAL02);

		switch (unitType)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			if (!isSea)
			{
				cnt++;
				checkFuel--;
				if(!isUnit)
					moveRange[idx] = true;
			}
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			if (!isOnlyInfry && !isSea)
			{
				cnt++;
				checkFuel--;
				if(!isUnit)
					moveRange[idx] = true;
			}
			else if (isOnlyInfry)
			{
				return;
			}
			break;
		default:
			break;
		}
		if (cnt >= movement || isSea) return;
		if (idx % 30 > 0) checkMoveRange(idx - 1, cnt, checkFuel);
		if (idx % 30 < 29) checkMoveRange(idx + 1, cnt, checkFuel);
		if (idx > 29) checkMoveRange(idx + 30, cnt, checkFuel);
		if (idx < 579) checkMoveRange(idx - 30, cnt, checkFuel);
	}
}

void CUnit::checkAttackRange(int idx, int cnt, CWeapon* useWeapon)
{
	if (idx % 30 > 0 || idx % 30 < 29 || idx > 29 || idx < 579)
	{
		cnt++;

		if (cnt > useWeapon->getMaxRange())
			return;

		if (cnt >= useWeapon->getMinRange() && !rangeCheck[idx])
		{
			for (int i = 0; i < gameMgr->getUnitMgr()->getVecUnit().size(); i++)
			{
				if (gameMgr->getUnitMgr()->getVecUnit()[i]->getTileIdx() == idx)
				{
					if (gameMgr->getUnitMgr()->getVecUnit()[i]->getPlayerType() != playerType)
						attackRange[idx] = true;
				}
			}
		}
		else
		{
			attackRange[idx] = false;
			rangeCheck[idx] = true;
		}

		if (idx % 30 > 0) checkAttackRange(idx - 1, cnt, useWeapon);
		if (idx % 30 < 29) checkAttackRange(idx + 1, cnt, useWeapon);
		if (idx > 29) checkAttackRange(idx - 30, cnt, useWeapon);
		if (idx < 579) checkAttackRange(idx + 30, cnt, useWeapon);
	}
}

void CUnit::checkRange(int idx, int cnt, CWeapon* useWeapon)
{
	if (idx % 30 > 0 || idx % 30 < 29 || idx > 29 || idx < 579)
	{
		cnt++;

		if (cnt > useWeapon->getMaxRange())
			return;

		if (cnt >= useWeapon->getMinRange() && !rangeCheck[idx])
		{
			availRange[idx] = true;
		}
		else
		{
			availRange[idx] = false;
			rangeCheck[idx] = true;
		}

		if (idx % 30 > 0) checkRange(idx - 1, cnt, useWeapon);
		if (idx % 30 < 29) checkRange(idx + 1, cnt, useWeapon);
		if (idx > 29) checkRange(idx - 30, cnt, useWeapon);
		if (idx < 579) checkRange(idx + 30, cnt, useWeapon);
	}
}

float CUnit::calculateDamage(CUnit* unit, CTile* tile)
{
	float weaponDamage1 = weaponDamage(unit->getUnitType(), WEAPON_NUMBER::WEAPON1);
	float weaponDamage2 = weaponDamage(unit->getUnitType(), WEAPON_NUMBER::WEAPON2);
	float resultDamage = 0;

	weaponDamage1 *= healthPoint;
	weaponDamage1 -= (weaponDamage1 / 10.0) * tile->getDefense();
	weaponDamage2 *= healthPoint;
	weaponDamage2 -= (weaponDamage2 / 10.0) * tile->getDefense();

	if (weaponDamage1 >= weaponDamage2) resultDamage = weaponDamage1;
	else resultDamage = weaponDamage2;

	return resultDamage;
}

float CUnit::weaponDamage(UNIT_TYPE type, WEAPON_NUMBER num)
{
	float damage = 0;

	switch (weaponArr[static_cast<int>(num)]->getWeaponType())
	{
	case WEAPON_TYPE::M_GUN:
		switch (type)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			damage = 5.5f;
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			damage = 0.5f;
			break;
		default:
			break;
		}
		break;
	case WEAPON_TYPE::BAZOOKA:
		switch (type)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			damage = 0;
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			damage = 6.5f;
			break;
		default:
			break;
		}
		break;
	case WEAPON_TYPE::CANNON:
		switch (type)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			damage = 8.0f;
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			damage = 6.5f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return damage;
}

bool CUnit::correctAttack(int idx)
{
	return attackRange[idx];
}

bool CUnit::isEnemyInFocus()
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (attackRange[idx])
		{
			return true;
		}
	}

	return false;
}

void CUnit::attack(CUnit* oppositUnit, CTile* oppositTile)
{
	float damage = 0;
	damage = calculateDamage(oppositUnit, oppositTile);
	bulletCount(oppositUnit);
	oppositUnit->damaged(damage / 10.0);
}

void CUnit::damaged(float damage)
{
	healthPoint -= damage;
	
	if (healthPoint < 0) healthPoint = 0;
}

void CUnit::bulletCount(CUnit* oppositUnit)
{
	float weaponDamage1 = weaponDamage(oppositUnit->getUnitType(), WEAPON_NUMBER::WEAPON1);
	float weaponDamage2 = weaponDamage(oppositUnit->getUnitType(), WEAPON_NUMBER::WEAPON2);

	if (weaponDamage1 >= weaponDamage2)
	{
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->setAmmo(weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->getAmmo() - 1);
	}
	else
	{
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->setAmmo(weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->getAmmo() - 1);
	}
}


void CUnit::supply()
{
	switch (unitType)
	{
	case UNIT_TYPE::INFANTRY:		
		fuel = 99;
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->reloadAmmo();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->reloadAmmo();
		break;
	case UNIT_TYPE::MECH:
		fuel = 70;
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->reloadAmmo();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->reloadAmmo();
		break;
	case UNIT_TYPE::TANK:
		fuel = 70;
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->reloadAmmo();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->reloadAmmo();
		break;
	case UNIT_TYPE::ARTILLERY:
		fuel = 50;
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->reloadAmmo();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->reloadAmmo();
		break;
	case UNIT_TYPE::APC:
		fuel = 70;
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)]->reloadAmmo();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)]->reloadAmmo();
		break;
	default:
		break;
	}
}

void CUnit::repair()
{
	healthPoint += 2;
	if (healthPoint > 10)
		healthPoint = 10;
}

void CUnit::weaponSetting(UNIT_TYPE type)
{
	switch (type)
	{
	case UNIT_TYPE::NONE:
	case UNIT_TYPE::APC:
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)] = new CWeapon();
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)] = new CWeapon();
		break;
	case UNIT_TYPE::INFANTRY:
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)] = new CWeapon(WEAPON_TYPE::M_GUN, 99, 1, 1);
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)] = new CWeapon();
		break;
	case UNIT_TYPE::MECH:
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)] = new CWeapon(WEAPON_TYPE::BAZOOKA, 3, 1, 1);
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)] = new CWeapon(WEAPON_TYPE::M_GUN, 99, 1, 1);
		break;
	case UNIT_TYPE::TANK:
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)] = new CWeapon(WEAPON_TYPE::CANNON, 9, 1, 1);
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)] = new CWeapon(WEAPON_TYPE::M_GUN, 99, 1, 1);
		break;
	case UNIT_TYPE::ARTILLERY:
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON1)] = new CWeapon(WEAPON_TYPE::CANNON, 9, 2, 3);
		weaponArr[static_cast<int>(WEAPON_NUMBER::WEAPON2)] = new CWeapon();
		break;
	}
}

bool CUnit::correctMove(int idx)
{
	return moveRange[idx];
}

void CUnit::capture()
{
	isCapturing = true;
}

void CUnit::unCapture()
{
	isCapturing = false;
}

void CUnit::settingByType(UNIT_TYPE type)
{
	switch (type)
	{
	case UNIT_TYPE::NONE:
		break;
	case UNIT_TYPE::INFANTRY:
		img = IMAGE->findImage("infantry_idle");
		fuel = 99;
		movement = 3;
		matchType = UNIT_MATCH::INFANTRY;
		break;
	case UNIT_TYPE::MECH:
		img = IMAGE->findImage("mech_idle");
		fuel = 70;
		movement = 2;
		matchType = UNIT_MATCH::INFANTRY;
		break;
	case UNIT_TYPE::TANK:
		img = IMAGE->findImage("tank_idle");
		fuel = 70;
		movement = 6;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	case UNIT_TYPE::ARTILLERY:
		img = IMAGE->findImage("artillery_idle");
		fuel = 50;
		movement = 5;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	case UNIT_TYPE::APC:
		img = IMAGE->findImage("APC_idle");
		fuel = 70;
		movement = 6;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	}
}