#pragma once
#include"singleton.h"

class CBuilding;
class CBuildingFactory : public Singleton<CBuildingFactory>
{
private:

public:
	CBuildingFactory();
	~CBuildingFactory();

	CBuilding* createBuilding(PLAYER_TYPE player, Vec2 pos, bool factory, bool HQ, int tileIdx);
};