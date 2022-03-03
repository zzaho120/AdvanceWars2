#pragma once
#include"gameNode.h"

class CGameResult : public gameNode
{
private:
	CGameManager* gameMgr;
	int bgAlpha;
	int resultIdx;

	int vitory;
	int lose;
	int winner;
	int loser;
	
	Vec2 vitoryPlayer;
	Vec2 losePlayer;
	Vec2 vitoryInfo;
	Vec2 loseInfo;
public:
	CGameResult();
	~CGameResult();

	HRESULT init();
	HRESULT init(CGameManager* mgr);
	void release();
	void update();
	void render();

	void pageMove();
	void settingData();
	void inputKey();
};

