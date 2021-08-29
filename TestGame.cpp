#include "framework.h"
#include "TestGame.h"

CTestGame::CTestGame() : 
	map(new CMap("save/spannisland.map")),
	cam(new CCamera),
	cursor({ map->getTile()[158]->getPos().x, map->getTile()[158]->getPos().y })
{
}

CTestGame::~CTestGame()
{
}

HRESULT CTestGame::init()
{
	ANIMATION->start("cursor_ani");
	map->setCameraLink(cam);
	return S_OK;
}

void CTestGame::release()
{
}

void CTestGame::update()
{
	cam->update(); 
	//cam->setTargetVec2(cursor);
	cursorMove();
}

void CTestGame::render()
{
	map->render();
	IMAGE->findImage("cursor")->aniRender(getMapDC(), cursor.x - 32, cursor.y - 32, ANIMATION->findAnimation("cursor_ani"));
	this->getMapBuffer()->render(getMemDC(), 0, 0, cam->getCam1().x, cam->getCam1().y, cam->getCamSize().x, cam->getCamSize().y);
}

void CTestGame::cursorMove()
{
	if (InputManager->isOnceKeyDown(VK_LEFT)) cursor.x -= TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_RIGHT)) cursor.x += TILE_SIZE_X;
	else if (InputManager->isOnceKeyDown(VK_UP)) cursor.y -= TILE_SIZE_Y;
	else if (InputManager->isOnceKeyDown(VK_DOWN)) cursor.y += TILE_SIZE_Y;
}
