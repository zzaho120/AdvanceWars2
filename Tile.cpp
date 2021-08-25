#include "framework.h"
#include "Tile.h"

CTile::CTile() :
	CObject(),
	tileType(ENVIRONMENT_TYPE::NONE),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE)
{ }

CTile::CTile(Vec2 _pos, Vec2 _size, image* _img, animation* _ani) :
	CObject(_pos, _size, _img, _ani),
	tileType(static_cast<ENVIRONMENT_TYPE>(RND->getFromIntTo(1 , 7))),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE),
	playerType(PLAYER_TYPE::NONE)
{
	ANIMATION->start("river_vertical");
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
	case ENVIRONMENT_TYPE::RIVER:
		ani = ANIMATION->findAnimation("river_vertical");
		IMAGE->findImage("river")->aniRender(getMapDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), ani);
		break;
	case ENVIRONMENT_TYPE::BRIDGE:
		img->frameRender(getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 2, 0);
		break;
	case ENVIRONMENT_TYPE::ROAD:
		IMAGE->frameRender("road", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	case ENVIRONMENT_TYPE::SEA:
		IMAGE->frameRender("sea", getTileDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
		break;
	default:
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
	default:
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
	default:
		break;
	}
}
