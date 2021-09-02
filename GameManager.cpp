#include "framework.h"
#include "GameManager.h"
#include "FactoryUI.h"

CGameManager::CGameManager() :
	cam(new CCamera),
	map(new CMap("save/spannisland.map")),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager),
	uiMgr(new CUIManager),
	command(nullptr)
{
	playerArr[0] = new CPlayer(PLAYER_TYPE::PLAYER1);
	playerArr[1] = new CPlayer(PLAYER_TYPE::PLAYER2);
	ASTAR->init(map);
	curPlayer = playerArr[0];
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::init()
{
	map->init(this);
	cursor->init(this);

	CUI* factoryUI = new CFactoryUI(this);
	uiMgr->addUI(factoryUI);

	for (int idx = 0; idx < static_cast<int>(PLAYER_TYPE::NONE); idx++)
		playerArr[idx]->init(this);

	initObject();
	return S_OK;
}

void CGameManager::release()
{
}

void CGameManager::update()
{
	cam->update();
	map->update();
	cursor->update();
	curPlayer->update();
	unitMgr->update();
	buildingMgr->update();
	uiMgr->update();

	// 커서 이동에 따른 카메라 이동
	cam->setTargetVec2(cursor->getPos());
}

void CGameManager::render()
{
	map->render();
	cursor->render();
	unitMgr->render();
	buildingMgr->render();
	uiMgr->render();

	// 플레이어 턴이 넘어가는지 확인 값
	TCHAR str[128];
	int p1 = 0;
	int p2 = 0;
	int none = 0;
	
	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		switch (buildingMgr->getVecBuilding()[idx]->getPlayerType())
		{
		case PLAYER_TYPE::PLAYER1:
			p1++;
			break;
		case PLAYER_TYPE::PLAYER2:
			p2++;
			break;
		case PLAYER_TYPE::NONE:
			none++;
			break;
		default:
			break;
		}
	}

	wsprintf(str, "%d %d", curPlayer->getPlayerType(), buildingMgr->getVecBuilding().size());
	TextOut(getMapDC(), 100, 150, str, strlen(str));

	wsprintf(str, "%d %d %d", p1, p2, none);
	TextOut(getMapDC(), 100, 180, str, strlen(str));

	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
}

void CGameManager::initObject()
{
	CTile** tile = map->getTile();
	PLAYER_TYPE player = PLAYER_TYPE::NONE;
	Vec2 pos = 0;
	bool factory = false, HQ = false;

	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (tile[idx]->getBuildtype() == BUILDING_TYPE::NONE) continue;
		else
		{
			pos = tile[idx]->getPos();
			player = tile[idx]->getPlayerType();

			switch (tile[idx]->getBuildtype())
			{
			case BUILDING_TYPE::CITY:
				factory = false;
				HQ = false;
				break;
			case BUILDING_TYPE::HEADQUATERS:
				factory = false;
				HQ = true;
				break;
			case BUILDING_TYPE::FACTORY:
				factory = true;
				HQ = false;
				break;
			}

			buildingMgr->addBuilding(player, pos, factory, HQ, idx);
		}
	}
}

// 이동 확정 메세지
void CGameManager::completeMoveUnitMsg()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			map->getTile()[unitMgr->getUnit(idx)->getTileIdx()]->setUnitType(unitMgr->getUnit(idx)->getUnitType());
			unitMgr->getUnit(idx)->wait();
			curPlayer->setUnitSelect(false);
			break;
		}
	}
}

// 유닛 생성 매세지
void CGameManager::generateUnitMsg(UNIT_TYPE type)
{
	if (map->getTile()[cursor->getCursorIdx()]->getUnitType() == UNIT_TYPE::NONE)
	{
		map->getTile()[cursor->getCursorIdx()]->setUnitType(type);
		command = new CGenerateUnitCommand(curPlayer->getPlayerType(), type, cursor->getPos(), cursor->getCursorIdx(), unitMgr, map);
		HISTORY->add(command);
		curPlayer->setFactorySelect(false);
		commandExcute();
	}
}

// 유닛 선택 메세지
void CGameManager::selectUnitMsg()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getTileIdx() == cursor->getCursorIdx())
		{
			if (unitMgr->getVecUnit()[idx]->getActive())
			{
				unitMgr->getUnit(idx)->setSelected(true);
				curPlayer->setUnitSelect(true);
				break;
			}
		}
	}
}

// 유닛 선택 취소 메세지
void CGameManager::selectUnitCancelMsg()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			unitMgr->getUnit(idx)->setSelected(false);
			curPlayer->setUnitSelect(false);
			break;
		}
	}
}

// 이동을 위한 데이터 세팅 메세지
void CGameManager::moveUnitSettingMsg()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			if (unitMgr->getUnit(idx)->correctMove(cursor->getCursorIdx()))
			{
				unitMgr->getUnit(idx)->setMove(true);
				unitMgr->getUnit(idx)->setMoveSetting(false);
				unitMgr->getUnit(idx)->setArrive(false);
				curPlayer->setMove(true);
				map->getTile()[unitMgr->getUnit(idx)->getTileIdx()]->setUnitType(UNIT_TYPE::NONE);
				command = new CMoveUnitCommand(unitMgr->getUnit(idx), getLeftTopVec2(cursor->getPos(), TILE_SIZE), cursor->getCursorIdx());
				HISTORY->add(command);
				break;
			}
		}
	}
}

// 이동 취소 메세지
void CGameManager::moveUndoMsg()
{
	command->undo();
	HISTORY->undo();
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			unitMgr->getUnit(idx)->setMove(false);
			map->getTile()[unitMgr->getUnit(idx)->getTileIdx()]->setUnitType(unitMgr->getUnit(idx)->getUnitType());
			curPlayer->setMove(false);
			break;
		}
	}
}

// 현재 플레이어 턴 교체 메세지
void CGameManager::changePlayerMsg()
{
	curPlayer->exit();
	switch (curPlayer->getPlayerType())
	{
	case PLAYER_TYPE::PLAYER1:
		curPlayer = playerArr[static_cast<int>(PLAYER_TYPE::PLAYER2)];
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			if (unitMgr->getVecUnit()[idx]->getPlayerType() == PLAYER_TYPE::PLAYER2)
				unitMgr->getVecUnit()[idx]->setActive(true);
		}
		break;
	case PLAYER_TYPE::PLAYER2:
		curPlayer = playerArr[static_cast<int>(PLAYER_TYPE::PLAYER1)];
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			if (unitMgr->getVecUnit()[idx]->getPlayerType() == PLAYER_TYPE::PLAYER1)
				unitMgr->getVecUnit()[idx]->setActive(true);
		}
		break;
	}
	curPlayer->enter();
}

void CGameManager::viewFactoryMsg()
{
	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (buildingMgr->getVecBuilding()[idx]->getTileIdx() == cursor->getCursorIdx())
		{
			for (int j = 0; j < uiMgr->getVecUI().size(); j++)
			{
				if (uiMgr->getVecUI()[j]->getUIType() == UI_TYPE::FACTORY_UI)
				{
					uiMgr->enterUI(j);
					curPlayer->setFactorySelect(true);
					break;
				}
			}
			break;
		}
	}
}

void CGameManager::commandExcute()
{
	command->excute();
}

bool CGameManager::isUnitArrive()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			if (!unitMgr->getVecUnit()[idx]->getArrive())
				return true;
		}
	}
	return false;
}