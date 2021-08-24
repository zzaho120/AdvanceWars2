#include "framework.h"
#include "Building.h"
#include "Map.h"

CMap::CMap()
{
}

CMap::~CMap()
{
}

HRESULT CMap::init()
{
	return S_OK;
}

void CMap::release()
{
}

void CMap::update()
{
}

void CMap::render()
{
	for (iterBuilding = vecBuilding.begin(); iterBuilding != vecBuilding.end(); iterBuilding++)
		(*iterBuilding)->render();
}
