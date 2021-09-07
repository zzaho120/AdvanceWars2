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
		actionUnit();
	}
}

void CPlayer::selectUnit()
{
	// 유닛 선택
	if (InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
	}
	// 유닛 사정거리 범위 보기
	if (InputManager->isStayKeyDown('X'))
	{
		gameMgr->viewUnitRangeMsg();
	}
	// 유닛 사정거리 범위 보기 취소
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
			// 유닛 공격 수행
			if (InputManager->isOnceKeyDown('Z'))
				gameMgr->attackUnitMsg();
			// 유닛 공격 취소
			else if (InputManager->isOnceKeyDown('X'))
			{
				isAttack = false;
				gameMgr->viewActionMsg();
			}
		}
		else if (!isAttack)
		{
			// 유닛 이동 타일 선택
			if (InputManager->isOnceKeyDown('Z'))
			{
				gameMgr->moveUnitSettingMsg();
			}
			// 유닛 선택 취소
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
