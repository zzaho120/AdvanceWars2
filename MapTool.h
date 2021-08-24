#pragma once
#include "gameNode.h"
#include "Map.h"
class CMapTool : public gameNode
{
private:
	CMap map;
public:
	CMapTool();
	~CMapTool();

	HRESULT init();
	void release();
	void update();
	void render();
};