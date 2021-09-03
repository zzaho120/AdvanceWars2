#include "framework.h"
#include "Unit.h"
#include "GameManager.h"
#include "UnitFactory.h"

CUnitFactory::CUnitFactory()
{
}

CUnitFactory::~CUnitFactory()
{
}

CUnit* CUnitFactory::createUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx, CGameManager* mgr)
{
	return new CUnit(player, type, pos, idx, mgr);
}

