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

	// 커서 타일이 팩토리라면
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
		moveUnit();
	}
}

void CPlayer::selectUnit()
{
	// 유닛 선택
	if (!isUnitSelect && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
	}
}

void CPlayer::moveUnit()
{
	// 이동 타일 선택
	if (!isMove && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->moveUnitSettingMsg();
	}

	// 유닛 선택 취소
	if (!isMove && InputManager->isOnceKeyDown('X'))
	{
		gameMgr->selectUnitCancelMsg();
	}

	// 이동 커맨드 실행
	if (isMove && !gameMgr->isUnitArrive())
	{
		gameMgr->commandExcute();
	}

	// 이동 타일이 선택이 됐다면
	if (isMove && gameMgr->isUnitArrive())
	{
		gameMgr->viewActionMsg();
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
}

void CPlayer::exit()
{
	isUnitSelect = false;
	isOnUI = false;
	isMove = false;
}
