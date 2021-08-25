#pragma once
#include"gameNode.h"
#include"MapTool.h"
#include"MapToolSub.h"
class mainGame : public gameNode
{
private:
	CMapTool* maptool;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	RECT checkGameSize();
};