#pragma once
#include"gameNode.h"
class CWeapon : public gameNode
{
private:
	int ammo;
	int maxRange;
	int minRange;
	WEAPON_TYPE weaponType;
public:
	CWeapon();
	CWeapon(WEAPON_TYPE _type, int _ammo, int min, int max);
	~CWeapon();

	void reloadAmmo();

	int getAmmo() { return ammo; }
	int getMaxRange() { return maxRange; }
	int getMinRange() { return minRange; }
	WEAPON_TYPE getWeaponType() { return weaponType; }

	void setAmmo(int bullet) 
	{ 
		ammo = bullet;  
		if (ammo <= 0) ammo = 0;
	}
};

