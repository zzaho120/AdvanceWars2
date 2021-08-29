#include "framework.h"
#include "Camera.h"
#include "Building.h"
#include "Map.h"

CMap::CMap() : 
	isDebug(false), cam(nullptr)
{
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
			tile[horizontal * TILE_NUM_X + vertical] = new CTile;
	}
}

CMap::CMap(Vec2 startPos, Vec2 size) : 
	isDebug(false), cam(nullptr)
{
	Vec2 tempPos = startPos;
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
		{
			tile[horizontal * TILE_NUM_X + vertical] = new CTile(startPos , size);
			startPos += Vec2{ size.x, 0 };
		}
		startPos = { tempPos.x, startPos.y + size.y };
	}
}

CMap::CMap(const char* fileName)
{
	load(fileName);
}

CMap::~CMap()
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if(tile[idx] != nullptr)
			SAFE_DELETE(tile[idx]);
	}
	if(cam != nullptr)
		SAFE_DELETE(cam);
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
	this->getTileBuffer()->render(getMapDC(), 0, 0);

	TCHAR str[128];
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx]->render();
		if (isDebug)
		{
			Rectangle(getMapDC(),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::LEFT),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::TOP),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::RIGHT),
				RectEdge(tile[idx]->getPos(), tile[idx]->getSize(), RECT_EDGE::BOTTOM));


			wsprintf(str, "%d %d %d", idx, tile[idx]->getTileType(), tile[idx]->getBuildtype());
			TextOut(getMapDC(), tile[idx]->getPos().x - 20, tile[idx]->getPos().y, str, strlen(str));
		}
	}
}

void CMap::load(const char* fileName)
{
	HANDLE file;
	DWORD read;
	bool result;
	CTile load[TILE_NUM_X * TILE_NUM_Y];

	file = CreateFile(fileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	result = ReadFile(file, load, sizeof(load), &read, NULL);

	clearBuilding();
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		bool isFactory = false, isHQ = false;
		tile[idx] = new CTile(load[idx]);
		tile[idx]->init();

		if (tile[idx]->getBuildtype() != BUILDING_TYPE::NONE)
		{
			if (tile[idx]->getBuildtype() == BUILDING_TYPE::FACTORY)
				isFactory = true;
			else if (tile[idx]->getBuildtype() == BUILDING_TYPE::HEADQUATERS)
				isHQ = true;
			addBuilding(tile[idx]->getPlayerType(),
				tile[idx]->getPos(),
				isFactory,
				isHQ,
				idx);
		}
	}

	CloseHandle(file);
}


void CMap::addBuilding(PLAYER_TYPE type, Vec2 pos,bool factory, bool HQ, int idx)
{
	vecBuilding.push_back(new CBuilding(type, pos, factory, HQ, idx));
}

void CMap::eraseBuilding(int idx)
{
	for (int i = 0; i < vecBuilding.size(); i++)
	{
		if(vecBuilding[i]->getTileIdx() == idx)
			vecBuilding.erase(vecBuilding.begin() + i);
	}
}

void CMap::clearBuilding()
{
	vecBuilding.clear();
}
