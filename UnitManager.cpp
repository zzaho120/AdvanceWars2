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

void CUnitManager::addUnit(UNIT_TYPE type, Vec2 pos)
{
    CUnit* tempUnit = UNITFACTORY->createUnit(type, { pos.x - TILE_SIZE_X / 2, pos.y - TILE_SIZE_Y / 2 });
    tempUnit->init();
    vecUnit.push_back(tempUnit);
}
