#include "framework.h"
#include "MapTool.h"

CMapTool::CMapTool() :
	map(new CMap({ 35, 35 }, { TILE_SIZE_X, TILE_SIZE_Y })),
	cam(new CCamera),
	cursor({ map->getTile()[31]->getPos().x, map->getTile()[31]->getPos().y })
{ }

CMapTool::~CMapTool()
{
}

HRESULT CMapTool::init()
{
	ANIMATION->start("cursor_ani");
	map->setCameraLink(cam);
	return S_OK;
}

void CMapTool::release()
{

}

void CMapTool::update()
{
	map->update();
	cam->setTargetVec2(cursor);
	cam->update();
	cursorMove();
}

void CMapTool::render()
{
	map->render();
	IMAGE->findImage("cursor")->aniRender(getMapDC(), cursor.x - 32, cursor.y - 32, ANIMATION->findAnimation("cursor_ani"));
	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
}

void CMapTool::cursorMove()
{
	if (InputManager->isOnceKeyDown(VK_LEFT)) cursor.x -= TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_RIGHT)) cursor.x += TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_UP)) cursor.y -= TILE_SIZE_Y;
	else if (InputManager->isOnceKeyDown(VK_DOWN)) cursor.y += TILE_SIZE_Y;
}
