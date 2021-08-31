#pragma once
#include"Command.h"
#include"Unit.h"
class CMoveUnitCommand : public CCommand
{
private:
	CUnit* unit;
	int tileIdx;
	Vec2 movePos;
	Vec2 firstPos;
public:
	CMoveUnitCommand(CUnit* _unit, Vec2 _pos, int idx) :
		unit(_unit), movePos(_pos), firstPos(_pos), tileIdx(idx)
	{ };

	virtual void excute()
	{
		unit->move(movePos, tileIdx);
	};

	virtual void undo()
	{
		unit->setPos(firstPos);
	}
};