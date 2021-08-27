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

		bool isSea = (tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
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

	switch (seaType)
	{
	case 0b00000000: 
	case 0b00010000: 
	case 0b00100000: 
	case 0b00110000: 
	case 0b01000000: 
	case 0b01010000: 
	case 0b01100000: 
	case 0b01110000: 
	case 0b10000000: 
	case 0b10010000: 
	case 0b10100000: 
	case 0b10110000: 
	case 0b11000000: 
	case 0b11010000: 
	case 0b11110000: 
		setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_NOWAYS, ROTATE_TYPE::DEG0);
		break;
	}
	//switch (seaType)
	//{
	//case 0b00000001: // left
	//case 0b01100001: // topright, bottomleft, left
	//case 0b01110001: // topright, bottomleft, topleft, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00000010: // right
	//case 0b01100010: // topright, bottomleft, right
	//case 0b01110010: // topright, bottomleft, topleft, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00000011: // right, left
	//case 0b01100011: // topright, bottomleft, right, left
	//case 0b01110011: // topright, bottomleft, topleft, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00000100: // top
	//case 0b01100100: // topright, bottomleft, top
	//case 0b01110100: // topright, bottomleft, topleft, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00000101: // top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b00000110: // top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00000111: // top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG225);
	//	break;
	//case 0b00001000: // bottom
	//case 0b01101000: // topright, bottomleft, bottom
	//case 0b01111000: // topright, bottomleft, topleft, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00001001: // bottom, left
	//case 0b01011001: // topright, topleft, bottom, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00001010: // bottom, right
	//case 0b01011010: // topright, topleft, bottom, right
	//case 0b01101010: // topright, bottomleft, bottom, right
	//case 0b01111010: // topright, bottomleft, topleft, bottom, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00001011: // bottom, right, left
	//case 0b01011011: // topright, topleft, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG45);
	//	break;
	//case 0b00001100: // bottom, top
	//case 0b01011100: // topright, topleft, bottom, top
	//case 0b01101100: // topright, bottomleft, bottom, top
	//case 0b01111100: // topright, bottomleft, topleft, bottom, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00001101: // bottom, top, left
	//case 0b01100101: // topright, bottomleft, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG135);
	//	break;
	//case 0b00001110: // bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b00001111: // bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG360);
	//	break;
	//
	//case 0b00010001: // topleft, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00010010: // topleft, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00010011: // topleft, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00010100: // topleft, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00010101: // topleft, top, left
	//case 0b01110101: // topright, bottomleft, topleft, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b00010110: // topleft, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00010111: // topleft, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00011000: // topleft, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00011001: // topleft, bottom, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00011010: // topleft, bottom, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00011011: // topleft, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG45);
	//	break;
	//case 0b00011100: // topleft, bottom, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00011101: // topleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00011110: // topleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00011111: // topleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00100001: // bottomleft, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00100010: // bottomleft, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00100011: // bottomleft, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00100100: // bottomleft, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00100101: // bottomleft, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00101000: // bottomleft, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00101001: // bottomleft, bottom, left
	//case 0b01101001: // topright, bottomleft, bottom, left
	//case 0b01111001: // topright, bottomleft, topleft, bottom, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00101010: // bottomleft, bottom, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b00101011: // bottomleft, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00101100: // bottomleft, bottom, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00101101: // bottomleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG225);
	//	break;
	//case 0b00101110: // bottomleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b00101111: // bottomleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b00110001: // bottomleft, topleft, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00110010: // bottomleft, topleft, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00110011: // bottomleft, topleft, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00110100: // bottomleft, topleft, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00110101: // bottomleft, topleft, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b00110110: // bottomleft, topleft, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b00110111: // bottomleft, topleft, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b00111000: // bottomleft, topleft, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00111001: // bottomleft, topleft, bottom, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG135);
	//	break;
	//case 0b00111010: // bottomleft, topleft, bottom, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00111011: // bottomleft, topleft, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00111100: // bottomleft, topleft, bottom, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b00111101: // bottomleft, topleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b00111110: // bottomleft, topleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b00111111: // bottomleft, topleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG45);
	//	break;
	//case 0b01000001: // topright, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01000010: // topright, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01000011: // topright, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01000100: // topright, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01000101: // topright, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b01000110: // topright, top, right
	//case 0b01100110: // topright, bottomleft, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b01000111: // topright, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b01001000: // topright, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01001001: // topright, bottom, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01001010: // topright, bottom, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_2WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b01001011: // topright, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG45);
	//	break;
	//case 0b01001100: // topright, bottom, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01001101: // topright, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG135);
	//	break;
	//case 0b01001110: // topright, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b01001111: // topright, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01010001: // topright, topleft, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01010010: // topright, topleft, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL00, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01010011: // topright, topleft, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_HORIZONTAL01, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01010100: // topright, topleft, top
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_VERTICAL02, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01010101: // topright, topleft, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b01010110: // topright, topleft, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_3WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b01010111: // topright, topleft, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b01011000: // topright, topleft, bottom
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_NOWAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01011101: // topright, topleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b01011110: // topright, topleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b01011111: // topright, topleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG135);
	//	break;
	//case 0b01100111: // topright, bottomleft, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG315);
	//	break;
	//case 0b01101011: // topright, bottomleft, bottom, right, left
	//case 0b01111011: // topright, bottomleft, topleft, bottom, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//case 0b01101101: // topright, bottomleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG225);
	//	break;
	//case 0b01101110: // topright, bottomleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG135);
	//	break;
	//case 0b01101111: // topright, bottomleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_6WAYS, ROTATE_TYPE::DEG225);
	//	break;
	//case 0b01110111: // topright, bottomleft, topleft, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG270);
	//	break;
	//case 0b01111101: // topright, bottomleft, topleft, bottom, top, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_5WAYS, ROTATE_TYPE::DEG180);
	//	break;
	//case 0b01111110: // topright, bottomleft, topleft, bottom, top, right
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_4WAYS, ROTATE_TYPE::DEG90);
	//	break;
	//case 0b01111111: // topright, bottomleft, topleft, bottom, top, right, left
	//	setEnvirType(tileNum, ENVIRONMENT_TYPE::SEA_7WAYS, ROTATE_TYPE::DEG0);
	//	break;
	//}
}

int CMapTool::checkSea(int tileNum, DIRECTION direction)
{
	CTile** tile = map->getTile();
	bool isSea = (tile[tileNum]->getTileType() == ENVIRONMENT_TYPE::SEA) ||
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
