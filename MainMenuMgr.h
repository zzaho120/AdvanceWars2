#pragma once
#include "gameNode.h"
class CMainMenuMgr : public gameNode
{
private:
	int selectIdx;
	int titleAlpha;
	int menuAlpha;
	int guideIdx;

	bool isTitle;
	bool isSelect;
	bool isGuide;

	char guideStr[128];
public:
	CMainMenuMgr();
	~CMainMenuMgr();

	HRESULT init();
	void release();
	void update();
	void render();

	void menuInput();
	void guideStrSetting();
	void chooseMenu();
};