#pragma once
#include"Building.h"
#include"gameNode.h"
class CBuildingManager : public gameNode
{
private:
	vector<CBuilding*> vecBuilding;
	vector<CBuilding*>::iterator iterBuilding;
public:
	CBuildingManager();
	~CBuildingManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addBuilding(PLAYER_TYPE player, Vec2 pos, bool factory, bool HQ, int tileIdx);

	vector<CBuilding*> getVecBuilding() { return vecBuilding; }
};