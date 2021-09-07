#pragma once
#include "Command.h"
#include "UnitManager.h"
#include "BuildingManager.h"
class CRepairUnitCommand : public CCommand
{
private:
	PLAYER_TYPE curPlayerType;
	CUnitManager* unitMgr;
	CBuildingManager* buildingMgr;
public:
	CRepairUnitCommand() { }
	CRepairUnitCommand(PLAYER_TYPE type, CUnitManager* unit, CBuildingManager* building) :
		curPlayerType(type), unitMgr(unit), buildingMgr(building)
	{ }

	virtual void excute()
	{
		CUnit* curUnit = nullptr;
		CBuilding* curBuilding = nullptr;
		for (int i = 0; i < unitMgr->getVecUnit().size(); i++)
		{
			curUnit = unitMgr->getVecUnit()[i];
			if (curPlayerType == curUnit->getPlayerType())
			{
				for (int j = 0; j < buildingMgr->getVecBuilding().size(); j++)
				{
					curBuilding = buildingMgr->getVecBuilding()[j];
					bool equalPlayer = curBuilding->getPlayerType() == curUnit->getPlayerType();
					bool equalTile = curBuilding->getTileIdx() == curUnit->getTileIdx();
					if (equalTile && equalPlayer)
					{
						curUnit->repair();
						curUnit->supply();
						break;
					}
				}
			}
		}
	}

	virtual void undo()
	{
	}
};

