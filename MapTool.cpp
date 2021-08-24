#include "framework.h"
#include "MapTool.h"

CMapTool::CMapTool() :
	map(new CMap({ 35, 35 }, { TILE_SIZE_X, TILE_SIZE_Y })),
	cursor({ map->getTile()[31]->getPos().x, map->getTile()[31]->getPos().y })
{ }

CMapTool::~CMapTool()
{
}

HRESULT CMapTool::init()
{
	ANIMATION->start("cursor_ani");
	return S_OK;
}

void CMapTool::release()
{

}

void CMapTool::update()
{
	map->update();
	cursorMove();
}

void CMapTool::render()
{
	map->render();
	IMAGE->findImage("cursor")->aniRender(getMemDC(), cursor.x - 32, cursor.y - 32, ANIMATION->findAnimation("cursor_ani"));
}

void CMapTool::cursorMove()
{
	if (InputManager->isOnceKeyDown(VK_LEFT)) cursor.x -= TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_RIGHT)) cursor.x += TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_UP)) cursor.y -= TILE_SIZE_Y;
	else if (InputManager->isOnceKeyDown(VK_DOWN)) cursor.y += TILE_SIZE_Y;
}
