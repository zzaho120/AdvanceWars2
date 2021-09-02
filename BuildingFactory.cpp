#include "framework.h"
#include "BuildingFactory.h"
#include "Building.h"

CBuildingFactory::CBuildingFactory()
{
}

CBuildingFactory::~CBuildingFactory()
{
}

CBuilding* CBuildingFactory::createBuilding(PLAYER_TYPE player, Vec2 pos, bool factory, bool HQ, int tileIdx)
{
	return new CBuilding(player, pos, factory, HQ, tileIdx);
}