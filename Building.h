#pragma once
#include "Object.h"
class CBuilding : public CObject
{
private:
	bool isFactory;
	bool isHQ;

	int tileIdx;
	//int income;
	//int def;
	PLAYER_TYPE playerType;
public:
	CBuilding();
	CBuilding(PLAYER_TYPE type, Vec2 pos, bool factory, bool HQ, int idx);
	~CBuilding();


	HRESULT init();
	void release();
	void update();
	void render();

	int getTileIdx() { return tileIdx; }
	bool getIsHQ() { return isHQ; }
	bool getIsFactory() { return isFactory; }
	PLAYER_TYPE getPlayerType() { return playerType; }

	void setIsHQ(bool HQ) { isHQ = HQ; }
	void setIsFactory(bool factory) { isFactory = factory; }
};