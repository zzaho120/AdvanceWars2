#pragma once
#include"gameNode.h"
#include "Camera.h"
#include "Map.h"

class CTestGame : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	Vec2 cursor;
public:
	CTestGame();
	~CTestGame();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
};