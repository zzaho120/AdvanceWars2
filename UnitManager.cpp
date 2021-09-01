#include "framework.h"
#include "UnitManager.h"

CUnitManager::CUnitManager()
{
}

CUnitManager::~CUnitManager()
{
}

HRESULT CUnitManager::init()
{
    return S_OK;
}

void CUnitManager::release()
{
}

void CUnitManager::update()
{
    if (InputManager->isOnceKeyDown(VK_F2))
    {
        for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
            (*iterUnit)->setActive(true);
    }
    for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
        (*iterUnit)->update();
}

void CUnitManager::render()
{
    for (iterUnit = vecUnit.begin(); iterUnit != vecUnit.end(); iterUnit++)
        (*iterUnit)->render();
}

void CUnitManager::addUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx, CMap* map)
{
    CUnit* tempUnit = UNITFACTORY->createUnit(player, type, getLeftTopVec2(pos, TILE_SIZE), idx, map);
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
