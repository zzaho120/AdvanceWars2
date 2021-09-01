#include "framework.h"
#include "Weapon.h"

CWeapon::CWeapon() :
	weaponType(WEAPON_TYPE::NONE), ammo(0), range(0)
{
}

CWeapon::CWeapon(WEAPON_TYPE _type, int _ammo, int _range) :
	weaponType(_type), ammo(_ammo), range(_range)
{ }

CWeapon::~CWeapon()
{ }