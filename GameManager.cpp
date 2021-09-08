#include "framework.h"
#include "GameManager.h"
#include "FactoryUI.h"
#include "OptionUI.h"
#include "InfoUI.h"
#include "ActionUI.h"
#include "MoveUnitCommand.h"
#include "GenerateUnitCommand.h"
#include "CaptureBuildingCommand.h"
#include "AttackUnitCommand.h"
#include "DestroyUnitCommand.h"
#include "RepairUnitCommand.h"
#include "SupplyUnitCommand.h"

CGameManager::CGameManager() :
	cam(new CCamera),
	map(new CMap("save/beansisland.map")),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager),
	uiMgr(new CUIManager),
	gameData(new CGameData),
	gameResult(new CGameResult),
	curPlayer(nullptr),
	command(nullptr),
	isGameover(false),
	isExit(false)
{
	playerArr[0] = new CPlayer(PLAYER_TYPE::PLAYER1);
	playerArr[1] = new CPlayer(PLAYER_TYPE::PLAYER2);
	ASTAR->init(map);
	isKO[0] = false;
	isKO[1] = false;
}

CGameManager::CGameManager(const char* fileName) :
	cam(new CCamera),
	map(new CMap(fileName)),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158)),
	unitMgr(new CUnitManager),
	buildingMgr(new CBuildingManager),
	uiMgr(new CUIManager),
	gameData(new CGameData),
	gameResult(new CGameResult),
	curPlayer(nullptr),
	command(nullptr),
	isGameover(false),
	isExit(false)
{
	playerArr[0] = new CPlayer(PLAYER_TYPE::PLAYER1);
	playerArr[1] = new CPlayer(PLAYER_TYPE::PLAYER2);
	ASTAR->init(map);
	isKO[0] = false;
	isKO[1] = false;
}

CGameManager::~CGameManager()
{
	SAFE_DELETE(map);
	SAFE_DELETE(cam);
	SAFE_DELETE(cursor);
	for (int idx = 0; idx < 2; idx++)
	{
		playerArr[idx]->release();
		SAFE_DELETE(playerArr[idx]);
	}
	SAFE_DELETE(unitMgr);
	SAFE_DELETE(uiMgr);
	SAFE_DELETE(gameData);
	command = nullptr;
	SAFE_DELETE(command);
}

HRESULT CGameManager::init()
{
	map->init(this);
	cursor->init(this);
	unitMgr->init(this);
	gameResult->init(this);

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
	SAFE_DELETE(map);
	SAFE_DELETE(cam);
	SAFE_DELETE(cursor);
	for (int idx = 0; idx < 2; idx++)
	{
		playerArr[idx]->release();
		SAFE_DELETE(playerArr[idx]);
	}
	SAFE_DELETE(unitMgr);
	SAFE_DELETE(uiMgr);
	SAFE_DELETE(gameData);
	command = nullptr;
	SAFE_DELETE(command);
}

void CGameManager::update()
{
	if (!isGameover)
	{
		cam->update();
		map->update();
		unitMgr->update();
		buildingMgr->update();
		uiMgr->update();

		EFFECT->update();
		if (!curPlayer->getOnUI())
		{
			curPlayer->update();
			cursor->update();
			// 커서 이동에 따른 카메라 이동
			cam->setTargetVec2(cursor->getPos());
		}

		isGameEnd();
		isExitGame();
	}
	else if (isGameover)
	{
		gameResult->update();
	}

}

void CGameManager::render()
{
	map->render();
	cursor->render();
	unitMgr->render();
	buildingMgr->render();
	EFFECT->render();
	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
	
	// 카메라에 영향을 받지 않는 유아이 렌더
	uiMgr->render();

	if (isGameover)
		gameResult->render();
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
			curPlayer->inputInit();
			break;
		}
	}
}

// 유닛이 도착했는지 판별하는 함수
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
		gameData->plusGenerate(curPlayer->getPlayerType());
		gameData->plusSpending(curPlayer->getPlayerType(), cost);
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
				unitMgr->getUnit(idx)->moveFloodFill();
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
	CBuilding* curBuilding = nullptr;
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			break;
		}
	}

	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (buildingMgr->getVecBuilding()[idx]->getTileIdx() == curUnit->getTileIdx())
		{
			curBuilding = buildingMgr->getVecBuilding()[idx];
		}
	}

	if (curUnit->correctMove(cursor->getCursorIdx()) && curUnit->getTileIdx() != cursor->getCursorIdx())
	{
		curUnit->setMove(true);
		curUnit->setMoveSetting(false);
		curUnit->setArrive(false);
		curPlayer->setMove(true);
		map->getTile()[curUnit->getTileIdx()]->setUnitType(UNIT_TYPE::NONE);
		command = new CMoveUnitCommand(curUnit, curBuilding, getLeftTopVec2(cursor->getPos(), TILE_SIZE), cursor->getCursorIdx());
		HISTORY->add(command);
	}
	else if (curUnit->getTileIdx() == cursor->getCursorIdx())
	{
		curUnit->setMove(true);
		viewActionMsg();
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
		unitMgr->setAllActive(PLAYER_TYPE::PLAYER1, true);
		break;
	case PLAYER_TYPE::PLAYER2:
		curPlayer = playerArr[static_cast<int>(PLAYER_TYPE::PLAYER1)];
		unitMgr->setAllActive(PLAYER_TYPE::PLAYER2, true);
		break;
	}
	curPlayer->enter();
	gameData->plusTurn();
	for (int idx = 0; idx < uiMgr->getVecUI().size(); idx++)
	{
		bool isInfoUI = uiMgr->getVecUI()[idx]->getUIType() == UI_TYPE::INFO_UI;
		if (isInfoUI)
			uiMgr->enterUI(idx);
	}
}

// 공장 생산 UI 출력 메시지
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

// 옵션 UI 출력 메시지
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

// 액션 UI 출력 메시지
void CGameManager::viewActionMsg()
{
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getVecUnit()[idx];
		}
	}
	curUnit->setAttack(false);

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

// UI 종료 메시지
void CGameManager::closeUIMsg()
{
	curPlayer->setOnUI(false);
}

// 빌딩 점령 메시지
void CGameManager::captureBuildingMsg()
{
	CUnit* curUnit = nullptr;
	CBuilding* curBuilding = nullptr;
	CTile* curTile = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getVecUnit()[idx];
		}
	}

	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (buildingMgr->getVecBuilding()[idx]->getTileIdx() == curUnit->getTileIdx())
		{
			curBuilding = buildingMgr->getVecBuilding()[idx];
		}
	}
	curTile = map->getTile()[curBuilding->getTileIdx()];
	command = new CCaptureBuildingCommand(curUnit, curBuilding, curTile);
	HISTORY->add(command);
	commandExcute();
}

// 유닛 공격을 위한 데이터 세팅 메시지
void CGameManager::attackUnitSettingMsg()
{
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getVecUnit()[idx];
		}
	}
	curUnit->setAttack(true);
	curPlayer->setAttack(true);
}

// 유닛 공격 메시지
void CGameManager::attackUnitMsg()
{
	CTile* curTile = nullptr;
	CTile* oppositTile = nullptr;
	CUnit* curUnit = nullptr;
	CUnit* oppositUnit = nullptr;

	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			curTile = map->getTile()[curUnit->getTileIdx()];
			break;
		}
	}

	if (curUnit->correctAttack(cursor->getCursorIdx()))
	{
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			if (unitMgr->getVecUnit()[idx]->getTileIdx() == cursor->getCursorIdx())
				oppositUnit = unitMgr->getVecUnit()[idx];
		}
		oppositTile = map->getTile()[oppositUnit->getTileIdx()];
	}
	else return;

	command = new CAttackUnitCommand(curUnit, oppositUnit, curTile, oppositTile);
	HISTORY->add(command);
	commandExcute();

	completeMoveUnitMsg();

	curUnit->setAttack(false);
	curPlayer->inputInit();
}

// 선택한 유닛이 공격 가능한지 판별하는 함수
bool CGameManager::isAvailableAttack()
{
	CUnit* curUnit = nullptr;
	bool result = false;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			break;
		}
	}
	if (curUnit->getUnitType() == UNIT_TYPE::ARTILLERY && curPlayer->getMove())
		result = false;
	else result = curUnit->isEnemyInFocus();
	return result;
}

// 선택한 유닛이 공격모드인지 판별하는 함수
bool CGameManager::isAttackMode()
{
	return curPlayer->getAttack();
}

// 유닛이 커서 위에 있는지 판별하는 함수
bool CGameManager::isUnitOnCursor()
{
	bool isCursorOnUnit = false;
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			break;
		}
	}
	isCursorOnUnit = curUnit->correctAttack(cursor->getCursorIdx());

	return isCursorOnUnit;
}

// 데미지를 예측하여 계산해주는 함수
int CGameManager::predictDamaged()
{
	CUnit* curUnit = nullptr;
	CUnit* oppositUnit = nullptr;
	CTile* oppositTile = nullptr;
	int damage = 0;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			break;
		}
	}
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getTileIdx() == cursor->getCursorIdx())
		{
			oppositUnit = unitMgr->getVecUnit()[idx];
			break;
		}
	}
	
	oppositTile = map->getTile()[oppositUnit->getTileIdx()];
	damage = curUnit->calculateDamage(oppositUnit, oppositTile);
	return damage;
}

// 유닛 파괴 메시지
void CGameManager::destroyUnitMsg(CUnit* unit)
{
	int tileIdx = unit->getTileIdx();
	map->getTile()[tileIdx]->setUnitType(UNIT_TYPE::NONE);
	command = new CDestroyUnitCommand(unit, unitMgr);
	command->excute();
	gameData->plusDeath(unit->getPlayerType());
}

// 선택한 유닛이 보급 기능을 수행할 수 있는지 판별하는 함수
bool CGameManager::isAvailableSupply()
{
	CUnit* curUnit = nullptr;
	int tileIdx = 0;
	bool result = false;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getSelected())
		{
			curUnit = unitMgr->getUnit(idx);
			tileIdx = curUnit->getTileIdx();
			break;
		}
	}

	if (curUnit->getUnitType() != UNIT_TYPE::APC) return false;
	if (tileIdx % 30 > 0) result |= (map->getTile()[tileIdx - 1]->getUnitType() != UNIT_TYPE::NONE);
	if (tileIdx % 30 < 29) result |= (map->getTile()[tileIdx + 1]->getUnitType() != UNIT_TYPE::NONE);
	if (tileIdx > 29) result |= (map->getTile()[tileIdx - 30]->getUnitType() != UNIT_TYPE::NONE);
	if (tileIdx < 579) result |= (map->getTile()[tileIdx + 30]->getUnitType() != UNIT_TYPE::NONE);
	
	return result;
}

// 유닛 보급 메시지
void CGameManager::supplyUnitMsg()
{
	command = new CSupplyUnitCommand(unitMgr);
	HISTORY->add(command);
	commandExcute();
}

// 유닛의 사정거리 출력 메시지
void CGameManager::viewUnitRangeMsg()
{
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getTileIdx() == cursor->getCursorIdx())
		{
			curUnit = unitMgr->getUnit(idx);
			break;
		}
	}
	curUnit->setRange(true);
	curUnit->rangeFloodFill();
}

// 유닛의 사정거리 출력 취소 메시지
void CGameManager::cancelUnitRangeMsg()
{
	CUnit* curUnit = nullptr;
	for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
	{
		if (unitMgr->getVecUnit()[idx]->getRange() == true)
		{
			curUnit = unitMgr->getUnit(idx);
			curUnit->setRange(false);
			break;
		}
	}
}

// 턴 시작 시 플레이어 돈 증가 메시지
void CGameManager::incomeMoneyMsg()
{
	int income = 0;

	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		if (curPlayer->getPlayerType() == buildingMgr->getVecBuilding()[idx]->getPlayerType())
			income += 1000;
	}

	gameData->plusIncome(curPlayer->getPlayerType(), income);
	curPlayer->setMoney(curPlayer->getMoney() + income);

	if (curPlayer->getMoney() > MONEY_MAX)
		curPlayer->setMoney(MONEY_MAX);
}

// 유닛 회복 메시지
void CGameManager::unitRepairMsg()
{
	command = new CRepairUnitCommand(curPlayer->getPlayerType(), unitMgr, buildingMgr);
	HISTORY->add(command);
	commandExcute();
}

// 게임 오버 체크
void CGameManager::isGameEnd()
{
	// HQ 건물이 없는 경우
	bool isPlayer1HQ = false;
	bool isPlayer2HQ = false;
	bool isPlayer1Unit = false;
	bool isPlayer2Unit = false;

	for (int idx = 0; idx < buildingMgr->getVecBuilding().size(); idx++)
	{
		CBuilding* curbuilding = buildingMgr->getVecBuilding()[idx];
		switch (curbuilding->getPlayerType())
		{
		case PLAYER_TYPE::PLAYER1:
			if(curbuilding->getIsHQ())
				isPlayer1HQ = true;
			break;
		case PLAYER_TYPE::PLAYER2:
			if (curbuilding->getIsHQ())
				isPlayer2HQ = true;
			break;
		}
	}

	
	if (gameData->getTurn() > 1)
	{
		for (int idx = 0; idx < unitMgr->getVecUnit().size(); idx++)
		{
			CUnit* curUnit = unitMgr->getVecUnit()[idx];
			switch (curUnit->getPlayerType())
			{
			case PLAYER_TYPE::PLAYER1:
				isPlayer1Unit = true;
				break;
			case PLAYER_TYPE::PLAYER2:
				isPlayer2Unit = true;
				break;
			}
		}
	}
	else if ((unitMgr->getVecUnit().size() == 0) || (gameData->getTurn() <= 1))
	{
		isPlayer1Unit = true;
		isPlayer2Unit = true;
	}

	if (!isPlayer1HQ || !isPlayer1Unit)
	{
		isGameover = true;
		isKO[0] = true;

		SOUND->stop("player1bg");
		SOUND->stop("player2bg");
		SOUND->play("gameover", 0.5F);
		return;
	}
	else if (!isPlayer2HQ || !isPlayer2Unit)
	{
		isGameover = true;
		isKO[1] = true;

		SOUND->stop("player1bg");
		SOUND->stop("player2bg");
		SOUND->play("gameover", 0.5F);
		return;
	}
}

// 커맨드 실행 함수
void CGameManager::commandExcute()
{
	command->excute();
}

void CGameManager::isExitGame()
{
	if(isExit)
		SCENE->changeScene("mainMenuScene");
}
