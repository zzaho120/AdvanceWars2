#pragma once
#include"Command.h"
#include"Unit.h"
class CMoveUnitCommand : public CCommand
{
private:
	CUnit* unit;
	CBuilding* building;
	int finalTileIdx;
	int firstTileIdx;
	Vec2 finalPos;
	Vec2 firstPos;
public:
	CMoveUnitCommand() { }
	CMoveUnitCommand(CUnit* _unit, CBuilding* _building, Vec2 _pos, int idx) :
		unit(_unit), building(_building), finalPos(_pos), firstPos(unit->getPos()), finalTileIdx(idx),
		firstTileIdx(unit->getTileIdx())
	{ }

	virtual void excute()
	{
		unit->move(finalPos, finalTileIdx);
		if (building != nullptr)
		{
			unit->unCapture();
			building->unCapture();
		}
	}

	virtual void undo()
	{
		unit->setPos(firstPos);
		unit->setTileIdx(firstTileIdx);
	}

	Vec2 getfinalPos() { return finalPos; }
	int getfinalIdx() { return finalTileIdx; }

	Vec2 getfirstPos() { return firstPos; }
	int getfirstIdx() { return firstTileIdx; }

	CUnit* getMoveUnit() { return unit; }
};

