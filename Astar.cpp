#include "framework.h"
#include "Tile.h"
#include "Astar.h"

CAstar::CAstar()
{
}

CAstar::CAstar(CTile** _tile, Vec2 start, Vec2 end)
{
	Vec2 tempPos = { TILE_SIZE_X / 2, TILE_SIZE_Y / 2 };
	astarState = ASTAR_STATE::END;
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
		{
			tile[horizontal * TILE_NUM_X + vertical].idx = horizontal * TILE_NUM_X + vertical;
			tile[horizontal * TILE_NUM_X + vertical].pos = tempPos;
			tile[horizontal * TILE_NUM_X + vertical].tileType = ASTAR_TYPE::EMPTY;
			tile[horizontal * TILE_NUM_X + vertical].isListOn = false;
			tile[horizontal * TILE_NUM_X + vertical].isWalkable = false;
			tile[horizontal * TILE_NUM_X + vertical].isOnlyInfry = false;
			tile[horizontal * TILE_NUM_X + vertical].parent = nullptr;
			tile[horizontal * TILE_NUM_X + vertical].valueF = ASTAR_MAX_NUM;
			tile[horizontal * TILE_NUM_X + vertical].valueH = 0;
			tile[horizontal * TILE_NUM_X + vertical].EnvirType = _tile[horizontal * TILE_NUM_X + vertical]->getTileType();
			tile[horizontal * TILE_NUM_X + vertical].unitType = _tile[horizontal * TILE_NUM_X + vertical]->getUnitType();
			tempPos += Vec2{ TILE_SIZE_X, 0 };
		}
		tempPos += Vec2{ 0, TILE_SIZE_Y };
	}

	startPos = start;
	endPos = end;

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (tile[idx].pos == startPos)
		{
			tile[idx].tileType = ASTAR_TYPE::START;
			break;
		}
	}
	
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (tile[idx].pos == endPos)
		{
			tile[idx].tileType = ASTAR_TYPE::END;
			break;
		}
	}

	Cg = Cidx = 0;

	tileInit();
}

CAstar::~CAstar()
{
}

HRESULT CAstar::init()
{
	return E_NOTIMPL;
}

void CAstar::release()
{
}

void CAstar::update()
{
	while (astarState != ASTAR_STATE::FOUND)
	{
		addOpenList();
		caculateH();
		caculateF();
		addCloseList();
		checkArrive();
	}
}

void CAstar::render()
{
}

void CAstar::tileInit()
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		switch (tile[idx].EnvirType)
		{
		case ENVIRONMENT_TYPE::NONE:
		case ENVIRONMENT_TYPE::PLAIN:
		case ENVIRONMENT_TYPE::WOOD:
		case ENVIRONMENT_TYPE::ROAD:
		case ENVIRONMENT_TYPE::ROAD_LINE:
		case ENVIRONMENT_TYPE::ROAD_CURVE:
		case ENVIRONMENT_TYPE::ROAD_3WAYS:
		case ENVIRONMENT_TYPE::ROAD_4WAYS:
		case ENVIRONMENT_TYPE::BRIDGE:
			tile[idx].isWalkable = true;
			tile[idx].isListOn = false;
			tile[idx].isOnlyInfry = false;
			break;
		case ENVIRONMENT_TYPE::MOUNTAIN:
		case ENVIRONMENT_TYPE::RIVER:
		case ENVIRONMENT_TYPE::RIVER_LINE:
		case ENVIRONMENT_TYPE::RIVER_CURVE:
		case ENVIRONMENT_TYPE::RIVER_3WAYS:
		case ENVIRONMENT_TYPE::RIVER_4WAYS:
			tile[idx].isWalkable = true;
			tile[idx].isListOn = false;
			tile[idx].isOnlyInfry = true;
			break;
		case ENVIRONMENT_TYPE::SEA:
		case ENVIRONMENT_TYPE::SEA_2WAYS:
		case ENVIRONMENT_TYPE::SEA_3WAYS:
		case ENVIRONMENT_TYPE::SEA_4WAYS:
		case ENVIRONMENT_TYPE::SEA_5WAYS:
		case ENVIRONMENT_TYPE::SEA_6WAYS:
		case ENVIRONMENT_TYPE::SEA_7WAYS:
		case ENVIRONMENT_TYPE::SEA_8WAYS:
		case ENVIRONMENT_TYPE::SEA_VERTICAL00:
		case ENVIRONMENT_TYPE::SEA_VERTICAL01:
		case ENVIRONMENT_TYPE::SEA_VERTICAL02:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL00:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL01:
		case ENVIRONMENT_TYPE::SEA_HORIZONTAL02:
		case ENVIRONMENT_TYPE::SEA_NOWAYS:
			tile[idx].isWalkable = false;
			tile[idx].isListOn = false;
			tile[idx].isOnlyInfry = false;
			break;
		}

		switch (tile[idx].tileType)
		{
		case ASTAR_TYPE::START:
			tile[idx].isWalkable = false;
			tile[idx].isListOn = false;
			tile[idx].isOnlyInfry = false;
			closeList.push_back(&tile[idx]);
			break;
		case ASTAR_TYPE::END:
			break;
		}
		
		if (tile[idx].unitType != UNIT_TYPE::NONE)
		{
			tile[idx].isWalkable = false;
			tile[idx].isListOn = false;
			tile[idx].isOnlyInfry = false;
		}
	}

	astarState = ASTAR_STATE::SEARCHING;
	lastIdx = 0;
}

void CAstar::addOpenList()
{
	Cidx = closeList[lastIdx]->idx;
	Cg = closeList[lastIdx]->valueG;
	int tileLine = Cidx % 30;
	if (tileLine > 1) visit(Cidx - 1);
	if (tileLine < 29) visit(Cidx + 1);
	if (Cidx > 29) visit(Cidx + 30);
	if (Cidx < 570) visit(Cidx - 30);
}

void CAstar::visit(int tileNum)
{
	if (tile[tileNum].isWalkable)
	{
		if (!tile[tileNum].isListOn)
		{
			tile[tileNum].isListOn = true;
			tile[tileNum].valueG = Cg + 10;
			tile[tileNum].parent = closeList[lastIdx];
			openList.push_back(&tile[tileNum]);
		}
		else
		{
			if (Cg + 10 < tile[tileNum].valueG)
			{
				tile[tileNum].valueG = Cg + 10;
				tile[tileNum].parent = closeList[lastIdx];
			}
		}
	}
}

void CAstar::caculateH()
{
	for (int idx = 0; idx < openList.size(); idx++)
	{
		int vertical = (endPos.x / TILE_SIZE_X - openList[idx]->pos.x / TILE_SIZE_X) * 10;
		int horizontal = (endPos.y / TILE_SIZE_Y - openList[idx]->pos.x / TILE_SIZE_Y) * 10;
		
		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;
		
		openList[idx]->valueH = vertical + horizontal;
	}
}

void CAstar::caculateF()
{
	for (int idx = 0; idx < openList.size(); idx++)
	{
		openList[idx]->valueF = openList[idx]->valueG + openList[idx]->valueH;
	}
}

void CAstar::addCloseList()
{
	if (openList.size() == 0)
	{
		astarState = ASTAR_STATE::NOWAY;
		return;
	}
	int index = 0;
	int lowest = ASTAR_MAX_NUM;

	for (int idx = 0; idx < openList.size(); idx++)
	{
		if (openList[idx]->valueF < lowest)
		{
			lowest = openList[idx]->valueF;
			index = idx;
		}
	}

	closeList.push_back(openList[index]);
	openList.erase(openList.begin() + index);//오픈 리스트에 추가된 타일은 오픈리스트에서 제외
	lastIdx++;//가장 나중에 추가된 클로즈의 인덱스
}

void CAstar::checkArrive()
{
	if (closeList[lastIdx]->pos == endPos)
	{
		astarState = ASTAR_STATE::FOUND;
	}
}
