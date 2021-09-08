#pragma once
#include "gameNode.h"
#include "MainMenuMgr.h"
class CMainMenuScene : public gameNode
{
private:
	CMainMenuMgr* mainMenuMgr;
public:
	CMainMenuScene();
	~CMainMenuScene();

	HRESULT init();
	void release();
	void update();
	void render();
};
