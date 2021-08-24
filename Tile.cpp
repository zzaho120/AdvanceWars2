#include "framework.h"
#include "Tile.h"

CTile::CTile() :
	tileType(ENVIRONMENT_TYPE::NONE)
{
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
}
