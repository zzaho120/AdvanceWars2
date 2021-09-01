#pragma once
#include"gameNode.h"
#include"MapTool.h"
#include"MapToolSub.h"
#include"TestGame.h"
#include"GameManager.h"
class mainGame : public gameNode
{
private:
	CMapTool* maptool;
	CTestGame* test;
	CGameManager* gameMgr;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	RECT checkGameSize();
};