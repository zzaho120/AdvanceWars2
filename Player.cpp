#include "framework.h"
#include "Player.h"
#include "Cursor.h"
#include "Map.h"

CPlayer::CPlayer() :
    isMove(false),
    curUnit(nullptr),
    command(nullptr),
	cursor(nullptr),
	map(nullptr),
	playerType(PLAYER_TYPE::NONE)
{
}

CPlayer::CPlayer(PLAYER_TYPE player, CCursor* _cursor, CMap* _map) :
	isMove(false),
	curUnit(nullptr),
	command(nullptr),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager),
	playerType(player),
	cursor(_cursor),
	map(_map)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::init()
{
    return S_OK;
}

void CPlayer::release()
{
}

void CPlayer::update()
{
	unitMgr->update();
	buildingMgr->update();
	selectUnit(); 
	moveUnit();

    if (InputManager->isOnceKeyDown('G')) addUnitToMgr(UNIT_TYPE::INFANTRY);
    if (InputManager->isOnceKeyDown('H')) addUnitToMgr(UNIT_TYPE::MECH);
    if (InputManager->isOnceKeyDown('J')) addUnitToMgr(UNIT_TYPE::TANK);
    if (InputManager->isOnceKeyDown('K')) addUnitToMgr(UNIT_TYPE::ARTILLERY);
    if (InputManager->isOnceKeyDown('L')) addUnitToMgr(UNIT_TYPE::APC);
}

void CPlayer::render()
{
	unitMgr->render();
	buildingMgr->render();
}

void CPlayer::addUnitToMgr(UNIT_TYPE type)
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (map->getTile()[idx]->getPos() == cursor->getPos() && map->getTile()[idx]->getUnitType() == UNIT_TYPE::NONE)
		{
			map->getTile()[idx]->setUnitType(type);
			unitMgr->addUnit(playerType, type, cursor->getPos(), cursor->getCursorIdx(), map);
			break;
		}
	}
}
//
//void CPlayer::selectUnit()
//{
//	if (!curUnit && InputManager->isOnceKeyDown('Z'))
//	{
//		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
//		{
//			if (unitMgr->getVecUnit()[idx]->getPos() == Vec2({ cursor->getPos().x - TILE_SIZE_X / 2, cursor->getPos().y - TILE_SIZE_Y / 2 }))
//			{
//				if (unitMgr->getVecUnit()[idx]->getActive())
//				{
//					curUnit = unitMgr->getUnit(idx);
//					curUnit->setSelected(true);
//					break;
//				}
//			}
//		}
//	}
//
//	if (curUnit && !isMove && InputManager->isOnceKeyDown('X'))
//	{
//		if (curUnit->getSelected())
//		{
//			curUnit->setSelected(false);
//			curUnit = nullptr;
//		}
//	}
//}
//
//void CPlayer::moveUnit()
//{
//	static Vec2 endPoint = 0;
//
//	if (isMove && curUnit->getPos() != endPoint)
//		command->excute();
//
//	if (isMove && curUnit->getPos() == endPoint)
//	{
//		if (InputManager->isOnceKeyDown('X'))
//		{
//			command->undo();
//			HISTORY->undo();
//			command = nullptr;
//
//
//			curUnit->setMove(false);
//			curUnit->setSelected(true);
//			isMove = false;
//		}	
//		else if (InputManager->isOnceKeyDown('Z'))
//		{
//			curUnit->wait();
//
//			isMove = false;
//			curUnit = nullptr;
//		}
//	}
//
//	
//	if (InputManager->isOnceKeyDown('Z') && curUnit && !isMove)
//	{
//		if (curUnit->correctMove(cursor->getCursorIdx()))
//		{
//			curUnit->setMove(true);
//			isMove = true;
//			endPoint = getLeftTopVec2(cursor->getPos(), cursor->getSize());
//			command = new CMoveUnitCommand(curUnit, endPoint, cursor->getCursorIdx());
//			HISTORY->add(command);
//		}
//	}
//}

void CPlayer::selectUnit()
{
	if (!curUnit && InputManager->isOnceKeyDown('Z'))
	{
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			if (unitMgr->getVecUnit()[idx]->getPos() == getLeftTopVec2(cursor->getPos(), TILE_SIZE))
			{
				if (unitMgr->getVecUnit()[idx]->getActive())
				{
					curUnit = unitMgr->getVecUnit()[idx];
					curUnit->setSelected(true);
				}
			}
		}
	}

	if (curUnit && !isMove && InputManager->isOnceKeyDown('X'))
	{
		curUnit->setSelected(false);
		curUnit = nullptr;
	}
}

void CPlayer::moveUnit()
{
	static int startIdx = 0;
	static Vec2 endPoint = 0;
	static int endIdx = 0;

	// 유닛 선택
	if (curUnit && !isMove && InputManager->isOnceKeyDown('Z'))
	{
		if (curUnit->correctMove(cursor->getCursorIdx()))
		{
			isMove = true;
			curUnit->setMove(true);
			curUnit->setMoveSetting(false);
			startIdx = curUnit->getTileIdx();
			endPoint = getLeftTopVec2(cursor->getPos(), TILE_SIZE);
			endIdx = cursor->getCursorIdx();
			command = new CMoveUnitCommand(curUnit, endPoint, endIdx);
			HISTORY->add(command);
		}
	}

	if (isMove && curUnit->getPos() != endPoint)
	{
		command->excute();
	}

	if (curUnit && isMove && curUnit->getPos() == endPoint)
	{
		// 이동 취소
		if (InputManager->isOnceKeyDown('X'))
		{
			command->undo();
			HISTORY->undo();
			isMove = false;
			curUnit->setMove(false);
		}
		// 이동 명령
		else if (InputManager->isOnceKeyDown('Z'))
		{
			map->getTile()[endIdx]->setUnitType(curUnit->getUnitType());
			map->getTile()[startIdx]->setUnitType(UNIT_TYPE::NONE);
			curUnit->wait();
			curUnit = nullptr;
			isMove = false;
		}
	}
}
void CPlayer::enter()
{
	command = nullptr;
	curUnit = nullptr;
	isMove = false;
	unitMgr->setAllActive(true);
}

void CPlayer::exit()
{
	command = nullptr;
	curUnit = nullptr;
	isMove = false;
	unitMgr->setAllActive(false);
}
