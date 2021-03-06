#include "framework.h"
#include "Tile.h"
#include "Building.h"

CTile::CTile() :
	CObject(),
	tileType(ENVIRONMENT_TYPE::NONE),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE),
	directionType(DIRECTION_SPRITE::NO),
	rotateType(ROTATE_TYPE::NONE),
	defense(0)
{ }

CTile::CTile(Vec2 _pos, Vec2 _size, image* _img, animation* _ani) :
	CObject(_pos, _size, _img, _ani),
	tileType(static_cast<ENVIRONMENT_TYPE>(RND->getFromIntTo(1, 6))),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE),
	directionType(DIRECTION_SPRITE::NO),
	rotateType(ROTATE_TYPE::DEG0),
	defense(0)
{}

CTile::~CTile()
{
}

HRESULT CTile::init()
{
	ANIMATION->start("river_line00");
	ANIMATION->start("river_line01");
	ANIMATION->start("river_curve00");
	ANIMATION->start("river_curve01");
	ANIMATION->start("river_curve02");
	ANIMATION->start("river_curve03");
	ANIMATION->start("river_3ways00");
	ANIMATION->start("river_3ways01");
	ANIMATION->start("river_3ways02");
	ANIMATION->start("river_3ways03");
	ANIMATION->start("river_4ways");

	ANIMATION->start("sea_2ways_curve00");
	ANIMATION->start("sea_2ways_curve01");
	ANIMATION->start("sea_2ways_curve02");
	ANIMATION->start("sea_2ways_curve03");

	ANIMATION->start("sea_3ways_curve00");
	ANIMATION->start("sea_3ways_curve01");
	ANIMATION->start("sea_3ways_curve02");
	ANIMATION->start("sea_3ways_curve03");


	ANIMATION->start("sea_3ways_top");
	ANIMATION->start("sea_3ways_left");
	ANIMATION->start("sea_3ways_right");
	ANIMATION->start("sea_3ways_bottom");

	ANIMATION->start("sea_4ways_top00");
	ANIMATION->start("sea_4ways_top01");
	ANIMATION->start("sea_4ways_left00");
	ANIMATION->start("sea_4ways_left01");
	ANIMATION->start("sea_4ways_right00");
	ANIMATION->start("sea_4ways_right01");
	ANIMATION->start("sea_4ways_bottom00");
	ANIMATION->start("sea_4ways_bottom01");
	ANIMATION->start("sea_4ways00");

	ANIMATION->start("sea_5ways_top");
	ANIMATION->start("sea_5ways_left");
	ANIMATION->start("sea_5ways_right");
	ANIMATION->start("sea_5ways_bottom");
	ANIMATION->start("sea_5ways00");
	ANIMATION->start("sea_5ways01");
	ANIMATION->start("sea_5ways02");
	ANIMATION->start("sea_5ways03");

	ANIMATION->start("sea_6ways00");
	ANIMATION->start("sea_6ways01");
	ANIMATION->start("sea_6ways02");
	ANIMATION->start("sea_6ways03");
	ANIMATION->start("sea_6ways04");
	ANIMATION->start("sea_6ways05");

	ANIMATION->start("sea_7ways00");
	ANIMATION->start("sea_7ways01");
	ANIMATION->start("sea_7ways02");
	ANIMATION->start("sea_7ways03");

	ANIMATION->start("sea_8ways");

	ANIMATION->start("sea_horizontal00");
	ANIMATION->start("sea_horizontal01");
	ANIMATION->start("sea_horizontal02");

	ANIMATION->start("sea_vertical00");
	ANIMATION->start("sea_vertical01");
	ANIMATION->start("sea_vertical02");
	ANIMATION->start("sea_noway");

	ANIMATION->start("city_red");
	ANIMATION->start("city_blue");

	ANIMATION->start("factory_red");
	ANIMATION->start("factory_blue");

	defenseSetting();
	return S_OK;
}

void CTile::release()
{
}

void CTile::update()
{
}

void CTile::render()
{
	tileRender();
}

void CTile::tileRender()
{
	Vec2 imgFrame = { 0, 0 };
	switch (tileType)
	{
	case ENVIRONMENT_TYPE::NONE:
		IMAGE->frameRender("single_environment", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::PLAIN:
		IMAGE->frameRender("single_environment", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::WOOD:
		IMAGE->frameRender("wood", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::MOUNTAIN:
		IMAGE->frameRender("single_environment", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 1, 0);
		break;
	case ENVIRONMENT_TYPE::SEA:
		IMAGE->frameRender("sea", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::ROAD:
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::BRIDGE:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
		case ROTATE_TYPE::DEG180:
			imgFrame = { 2, 0 };
			break;
		case ROTATE_TYPE::DEG90:
		case ROTATE_TYPE::DEG270:
			imgFrame = { 3, 0 };
			break;
		}
		IMAGE->frameRender("single_environment", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), imgFrame.x, imgFrame.y);
		break;
	case ENVIRONMENT_TYPE::RIVER_LINE:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("river_line00");
			break;
		case ROTATE_TYPE::DEG90:
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("river_line01");
			break;
		}
		IMAGE->findImage("flow_river")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::RIVER_CURVE:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("river_curve00");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("river_curve01");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("river_curve02");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("river_curve03");
			break;
		}
		IMAGE->findImage("flow_river")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::RIVER_3WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("river_3ways00");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("river_3ways01");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("river_3ways02");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("river_3ways03");
			break;
		}
		IMAGE->findImage("flow_river")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::RIVER_4WAYS:
		ani = ANIMATION->findAnimation("river_4ways");
		IMAGE->findImage("flow_river")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::ROAD_LINE:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
		case ROTATE_TYPE::DEG180:
			imgFrame = { 1, 0 };
			break;
		case ROTATE_TYPE::DEG90:
		case ROTATE_TYPE::DEG270:
			imgFrame = { 0, 0 };
			break;
		}
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), imgFrame.x, imgFrame.y);
		break;
	case ENVIRONMENT_TYPE::ROAD_CURVE:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			imgFrame = { 2, 0 };
			break;
		case ROTATE_TYPE::DEG90:
			imgFrame = { 4, 0 };
			break;
		case ROTATE_TYPE::DEG180:
			imgFrame = { 4, 2 };
			break;
		case ROTATE_TYPE::DEG270:
			imgFrame = { 2, 2 };
			break;
		}
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), imgFrame.x, imgFrame.y);
		break;
	case ENVIRONMENT_TYPE::ROAD_3WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			imgFrame = { 2, 1 };
			break;
		case ROTATE_TYPE::DEG90:
			imgFrame = { 3, 0 };
			break;
		case ROTATE_TYPE::DEG180:
			imgFrame = { 4, 1 };
			break;
		case ROTATE_TYPE::DEG270:
			imgFrame = { 3, 2 };
			break;
		}
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), imgFrame.x, imgFrame.y);
		break;
	case ENVIRONMENT_TYPE::ROAD_4WAYS:
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 3, 1);
		break;

	case ENVIRONMENT_TYPE::SEA_VERTICAL00:
		ani = ANIMATION->findAnimation("sea_vertical00");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::SEA_VERTICAL01:
		ani = ANIMATION->findAnimation("sea_vertical01");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::SEA_VERTICAL02:
		ani = ANIMATION->findAnimation("sea_vertical02");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_HORIZONTAL00:
		ani = ANIMATION->findAnimation("sea_horizontal00");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::SEA_HORIZONTAL01:
		ani = ANIMATION->findAnimation("sea_horizontal01");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::SEA_HORIZONTAL02:
		ani = ANIMATION->findAnimation("sea_horizontal02");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;


	case ENVIRONMENT_TYPE::SEA_NOWAYS:
		ani = ANIMATION->findAnimation("sea_noway");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_2WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_2ways_curve01");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_2ways_curve00");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_2ways_curve03");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("sea_2ways_curve02");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_3WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_3ways_curve00");
			break;
		case ROTATE_TYPE::DEG45:
			ani = ANIMATION->findAnimation("sea_3ways_top");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_3ways_curve01");
			break;
		case ROTATE_TYPE::DEG135:
			ani = ANIMATION->findAnimation("sea_3ways_right");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_3ways_curve03");
			break;
		case ROTATE_TYPE::DEG225:
			ani = ANIMATION->findAnimation("sea_3ways_bottom");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("sea_3ways_curve02");
			break;
		case ROTATE_TYPE::DEG315:
			ani = ANIMATION->findAnimation("sea_3ways_left");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_4WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_4ways_top00");
			break;
		case ROTATE_TYPE::DEG45:
			ani = ANIMATION->findAnimation("sea_4ways_top01");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_4ways_left00");
			break;
		case ROTATE_TYPE::DEG135:
			ani = ANIMATION->findAnimation("sea_4ways_left01");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_4ways_right00");
			break;
		case ROTATE_TYPE::DEG225:
			ani = ANIMATION->findAnimation("sea_4ways_right01");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("sea_4ways_bottom00");
			break;
		case ROTATE_TYPE::DEG315:
			ani = ANIMATION->findAnimation("sea_4ways_bottom01");
			break;
		case ROTATE_TYPE::DEG360:
			ani = ANIMATION->findAnimation("sea_4ways00");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_5WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_5ways_top");
			break;
		case ROTATE_TYPE::DEG45:
			ani = ANIMATION->findAnimation("sea_5ways00");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_5ways_left");
			break;
		case ROTATE_TYPE::DEG135:
			ani = ANIMATION->findAnimation("sea_5ways01");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_5ways_right");
			break;
		case ROTATE_TYPE::DEG225:
			ani = ANIMATION->findAnimation("sea_5ways02");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("sea_5ways_bottom");
			break;
		case ROTATE_TYPE::DEG315:
			ani = ANIMATION->findAnimation("sea_5ways03");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_6WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_6ways00");
			break;
		case ROTATE_TYPE::DEG45:
			ani = ANIMATION->findAnimation("sea_6ways01");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_6ways02");
			break;
		case ROTATE_TYPE::DEG135:
			ani = ANIMATION->findAnimation("sea_6ways03");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_6ways04");
			break;
		case ROTATE_TYPE::DEG225:
			ani = ANIMATION->findAnimation("sea_6ways05");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_7WAYS:
		switch (rotateType)
		{
		case ROTATE_TYPE::DEG0:
			ani = ANIMATION->findAnimation("sea_7ways00");
			break;
		case ROTATE_TYPE::DEG90:
			ani = ANIMATION->findAnimation("sea_7ways01");
			break;
		case ROTATE_TYPE::DEG180:
			ani = ANIMATION->findAnimation("sea_7ways02");
			break;
		case ROTATE_TYPE::DEG270:
			ani = ANIMATION->findAnimation("sea_7ways03");
			break;
		}
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;

	case ENVIRONMENT_TYPE::SEA_8WAYS:
		ani = ANIMATION->findAnimation("sea_8ways");
		IMAGE->findImage("flow_sea")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	}

	int playerColor = 0;
	switch (playerType)
	{
	case PLAYER_TYPE::NONE:
		playerColor = 5;
		break;
	case PLAYER_TYPE::PLAYER1:
		playerColor = 0;
		break;
	case PLAYER_TYPE::PLAYER2:
		playerColor = 1;
		break;
	}
	switch (buildingType)
	{
	case BUILDING_TYPE::NONE:
		break;
	case BUILDING_TYPE::CITY:
		switch (playerType)
		{
		case PLAYER_TYPE::NONE:
			IMAGE->frameRender("city", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, 0, 5);
			break;
		case PLAYER_TYPE::PLAYER1:
			ani = ANIMATION->findAnimation("city_red"); 
			IMAGE->findImage("city")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, ani);
			break;
		case PLAYER_TYPE::PLAYER2:
			ani = ANIMATION->findAnimation("city_blue");
			IMAGE->findImage("city")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, ani);
			break;
		}
		break;
	case BUILDING_TYPE::HEADQUATERS:
		switch (playerType)
		{
		case PLAYER_TYPE::NONE:
			IMAGE->frameRender("HQ", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, 0, 5);
			break;
		case PLAYER_TYPE::PLAYER1:
			ani = ANIMATION->findAnimation("HQ_red");
			IMAGE->findImage("HQ")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, ani);
			break;
		case PLAYER_TYPE::PLAYER2:
			ani = ANIMATION->findAnimation("HQ_blue");
			IMAGE->findImage("HQ")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 64, ani);
			break;
		}
		break;
	case BUILDING_TYPE::FACTORY:
		switch (playerType)
		{
		case PLAYER_TYPE::NONE:
			IMAGE->frameRender("factory", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 5);
			break;
		case PLAYER_TYPE::PLAYER1:
			ani = ANIMATION->findAnimation("factory_red");
			IMAGE->findImage("factory")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
			break;
		case PLAYER_TYPE::PLAYER2:
			ani = ANIMATION->findAnimation("factory_blue");
			IMAGE->findImage("factory")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
			break;
		}
		break;
	}
}

void CTile::defenseSetting()
{
	bool isBuilding = buildingType != BUILDING_TYPE::NONE;
	if (isBuilding)
	{
		switch (buildingType)
		{
		case BUILDING_TYPE::CITY:
		case BUILDING_TYPE::FACTORY:
			defense = 3;
			break;
		case BUILDING_TYPE::HEADQUATERS:
			defense = 4;
			break;
		}
	}
	else
	{
		switch (tileType)
		{
		case ENVIRONMENT_TYPE::PLAIN:
			defense = 1;
			break;
		case ENVIRONMENT_TYPE::WOOD:
			defense = 2;
			break;
		case ENVIRONMENT_TYPE::MOUNTAIN:
			defense = 4;
			break;
		case ENVIRONMENT_TYPE::RIVER:
		case ENVIRONMENT_TYPE::SEA:
		case ENVIRONMENT_TYPE::ROAD:
		case ENVIRONMENT_TYPE::BRIDGE:
		case ENVIRONMENT_TYPE::RIVER_LINE:
		case ENVIRONMENT_TYPE::RIVER_CURVE:
		case ENVIRONMENT_TYPE::RIVER_3WAYS:
		case ENVIRONMENT_TYPE::RIVER_4WAYS:
		case ENVIRONMENT_TYPE::ROAD_LINE:
		case ENVIRONMENT_TYPE::ROAD_CURVE:
		case ENVIRONMENT_TYPE::ROAD_3WAYS:
		case ENVIRONMENT_TYPE::ROAD_4WAYS:
		case ENVIRONMENT_TYPE::SEA_2WAYS:
		case ENVIRONMENT_TYPE::SEA_3WAYS:
		case ENVIRONMENT_TYPE::SEA_4WAYS:
		case ENVIRONMENT_TYPE::SEA_5WAYS:
		case ENVIRONMENT_TYPE::SEA_6WAYS:
		case ENVIRONMENT_TYPE::SEA_7WAYS:
		case ENVIRONMENT_TYPE::SEA_8WAYS:
		case ENVIRONMENT_TYPE::SEA_VERTICAL00:
		case ENVIRONMENT_TYPE::SEA_VERTICAL01:
		case ENVIRONMENT_TYPE::SEA_VERTICAL02:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL00:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL01:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL02:
		case ENVIRONMENT_TYPE::SEA_NOWAYS:
			defense = 0;
			break;
		}
	}
}

void CTile::capture(CBuilding* building)
{
	playerType = building->getPlayerType();
}

CTile& CTile::operator=(const CTile& ref)
{
	CObject::operator=(ref);

	tileType = ref.tileType;
	buildingType = ref.buildingType;
	unitType = ref.unitType;
	playerType = ref.playerType;
	directionType = ref.directionType;
	rotateType = ref.rotateType;

	return *this;
}

CTile* CTile::operator=(const CTile* ref)
{
	CObject::operator=(ref);

	tileType = ref->tileType;
	buildingType = ref->buildingType;
	unitType = ref->unitType;
	playerType = ref->playerType;
	directionType = ref->directionType;
	rotateType = ref->rotateType;

	return this;
}