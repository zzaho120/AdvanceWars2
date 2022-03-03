#include "framework.h"
#include "Weapon.h"

CWeapon::CWeapon() :
	weaponType(WEAPON_TYPE::NONE), ammo(0), maxRange(0), minRange(0)
{
}

CWeapon::CWeapon(WEAPON_TYPE _type, int _ammo, int min, int max) :
	weaponType(_type), ammo(_ammo), maxRange(max), minRange(min)
{ }

CWeapon::~CWeapon()
{ }

void CWeapon::reloadAmmo()
{
	switch (weaponType)
	{
	case WEAPON_TYPE::NONE:
		ammo = 0;
		break;
	case WEAPON_TYPE::M_GUN:
		ammo = 99;
		break;
	case WEAPON_TYPE::BAZOOKA:
		ammo = 3;
		break;
	case WEAPON_TYPE::CANNON:
		ammo = 9;
		break;
	}
}
