#include "framework.h"
#include "Environment.h"
#include "Building.h"
#include "Map.h"

CMap::CMap() : isDebug(false)
{
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
			tile[horizontal * TILE_NUM_X + vertical] = new CTile;
	}
}

CMap::CMap(Vec2 startPos, Vec2 size) : isDebug(false)
{
	Vec2 tempPos = startPos;
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
		{
			tile[horizontal * TILE_NUM_X + vertical] = new CTile(startPos , size, IMAGE->findImage("single_environment"));
			startPos += Vec2{ size.x, 0 };
		}
		startPos = { tempPos.x, startPos.y + size.y };
	}
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
	if (InputManager->isOnceKeyDown(VK_F1)) isDebug = !isDebug;
}

void CMap::render()
{
	TCHAR str[128];
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx]->render();
		if (isDebug)
		{
			Rectangle(getMemDC(),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::LEFT),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::TOP),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::RIGHT),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::BOTTOM));


			wsprintf(str, "%d", idx);
			TextOut(getMemDC(), tile[idx]->getPos().x, tile[idx]->getPos().y, str, strlen(str));
		}
	}
		
	for (iterBuilding = vecBuilding.begin(); iterBuilding != vecBuilding.end(); iterBuilding++)
		(*iterBuilding)->render();

	for (iterEnvironment = vecEnvironment.begin(); iterEnvironment != vecEnvironment.end(); iterEnvironment++)
		(*iterEnvironment)->render();
}
