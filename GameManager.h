#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "Player.h"

class CGameManager : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	CCursor* cursor;

	CPlayer* playerArr[2];
	CPlayer* curPlayer;
public:
	CGameManager();
	~CGameManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void changePlayer(int type);
};