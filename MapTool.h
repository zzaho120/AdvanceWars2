#pragma once
#include "gameNode.h"
#include "Map.h"
class CMapTool : public gameNode
{
private:
	CMap* map;

	Vec2 cursor;
public:
	CMapTool();
	~CMapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
};