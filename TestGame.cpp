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

	if (InputManager->isOnceKeyDown('G')) addUnitToMgr(UNIT_TYPE::INFANTRY);
	if (InputManager->isOnceKeyDown('H')) addUnitToMgr(UNIT_TYPE::MECH);
	if (InputManager->isOnceKeyDown('J')) addUnitToMgr(UNIT_TYPE::TANK);
	if (InputManager->isOnceKeyDown('K')) addUnitToMgr(UNIT_TYPE::ARTILLERY);
	if (InputManager->isOnceKeyDown('L')) addUnitToMgr(UNIT_TYPE::APC);
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

void CTestGame::addUnitToMgr(UNIT_TYPE type)
{
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		if (map->getTile()[idx]->getPos() == cursor && map->getTile()[idx]->getUnitType() == UNIT_TYPE::NONE)
		{
			map->getTile()[idx]->setUnitType(type);
			switch (type)
			{
			case UNIT_TYPE::NONE:
				break;
			case UNIT_TYPE::INFANTRY:
				unitMgr->addUnit(UNIT_TYPE::INFANTRY, cursor);
				break;
			case UNIT_TYPE::MECH:
				unitMgr->addUnit(UNIT_TYPE::MECH, cursor);
				break;
			case UNIT_TYPE::TANK:
				unitMgr->addUnit(UNIT_TYPE::TANK, cursor);
				break;
			case UNIT_TYPE::ARTILLERY:
				unitMgr->addUnit(UNIT_TYPE::ARTILLERY, cursor);
				break;
			case UNIT_TYPE::APC:
				unitMgr->addUnit(UNIT_TYPE::APC, cursor);
			default:
				break;
			}
			break;
		}
	}
}
