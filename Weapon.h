#pragma once
#include"gameNode.h"
class CWeapon : public gameNode
{
private:
	int ammo;
	int range;
	WEAPON_TYPE weaponType;
public:
	CWeapon();
	CWeapon(WEAPON_TYPE _type, int _ammo, int _range);
	~CWeapon();

	int getAmmo() { return ammo; }
	int getRange() { return range; }
	WEAPON_TYPE getWeaponType() { return weaponType; }
};

