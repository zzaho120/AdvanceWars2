#include "framework.h"
#include "Unit.h"
#include "Map.h"

CUnit::CUnit() :
	CObject(), fuel(0),
	movement(0), healthPoint(1), tileIdx(0),
	matchType(UNIT_MATCH::NONE), isActive(false),
	unitType(UNIT_TYPE::NONE), isSelected(false),
	isMove(false)
{
}

CUnit::CUnit(UNIT_TYPE _type, Vec2 _pos, int idx) :
	CObject(_pos, { TILE_SIZE_X, TILE_SIZE_Y }), tileIdx(idx),
	unitType(_type), isActive(false), healthPoint(10),
	isSelected(false), isMove(false), setting(false)
{
	memset(tileRange, 0, sizeof(tileRange));
	settingByType(unitType);
}

CUnit::~CUnit()
{
}

HRESULT CUnit::init()
{
	ANIMATION->start("infry_idle_red_on");
	ANIMATION->start("infry_idle_red_off");
	ANIMATION->start("mech_idle_red_on");
	ANIMATION->start("mech_idle_red_off");
	ANIMATION->start("tank_idle_red_on");
	ANIMATION->start("tank_idle_red_off");
	ANIMATION->start("artil_idle_red_on");
	ANIMATION->start("artil_idle_red_off");
	ANIMATION->start("APC_idle_red_on");
	ANIMATION->start("APC_idle_red_off"); 
	ANIMATION->start("infry_move_left_red");
	ANIMATION->start("mech_move_left_red");
	ANIMATION->start("tank_move_left_red");
	ANIMATION->start("artil_move_left_red");
	ANIMATION->start("APC_move_left_red");

	return S_OK;
}

void CUnit::release()
{
}

void CUnit::update()
{
	floodFill();
}

void CUnit::render()
{
	TCHAR str[128];
	if (isSelected && !isMove)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			for (int j = 0; j < TILE_NUM_X; j++)
			{
				if (!tileRange[i * TILE_NUM_X + j]) continue;

				int left = 35 + j % TILE_NUM_X * TILE_SIZE_X - TILE_SIZE_X / 2;
				int top = 35 + i % TILE_NUM_Y * TILE_SIZE_Y - TILE_SIZE_Y / 2;
				IMAGE->alphaRender("move_range", getMapDC(), left, top, 200);

			}
		}
	}

	if (!isSelected)
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
	else
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

	if (!ASTAR->getRoadList().empty())
	{
		wsprintf(str, "%d %d %d", ASTAR->getRoadList().size(), tileIdx, ASTAR->getRoadList().top());
		TextOut(getMapDC(), 100, 100, str, strlen(str));
	}
}

void CUnit::select()
{
}

void CUnit::move(Vec2 _pos, int idx)
{
	if (!setting)
	{
		ASTAR->setStartEnd(tileIdx, idx, unitType);
		ASTAR->update();
		popIdx = ASTAR->getRoadList().top();
		ASTAR->eraseRoadList();
		setting = true;
	}
	if (pos == getLeftTopVec2(STAGE->getCurMap()->getTile()[popIdx]->getPos(), TILE_SIZE))
	{
		ASTAR->eraseRoadList();
		if(!ASTAR->getRoadList().empty())
			popIdx = ASTAR->getRoadList().top();
	}
	if (pos.x < getLeftTopVec2(STAGE->getCurMap()->getTile()[popIdx]->getPos(), TILE_SIZE).x)
	{
		pos.x += UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.x > getLeftTopVec2(STAGE->getCurMap()->getTile()[popIdx]->getPos(), TILE_SIZE).x)
	{
		pos.x -= UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.y < getLeftTopVec2(STAGE->getCurMap()->getTile()[popIdx]->getPos(), TILE_SIZE).y)
	{
		pos.y += UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
	else if (pos.y > getLeftTopVec2(STAGE->getCurMap()->getTile()[popIdx]->getPos(), TILE_SIZE).y)
	{
		pos.y -= UNIT_MOVE_SPEED;
		tileIdx = popIdx;
	}
}

void CUnit::wait()
{
	isActive = false;
}

void CUnit::floodFill()
{
	int cnt = 0;
	memset(tileRange, 0, sizeof(tileRange));
	if (isSelected && !isMove)
	{
		if (tileIdx % 30 > 0 || tileIdx % 30 < 29 || tileIdx > 29 || tileIdx < 579)
		{
			cnt++;
			tileRange[tileIdx] = true;

			if (tileIdx % 30 > 0) checkMoveRange(tileIdx - 1, cnt);
			if (tileIdx % 30 < 29) checkMoveRange(tileIdx + 1, cnt);
			if (tileIdx > 29) checkMoveRange(tileIdx + 30, cnt);
			if (tileIdx < 579) checkMoveRange(tileIdx - 30, cnt);

			if (cnt >= movement) return;
		}

	}
}

void CUnit::checkMoveRange(int idx, int cnt)
{
	if (tileIdx % 30 > 0 || tileIdx % 30 < 29 || tileIdx > 29 || tileIdx < 579)
	{
		ENVIRONMENT_TYPE curTile = STAGE->getCurMap()->getTile()[idx]->getTileType();
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
				tileRange[idx] = true;
			}
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			if (!isOnlyInfry && !isSea)
			{
				cnt++;
				tileRange[idx] = true;
			}
			else if (isOnlyInfry)
			{
				return;
			}
			break;
		default:
			break;
		}
		if (cnt > movement || isSea) return;
		if (tileIdx % 30 > 0) checkMoveRange(idx - 1, cnt);
		if (tileIdx % 30 < 29) checkMoveRange(idx + 1, cnt);
		if (tileIdx > 29) checkMoveRange(idx + 30, cnt);
		if (tileIdx < 579) checkMoveRange(idx - 30, cnt);
	}
}

bool CUnit::correctMove(int idx)
{
	if (tileRange[idx])
		return true;
	else
		return false;
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