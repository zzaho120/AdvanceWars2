#include "framework.h"
#include "UnitManager.h"

CUnitManager::CUnitManager() : gameMgr(nullptr)
{
}

CUnitManager::~CUnitManager()
{
}

HRESULT CUnitManager::init()
{
    return S_OK;
}

HRESULT CUnitManager::init(CGameManager* mgr)
{
    gameMgr = mgr;
    return S_OK;
}

void CUnitManager::release()
{
}

void CUnitManager::update()
{
    for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
        (*iterUnit)->update();
}

void CUnitManager::render()
{
    for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
        (*iterUnit)->render();
}

void CUnitManager::addUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx)
{
    CUnit* tempUnit = UNITFACTORY->createUnit(player, type, getLeftTopVec2(pos, TILE_SIZE), idx, gameMgr);
    tempUnit->init();
    vecUnit.push_back(tempUnit);
}

void CUnitManager::setAllActive(bool active)
{
    for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
    {
        (*iterUnit)->setActive(active);
    }
}
