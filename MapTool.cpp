#include "framework.h"
#include "MapTool.h"

CMapTool::CMapTool() :
	map(new CMap({ 35, 35 }, { TILE_SIZE_X, TILE_SIZE_Y })),
	cam(new CCamera),
	cursor({ map->getTile()[158]->getPos().x, map->getTile()[158]->getPos().y })
{ }

CMapTool::~CMapTool()
{
}

HRESULT CMapTool::init()
{
	ANIMATION->start("cursor_ani");
	map->setCameraLink(cam);
	return S_OK;
}

void CMapTool::release()
{

}

void CMapTool::update()
{
	map->update();
	cam->update();
	cam->setTargetVec2(cursor);

	cursorMove();

	if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_SPACE))
		setMap();
}

void CMapTool::render()
{
	map->render();
	IMAGE->findImage("cursor")->aniRender(getMapDC(), cursor.x - 32, cursor.y - 32, ANIMATION->findAnimation("cursor_ani"));
	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
}

void CMapTool::cursorMove()
{	
	if (InputManager->isOnceKeyDown(VK_LEFT)) cursor.x -= TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_RIGHT)) cursor.x += TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_UP)) cursor.y -= TILE_SIZE_Y;
	else if (InputManager->isOnceKeyDown(VK_DOWN)) cursor.y += TILE_SIZE_Y;
}

void CMapTool::setMap()
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		CTile* tile = map->getTile()[idx];
		if (map->getTile()[idx]->getPos() == cursor)
		{
			if (SUBWIN->GetTileFrame().y == 0)
			{
				if (tile->getBuildtype() != BUILDING_TYPE::NONE)
				{
					tile->setBuildingType(BUILDING_TYPE::NONE);
					map->eraseBuilding(idx);
				}
				switch (SUBWIN->GetTileFrame().x)
				{
				case 0:
					tile->setTileType(ENVIRONMENT_TYPE::PLAIN);
					break;
				case 1:
					tile->setTileType(ENVIRONMENT_TYPE::WOOD);
					break;
				case 2:
					tile->setTileType(ENVIRONMENT_TYPE::MOUNTAIN);
					break;
				case 3:
					tile->setTileType(ENVIRONMENT_TYPE::SEA);
					break;
				case 4:
					tile->setTileType(ENVIRONMENT_TYPE::RIVER);
					break;
				case 5:
					tile->setTileType(ENVIRONMENT_TYPE::ROAD);
					break;
				case 6:
					tile->setTileType(ENVIRONMENT_TYPE::BRIDGE);
					break;
				}
			}
			else if (SUBWIN->GetTileFrame().y == 1)
			{
				tile->setTileType(ENVIRONMENT_TYPE::NONE);
				switch (SUBWIN->GetTileFrame().x)
				{
				case 0:
					tile->setPlayerType(PLAYER_TYPE::PLAYER1);
					tile->setBuildingType(BUILDING_TYPE::CITY);
					map->addBuilding(PLAYER_TYPE::PLAYER1, tile->getPos(), false, false, idx);
					break;
				case 1:
					tile->setPlayerType(PLAYER_TYPE::PLAYER2);
					tile->setBuildingType(BUILDING_TYPE::CITY);
					map->addBuilding(PLAYER_TYPE::PLAYER2, tile->getPos(), false, false, idx);
					break;
				case 5:
					tile->setPlayerType(PLAYER_TYPE::NONE);
					tile->setBuildingType(BUILDING_TYPE::CITY);
					map->addBuilding(PLAYER_TYPE::NONE, tile->getPos(), false, false, idx);
					break;
				}
			}

			else if (SUBWIN->GetTileFrame().y == 2)
			{
				tile->setTileType(ENVIRONMENT_TYPE::NONE);
				if (tile->getBuildtype() != BUILDING_TYPE::NONE)
					map->eraseBuilding(idx);
				switch (SUBWIN->GetTileFrame().x)
				{
				case 0:
					tile->setPlayerType(PLAYER_TYPE::PLAYER1);
					tile->setBuildingType(BUILDING_TYPE::FACTORY);
					map->addBuilding(PLAYER_TYPE::PLAYER1, tile->getPos(), true, false, idx);
					break;
				case 1:
					tile->setPlayerType(PLAYER_TYPE::PLAYER2);
					tile->setBuildingType(BUILDING_TYPE::FACTORY);
					map->addBuilding(PLAYER_TYPE::PLAYER2, tile->getPos(), true, false, idx);
					break;
				case 5:
					tile->setPlayerType(PLAYER_TYPE::NONE);
					tile->setBuildingType(BUILDING_TYPE::FACTORY);
					map->addBuilding(PLAYER_TYPE::NONE, tile->getPos(), true, false, idx);
					break;
				}
			}
		}
	}
}

bool CMapTool::save(const char* fileName)
{
	HANDLE file;
	DWORD write;
	bool result;
	CMap* save[1];

	file = CreateFile(fileName,
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	save[0] = map;
	result = WriteFile(file, save, sizeof(map), &write, NULL);

	CloseHandle(file);

	return result;
}

bool CMapTool::load(const char* fileName)
{
	HANDLE file;
	DWORD read;
	bool result;
	CMap* load[1];

	file = CreateFile(fileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	result = ReadFile(file, load, sizeof(map), &read, NULL);
	map = load[0];

	CloseHandle(file);

	return result;
}
