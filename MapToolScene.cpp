#include "framework.h"
#include "MapToolScene.h"

CMapToolScene::CMapToolScene() :
	mapToolMgr(new CMapToolMgr)
{
}

CMapToolScene::~CMapToolScene()
{
	SAFE_DELETE(mapToolMgr);
}

HRESULT CMapToolScene::init()
{
	mapToolMgr->init();
	return S_OK;
}

void CMapToolScene::release()
{
	mapToolMgr->release();
}

void CMapToolScene::update()
{
	mapToolMgr->update();
}

void CMapToolScene::render()
{
	mapToolMgr->render();
}
