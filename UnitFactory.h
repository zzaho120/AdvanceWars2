#pragma once
#include"singleton.h"

class CUnit;
class CGameManager;
class CUnitFactory : public Singleton<CUnitFactory>
{
private:

public:
	CUnitFactory();
	~CUnitFactory();

	CUnit* createUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx, CGameManager* mgr);
};