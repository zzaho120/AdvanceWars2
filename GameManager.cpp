#include "framework.h"
#include "GameManager.h"
#include "FactoryUI.h"
#include "OptionUI.h"
#include "InfoUI.h"
#include "ActionUI.h"

CGameManager::CGameManager() :
	cam(new CCamera),
	map(new CMap("save/beanisland.map")),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager),
	uiMgr(new CUIManager),
	curPlayer(nullptr),
	command(nullptr)
{
	playerArr[0] = new CPlayer(PLAYER_TYPE::PLAYER1);
	playerArr[1] = new CPlayer(PLAYER_TYPE::PLAYER2);
	ASTAR->init(map);
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::init()
{
	map->init(this);
	cursor->init(this);
	unitMgr->init(this);

	uiMgr->addUI(new CFactoryUI(this));
	uiMgr->addUI(new COptionUI(this));
	uiMgr->addUI(new CInfoUI(this));
	uiMgr->addUI(new CActionUI(this));

	for (int idx = 0; idx < static_cast<int>(PLAYER_TYPE::NONE); idx++)
		playerArr[idx]->init(this);

	initObject();

	curPlayer = playerArr[0];

	curPlayer->enter();
	return S_OK;
}

void CGameManager::release()
{
}

void CGameManager::update()
{
	cam->update();
	map->update();
	unitMgr->update();
	buildingMgr->update();
	uiMgr->update();

	
	if (!curPlayer->getOnUI())
	{
		curPlayer->update();
		cursor->update();
		// 커서 이동에 따른 카메라 이동
		cam->setTargetVec2(cursor->getPos());
	}
}

void CGameManager::render()
{
	map->render();
	cursor->render();
	unitMgr->render();
	buildingMgr->render();

	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
	
	// 카메라에 영향을 받지 않는 유아이 렌더
	uiMgr->render();
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
			curPlayer->setMove(false);
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
		curPlayer->setOnUI(false);
		commandExcute();

		int cost = 0;
		switch (type)
		{
		case UNIT_TYPE::INFANTRY:
			cost = 1000;
			break;
		case UNIT_TYPE::MECH:
			cost = 3000;
			break;
		case UNIT_TYPE::TANK:
			cost = 7000;
			break;
		case UNIT_TYPE::ARTILLERY:
			cost = 6000;
			break;
		case UNIT_TYPE::APC:
			cost = 5000;
			break;
		}

		curPlayer->setMoney(curPlayer->getMoney() - cost);
	}
}

// 유닛 선택 메세지
void CGameManager::selectUnitMsg()
{
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		bool isCursorOnUnit = unitMgr->getVecUnit()[idx]->getTileIdx() == cursor->getCursorIdx();
		bool isCorrectPlayer = unitMgr->getVecUnit()[idx]->getPlayerType() == curPlayer->getPlayerType();
		if (isCursorOnUnit && isCorrectPlayer)
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
			if (unitMgr->getUnit(idx)->correctMove(cursor->getCursorIdx()) && unitMgr->getUnit(idx)->getTileIdx() != cursor->getCursorIdx())
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
	for (int idx = 0; idx < uiMgr->getVecUI().size(); idx++)
	{
		bool isInfoUI = uiMgr->getVecUI()[idx]->getUIType() == UI_TYPE::INFO_UI;
		if (isInfoUI)
			uiMgr->enterUI(idx);
	}
}

void CGameManager::viewFactoryMsg()
{
	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (buildingMgr->getVecBuilding()[idx]->getTileIdx() == cursor->getCursorIdx())
		{
			for (int j = 0; j < uiMgr->getVecUI().size(); j++)
			{
				bool isFactory = uiMgr->getVecUI()[j]->getUIType() == UI_TYPE::FACTORY_UI;
				bool isPlayer = buildingMgr->getVecBuilding()[idx]->getPlayerType() == curPlayer->getPlayerType();
				if (isFactory && isPlayer)
				{
					uiMgr->enterUI(j);
					curPlayer->setOnUI(true);
					break;
				}
			}
			break;
		}
	}
}

void CGameManager::viewOptionMsg()
{
	for (int idx = 0; idx < uiMgr->getVecUI().size(); idx++)
	{
		bool isOption = uiMgr->getVecUI()[idx]->getUIType() == UI_TYPE::OPTION_UI;
		if (isOption)
		{
			uiMgr->enterUI(idx);
			curPlayer->setOnUI(true);
			break;
		}
	}
}

void CGameManager::viewActionMsg()
{
	for (int idx = 0; idx < uiMgr->getVecUI().size(); idx++)
	{
		bool isAction = uiMgr->getVecUI()[idx]->getUIType() == UI_TYPE::ACTION_UI;
		if (isAction)
		{
			uiMgr->enterUI(idx);
			curPlayer->setOnUI(true);
			break;
		}
	}
}

void CGameManager::closeUIMsg()
{
	curPlayer->setOnUI(false);
}

void CGameManager::incomeMoneyMsg()
{
	int income = 0;

	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (curPlayer->getPlayerType() == buildingMgr->getVecBuilding()[idx]->getPlayerType())
			income += 1000;
	}

	curPlayer->setMoney(curPlayer->getMoney() + income);

	if (curPlayer->getMoney() > MONEY_MAX)
		curPlayer->setMoney(MONEY_MAX);
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
				return false;
		}
	}
	return true;
}