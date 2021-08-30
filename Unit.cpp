#include "framework.h"
#include "Unit.h"

CUnit::CUnit() :
	CObject(), fuel(0),
	movement(0), healthPoint(1),
	matchType(UNIT_MATCH::NONE), isActive(false),
	unitType(UNIT_TYPE::NONE)
{
}

CUnit::CUnit(UNIT_TYPE _type, Vec2 _pos) :
	CObject(_pos, { TILE_SIZE_X, TILE_SIZE_Y }),
	unitType(_type), isActive(false), healthPoint(10)
{
	settingByType(unitType);
}

CUnit::~CUnit()
{
}

HRESULT CUnit::init()
{
	ANIMATION->start("infry_idle_red_on");
	ANIMATION->start("infry_idle_red_off");
	ANIMATION->start("mech_idle_red_on");
	ANIMATION->start("mech_idle_red_off");
	ANIMATION->start("tank_idle_red_on");
	ANIMATION->start("tank_idle_red_off");
	ANIMATION->start("artil_idle_red_on");
	ANIMATION->start("artil_idle_red_off");
	ANIMATION->start("APC_idle_red_on");
	ANIMATION->start("APC_idle_red_off");
	return S_OK;
}

void CUnit::release()
{
}

void CUnit::update()
{
}

void CUnit::render()
{
	switch (unitType)
	{
	case UNIT_TYPE::NONE:
		break;
	case UNIT_TYPE::INFANTRY:
		if (isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_red_on"));
		else if (!isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("infry_idle_red_off"));
		break;
	case UNIT_TYPE::MECH:
		if (isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_red_on"));
		else if (!isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("mech_idle_red_off"));
		break;
	case UNIT_TYPE::TANK:
		if (isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_red_on"));
		else if (!isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("tank_idle_red_off"));
		break;
	case UNIT_TYPE::ARTILLERY:
		if (isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_red_on"));
		else if (!isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("artil_idle_red_off"));
		break;
	case UNIT_TYPE::APC:
		if (isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_red_on"));
		else if (!isActive)
			img->aniRender(getMapDC(), pos.x, pos.y, ANIMATION->findAnimation("APC_idle_red_off"));
		break;
	}
	
}

void CUnit::settingByType(UNIT_TYPE type)
{
	switch (type)
	{
	case UNIT_TYPE::NONE:
		break;
	case UNIT_TYPE::INFANTRY:
		img = IMAGE->findImage("infantry_idle");
		fuel = 99;
		movement = 3;
		matchType = UNIT_MATCH::INFANTRY;
		break;
	case UNIT_TYPE::MECH:
		img = IMAGE->findImage("mech_idle");
		fuel = 70;
		movement = 2;
		matchType = UNIT_MATCH::INFANTRY;
		break;
	case UNIT_TYPE::TANK:
		img = IMAGE->findImage("tank_idle");
		fuel = 70;
		movement = 6;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	case UNIT_TYPE::ARTILLERY:
		img = IMAGE->findImage("artillery_idle");
		fuel = 50;
		movement = 5;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	case UNIT_TYPE::APC:
		img = IMAGE->findImage("APC_idle");
		fuel = 70;
		movement = 6;
		matchType = UNIT_MATCH::VEHICLE;
		break;
	}
}