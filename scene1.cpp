#include "framework.h"
#include "scene1.h"

scene1::scene1()
{
}

scene1::~scene1()
{
}

HRESULT scene1::init()
{
	IMAGE->addImage("�糪1", "images/�糪.bmp", WINSIZEX, WINSIZEY,true,RGB(255,0,255));

	return S_OK;
}

void scene1::release()
{
}

void scene1::update()
{
	if (InputManager->isOnceKeyDown('2'))
	{
		//��ü����
		SCENE->changeScene("scene2");
	}
}

void scene1::render()
{
	IMAGE->render("�糪1", getMemDC());
}
