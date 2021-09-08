#pragma once
#include "Command.h"
#include "Unit.h"
#include "Tile.h"
class CAttackUnitCommand : public CCommand
{
private:
	CUnit* currentUnit;
	CUnit* oppositUnit;
	CTile* currentTile;
	CTile* oppositTile;
public:
	CAttackUnitCommand() { }
	CAttackUnitCommand(CUnit* curUnit, CUnit* oppoUnit, CTile* curTile, CTile* oppoTile) :
		currentUnit(curUnit), oppositUnit(oppoUnit), currentTile(curTile), oppositTile(oppoTile)
	{ }
	~CAttackUnitCommand() { }

	virtual void excute()
	{
		currentUnit->attack(oppositUnit, oppositTile);
		if(currentUnit->getUnitType() != UNIT_TYPE::ARTILLERY && oppositTile->getUnitType() != UNIT_TYPE::ARTILLERY)
			oppositUnit->attack(currentUnit, currentTile);
	}

	virtual void undo()
	{
	}
};

