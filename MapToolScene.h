#pragma once
#include"gameNode.h"
#include"MapToolMgr.h"
class CMapToolScene : public gameNode
{
private:
	CMapToolMgr* mapToolMgr;
public:
	CMapToolScene();
	~CMapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

