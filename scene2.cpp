#include "framework.h"
#include "scene2.h"

scene2::scene2()
{
}

scene2::~scene2()
{
}

HRESULT scene2::init()
{


    IMAGE->addImage("����1", "images/����.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
    return S_OK;
}

void scene2::release()
{
}

void scene2::update()
{
	if (InputManager->isOnceKeyDown('1'))
	{
		//��ü����
		SCENE->changeScene("scene1");
	}
}

void scene2::render()
{
    IMAGE->render("����1", getMemDC());
}
