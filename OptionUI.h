#pragma once
#include"UI.h"
#include"GameManager.h"
class COptionUI : public CUI
{
private:
	int cursorIdx;
	PLAYER_TYPE curPlayerType;

	CGameManager* gameMgr;
public:
	COptionUI();
	COptionUI(CGameManager* mgr);
	~COptionUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enter();
	virtual void exit();

	void cursorMove();
	void turnOver();
	void closeOptionUI();
};

