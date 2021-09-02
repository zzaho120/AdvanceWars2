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

CMap::CMap(const char* fileName, CCamera* camera) :
	cam(camera), gameMgr(nullptr)
{
	load(fileName);
}

CMap::CMap(const char* fileName) :
	gameMgr(nullptr), cam(nullptr)
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

HRESULT CMap::init(CGameManager* mgr)
{
	gameMgr = mgr;
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


			wsprintf(str, "%d %d %d", idx, tile[idx]->getTileType(), tile[idx]->getUnitType());
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

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx] = new CTile(load[idx]);
		tile[idx]->init();
	}

	CloseHandle(file);
}
