#include "framework.h"
#include "Tile.h"

CTile::CTile() :
	CObject(),
	tileType(ENVIRONMENT_TYPE::NONE),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE),
	directionType(DIRECTION_SPRITE::NO),
	rotateType(ROTATE_TYPE::NONE)
{ }

CTile::CTile(Vec2 _pos, Vec2 _size, image* _img, animation* _ani) :
	CObject(_pos, _size, _img, _ani),
	tileType(static_cast<ENVIRONMENT_TYPE>(0)),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE),
	directionType(DIRECTION_SPRITE::NO),
	rotateType(ROTATE_TYPE::NONE)
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
}

CTile::~CTile()
{
}

HRESULT CTile::init()
{
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
	tileRenderSet();
}

void CTile::tileRenderSet()
{
	Vec2 imgFrame = { 0, 0 };
	switch (tileType)
	{
	case ENVIRONMENT_TYPE::NONE:
		img->frameRender(getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::PLAIN:
		img->frameRender(getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::WOOD:
		IMAGE->frameRender("wood", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::MOUNTAIN:
		img->frameRender(getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 1, 0);
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
		img->frameRender(getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), imgFrame.x, imgFrame.y);
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
		IMAGE->frameRender("city", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP) - 32, 0, playerColor);
		break;
	case BUILDING_TYPE::HEADQUATERS:
		break;
	case BUILDING_TYPE::FACTORY:
		IMAGE->frameRender("factory", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, playerColor);
		break;
	}
}

