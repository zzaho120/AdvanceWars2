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
	// 유닛 선택
	if (!isUnitSelect && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
	}

	// 유닛 선택 취소
	if (isUnitSelect && !isMove && InputManager->isOnceKeyDown('X'))
	{
		gameMgr->selectUnitCancelMsg();
	}
}

void CPlayer::moveUnit()
{
	// 이동 타일 선택
	if (isUnitSelect && !isMove && InputManager->isOnceKeyDown('Z'))
	{
		isMove = true;
		gameMgr->moveUnitSettingMsg();
	}

	// 이동 커맨드 실행
	if (isMove && gameMgr->isUnitArrive())
	{
		gameMgr->commandExcute();
	}

	// 이동 타일이 선택이 됐다면
	if (isUnitSelect && isMove)
	{
		// 이동 취소
		if (InputManager->isOnceKeyDown('X'))
		{
			gameMgr->moveUndoMsg();
		}

		// 이동 명령 완료
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
