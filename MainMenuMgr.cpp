#include "framework.h"
#include "MainMenuMgr.h"

CMainMenuMgr::CMainMenuMgr() :
	selectIdx(0), titleAlpha(0),
	menuAlpha(0), isGuide(false),
	isTitle(true), guideIdx(0)
{
	memset(guideStr, 0, sizeof(guideStr));
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
	guideStrSetting();
}

void CMainMenuMgr::render()
{
	static int frameX = 0;
	static int frameY = 0;
	
	IMAGE->render("black", getMemDC());

	if (isTitle)
	{
		IMAGE->alphaRender("title", getMemDC(), 0, 0, titleAlpha);

		if (titleAlpha > 254)
		{
			IMAGE->frameRender("key", getMemDC(), 450, 600, 0, 0);
			TextOut(getMemDC(), 515, 605, "시작", strlen("시작"));
		}
	}
	else
	{
		IMAGE->loopAlphaRender("mainmenu_bg", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), frameX++, frameY++, menuAlpha);
		IMAGE->alphaRender("mainmenu_selectmode", getMemDC(), 40, 40, menuAlpha);
		IMAGE->alphaRender("mainmenu_catherine", getMemDC(), 680, 60, menuAlpha);
		IMAGE->alphaRender("black", getMemDC(), 0, 700, menuAlpha);

		if (menuAlpha > 254)
		{
			IMAGE->frameRender("key", getMemDC(), 700, 710, 0, 0);
			TextOut(getMemDC(), 760, 715, "선택", strlen("선택"));
			//IMAGE->frameRender("key", getMemDC(), 850, 710, 1, 0);
		}
		
		if (selectIdx != 0)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 200, 0, 0, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 200, 0, 0, menuAlpha);
		if (selectIdx != 1)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 300, 0, 1, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 300, 0, 1, menuAlpha);
		if (selectIdx != 2)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 400, 0, 2, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 400, 0, 2, menuAlpha);
		if (selectIdx != 3)
			IMAGE->alphaFrameRender("mainmenu_menu_small", getMemDC(), 20, 500, 0, 3, menuAlpha);
		else
			IMAGE->alphaFrameRender("mainmenu_menu", getMemDC(), 20, 500, 0, 3, menuAlpha);

		if (isGuide)
			IMAGE->frameRender("help", getMemDC(), 200, 0, guideIdx, 0);
		if (menuAlpha > 254 && !isGuide)
			TextOut(getMemDC(), 50, 720, guideStr, strlen(guideStr));
		
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
				SOUND->play("select_menu", 0.4F);
			}
		}
	}
	else
	{
		if (menuAlpha < 255)
		{
			if(menuAlpha == 3)
				SOUND->play("mainmenu", 0.5F);
			if(menuAlpha == 90)
				SOUND->stop("select_menu");
			menuAlpha += 3;
		}
		if (menuAlpha > 254 && !isGuide)
		{
			if (InputManager->isOnceKeyDown('Z'))
			{
				chooseMenu();
			}
			else 
			{
				SOUND->stop("select_menu");
			}
			if (InputManager->isOnceKeyDown(VK_UP))
			{
				guideStrSetting();
				selectIdx--;
				if (SOUND->isPlaySound("move_menu"))
					SOUND->stop("move_menu");
				if (!SOUND->isPlaySound("move_menu"))
					SOUND->play("move_menu", 0.4F);
			}
			else if (InputManager->isOnceKeyDown(VK_DOWN))
			{
				guideStrSetting();
				selectIdx++;
				if (SOUND->isPlaySound("move_menu"))
					SOUND->stop("move_menu");
				if (!SOUND->isPlaySound("move_menu"))
					SOUND->play("move_menu", 0.4F);
			}

			if (selectIdx < 0) selectIdx = 3;
			if (selectIdx > 3) selectIdx = 0;
		}
		else if (isGuide)
		{
			if (InputManager->isOnceKeyDown(VK_LEFT))
			{
				guideIdx--;
				if (SOUND->isPlaySound("move_menu"))
					SOUND->stop("move_menu");
				if (!SOUND->isPlaySound("move_menu"))
					SOUND->play("move_menu", 0.4F);
			}
			else if (InputManager->isOnceKeyDown(VK_RIGHT))
			{
				guideIdx++;
				if (SOUND->isPlaySound("move_menu"))
					SOUND->stop("move_menu");
				if (!SOUND->isPlaySound("move_menu"))
					SOUND->play("move_menu", 0.4F);
			}
			else if (InputManager->isOnceKeyDown('X'))
			{
				isGuide = false;
			}

			if (guideIdx < 0) guideIdx = 0;
			if (guideIdx > 16) guideIdx = 16;
		}
	}

}

void CMainMenuMgr::guideStrSetting()
{
	switch (selectIdx)
	{
	case 0:
		strcpy(guideStr, "어드밴스 워즈2 게임을 시작합니다.");
		break;
	case 1:
		strcpy(guideStr, "맵툴을 사용하여 직접 맵을 만듭니다.");
		break;
	case 2:
		strcpy(guideStr, "게임 방법을 알려주는 도움말을 봅니다.");
		break;
	case 3:
		strcpy(guideStr, "게임을 종료합니다.");
		break;
	}
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
		isGuide = true;
		break;
	case 3:
		PostQuitMessage(0);
		break;
	}
}
