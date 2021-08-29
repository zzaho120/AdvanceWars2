#include "framework.h"
#include "Unit.h"

CUnit::CUnit() :
	CObject(), fuel(0),
	movement(0), healthPoint(1),
	matchType(0), isActive(false),
	unitType(UNIT_TYPE::NONE)
{
}

CUnit::CUnit(UNIT_TYPE _type, int _fuel, int _move, int _match, Vec2 _pos) :
	CObject(_pos, { TILE_SIZE_X, TILE_SIZE_Y }), fuel(_fuel),
	movement(_move), healthPoint(10),
	matchType(_match), isActive(true),
	unitType(_type)
{ 
	switch (unitType)
	{
	case UNIT_TYPE::NONE:
		break;
	case UNIT_TYPE::INFANTRY:
		img = IMAGE->findImage("infantry_idle");
		break;
	case UNIT_TYPE::MECH:
		img = IMAGE->findImage("mech_idle");
		break;
	case UNIT_TYPE::TANK:
		img = IMAGE->findImage("tank_idle");
		break;
	case UNIT_TYPE::ARTILLERY:
		img = IMAGE->findImage("artillery_idle");
		break;
	case UNIT_TYPE::APC:
		img = IMAGE->findImage("APC_idle");
		break;
	default:
		break;
	}
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
	default:
		break;
	}
	
}
