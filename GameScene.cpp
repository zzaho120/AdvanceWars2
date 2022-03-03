#include "framework.h"
#include "GameScene.h"

CGameScene::CGameScene() :
	gameMgr(nullptr)
{
}

CGameScene::~CGameScene()
{
	SAFE_DELETE(gameMgr);
}

HRESULT CGameScene::init()
{
	gameMgr = new CGameManager;
	gameMgr->init();
	return S_OK;
}

void CGameScene::release()
{
	SAFE_DELETE(gameMgr);
}

void CGameScene::update()
{
	gameMgr->update();
}

void CGameScene::render()
{
	gameMgr->render();
}
