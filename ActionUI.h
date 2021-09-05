#pragma once
#include"UI.h"
#include "GameManager.h"

class CActionUI : public CUI
{
private:
	PLAYER_TYPE curPlayerType;
	UNIT_TYPE curUnitType;
	Vec2 panelPos;
	int cursorIdx;

	bool isCapture;
	CGameManager* gameMgr;
public:
	CActionUI();
	CActionUI(CGameManager* mgr);
	~CActionUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enter();
	virtual void exit();

	void cursorMove();
	void chooseAction();
	void checkCapture();
};