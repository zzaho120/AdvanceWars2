#pragma once
#include "Object.h"

class CGameManager;
class CCursor : public CObject
{
private:
	int tileIdx;

	CGameManager* gameMgr;
public:
	CCursor();
	CCursor(Vec2 pos, int tileIndex);
	~CCursor();

	HRESULT init();
	HRESULT init(CGameManager* mgr);
	void release();
	void update();
	void render();

	void cursorMove();
	
	int getCursorIdx() { return tileIdx; }
};