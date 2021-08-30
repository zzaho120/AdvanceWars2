#pragma once
#include"Unit.h"
class CUnitManager
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

	void addUnit(UNIT_TYPE type, Vec2 pos);

	vector<CUnit*> getVecUnit() { return vecUnit; }

	CUnit* getUnit(int idx) { return vecUnit[idx]; }
};

