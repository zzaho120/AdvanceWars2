#include "framework.h"
#include "MapTool.h"
#include "Building.h"

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

	if (InputManager->isOnceKeyDown('J'))
		setAllTile(ENVIRONMENT_TYPE::SEA);

	map->update();
	cam->setTargetVec2(cursor);
	cam->update();

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
					tile->setPlayerType(PLAYER_TYPE::NONE);
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
					bool isSea = 
						tile->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01 ||
						tile->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01;
					bool isRiver =
						tile->getTileType() == ENVIRONMENT_TYPE::RIVER_LINE;

					if (isSea)
					{
						if (tile->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01)
							setEnvirType(idx, ENVIRONMENT_TYPE::BRIDGE, ROTATE_TYPE::DEG0);
						else if (tile->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01)
							setEnvirType(idx, ENVIRONMENT_TYPE::BRIDGE, ROTATE_TYPE::DEG90);
					}
					else if (isSea)
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
					setBuilding(idx, BUILDING_TYPE::CITY, PLAYER_TYPE::PLAYER1);
					break;
				case 1:
					setBuilding(idx, BUILDING_TYPE::CITY, PLAYER_TYPE::PLAYER2);
					break;
				case 5:
					setBuilding(idx, BUILDING_TYPE::CITY, PLAYER_TYPE::NONE);
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
					setBuilding(idx, BUILDING_TYPE::FACTORY, PLAYER_TYPE::PLAYER1);
					break;
				case 1:
					setBuilding(idx, BUILDING_TYPE::FACTORY, PLAYER_TYPE::PLAYER2);
					break;
				case 5:
					setBuilding(idx, BUILDING_TYPE::FACTORY, PLAYER_TYPE::NONE);
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
					setHQ(idx, PLAYER_TYPE::PLAYER1);
					break;
				case 1:
					setHQ(idx, PLAYER_TYPE::PLAYER2);
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
		bool isRiver = (tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_LINE) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_CURVE) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_3WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::RIVER_4WAYS);

		if (isRiver)
		{
			riverSetting(tileNum);
			continue;
		}

		bool isRoad = (tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_LINE) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_CURVE) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_3WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::ROAD_4WAYS);
		
		if (isRoad)
		{
			roadSetting(tileNum);
			continue;
		}

		bool isSea = 
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_2WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_3WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_4WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_5WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_6WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_7WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_8WAYS) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL00) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL02) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL00) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL02) ||
			(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_NOWAYS);

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
	case 0b01110110: // topright, bottomleft, topleft, top, right
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

// 2진수의 8비트만을 가지고 바다의 방향성을 체크
// 0  0  0  0  0 0 0 0 8자리
// BR BL TR TL B T R L 
void CMapTool::seaSetting(int tileNum)
{
	int seaType = 0b00000000;
	int tileline = tileNum % 30;
	if (tileline > 0)
	{
		if (tileNum > 29)
			seaType += checkSea(tileNum - 31, DIRECTION::TOP_LEFT);
		if (tileNum < 570)
			seaType += checkSea(tileNum + 29, DIRECTION::BOTTOM_LEFT);
			seaType += checkSea(tileNum - 1, DIRECTION::LEFT);
	}
	if (tileline < 29)
	{
		if (tileNum > 29)
			seaType += checkSea(tileNum - 29, DIRECTION::TOP_RIGHT);
		if (tileNum < 570)
			seaType += checkSea(tileNum + 31, DIRECTION::BOTTOM_RIGHT);
		seaType += checkSea(tileNum + 1, DIRECTION::RIGHT);
	}
	if (tileNum > 29) seaType += checkSea(tileNum - 30, DIRECTION::TOP);
	if (tileNum < 570) seaType += checkSea(tileNum + 30, DIRECTION::BOTTOM);

	seaTileSet(tileNum, seaType);
}

int CMapTool::checkSea(int tileNum, DIRECTION direction)
{
	CTile** tile = map->getTile();
	bool isSea = (tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::BRIDGE) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_2WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_3WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_4WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_5WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_6WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_7WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_8WAYS) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL00) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL01) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_VERTICAL02) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL00) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL01) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_HORIZONTAL02) ||
		(tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA_NOWAYS);
	
	if (isSea)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			return 0b00000001;
			break;
		case DIRECTION::RIGHT:
			return 0b00000010;
			break;
		case DIRECTION::TOP:
			return 0b00000100;
			break;
		case DIRECTION::BOTTOM:
			return 0b00001000;
			break;
		case DIRECTION::TOP_LEFT:
			return 0b00010000;
			break;
		case DIRECTION::TOP_RIGHT:
			return 0b00100000;
			break;
		case DIRECTION::BOTTOM_LEFT:
			return 0b01000000;
			break;
		case DIRECTION::BOTTOM_RIGHT:
			return 0b10000000;
			break;
		}
	}
}

void CMapTool::seaTileSet(int tileNum, int seaType)
{
	switch (seaType)
	{
	case 0b00000000: // noway
	case 0b00010000: // TL
	case 0b00100000: // TR
	case 0b00110000: // TR, TL
	case 0b01000000: // BL
	case 0b01010000: // BL, TL
	case 0b01100000: // BL, TR
	case 0b01110000: // BL, TR, TL

	case 0b10000000: // BR
	case 0b10010000: // BR, TL
	case 0b10100000: // BR, TR
	case 0b10110000: // BR, TR, TL
	case 0b11000000: // BR, BL
	case 0b11010000: // BR, BL, TL
	case 0b11100000: // BR, BL, TR
	case 0b11110000: // BR, BL, TR, TL
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_NOWAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b00000001: // L
	case 0b00010001: // TL, L
	case 0b00100001: // TR, L
	case 0b00110001: // TR, TL, L
	case 0b01000001: // BL, L
	case 0b01010001: // BL, TL, L
	case 0b01100001: // BL, TR, L
	case 0b01110001: // BL, TR, TL, L

	case 0b10000001: // BR, L
	case 0b10010001: // BR, TL, L
	case 0b10100001: // BR, TR, L
	case 0b10110001: // BR, TR, TL, L
	case 0b11000001: // BR, BL, L
	case 0b11010001: // BR, BL, TL, L
	case 0b11100001: // BR, BL, TR, L
	case 0b11110001: // BR, BL, TR, TL, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
		break;

	case 0b00000010: // R
	case 0b00010010: // TL, R
	case 0b00100010: // TR, R
	case 0b00110010: // TR, TL, R
	case 0b01000010: // BL, R
	case 0b01010010: // BL, TL, R
	case 0b01100010: // BL, TR, R
	case 0b01110010: // BL, TR, TL, R

	case 0b10000010: // BR, R
	case 0b10010010: // BR, TL, R
	case 0b10100010: // BR, TR, R
	case 0b10110010: // BR, TR, TL, R
	case 0b11000010: // BR, BL, R
	case 0b11010010: // BR, BL, TL, R
	case 0b11100010: // BR, BL, TR, R
	case 0b11110010: // BR, BL, TR, TL, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
		break;

	case 0b00000011: // R, L
	case 0b00010011: // TL, R, L
	case 0b00100011: // TR, R, L
	case 0b00110011: // TR, TL, R, L
	case 0b01000011: // BL, R, L
	case 0b01010011: // BL, TL, R, L
	case 0b01100011: // BL, TR, R, L
	case 0b01110011: // BL, TR, TL, R, L

	case 0b10000011: // BR, R, L
	case 0b10010011: // BR, TL, R, L
	case 0b10100011: // BR, TR, R, L
	case 0b10110011: // BR, TR, TL, R, L
	case 0b11000011: // BR, BL, R, L
	case 0b11010011: // BR, BL, TL, R, L
	case 0b11100011: // BR, BL, TR, R, L
	case 0b11110011: // BR, BL, TR, TL, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
		break;

	case 0b00000100: // T
	case 0b00010100: // TL, T
	case 0b00100100: // TR, T
	case 0b00110100: // TR, TL, T
	case 0b01000100: // BL, T
	case 0b01010100: // BL, TL, T
	case 0b01100100: // BL, TR, T
	case 0b01110100: // BL, TR, TL, T

	case 0b10000100: // BR, T
	case 0b10010100: // BR, TL, T
	case 0b10100100: // BR, TR, T
	case 0b10110100: // BR, TR, TL, T
	case 0b11000100: // BR, BL, T
	case 0b11010100: // BR, BL, TL, T
	case 0b11100100: // BR, BL, TR, T
	case 0b11110100: // BR, BL, TR, TL, T
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
		break;

	case 0b00001000: // B
	case 0b00011000: // TL, B
	case 0b00101000: // TR, B
	case 0b00111000: // TR, TL, B
	case 0b01001000: // BL, B
	case 0b01011000: // BL, TL, B
	case 0b01101000: // BL, TR, B
	case 0b01111000: // BL, TR, TL, B

	case 0b10001000: // BR, B
	case 0b10011000: // BR, TL, B
	case 0b10101000: // BR, TR, B
	case 0b10111000: // BR, TR, TL, B
	case 0b11001000: // BR, BL, B
	case 0b11011000: // BR, BL, TL, B
	case 0b11101000: // BR, BL, TR, B
	case 0b11111000: // BR, BL, TR, TL, B
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
		break;

	case 0b00001100: // B, T
	case 0b00011100: // TL, B, T
	case 0b00101100: // TR, B, T
	case 0b00111100: // TR, TL, B, T
	case 0b01001100: // BL, B, T
	case 0b01011100: // BL, TL, B, T
	case 0b01101100: // BL, TR, B, T
	case 0b01111100: // BL, TR, TL, B, T

	case 0b10001100: // BR, B, T
	case 0b10011100: // BR, TL, B, T
	case 0b10101100: // BR, TR, B, T
	case 0b10111100: // BR, TR, TL, B, T
	case 0b11001100: // BR, BL, B, T
	case 0b11011100: // BR, BL, TL, B, T
	case 0b11101100: // BR, BL, TR, B, T
	case 0b11111100: // BR, BL, TR, TL, B, T
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
		break;

	case 0b00001001: // B, L
	case 0b00011001: // TL, B, L
	case 0b00101001: // TR, B, L
	case 0b00111001: // TR, TL, B, L
	case 0b10001001: // BR, B, L
	case 0b10011001: // BR, TL, B, L
	case 0b10101001: // BR, TR, B, L
	case 0b10111001: // BR, TR, TL, B, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b00001010: // B, R
	case 0b00011010: // TL, B, R
	case 0b00101010: // TR, B, R
	case 0b00111010: // TR, TL, B, R
	case 0b01001010: // BR, B, R
	case 0b01011010: // BR, TL, B, R
	case 0b01101010: // BR, TR, B, R
	case 0b01111010: // BR, TR, TL, B, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b00000101: // T, L
	case 0b00100101: // TR, T, L
	case 0b01000101: // BL, T, L
	case 0b01100101: // BL, TR, T, L
	case 0b10000101: // BR, T, L
	case 0b10100101: // BR, TR, T, L
	case 0b11000101: // BR, BL, T, L
	case 0b11100101: // BR, BL, TR, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b00000110: // T, R
	case 0b00010110: // TL, T, R
	case 0b01000110: // BL, T, R
	case 0b01010110: // BL, TL, T, R
	case 0b10000110: // BR, T, R
	case 0b10010110: // BR, TL, T, R
	case 0b11000110: // BR, BL, T, R
	case 0b11010110: // BR, BL, TL, T, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG270);
		break;

	case 0b10001010: // BR, B, R
	case 0b10011010: // BR, TL, B, R
	case 0b10101010: // BR, TR, B, R
	case 0b10111010: // BR, TR, TL, B, R
	case 0b11001010: // BR, BL, B, R
	case 0b11011010: // BR, BL, TL, B, R
	case 0b11101010: // BR, BL, TR, B, R
	case 0b11111010: // BR, BL, TR, TL, B, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b00001011: // B, R, L
	case 0b00011011: // TL, B, R, L
	case 0b00101011: // TR, B, R, L
	case 0b00111011: // TR, TL, B, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG45);
		break;

	case 0b01001001: // BL, B, L
	case 0b01011001: // BL, TL, B, L
	case 0b01101001: // BL, TR, B, L
	case 0b01111001: // BR, TR, TL, B, L
	case 0b11001001: // BR, BL, B, L
	case 0b11011001: // BR, BL, TL, B, L
	case 0b11101001: // BR, BL, TR, B, L
	case 0b11111001: // BR, BL, TR, TL, B, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b00001101: // B, T, L
	case 0b00101101: // TR, B, T, L
	case 0b10001101: // BR, B, T, L
	case 0b10101101: // BR, TR, B, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG135);
		break;

	case 0b00010101: // TL, T, L
	case 0b00110101: // TR, TL, T, L
	case 0b01010101: // BL, TL, T, L
	case 0b01110101: // BL, TR, TL, T, L
	case 0b10010101: // BR, TL, T, L
	case 0b10110101: // BR, TR, TL, T, L
	case 0b11010101: // BR, BL, TL, T, L
	case 0b11110101: // BR, BL, TR, TL, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b00000111: // T, R, L
	case 0b01000111: // BL, T, R, L
	case 0b10000111: // BR, T, R, L
	case 0b11000111: // BR, BL, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG225);
		break;

	case 0b00100110: // TR, T, R
	case 0b00110110: // TR, TL, T, R
	case 0b01100110: // BL, TR, T, R
	case 0b01110110: // BL, TR, TL, T, R
	case 0b10100110: // BR, TR, T, R
	case 0b10110110: // BR, TR, TL, T, R
	case 0b11100110: // BR, BL, TR, T, R
	case 0b11110110: // BR, BL, TR, TL, T, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG270);
		break;

	case 0b00001110: // B, T, L
	case 0b00011110: // TL, B, T, L
	case 0b01001110: // BL, B, T, L
	case 0b01011110: // BL, TL, B, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG315);
		break;

	case 0b01001011: // BL, B, R, L
	case 0b01011011: // BL, TL, B, R, L
	case 0b01101011: // BL, TR, B, R, L
	case 0b01111011: // BL, TR, TL, B, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b10001011: // BR, B, R, L
	case 0b10011011: // BR, TL, B, R, L
	case 0b10101011: // BR, TR, B, R, L
	case 0b10111011: // BR, TR, TL, B, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG45);
		break;

	case 0b00101110: // TR, B, T, R
	case 0b00111110: // TR, TL, B, T, R
	case 0b01101110: // BL, TR, B, T, R
	case 0b01111110: // BL, TR, TL, B, T, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b10001110: // BR, B, T, R
	case 0b10011110: // BR, TL, B, T, R
	case 0b11001110: // BR, BL, B, T, R
	case 0b11011110: // BR, BL, TL, B, T, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG135);
		break;

	case 0b00011101: // TL, B, T, L
	case 0b00111101: // TR, TL, B, T, L
	case 0b10011101: // BR, TL, B, T, L
	case 0b10111101: // BR, TR, TL, B, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b01001101: // BL, B, T, L
	case 0b01101101: // BL, TR, B, T, L
	case 0b11001101: // BR, BL, B, T, L
	case 0b11101101: // BR, BL, TR, B, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG225);
		break;

	case 0b00010111: // TL, T, R, L
	case 0b01010111: // BL, TL, T, R, L
	case 0b10010111: // BR, TL, T, R, L
	case 0b11010111: // BR, BL, TL, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG270);
		break;

	case 0b00100111: // TR, T, R, L
	case 0b01100111: // BL, TR, T, R, L
	case 0b10100111: // BR, TR, T, R, L
	case 0b11100111: // BR, BL, TR, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG315);
		break;

	case 0b00001111: // B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG360);
		break;

	case 0b11001011: // BR, BL, B, R, L
	case 0b11011011: // BR, BL, TL, B, R, L
	case 0b11101011: // BR, BL, TR, B, R, L
	case 0b11111011: // BR, BL, TR, TL, B, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b00011111: // TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG45);
		break;

	case 0b10101110: // BR, TR, B, T, R
	case 0b10111110: // BR, TR, TL, B, T, R
	case 0b11101110: // BR, BL, TR, B, T, R
	case 0b11111110: // BR, BL, TR, TL, B, T, R
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b00101111: // TR, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG135);
		break;

	case 0b01011101: // BL, TL, B, T, L
	case 0b01111101: // BL, TR, TL, B, T, L
	case 0b11011101: // BR, BL, TL, B, T, L
	case 0b11111101: // BR, BL, TR, TL, B, T, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b01001111: // BL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG225);
		break;

	case 0b00110111: // TR, TL, T, R, L
	case 0b01110111: // BL, TR, TL, T, R, L
	case 0b10110111: // BR, TR, TL, T, R, L
	case 0b11110111: // BR, BL, TR, TL, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG270);
		break;

	case 0b10001111: // BR, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG315);
		break;

	case 0b11001111: // BR, BL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b01011111: // BL, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG45);
		break;

	case 0b10101111: // BR, TR, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b00111111: // TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG135);
		break;

	case 0b01101111: // BL, TR, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b10011111: // BL, TR, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG225);
		break;

	case 0b01111111: // BL, TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_7WAYS, ROTATE_TYPE::DEG0);
		break;

	case 0b10111111: // BL, TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_7WAYS, ROTATE_TYPE::DEG90);
		break;

	case 0b11011111: // BL, TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_7WAYS, ROTATE_TYPE::DEG180);
		break;

	case 0b11101111: // BL, TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_7WAYS, ROTATE_TYPE::DEG270);
		break;

	case 0b11111111: // BR, BL, TR, TL, B, T, R, L
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_8WAYS, ROTATE_TYPE::DEG0);
		break;
	}
}

void CMapTool::setEnvirType(int tileNum, ENVIRONMENT_TYPE environment, ROTATE_TYPE rotate)
{
	CTile** tile = map->getTile();
	tile[tileNum]->setTileType(environment);
	tile[tileNum]->setRotateType(rotate);
}

void CMapTool::setBuilding(int tileNum, BUILDING_TYPE building, PLAYER_TYPE player)
{
	map->getTile()[tileNum]->setPlayerType(player);
	map->getTile()[tileNum]->setBuildingType(building);
	if(building == BUILDING_TYPE::FACTORY)
		map->addBuilding(player, map->getTile()[tileNum]->getPos(), true, false, tileNum);
	else if(building == BUILDING_TYPE::CITY)
		map->addBuilding(player, map->getTile()[tileNum]->getPos(), false, false, tileNum);
}

void CMapTool::setHQ(int tileNum, PLAYER_TYPE player)
{
	for (int vecIdx = 0; vecIdx < map->getVecBuilding().size(); vecIdx++)
	{
		if (map->getVecBuilding()[vecIdx]->getIsHQ() &&
			map->getVecBuilding()[vecIdx]->getPlayerType() == player)
		{
			int tileIdx = map->getVecBuilding()[vecIdx]->getTileIdx();
			map->getTile()[tileIdx]->setTileType(ENVIRONMENT_TYPE::PLAIN);
			map->getTile()[tileIdx]->setBuildingType(BUILDING_TYPE::NONE);
			map->getTile()[tileIdx]->setPlayerType(PLAYER_TYPE::NONE);
			map->eraseBuilding(tileIdx);
		}
	}
	map->getTile()[tileNum]->setPlayerType(player);
	map->getTile()[tileNum]->setBuildingType(BUILDING_TYPE::HEADQUATERS);
	map->addBuilding(player, map->getTile()[tileNum]->getPos(), false, true, tileNum);
}

bool CMapTool::save(const char* fileName)
{
	HANDLE file;
	DWORD write;
	bool result;
	CTile save[TILE_NUM_X * TILE_NUM_Y];

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
		save[idx] = map->getTile()[idx];

	file = CreateFile(fileName,
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	result = WriteFile(file, save, sizeof(save), &write, NULL);

	CloseHandle(file);

	return result;
}

bool CMapTool::load(const char* fileName)
{
	HANDLE file;
	DWORD read;
	bool result;
	CTile load[TILE_NUM_X * TILE_NUM_Y];

	file = CreateFile(fileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	result = ReadFile(file, load, sizeof(load), &read, NULL);

	map->clearBuilding();
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		bool isFactory = false, isHQ = false;
		map->getTile()[idx] = new CTile(load[idx]);

		if (map->getTile()[idx]->getBuildtype() != BUILDING_TYPE::NONE)
		{
			if (map->getTile()[idx]->getBuildtype() == BUILDING_TYPE::FACTORY)
				isFactory = true;
			else if (map->getTile()[idx]->getBuildtype() == BUILDING_TYPE::HEADQUATERS)
				isHQ = true;
			map->addBuilding(map->getTile()[idx]->getPlayerType(),
				map->getTile()[idx]->getPos(),
				isFactory,
				isHQ,
				idx);
		}			
	}

	CloseHandle(file);

	return result;
}

void CMapTool::setAllTile(ENVIRONMENT_TYPE type)
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
		map->getTile()[idx]->setTileType(type);
}