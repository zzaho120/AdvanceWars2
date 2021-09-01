#include "framework.h"
#include "Unit.h"
#include "Map.h"
#include "UnitFactory.h"
CUnitFactory::CUnitFactory()
{
}

CUnitFactory::~CUnitFactory()
{
}

CUnit* CUnitFactory::createUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx, CMap* map)
{
	return new CUnit(player, type, pos, idx, map);
}
