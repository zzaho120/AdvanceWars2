#pragma once
#include"gameNode.h"
#include"Unit.h"

class CGameManager;
class CUnitManager : public gameNode
{
private:
	vector<CUnit*> vecUnit;
	vector<CUnit*>::iterator iterUnit;

	CGameManager* gameMgr;
public:
	CUnitManager();
	~CUnitManager();

	HRESULT init();
	HRESULT init(CGameManager* mgr);
	void release();
	void update();
	void render();

	void addUnit(PLAYER_TYPE player, UNIT_TYPE type, Vec2 pos, int idx);
	void eraseUnit(CUnit* unit);
	void setAllActive(bool active);
	void setAllActive(PLAYER_TYPE player, bool active);

	vector<CUnit*> getVecUnit() { return vecUnit; }

	CUnit* getUnit(int idx) { return vecUnit[idx]; }

};