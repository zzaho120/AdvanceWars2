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
	if (InputManager->isOnceKeyDown('X'))
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
		strcpy(key_Z, "����");
		strcpy(key_X, "���");
	}
	else if (isUnitSelect)
	{
		strcpy(key_Z, "�̵�");
		strcpy(key_X, "���");
	}
	else
	{
		strcpy(key_Z, "�޴�");
		strcpy(key_X, "���� �����Ÿ�");
	}
}
