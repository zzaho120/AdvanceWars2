#pragma once
#include"Command.h"
#include"Unit.h"
#include"Building.h"
#include"Tile.h"
class CCaptureBuildingCommand : public CCommand
{
private:
	CUnit* curUnit;
	CBuilding* curBuilding;
	CTile* curTile;
public:
	CCaptureBuildingCommand() { }
	CCaptureBuildingCommand(CUnit* unit, CBuilding* building, CTile* tile) :
		curUnit(unit), curBuilding(building), curTile(tile)
	{ }
	~CCaptureBuildingCommand() { }

	virtual void excute()
	{
		curUnit->capture();
		if (curBuilding->getCapturePoint() - curUnit->getHP() <= 0)
			curUnit->unCapture();
		curBuilding->capture(curUnit);
		curTile->capture(curBuilding);
	}

	virtual void undo()
	{
	}


};

