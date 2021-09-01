#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	//maptool = new CMapTool;
	//maptool->init();
	//SUBWIN->init();
	//SUBWIN->SetMapLink(maptool);
	//SUBWIN->SetScene(new CMapToolSub);
	gameMgr = new CGameManager;
	gameMgr->init();
	//test = new CTestGame;
	//test->init();
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
	//maptool->update();
	//SUBWIN->update();
	//test->update();
	gameMgr->update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	gameNode::render();
	//maptool->render();
	//SUBWIN->render();
	//test->render();
	gameMgr->render();
	TIME->render(getMemDC());
	//==============================================
	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	RECT rc = checkGameSize();
	this->getBackBuffer()->stretchRender(getHDC(), RectCenterX(rc), RectCenterY(rc), RectWidth(rc), RectHeight(rc));
}

RECT mainGame::checkGameSize()
{
	RECT rc = this->getClientRC();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)WINSIZEX / WINSIZEY;
	float heiOverWid = (float)WINSIZEY / WINSIZEX;

	float w, h;
	//현재 가로에 맞춘 세로가 현재 창의 세로보다 크다면, 현재 세로에 맞춘다.
	(wid * heiOverWid > hei) ? w = hei * widOverHei, h = hei
		: w = wid, h = w * heiOverWid;

	int left, top, right, bottom;
	if (w < wid) {
		left = wid / 2 - w / 2;
		right = left + w;
		top = 0;
		bottom = h;
	}
	else {
		left = 0;
		right = w;
		top = hei / 2 - h / 2;
		bottom = top + h;
	}
	return { left, top, right, bottom };
}

