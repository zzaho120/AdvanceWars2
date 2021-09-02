#include "framework.h"
#include "Player.h"
#include "GameManager.h"

CPlayer::CPlayer() :
	isSelected(false),
    isMove(false),
	playerType(PLAYER_TYPE::NONE),
	gameMgr(nullptr)
{
}

CPlayer::CPlayer(PLAYER_TYPE player) :
	isSelected(false),
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
	if (!isSelected && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
		isSelected = true;
	}

	// ���� ���� ���
	if (isSelected && !isMove && InputManager->isOnceKeyDown('X'))
	{
		gameMgr->selectUnitCancelMsg();
		isSelected = false;
	}
}

void CPlayer::moveUnit()
{
	// �̵� Ÿ�� ����
	if (isSelected && !isMove && InputManager->isOnceKeyDown('Z'))
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
	if (isSelected && isMove)
	{
		// �̵� ���
		if (InputManager->isOnceKeyDown('X'))
		{
			gameMgr->moveUndoMsg();
			isMove = false;
		}

		// �̵� ��� �Ϸ�
		else if (InputManager->isOnceKeyDown('Z'))
		{
			gameMgr->completeMoveUnitMsg();
			isSelected = false;
		}
	}
}

void CPlayer::selectFactory()
{
	if (!isSelected && !isMove && InputManager->isOnceKeyDown('Z'))
	{

	}
}

void CPlayer::enter()
{
	isSelected = false;
	isMove = false;
}

void CPlayer::exit()
{
	isSelected = false;
	isMove = false;
}
