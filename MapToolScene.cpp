#include "framework.h"
#include "MapToolScene.h"

CMapToolScene::CMapToolScene() :
	mapTool(nullptr),
	mapToolSub(nullptr)
{
}

CMapToolScene::~CMapToolScene()
{
	SUBWIN->subWindowClose();
	SUBWIN->release();
	mapTool->release();
	SAFE_DELETE(mapTool);
	mapToolSub->release();
	SAFE_DELETE(mapToolSub);
}

HRESULT CMapToolScene::init()
{
	mapTool = new CMapTool;
	mapToolSub = new CMapToolSub;
	mapTool->init();
	mapToolSub->init();
	SUBWIN->init();
	SUBWIN->SetMapLink(mapTool);
	SUBWIN->SetScene(mapToolSub);
	return S_OK;
}

void CMapToolScene::release()
{
	SUBWIN->subWindowClose();
	SUBWIN->release();
	mapTool->release();
	SAFE_DELETE(mapTool);
	mapToolSub->release();
	SAFE_DELETE(mapToolSub);
}

void CMapToolScene::update()
{
	mapTool->update();
	SUBWIN->update();
}

void CMapToolScene::render()
{
	mapTool->render();
	SUBWIN->render();
}
