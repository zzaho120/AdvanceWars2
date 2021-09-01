#include "framework.h"
#include "GameManager.h"

CGameManager::CGameManager() :
	cam(new CCamera),
	map(new CMap("save/spannisland.map", cam)),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager)
{
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::init()
{
	return S_OK;
}

void CGameManager::release()
{
}

void CGameManager::update()
{
	cam->update();
	map->update();
	//cam->setTargetVec2(cursor);
	cursor->update();
	unitMgr->update();

}

void CGameManager::render()
{
	map->render();
	unitMgr->render();
	cursor->render();
	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);

}
