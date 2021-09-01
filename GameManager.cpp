#include "framework.h"
#include "GameManager.h"

GameManager::GameManager() :
	cam(new CCamera),
	map(new CMap("save/spannisland.map")),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager)
{
}

GameManager::~GameManager()
{
}

HRESULT GameManager::init()
{
	return S_OK;
}

void GameManager::release()
{
}

void GameManager::update()
{
	cursor->update();
}

void GameManager::render()
{
	cursor->render();
}
