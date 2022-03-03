#include "framework.h"
#include "BuildingManager.h"

CBuildingManager::CBuildingManager()
{
}

CBuildingManager::~CBuildingManager()
{
}

HRESULT CBuildingManager::init()
{
	return E_NOTIMPL;
}

void CBuildingManager::release()
{
}

void CBuildingManager::update()
{
}

void CBuildingManager::render()
{
}

void CBuildingManager::addBuilding(PLAYER_TYPE player, Vec2 pos, bool factory, bool HQ, int tileIdx)
{
	CBuilding* tempBuilding = BUILDINGFACTORY->createBuilding(player, pos, factory, HQ, tileIdx);
	tempBuilding->init();
	vecBuilding.push_back(tempBuilding);
}