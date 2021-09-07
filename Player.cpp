#include "framework.h"
#include "Player.h"
#include "GameManager.h"

CPlayer::CPlayer() :
	isUnitSelect(false),
	isOnUI(false),
    isMove(false),
	money(0),
	playerType(PLAYER_TYPE::NONE),
	gameMgr(nullptr)
{
}

CPlayer::CPlayer(PLAYER_TYPE player) :
	isUnitSelect(false),
	isOnUI(false),
	isMove(false),
	money(0),
	playerType(player),
	gameMgr(nullptr)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::init()
{
    return S_OK;
}

HRESULT CPlayer::init(CGameManager* mgr)
{
	gameMgr = mgr;
    return S_OK;
}

void CPlayer::release()
{
}

void CPlayer::update()
{
	playerInput();
}


void CPlayer::playerInput()
{
	bool isFactory = gameMgr->getMap()->getTile()[gameMgr->getCursor()->getCursorIdx()]->getBuildtype() == BUILDING_TYPE::FACTORY;
	bool isNoneUnit = gameMgr->getMap()->getTile()[gameMgr->getCursor()->getCursorIdx()]->getUnitType() == UNIT_TYPE::NONE;

	// Ŀ�� Ÿ���� ���丮���
	if (!isUnitSelect)
	{
		if (!isNoneUnit)
		{
			selectUnit();
		}
		else if(isNoneUnit)
		{
			if (isFactory)
			{
				viewFactory();
			}
			else if (!isFactory)
			{
				viewOption();
			}
		}
	}
	else
	{
		actionUnit();
	}
}

void CPlayer::selectUnit()
{
	// ���� ����
	if (InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
	}
	// ���� �����Ÿ� ���� ����
	if (InputManager->isStayKeyDown('X'))
	{
		gameMgr->viewUnitRangeMsg();
	}
	// ���� �����Ÿ� ���� ���� ���
	if (InputManager->isOnceKeyUp('X'))
	{
		gameMgr->cancelUnitRangeMsg();
	}
}

void CPlayer::actionUnit()
{
	if (!isMove)
	{
		if (isAttack)
		{
			// ���� ���� ����
			if (InputManager->isOnceKeyDown('Z'))
				gameMgr->attackUnitMsg();
			// ���� ���� ���
			else if (InputManager->isOnceKeyDown('X'))
			{
				isAttack = false;
				gameMgr->viewActionMsg();
			}
		}
		else if (!isAttack)
		{
			// ���� �̵� Ÿ�� ����
			if (InputManager->isOnceKeyDown('Z'))
			{
				gameMgr->moveUnitSettingMsg();
			}
			// ���� ���� ���
			else if (isUnitSelect && InputManager->isOnceKeyDown('X'))
			{
				isUnitSelect = false;
				gameMgr->selectUnitCancelMsg();
			}
		}
		
	}
	else if (isMove)
	{
		if(!isAttack && !gameMgr->isUnitArrive())
			gameMgr->commandExcute();
		else if (!isAttack && gameMgr->isUnitArrive() && !isOnUI)
			gameMgr->viewActionMsg();
		else if (isAttack && InputManager->isOnceKeyDown('Z'))
			gameMgr->attackUnitMsg();
		else if (isAttack && InputManager->isOnceKeyDown('X'))
		{
			isAttack = false;
			gameMgr->viewActionMsg();
		}
	}
}

void CPlayer::viewFactory()
{
	if (InputManager->isOnceKeyDown('Z'))
		gameMgr->viewFactoryMsg();
}

void CPlayer::viewOption()
{
	if (InputManager->isOnceKeyDown('Z'))
		gameMgr->viewOptionMsg();
}

void CPlayer::enter()
{
	isUnitSelect = false;
	isOnUI = false;
	isMove = false;

	gameMgr->incomeMoneyMsg();
	gameMgr->unitRepairMsg();
}

void CPlayer::exit()
{
	isUnitSelect = false;
	isOnUI = false;
	isMove = false;
}

void CPlayer::inputInit()
{
	isUnitSelect = false;
	isMove = false;
	isAttack = false;
}
