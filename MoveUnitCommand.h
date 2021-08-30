#pragma once
#include"Command.h"
#include"Unit.h"
class CMoveUnitCommand : public CCommand
{
private:
	CUnit* unit;
	Vec2 movePos;
	Vec2 firstPos;
public:
	CMoveUnitCommand(CUnit* _unit, Vec2 _pos) :
		unit(_unit), movePos(_pos), firstPos(_pos)
	{ };

	virtual void excute()
	{
		unit->move(movePos);
	};

	virtual void undo()
	{
		unit->setPos(firstPos);
	}
};