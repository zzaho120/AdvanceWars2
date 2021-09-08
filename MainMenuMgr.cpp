#include "framework.h"
#include "MainMenuMgr.h"

CMainMenuMgr::CMainMenuMgr() :
	selectIdx(0), titleAlpha(0),
	menuAlpha(0),
	isTitle(true)
{
	SOUND->play("title", 0.5F);
}

CMainMenuMgr::~CMainMenuMgr()
{
}

HRESULT CMainMenuMgr::init()
{
	selectIdx = 0;
	titleAlpha = 0;
	menuAlpha = 0;
	return S_OK;
}

void CMainMenuMgr::release()
{
}

void CMainMenuMgr::update()
{
	menuInput();
}

void CMainMenuMgr::render()
{
	static int frameX = 0;
	static int frameY = 0;
	
	IMAGE->render("black", getMemDC());

	if (isTitle)
	{
		IMAGE->alphaRender("title", getMemDC(), 0, 0, titleAlpha);
	}
	else
	{
		IMAGE->loopAlphaRender("mainmenu_bg", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), frameX++, frameY++, menuAlpha);
		IMAGE->alphaRender("mainmenu_selectmode", getMemDC(), 40, 40, menuAlpha);
		IMAGE->alphaRender("mainmenu_catherine", getMemDC(), 680, 60, menuAlpha);

		if (selectIdx != 0)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 200, 0, 0, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 200, 0, 0, menuAlpha);
		if (selectIdx != 1)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 350, 0, 1, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 350, 0, 1, menuAlpha);
		if (selectIdx != 2)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 500, 0, 2, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 500, 0, 2, menuAlpha);
	}
}

void CMainMenuMgr::menuInput()
{
	if (isTitle)
	{
		if (titleAlpha < 255) titleAlpha += 3;
		if (titleAlpha > 254)
		{
			if (InputManager->isOnceKeyDown('Z'))
			{
				isTitle = false;
				SOUND->stop("title");
			}
		}
	}
	else
	{
		if (menuAlpha < 255)
		{
			menuAlpha += 3;
			if(menuAlpha == 3)
				SOUND->play("mainmenu", 0.5F);
		}
		if (menuAlpha > 254)
		{
			if (InputManager->isOnceKeyDown('Z'))
			{
				chooseMenu();
			}
		}
	}

	if (InputManager->isOnceKeyDown(VK_UP)) selectIdx--;
	else if (InputManager->isOnceKeyDown(VK_DOWN)) selectIdx++;

	if (selectIdx < 0) selectIdx = 2;
	if (selectIdx > 2) selectIdx = 0;
}

void CMainMenuMgr::chooseMenu()
{
	switch (selectIdx)
	{
	case 0:
		SOUND->stop("mainmenu");
		SCENE->changeScene("gameScene");
		break;
	case 1:
		SOUND->stop("mainmenu");
		SCENE->changeScene("mapToolScene");
		break;
	case 2:
		PostQuitMessage(0);
		break;
	}
}
