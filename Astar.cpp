#include "framework.h"
#include "Astar.h"
#include "Map.h"
CAstar::CAstar()
{
}

CAstar::~CAstar()
{
}

HRESULT CAstar::init()
{
	openList.clear();
	closeList.clear();

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx].type = TILE_TYPE::TILE_TYPE_EMPTY;
		tile[idx].walkable = false;
		tile[idx].parent = NULL;
		tile[idx].F = ASTAR_MAX_NUM;
		tile[idx].H = 0;
		tile[idx].G = 0;
		tile[idx].tileIdx = idx;
	}

	curUnitType = UNIT_TYPE::NONE;
	isArrive = false;
	return S_OK;
}

HRESULT CAstar::init(CMap* map)
{
	openList.clear();
	closeList.clear();
	while (!pathList.empty())
		pathList.pop();

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx].type = TILE_TYPE::TILE_TYPE_EMPTY;
		tile[idx].walkable = false;
		tile[idx].parent = NULL;
		tile[idx].F = ASTAR_MAX_NUM;
		tile[idx].H = 0;
		tile[idx].G = 0;
		tile[idx].pos = map->getTile()[idx]->getPos();
		tile[idx].tileIdx = idx;
		tile[idx].envirType = map->getTile()[idx]->getTileType();
	}

	curUnitType = UNIT_TYPE::NONE;
	isArrive = false;
	return S_OK;
}

void CAstar::release()
{
}

void CAstar::update()
{
	tileInitializing();
	while (!isArrive)
	{
		addOpenList();
		caculateH();
		caculateF();
		addCloseList();
		checkArrive();
	}
	setPath(closeList[lastIdx]);
}

void CAstar::tileInitializing()
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		tile[idx].listOn = false;
		if (tile[idx].type == TILE_TYPE::TILE_TYPE_START)
		{
			tile[idx].walkable = false;
			closeList.push_back(&tile[idx]);
			continue;
		}
		if (tile[idx].type == TILE_TYPE::TILE_TYPE_END)
		{
			tile[idx].walkable = true;
			continue;
		}
		
		switch (curUnitType)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			switch (tile[idx].envirType)
			{
			case ENVIRONMENT_TYPE::NONE:
			case ENVIRONMENT_TYPE::PLAIN:
			case ENVIRONMENT_TYPE::WOOD:
			case ENVIRONMENT_TYPE::ROAD:
			case ENVIRONMENT_TYPE::BRIDGE:
			case ENVIRONMENT_TYPE::ROAD_LINE:
			case ENVIRONMENT_TYPE::ROAD_CURVE:
			case ENVIRONMENT_TYPE::ROAD_3WAYS:
			case ENVIRONMENT_TYPE::ROAD_4WAYS:
			case ENVIRONMENT_TYPE::MOUNTAIN:
			case ENVIRONMENT_TYPE::RIVER:
			case ENVIRONMENT_TYPE::RIVER_LINE:
			case ENVIRONMENT_TYPE::RIVER_CURVE:
			case ENVIRONMENT_TYPE::RIVER_3WAYS:
			case ENVIRONMENT_TYPE::RIVER_4WAYS:
				tile[idx].walkable = true;
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
				tile[idx].walkable = false;
				break;
			}
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
		case UNIT_TYPE::APC:
			switch (tile[idx].envirType)
			{
			case ENVIRONMENT_TYPE::NONE:
			case ENVIRONMENT_TYPE::PLAIN:
			case ENVIRONMENT_TYPE::WOOD:
			case ENVIRONMENT_TYPE::ROAD:
			case ENVIRONMENT_TYPE::BRIDGE:
			case ENVIRONMENT_TYPE::ROAD_LINE:
			case ENVIRONMENT_TYPE::ROAD_CURVE:
			case ENVIRONMENT_TYPE::ROAD_3WAYS:
			case ENVIRONMENT_TYPE::ROAD_4WAYS:
				tile[idx].walkable = true;
				break;
			case ENVIRONMENT_TYPE::MOUNTAIN:
			case ENVIRONMENT_TYPE::RIVER:
			case ENVIRONMENT_TYPE::RIVER_LINE:
			case ENVIRONMENT_TYPE::RIVER_CURVE:
			case ENVIRONMENT_TYPE::RIVER_3WAYS:
			case ENVIRONMENT_TYPE::RIVER_4WAYS:
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
				tile[idx].walkable = false;
				break;
			}
			break;
		}
	}

	lastIdx = 0;
}

void CAstar::addOpenList()
{
	closeIdx = closeList[lastIdx]->tileIdx;
	Cg = closeList[lastIdx]->G;
	int idx = 0;

	if (closeIdx > 29)	//0번째 줄이아니면 상단라인 계산
	{
		idx = closeIdx - TILE_NUM_X;
		checkGValue(idx);
	}
	if (closeIdx % TILE_NUM_X > 0)//좌측 : 0번째 열이 아니라면
	{
		idx = closeIdx - 1;
		checkGValue(idx);
	}
	if (closeIdx % TILE_NUM_X < 29)//우측 :마지막열이 아니라면
	{
		idx = closeIdx + 1;
		checkGValue(idx);
	}
	if (closeIdx < 570)//마지막 행이 아니라면 하단 라인 계산
	{
		idx = closeIdx + TILE_NUM_X;
		checkGValue(idx);
	}
}

void CAstar::caculateH()
{
	for (size_t i = 0; i < openList.size(); i++)
	{
		int vertical = (endIdx % TILE_NUM_X - openList[i]->tileIdx % TILE_NUM_X) * 10;		//가로H
		int horizontal = (endIdx / TILE_NUM_X - openList[i]->tileIdx / TILE_NUM_X) * 10;	//세로H

		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		openList[i]->H = vertical + horizontal;
	}
}

void CAstar::caculateF()
{
	for (size_t i = 0; i < openList.size(); i++)
	{
		openList[i]->F = openList[i]->G + openList[i]->H;
	}
}

void CAstar::addCloseList()
{
	if (openList.size() == 0)
		return;

	int index = 0;
	int lowest = ASTAR_MAX_NUM;

	for (size_t i = 0; i < openList.size(); i++)
	{
		if (openList[i]->F < lowest)
		{
			lowest = openList[i]->F;
			index = i;
		}
	}

	closeList.push_back(openList[index]);
	openList.erase(openList.begin() + index);	//오픈 리스트에 추가된 타일은 오픈리스트에서 제외
	lastIdx++;									//가장 나중에 추가된 클로즈의 인덱스
}

void CAstar::checkArrive()
{
	if (closeList[lastIdx]->tileIdx == endIdx)
		isArrive = true;
}

void CAstar::setStartEnd(int _startIdx, int _endIdx, UNIT_TYPE type)
{
	init();

	startIdx = _startIdx;
	endIdx = _endIdx;

	curUnitType = type;

	tile[startIdx].type = TILE_TYPE::TILE_TYPE_START;
	tile[endIdx].type = TILE_TYPE::TILE_TYPE_END;
}

void CAstar::setPath(aStarTile* tile)
{
	pathList.push(tile->tileIdx);
	tile = tile->parent;

	if (tile->parent == NULL)
		return;
	else
		setPath(tile);
}

void CAstar::checkGValue(int idx)
{
	if (tile[idx].walkable)
	{
		if (!tile[idx].listOn)
		{
			tile[idx].listOn = true;
			tile[idx].G = Cg + 10;
			tile[idx].parent = closeList[lastIdx];
			openList.push_back(&tile[idx]);
		}
		else
		{
			if (Cg + 10 < tile[idx].G)
			{
				tile[idx].G = Cg + 10;
				tile[idx].parent = closeList[lastIdx];
			}
		}
	}
}
