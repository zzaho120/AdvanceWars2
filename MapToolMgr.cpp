#include "framework.h"
#include "MapToolMgr.h"

CMapToolMgr::CMapToolMgr() :
    mapTool(nullptr),
    mapToolSub(nullptr)
{
}

CMapToolMgr::~CMapToolMgr()
{
	SUBWIN->subWindowClose();
	SUBWIN->release();
	mapTool->release();
	SAFE_DELETE(mapTool);
	mapToolSub->release();
	SAFE_DELETE(mapToolSub);
}

HRESULT CMapToolMgr::init()
{
	SOUND->play("maptool", 0.5F);
	mapTool = new CMapTool;
	mapToolSub = new CMapToolSub;
	mapTool->init();
	mapToolSub->init();
	SUBWIN->init();
	SUBWIN->SetMapLink(mapTool);
	SUBWIN->SetScene(mapToolSub);
    return E_NOTIMPL;
}

void CMapToolMgr::release()
{
	SUBWIN->subWindowClose();
	SUBWIN->release();
	mapTool->release();
	SAFE_DELETE(mapTool);
	mapToolSub->release();
	SAFE_DELETE(mapToolSub);
}

void CMapToolMgr::update()
{
	mapTool->update();
	SUBWIN->update();
}

void CMapToolMgr::render()
{
	mapTool->render();
	SUBWIN->render();
}
