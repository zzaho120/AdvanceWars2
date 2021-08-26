#include "framework.h"
#include "MapTool.h"

CMapTool::CMapTool() :
	map(new CMap({ 35, 35 }, { TILE_SIZE_X, TILE_SIZE_Y })),
	cam(new CCamera),
	cursor({ map->getTile()[158]->getPos().x, map->getTile()[158]->getPos().y })
{
	tileDirectionSet();
}

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
	if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_SPACE))
		setMap();

	map->update();
	cam->update();
	cam->setTargetVec2(cursor);

	cursorMove();
	tileDirectionSet();
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
					tile->setDirectionType(DIRECTION_SPRITE::YES);
					break;
				case 5:
					tile->setTileType(ENVIRONMENT_TYPE::ROAD);
					tile->setDirectionType(DIRECTION_SPRITE::YES);
					break;
				case 6:
					if (tile->getTileType() == ENVIRONMENT_TYPE::RIVER_LINE)
					{
						if (tile->getRotateType() == ROTATE_TYPE::DEG0)
							setEnvirType(idx, ENVIRONMENT_TYPE::BRIDGE, ROTATE_TYPE::DEG0);
						else if (tile->getRotateType() == ROTATE_TYPE::DEG90)
							setEnvirType(idx, ENVIRONMENT_TYPE::BRIDGE, ROTATE_TYPE::DEG90);
					}
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

			else if (SUBWIN->GetTileFrame().y == 3)
			{
				tile->setTileType(ENVIRONMENT_TYPE::NONE);
				if (tile->getBuildtype() != BUILDING_TYPE::NONE)
					map->eraseBuilding(idx);
				switch (SUBWIN->GetTileFrame().x)
				{
				case 0:
					tile->setPlayerType(PLAYER_TYPE::PLAYER1);
					tile->setBuildingType(BUILDING_TYPE::HEADQUATERS);
					map->addBuilding(PLAYER_TYPE::PLAYER1, tile->getPos(), true, false, idx);
					break;
				case 1:
					tile->setPlayerType(PLAYER_TYPE::PLAYER2);
					tile->setBuildingType(BUILDING_TYPE::HEADQUATERS);
					map->addBuilding(PLAYER_TYPE::PLAYER2, tile->getPos(), true, false, idx);
					break;
				}
			}
		}
	}
}

void CMapTool::tileDirectionSet()
{
	CTile** tile = map->getTile();
	for (int tileNum = 0; tileNum < TILE_NUM_X * TILE_NUM_Y; tileNum++)
	{
		bool isRiver = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_LINE) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_CURVE) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_3WAYS) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_4WAYS);

		if (isRiver)
		{
			riverSetting(tileNum);
			continue;
		}

		bool isRoad = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_LINE) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_CURVE) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_3WAYS) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_4WAYS);
		
		if (isRoad)
		{
			roadSetting(tileNum);
			continue;
		}

		bool isSea = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_CURVE) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_3WAYS) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_4WAYS) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL00) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL02) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL00) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL02) ||
			(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_NOWAYS);

		if (isSea)
		{
			seaSetting(tileNum);
			continue;
		}
	}
}

// 2진수의 4비트만을 가지고 강의 방향성을 체크
// 0 0 0 0 8자리
// B T R L 
void CMapTool::riverSetting(int tileNum)
{
	int riverType = 0b0000;
	int tileline = tileNum % 30;
	if (tileline > 0) riverType += checkRiver(tileNum - 1, DIRECTION::LEFT);
	if (tileline < 29) riverType += checkRiver(tileNum + 1, DIRECTION::RIGHT);
	if (tileNum > 29) riverType += checkRiver(tileNum - 30, DIRECTION::TOP);
	if (tileNum < 570) riverType += checkRiver(tileNum + 30, DIRECTION::BOTTOM);

	switch (riverType)
	{
	case 0b0000: // NO 4ways
	case 0b0001: // left
	case 0b0010: // right
	case 0b0011: // right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_LINE, ROTATE_TYPE::DEG90);
		break;
	case 0b0100: // top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_LINE, ROTATE_TYPE::DEG0);
		break;
	case 0b0101: // top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_CURVE, ROTATE_TYPE::DEG180);
		break;
	case 0b0110: // top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_CURVE, ROTATE_TYPE::DEG270);
		break;
	case 0b0111: // top, right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_3WAYS, ROTATE_TYPE::DEG270);
		break;
	case 0b1000: // bottom
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_LINE, ROTATE_TYPE::DEG0);
		break;
	case 0b1001: // bottom, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_CURVE, ROTATE_TYPE::DEG90);
		break;
	case 0b1010: // bottom, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_CURVE, ROTATE_TYPE::DEG0);
		break;
	case 0b1011: // bottom, left, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_3WAYS, ROTATE_TYPE::DEG90);
		break;
	case 0b1100: // bottom, top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_LINE, ROTATE_TYPE::DEG0);
		break;
	case 0b1101: // bottom, top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_3WAYS, ROTATE_TYPE::DEG180);
		break;
	case 0b1110: // bottom, top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_3WAYS, ROTATE_TYPE::DEG0);
		break;
	case 0b1111: // 4ways
		setEnvirType(tileNum, ENVIRONMENT_TYPE::RIVER_4WAYS, ROTATE_TYPE::DEG0);
		break;
	}
}

int CMapTool::checkRiver(int tileNum, DIRECTION direction)
{
	CTile** tile = map->getTile();
	bool isRiver = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_LINE) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_CURVE) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_3WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_4WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::BRIDGE);
	if (isRiver)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			return 0b0001;
			break;
		case DIRECTION::RIGHT:
			return 0b0010;
			break;
		case DIRECTION::TOP:
			return 0b0100;
			break;
		case DIRECTION::BOTTOM:
			return 0b1000;
			break;
		}
	}
}

void CMapTool::roadSetting(int tileNum)
{
	int roadType = 0b0000;
	int tileline = tileNum % 30;
	if (tileline > 0) roadType += checkRoad(tileNum - 1, DIRECTION::LEFT);
	if (tileline < 29) roadType += checkRoad(tileNum + 1, DIRECTION::RIGHT);
	if (tileNum > 29) roadType += checkRoad(tileNum - 30, DIRECTION::TOP);
	if (tileNum < 570) roadType += checkRoad(tileNum + 30, DIRECTION::BOTTOM);

	switch (roadType)
	{
	case 0b0000: // NO 4ways
	case 0b0001: // left
	case 0b0010: // right
	case 0b0011: // right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_LINE, ROTATE_TYPE::DEG90);
		break;
	case 0b0100: // top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_LINE, ROTATE_TYPE::DEG0);
		break;
	case 0b0101: // top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_CURVE, ROTATE_TYPE::DEG180);
		break;
	case 0b0110: // top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_CURVE, ROTATE_TYPE::DEG270);
		break;
	case 0b0111: // top, right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_3WAYS, ROTATE_TYPE::DEG270);
		break;
	case 0b1000: // bottom
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_LINE, ROTATE_TYPE::DEG180);
		break;
	case 0b1001: // bottom, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_CURVE, ROTATE_TYPE::DEG90);
		break;
	case 0b1010: // bottom, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_CURVE, ROTATE_TYPE::DEG0);
		break;
	case 0b1011: // bottom, left, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_3WAYS, ROTATE_TYPE::DEG90);
		break;
	case 0b1100: // bottom, top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_LINE, ROTATE_TYPE::DEG180);
		break;
	case 0b1101: // bottom, top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_3WAYS, ROTATE_TYPE::DEG180);
		break;
	case 0b1110: // bottom, top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_3WAYS, ROTATE_TYPE::DEG0);
		break;
	case 0b1111: // 4ways
		setEnvirType(tileNum, ENVIRONMENT_TYPE::ROAD_4WAYS, ROTATE_TYPE::DEG0);
		break;
	}
}

int CMapTool::checkRoad(int tileNum, DIRECTION direction)
{
	CTile** tile = map->getTile();
	bool isRoad = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_LINE) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_CURVE) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_3WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_4WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::BRIDGE);

	if (isRoad)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			return 0b0001;
			break;
		case DIRECTION::RIGHT:
			return 0b0010;
			break;
		case DIRECTION::TOP:
			return 0b0100;
			break;
		case DIRECTION::BOTTOM:
			return 0b1000;
			break;
		}
	}
}

void CMapTool::seaSetting(int tileNum)
{
	int seaType = 0b0000;
	int tileline = tileNum % 30;
	if (tileline > 0) seaType += checkSea(tileNum - 1, DIRECTION::LEFT);
	if (tileline < 29) seaType += checkSea(tileNum + 1, DIRECTION::RIGHT);
	if (tileNum > 29) seaType += checkSea(tileNum - 30, DIRECTION::TOP);
	if (tileNum < 570) seaType += checkSea(tileNum + 30, DIRECTION::BOTTOM);

	switch (seaType)
	{
	case 0b0000: // NO 4ways
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_NOWAYS, ROTATE_TYPE::DEG0);
		break;
	case 0b0001: // left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
		break;
	case 0b0010: // right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
		break;
	case 0b0011: // right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
		break;
	case 0b0100: // top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
		break;
	case 0b0101: // top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_CURVE, ROTATE_TYPE::DEG270);
		break;
	case 0b0110: // top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_CURVE, ROTATE_TYPE::DEG180);
		break;
	case 0b0111: // top, right, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG180);
		break;
	case 0b1000: // bottom
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
		break;
	case 0b1001: // bottom, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_CURVE, ROTATE_TYPE::DEG90);
		break;
	case 0b1010: // bottom, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_CURVE, ROTATE_TYPE::DEG0);
		break;
	case 0b1011: // bottom, left, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG0);
		break;
	case 0b1100: // bottom, top
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
		break;
	case 0b1101: // bottom, top, left
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG90);
		break;
	case 0b1110: // bottom, top, right
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG270);
		break;
	case 0b1111: // 4ways
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG0);
		break;
	}
}

int CMapTool::checkSea(int tileNum, DIRECTION direction)
{
	CTile** tile = map->getTile();
	bool isSea = (map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_CURVE) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_3WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_4WAYS) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL00) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL02) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL00) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL02) ||
		(map->getTile()[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_NOWAYS);

	if (isSea)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			return 0b0001;
			break;
		case DIRECTION::RIGHT:
			return 0b0010;
			break;
		case DIRECTION::TOP:
			return 0b0100;
			break;
		case DIRECTION::BOTTOM:
			return 0b1000;
			break;
		}
	}
}

void CMapTool::setEnvirType(int tileNum, ENVIRONMENT_TYPE environment, ROTATE_TYPE rotate)
{
	CTile** tile = map->getTile();
	tile[tileNum]->setTileType(environment);
	tile[tileNum]->setRotateType(rotate);
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
