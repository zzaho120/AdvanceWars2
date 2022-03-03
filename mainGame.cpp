#include"framework.h"
#include "mainGame.h"
#include"GameScene.h"
#include"MapToolScene.h"
#include"MainMenuScene.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	SCENE->addScene("gameScene", new CGameScene);
	SCENE->addScene("mapToolScene", new CMapToolScene);
	SCENE->addScene("mainMenuScene", new CMainMenuScene);
	SCENE->changeScene("mainMenuScene");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	
	gameNode::update();
	SCENE->update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	gameNode::render();
	SCENE->render();/*
	TIME->render(getMemDC()); 
	TCHAR str[128];
	wsprintf(str, "%d ���ƾƾƤ�", SOUND->getSize());
	TextOut(getMemDC(), 100, 100, str, strlen(str));*/
	//==============================================
	//������� ������ HDC�׸���.(�ǵ帮�� ����.)
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
	//���� ���ο� ���� ���ΰ� ���� â�� ���κ��� ũ�ٸ�, ���� ���ο� �����.
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

