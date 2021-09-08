#pragma once
#include"gameNode.h"
#include"MapTool.h"
#include"MapToolSub.h"
class CMapToolMgr : public gameNode
{
private:
	CMapTool* mapTool;
	CMapToolSub* mapToolSub;
public:
	CMapToolMgr();
	~CMapToolMgr();

	HRESULT init();
	void release();
	void update();
	void render();
};

