#pragma once
#include "Object.h"
class CBuilding : public CObject
{
private:
	bool isFactory;
	bool isHeadQuater;

	int tileIdx;
	int income;
	int def;
	PLAYER_TYPE playerType;
public:
	CBuilding();
	~CBuilding();

	HRESULT init();
	void release();
	void update();
	void render();
};