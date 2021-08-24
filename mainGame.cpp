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

	_astar = new Astar;
	_astar->init();

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	//SCENE->release();
	SAFE_DELETE(_astar);
}

void mainGame::update()
{

	gameNode::update();
	//SCENE->update();
	//ANIMATION->update();
	//EFFECT->update();
	_astar->update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	//IMAGE->render("���ȭ��", getMemDC());
	
	//SCENE->render();
	//EFFECT->render();
	//==============================================
	_astar->render();
	TIME->render(getMemDC());


	//������� ������ HDC�׸���.(�ǵ帮�� ����.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

