#include "framework.h"
#include "Unit.h"
#include "UnitFactory.h"

CUnitFactory::CUnitFactory()
{
}

CUnitFactory::~CUnitFactory()
{
}

CUnit* CUnitFactory::createUnit(UNIT_TYPE type, Vec2 pos, int idx)
{
	return new CUnit(type, pos, idx);
}
