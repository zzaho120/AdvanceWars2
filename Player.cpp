#include "framework.h"
#include "Player.h"
#include "GameManager.h"

CPlayer::CPlayer() :
	isUnitSelect(false),
	isFactorySelect(false),
    isMove(false),
	playerType(PLAYER_TYPE::NONE),
	gameMgr(nullptr)
{
}

CPlayer::CPlayer(PLAYER_TYPE player) :
	isUnitSelect(false),
	isFactorySelect(false),
	isMove(false),
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
	selectUnit();
	selectFactory();
	moveUnit();

	if (InputManager->isOnceKeyDown('G')) gameMgr->generateUnitMsg(UNIT_TYPE::INFANTRY);
    if (InputManager->isOnceKeyDown('H')) gameMgr->generateUnitMsg(UNIT_TYPE::MECH);
    if (InputManager->isOnceKeyDown('J')) gameMgr->generateUnitMsg(UNIT_TYPE::TANK);
    if (InputManager->isOnceKeyDown('K')) gameMgr->generateUnitMsg(UNIT_TYPE::ARTILLERY);
    if (InputManager->isOnceKeyDown('L')) gameMgr->generateUnitMsg(UNIT_TYPE::APC);

	if (InputManager->isOnceKeyDown('C'))
		gameMgr->changePlayerMsg();
}


void CPlayer::selectUnit()
{
	// ���� ����
	if (!isUnitSelect && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
	}

	// ���� ���� ���
	if (isUnitSelect && !isMove && InputManager->isOnceKeyDown('X'))
	{
		gameMgr->selectUnitCancelMsg();
	}
}

void CPlayer::moveUnit()
{
	// �̵� Ÿ�� ����
	if (isUnitSelect && !isMove && InputManager->isOnceKeyDown('Z'))
	{
		isMove = true;
		gameMgr->moveUnitSettingMsg();
	}

	// �̵� Ŀ�ǵ� ����
	if (isMove && gameMgr->isUnitArrive())
	{
		gameMgr->commandExcute();
	}

	// �̵� Ÿ���� ������ �ƴٸ�
	if (isUnitSelect && isMove)
	{
		// �̵� ���
		if (InputManager->isOnceKeyDown('X'))
		{
			gameMgr->moveUndoMsg();
		}

		// �̵� ��� �Ϸ�
		else if (InputManager->isOnceKeyDown('Z'))
		{
			gameMgr->completeMoveUnitMsg();
		}
	}
}

void CPlayer::selectFactory()
{
	if (!isUnitSelect && !isFactorySelect && !isMove && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->viewFactoryMsg();
	}
}

void CPlayer::enter()
{
	isUnitSelect = false;
	isFactorySelect = false;
	isMove = false;
}

void CPlayer::exit()
{
	isUnitSelect = false;
	isFactorySelect = false;
	isMove = false;
}
