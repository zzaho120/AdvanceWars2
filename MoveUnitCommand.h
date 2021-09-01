#pragma once
#include"Command.h"
#include"Unit.h"
class CMoveUnitCommand : public CCommand
{
private:
	CUnit* unit;
	int tileIdx;
	int firstTileIdx;
	Vec2 movePos;
	Vec2 firstPos;
public:
	CMoveUnitCommand(CUnit* _unit, Vec2 _pos, int idx) :
		unit(_unit), movePos(_pos), firstPos(unit->getPos()), tileIdx(idx),
		firstTileIdx(unit->getTileIdx())
	{ };

	virtual void excute()
	{
		unit->move(movePos, tileIdx);
	};

	virtual void undo()
	{
		unit->setPos(firstPos);
		unit->setTileIdx(firstTileIdx);
	}
};