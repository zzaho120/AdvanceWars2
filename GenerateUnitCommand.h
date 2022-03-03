#pragma once
#include "Command.h"
#include "UnitManager.h"

class CMap;
class CGenerateUnitCommand : public CCommand
{
private:
	PLAYER_TYPE playerType;
	UNIT_TYPE unitType;
	Vec2 generatePos;
	int generateIdx;

	CUnitManager* unitMgr;
	CMap* map;
public:
	CGenerateUnitCommand(PLAYER_TYPE player, UNIT_TYPE unit, Vec2 pos, 
		int idx, CUnitManager* mgr, CMap* _map) :
		playerType(player), unitType(unit), generatePos(pos),
		generateIdx(idx), unitMgr(mgr), map(_map)
	{ }
	~CGenerateUnitCommand() { }

	virtual void excute()
	{
		unitMgr->addUnit(playerType, unitType, generatePos, generateIdx);
	}

	virtual void undo()
	{

	}
};

