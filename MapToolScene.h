#pragma once
#include"gameNode.h"
#include"MapTool.h"
#include"MapToolSub.h"
class CMapToolScene : public gameNode
{
private:
	CMapTool* mapTool;
	CMapToolSub* mapToolSub;
public:
	CMapToolScene();
	~CMapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

