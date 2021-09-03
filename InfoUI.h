#pragma once
#include"UI.h"
#include "GameManager.h"
class CInfoUI : public CUI
{
private:
	Vec2 goldInfoPos;

	PLAYER_TYPE curPlayerType;

	CGameManager* gameMgr;
public:
	CInfoUI();
	CInfoUI(CGameManager* mgr);
	~CInfoUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enter();
	virtual void exit();
};

