#pragma once
#include"singleton.h"

class CUnit;
class CUnitFactory : public Singleton<CUnitFactory>
{
private:

public:
	CUnitFactory();
	~CUnitFactory();

	CUnit* createUnit(UNIT_TYPE type, Vec2 pos);
};