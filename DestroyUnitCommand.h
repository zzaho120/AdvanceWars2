#pragma once
#include"Command.h"
#include"Unit.h"
#include"UnitManager.h"
class CDestroyUnitCommand : public CCommand
{
private:
	CUnit* curUnit;
	CUnitManager* unitMgr;
public:
	CDestroyUnitCommand() { }
	CDestroyUnitCommand(CUnit* unit, CUnitManager* mgr) :
		curUnit(unit), unitMgr(mgr)
	{ }
	~CDestroyUnitCommand() { }

	virtual void excute()
	{
		EFFECT->play("ground_destroy", curUnit->getPos().x + TILE_SIZE_X / 2, curUnit->getPos().y + TILE_SIZE_Y / 2);
		unitMgr->eraseUnit(curUnit);
	}

	virtual void undo()
	{
	}

};

