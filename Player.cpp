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
	// 유닛 선택
	if (!isSelected && InputManager->isOnceKeyDown('Z'))
	{
		gameMgr->selectUnitMsg();
		isSelected = true;
	}

	// 유닛 선택 취소
	if (isSelected && !isMove && InputManager->isOnceKeyDown('X'))
	{
		gameMgr->selectUnitCancelMsg();
		isSelected = false;
	}
}

void CPlayer::moveUnit()
{
	// 이동 타일 선택
	if (isSelected && !isMove && InputManager->isOnceKeyDown('Z'))
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
	if (isSelected && isMove)
	{
		// 이동 취소
		if (InputManager->isOnceKeyDown('X'))
		{
			gameMgr->moveUndoMsg();
			isMove = false;
		}

		// 이동 명령 완료
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
