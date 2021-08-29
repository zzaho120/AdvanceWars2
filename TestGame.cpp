#include "framework.h"
#include "TestGame.h"

CTestGame::CTestGame() :
	map(new CMap("save/spannisland.map")),
	cam(new CCamera),
	cursor({ map->getTile()[158]->getPos().x, map->getTile()[158]->getPos().y }),
	unitMgr(new CUnitManager)
	/*unit(new CUnit(UNIT_TYPE::APC, 99, 3, 0b0000,
		{ map->getTile()[158]->getPos().x - TILE_SIZE_X / 2, 
		map->getTile()[158]->getPos().y - TILE_SIZE_Y / 2 }))*/
{
}

CTestGame::~CTestGame()
{
}

HRESULT CTestGame::init()
{
	ANIMATION->start("cursor_ani");
	map->setCameraLink(cam);
	unitMgr->init();
	unitMgr->addUnit(UNIT_TYPE::INFANTRY, { map->getTile()[212]->getPos().x, map->getTile()[212]->getPos().y });
	unitMgr->addUnit(UNIT_TYPE::MECH, { map->getTile()[216]->getPos().x, map->getTile()[216]->getPos().y });
	unitMgr->addUnit(UNIT_TYPE::TANK, { map->getTile()[188]->getPos().x, map->getTile()[188]->getPos().y });
	unitMgr->addUnit(UNIT_TYPE::ARTILLERY, { map->getTile()[66]->getPos().x, map->getTile()[66]->getPos().y });
	unitMgr->addUnit(UNIT_TYPE::APC, { map->getTile()[93]->getPos().x, map->getTile()[93]->getPos().y });

	return S_OK;
}

void CTestGame::release()
{
}

void CTestGame::update()
{
	cam->update(); 
	map->update();
	//cam->setTargetVec2(cursor);
	cursorMove();
	unitMgr->update();
}

void CTestGame::render()
{
	map->render();
	unitMgr->render();
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
