#pragma once
#include"Object.h"
class CUnit : public CObject
{
private:
	int fuel;
	int movement;
	int healthPoint;
	int matchType;
	UNIT_TYPE unitType;
	//PLAYER_TYPE playerType;
	bool isActive;
	
	// ���⸦ 2�� ���� �� �ִ� ���Ϳ� �� Ŭ������ ���� ��
public:
	CUnit();
	CUnit(UNIT_TYPE _type, int _fuel, int _move, int _match, Vec2 _pos);
	~CUnit();

	HRESULT init();
	void release();
	void update();
	void render();
};

