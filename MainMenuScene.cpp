#include "framework.h"
#include "MainMenuScene.h"

CMainMenuScene::CMainMenuScene() : mainMenuMgr(new CMainMenuMgr)
{
}

CMainMenuScene::~CMainMenuScene()
{
    SAFE_DELETE(mainMenuMgr);
}

HRESULT CMainMenuScene::init()
{
    mainMenuMgr->init();
    return S_OK;
}

void CMainMenuScene::release()
{
    mainMenuMgr->release();
}

void CMainMenuScene::update()
{
    mainMenuMgr->update();
}

void CMainMenuScene::render()
{
    mainMenuMgr->render();
}
