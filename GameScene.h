#pragma once
#include"gameNode.h"
#include"GameManager.h"
class CGameScene : public gameNode
{
private:
	CGameManager* gameMgr;
public:
	CGameScene();
	~CGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

