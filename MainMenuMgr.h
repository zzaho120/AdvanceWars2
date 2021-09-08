#pragma once
#include "gameNode.h"
class CMainMenuMgr : public gameNode
{
private:
	int selectIdx;
	int titleAlpha;
	int menuAlpha;
	bool isTitle;
	bool isSelect;
public:
	CMainMenuMgr();
	~CMainMenuMgr();

	HRESULT init();
	void release();
	void update();
	void render();

	void menuInput();
	void chooseMenu();
};