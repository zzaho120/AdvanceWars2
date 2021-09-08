#include "framework.h"
#include "Player.h"
#include "GameManager.h"

CPlayer::CPlayer() :
	isUnitSelect(false),
	isOnUI(false),
    isMove(false),
	isAttack(false),
	money(0),
	playerType(PLAYER_TYPE::NONE),
	gameMgr(nullptr)
{
	memset(key_Z, 0, sizeof(key_Z));
	memset(key_X, 0, sizeof(key_X));
}

CPlayer::CPlayer(PLAYER_TYPE player) :
	isUnitSelect(false),
	isOnUI(false),
	isMove(false),
	isAttack(false),
	money(0),
	playerType(player),
	gameMgr(nullptr)
{
	memset(key_Z, 0, sizeof(key_Z));
	memset(key_X, 0, sizeof(key_X));
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

void CPlayer::render()
{
	keyStrSetting();
	IMAGE->frameRender("key", getMemDC(), 50, 710, 0, 0);
	TextOut(getMemDC(), 110, 715, key_Z, strlen(key_Z));
	IMAGE->frameRender("key", getMemDC(), 160, 710, 1, 0);
	TextOut(getMemDC(), 220, 715, key_X, strlen(key_X));
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
	if (InputManager->isOnceKeyDown('X'))
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
	switch (playerType)
	{
	case PLAYER_TYPE::PLAYER1:
		SOUND->play("player1bg", 0.5F);
		break;
	case PLAYER_TYPE::PLAYER2:
		SOUND->play("player2bg", 0.5F);
		break;
	}
	gameMgr->incomeMoneyMsg();
	gameMgr->unitRepairMsg();
}

void CPlayer::exit()
{
	switch (playerType)
	{
	case PLAYER_TYPE::PLAYER1:
		SOUND->stop("player1bg");
		break;
	case PLAYER_TYPE::PLAYER2:
		SOUND->stop("player2bg");
		break;
	}
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

void CPlayer::keyStrSetting()
{
	if (isOnUI)
	{
		strcpy(key_Z, "선택");
		strcpy(key_X, "취소");
	}
	else if (isUnitSelect)
	{
		strcpy(key_Z, "이동");
		strcpy(key_X, "취소");
	}
	else
	{
		strcpy(key_Z, "메뉴");
		strcpy(key_X, "유닛 사정거리");
	}
}
