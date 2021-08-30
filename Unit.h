#pragma once
#include"Object.h"
class CUnit : public CObject
{
private:
	int fuel;
	int movement;
	int healthPoint;
	UNIT_MATCH matchType;
	UNIT_TYPE unitType;
	PLAYER_TYPE playerType;
	bool isActive;
	
	// 무기를 2종 담을 수 있는 벡터와 그 클래스를 만들 것
public:
	CUnit();
	CUnit(UNIT_TYPE _type, Vec2 _pos);
	~CUnit();

	HRESULT init();
	void release();
	void update();
	void render();

	void settingByType(UNIT_TYPE type);

	void setPlayerType(PLAYER_TYPE type) { if(playerType == PLAYER_TYPE::NONE) playerType = type; }
};