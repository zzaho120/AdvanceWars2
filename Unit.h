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
	
	// ���⸦ 2�� ���� �� �ִ� ���Ϳ� �� Ŭ������ ���� ��
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