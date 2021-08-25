#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
class CMapTool : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	Vec2 cursor;

	//vector<CObject*>
public:
	CMapTool();
	~CMapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();

	//void subscribe(CObject* obj);
	//void unsubscribe(CObject* obj);
};