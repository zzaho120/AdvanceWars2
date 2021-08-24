#include "framework.h"
#include "Tile.h"

CTile::CTile() :
	CObject(),
	tileType(ENVIRONMENT_TYPE::NONE),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE)
{
}

CTile::CTile(Vec2 _pos, Vec2 _size, image* _img, animation* _ani) :
	CObject(_pos, _size, _img, _ani),
	tileType(ENVIRONMENT_TYPE::PLAIN),
	buildingType(BUILDING_TYPE::NONE),
	unitType(UNIT_TYPE::NONE)
{ }

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
	img->frameRender(getMemDC(), RectEdge(pos, size, RECT_EDGE::LEFT), RectEdge(pos, size, RECT_EDGE::TOP), 0, 0);
}
