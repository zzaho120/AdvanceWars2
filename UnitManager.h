#pragma once
#include"gameNode.h"
#include"Unit.h"

class CMap;
class CUnitManager : public gameNode
{
private:
	vector<CUnit*> vecUnit;
	vector<CUnit*>::iterator iterUnit;
public:
	CUnitManager();
	~CUnitManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx, CMap* map);
	void setAllActive(bool active);

	vector<CUnit*> getVecUnit() { return vecUnit; }

	CUnit* getUnit(int idx) { return vecUnit[idx]; }
};

