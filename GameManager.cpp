#include "framework.h"
#include "GameManager.h"

CGameManager::CGameManager() :
	cam(new CCamera),
	map(new CMap("save/spannisland.map", cam)),
	cursor(new CCursor(map->getTile()[158]->getPos(), 158))
{
	playerArr[0] = new CPlayer(PLAYER_TYPE::PLAYER1, cursor, map);
	playerArr[1] = new CPlayer(PLAYER_TYPE::PLAYER2, cursor, map);
	ASTAR->init(map);
	curPlayer = playerArr[0];
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::init()
{
	return S_OK;
}

void CGameManager::release()
{
}

void CGameManager::update()
{
	cam->update();
	map->update();
	//cam->setTargetVec2(cursor);
	cursor->update();
	curPlayer->update();

	if (InputManager->isOnceKeyDown('C'))
	{
		if (curPlayer->getPlayerType() == PLAYER_TYPE::PLAYER1)
			changePlayer(1);
		else if (curPlayer->getPlayerType() == PLAYER_TYPE::PLAYER2)
			changePlayer(0);
	}
}

void CGameManager::render()
{
	map->render();
	cursor->render();
	for (int idx = 0; idx < 2; idx++)
		playerArr[idx]->render();
	
	TCHAR str[128];
	wsprintf(str, "%d", curPlayer->getPlayerType());
	TextOut(getMapDC(), 100, 150, str, strlen(str));

	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
}

void CGameManager::changePlayer(int type)
{
	curPlayer->exit();
	curPlayer = playerArr[type];
	curPlayer->enter();
	//curPlayer = playerArr[static_cast<int>(type)];
}
