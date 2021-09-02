#pragma once
#include "UI.h"
#include "GameManager.h"
class CFactoryUI : public CUI
{
private:
	int cursorIdx;
	PLAYER_TYPE curPlayerType;

	CGameManager* gameMgr;
public:
	CFactoryUI();
	CFactoryUI(CGameManager* mgr);
	~CFactoryUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enter();
	virtual void exit();

	void cursorMove();
	void unitGenerate();
	void closeFactoryUI();
};