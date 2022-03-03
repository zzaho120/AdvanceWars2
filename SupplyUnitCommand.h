#pragma once
#include "Command.h"
#include "UnitManager.h"
class CSupplyUnitCommand : public CCommand
{
private:
	CUnitManager* unitMgr;

public:
	CSupplyUnitCommand() { }
	CSupplyUnitCommand(CUnitManager* mgr) :
		unitMgr(mgr)
	{ }
	~CSupplyUnitCommand() { }


	virtual void excute()
	{
		CUnit* curUnit = nullptr;
		int tileIdx = 0;
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			if (unitMgr->getVecUnit()[idx]->getSelected())
			{
				curUnit = unitMgr->getUnit(idx);
				tileIdx = curUnit->getTileIdx();
				break;
			}
		}

		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			int unitIdx = unitMgr->getVecUnit()[idx]->getTileIdx();
			if (unitIdx == tileIdx)
				continue;
			if (unitIdx == tileIdx - 1)
				unitMgr->getVecUnit()[idx]->supply();
			if (unitIdx == tileIdx + 1)
				unitMgr->getVecUnit()[idx]->supply();
			if (unitIdx == tileIdx - 30)
				unitMgr->getVecUnit()[idx]->supply();
			if (unitIdx == tileIdx + 30)
				unitMgr->getVecUnit()[idx]->supply();
		}
	}

	virtual void undo()
	{
	}
};

