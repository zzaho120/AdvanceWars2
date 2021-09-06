#include "framework.h"
#include "ActionUI.h"

CActionUI::CActionUI() :
	CUI(UI_TYPE::ACTION_UI),
	curPlayerType(PLAYER_TYPE::NONE),
	panelPos({ 50, 50 }),
	cursorIdx(0),
	isCapture(false),
	isAttack(false),
	gameMgr(nullptr)
{
}

CActionUI::CActionUI(CGameManager* mgr) :
	CUI(UI_TYPE::ACTION_UI),
	panelPos({ 50, 50 }),
	cursorIdx(0),
	isCapture(false),
	isAttack(false),
	curPlayerType(PLAYER_TYPE::NONE)
{
	gameMgr = mgr;
}

CActionUI::~CActionUI()
{
}

HRESULT CActionUI::init()
{
	return S_OK;
}

void CActionUI::release()
{
}

void CActionUI::update()
{
	if (isActive && curPlayerType != PLAYER_TYPE::NONE)
	{
		checkCapture();
		checkAttack();
		cursorMove();
		chooseAction();
	}
}

void CActionUI::render()
{
	if (isActive && !isAttack && curPlayerType != PLAYER_TYPE::NONE )
	{
		switch (curPlayerType)
		{
		case PLAYER_TYPE::PLAYER1:
			IMAGE->render("action_panel_red", getMemDC(), panelPos.x, panelPos.y);
			break;
		case PLAYER_TYPE::PLAYER2:
			IMAGE->render("action_panel_blue", getMemDC(), panelPos.x, panelPos.y);
			break;
		}

		int buttonX = panelPos.x + 20;
		int buttonY = panelPos.y + 25;
		IMAGE->render("action_fire", getMemDC(), buttonX, buttonY);
		IMAGE->render("action_capture", getMemDC(), buttonX, buttonY + 75);
		IMAGE->render("action_supply", getMemDC(), buttonX, buttonY + 75 * 2);
		IMAGE->render("action_wait", getMemDC(), buttonX, buttonY + 75 * 3);
		IMAGE->render("factory_arrow", getMemDC(), 30, panelPos.y + 45 + cursorIdx * 75);

		switch (curUnitType)
		{
		case UNIT_TYPE::INFANTRY:
		case UNIT_TYPE::MECH:
			if (!gameMgr->isAvailableAttack())
				IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5);
			IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5 + 75 * 2);
			if(!isCapture)
				IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5 + 75);
			break;
		case UNIT_TYPE::TANK:
		case UNIT_TYPE::ARTILLERY:
			if (!gameMgr->isAvailableAttack())
				IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5);
			IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5 + 75);
			IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5 + 75 * 2);
			break;
		case UNIT_TYPE::APC:
			IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5);
			IMAGE->render("action_failed", getMemDC(), buttonX + 5, buttonY + 5 + 75);
			break;
		default:
			break;
		}
	}
}

void CActionUI::enter()
{
	cursorIdx = 0;
	isActive = true;
	isAttack = false;
	curPlayerType = gameMgr->getCurPlayer()->getPlayerType();

	for (int idx = 0; idx < gameMgr->getUnitMgr()->getVecUnit().size(); idx++)
	{
		if (gameMgr->getUnitMgr()->getVecUnit()[idx]->getSelected())
		{
			curUnitType = gameMgr->getUnitMgr()->getVecUnit()[idx]->getUnitType();
		}
	}
}

void CActionUI::exit()
{
	cursorIdx = 0;
	isActive = false;
	curPlayerType = PLAYER_TYPE::NONE;
}

void CActionUI::cursorMove()
{
	if (InputManager->isOnceKeyDown(VK_UP) && cursorIdx > 0) cursorIdx--;
	else if (InputManager->isOnceKeyDown(VK_DOWN) && cursorIdx < ACTION_MAX) cursorIdx++;
}

void CActionUI::chooseAction()
{
	if (InputManager->isOnceKeyDown('Z'))
	{
		switch (cursorIdx)
		{
		case 0: // 공격
			if (gameMgr->isAvailableAttack())
			{
				gameMgr->attackUnitSettingMsg();
				gameMgr->closeUIMsg();
				isAttack = true;
				exit();
			}
			break;
		case 1: // 점령
			if (isCapture)
			{
				gameMgr->captureBuildingMsg();
				gameMgr->completeMoveUnitMsg();
				gameMgr->closeUIMsg();
				exit();
			}
			break;
		case 2: // 보급
			break;
		case 3: // 대기
			gameMgr->completeMoveUnitMsg();
			gameMgr->closeUIMsg();
			exit();
			break;
		}
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		gameMgr->moveUndoMsg();
		gameMgr->closeUIMsg();
		exit();
	}
}

void CActionUI::checkCapture()
{
	isCapture = false;
	if (curUnitType == UNIT_TYPE::INFANTRY || curUnitType == UNIT_TYPE::MECH)
	{
		for (int idx = 0; idx < gameMgr->getUnitMgr()->getVecUnit().size(); idx++)
		{
			bool isSelected = gameMgr->getUnitMgr()->getVecUnit()[idx]->getSelected();
			if (isSelected)
			{
				int unitTileIdx = gameMgr->getUnitMgr()->getVecUnit()[idx]->getTileIdx();
				for (int i = 0; i < gameMgr->getBuildingMgr()->getVecBuilding().size(); i++)
				{
					bool isBuilding = gameMgr->getBuildingMgr()->getVecBuilding()[i]->getTileIdx() == unitTileIdx;
					bool isOppositPlayer = gameMgr->getBuildingMgr()->getVecBuilding()[i]->getPlayerType() != curPlayerType;
					if (isBuilding && isOppositPlayer)
					{
						isCapture = true;
						return;
					}
				}
			}
		}
	}
}

void CActionUI::checkAttack()
{
}
