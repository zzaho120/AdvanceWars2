#include "framework.h"
#include "Unit.h"
#include "UnitFactory.h"

CUnitFactory::CUnitFactory()
{
}

CUnitFactory::~CUnitFactory()
{
}

CUnit* CUnitFactory::createUnit(UNIT_TYPE type, Vec2 pos)
{
	return new CUnit(type, pos);
}
