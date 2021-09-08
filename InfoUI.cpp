#include "framework.h"
#include "InfoUI.h"

CInfoUI::CInfoUI() : 
	CUI(UI_TYPE::INFO_UI), 
	curPlayerType(PLAYER_TYPE::NONE),
	gameMgr(nullptr)
{
}

CInfoUI::CInfoUI(CGameManager* mgr) :
    CUI(UI_TYPE::INFO_UI),
    panelPos({ 750, 50 }),
    infoPos({ 850, 550 }),
    curPlayerType(PLAYER_TYPE::PLAYER1),
	gameMgr(mgr)
{
}

CInfoUI::~CInfoUI()
{
}

HRESULT CInfoUI::init()
{
	return S_OK;
}

void CInfoUI::release()
{
}

void CInfoUI::update()
{
}

void CInfoUI::render()
{
    switch (curPlayerType)
    {
    case PLAYER_TYPE::PLAYER1:
        IMAGE->render("infoUI_gold_red", getMemDC(), panelPos.x, panelPos.y);
        break;
    case PLAYER_TYPE::PLAYER2:
        IMAGE->render("infoUI_gold_blue", getMemDC(), panelPos.x, panelPos.y);
        break;
    }

    infoRender();

    int curMoney = gameMgr->getCurPlayer()->getMoney();
    int curTurn = gameMgr->getGameData()->getTurn();
    if(curMoney > 99999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 60, panelPos.y + 10, curMoney % 1000000 / 100000, 0); // 100000의 자리
    if(curMoney > 9999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 90, panelPos.y + 10, curMoney % 100000 / 10000, 0); // 10000의 자리
    if (curMoney > 999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 120, panelPos.y + 10, curMoney % 10000 / 1000, 0); // 1000의 자리
    if (curMoney > 99)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 150, panelPos.y + 10, curMoney % 1000 / 100, 0); // 100의 자리
    if (curMoney > 9)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 180, panelPos.y + 10, curMoney % 100 / 10, 0); // 10의 자리
    IMAGE->frameRender("number", getMemDC(), panelPos.x + 210, panelPos.y + 10, curMoney % 10, 0); // 1의 자리.
    
    if (curTurn > 9)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 20, panelPos.y + 55, curTurn % 100 / 10, 0); // 10의 자리
    IMAGE->frameRender("number", getMemDC(), panelPos.x + 50, panelPos.y + 55, curTurn % 10, 0); // 1의 자리.
    IMAGE->render("turn", getMemDC(), panelPos.x + 80, panelPos.y + 55);
}

void CInfoUI::enter()
{
    curPlayerType = gameMgr->getCurPlayer()->getPlayerType();
}

void CInfoUI::exit()
{
    curPlayerType = PLAYER_TYPE::NONE;
}

void CInfoUI::infoRender()
{
    int cursorIdx = gameMgr->getCursor()->getCursorIdx();
    bool isUnitOnCursor = gameMgr->getMap()->getTile()[cursorIdx]->getUnitType() != UNIT_TYPE::NONE;
    PLAYER_TYPE playerType = PLAYER_TYPE::NONE;
    UNIT_TYPE unitType = UNIT_TYPE::NONE;

    Vec2 tileRenderFrame = 0;
    int tileNameRenderFrame = 0;
    Vec2 unitRenderFrame = 0;
    CUnit* curUnit = nullptr;
    int unitnameRenderFrame = 0;
    float unitHP = 0;
    int fuel = 0;
    int ammo = 0;
    int capturePoint = 0;
    int defense = gameMgr->getMap()->getTile()[cursorIdx]->getDefense();

    if (isUnitOnCursor)
    {
        for (int idx = 0; idx < gameMgr->getUnitMgr()->getVecUnit().size(); idx++)
        {
            if (gameMgr->getUnitMgr()->getVecUnit()[idx]->getTileIdx() == cursorIdx)
            {
                curUnit = gameMgr->getUnitMgr()->getVecUnit()[idx];
                unitHP = curUnit->getHP();
                fuel = curUnit->getFuel();
                ammo = curUnit->getAmmo();
                unitType = curUnit->getUnitType();
                playerType = curUnit->getPlayerType();
                break;
            }
        }

        IMAGE->alphaRender("black_info2", getMemDC(), infoPos.x - 150, infoPos.y, 100);
       
        switch (unitType)
        {
        case UNIT_TYPE::INFANTRY:
            unitnameRenderFrame = 0;
            if (playerType == PLAYER_TYPE::PLAYER1)
                unitRenderFrame = { 0, 0 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                unitRenderFrame = { 0, 1 };
            break;
        case UNIT_TYPE::MECH:
            unitnameRenderFrame = 1;
            if (playerType == PLAYER_TYPE::PLAYER1)
                unitRenderFrame = { 1, 0 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                unitRenderFrame = { 1, 1 };
            break;
        case UNIT_TYPE::TANK:
            unitnameRenderFrame = 2;
            if (playerType == PLAYER_TYPE::PLAYER1)
                unitRenderFrame = { 2, 0 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                unitRenderFrame = { 2, 1 };
            break;
        case UNIT_TYPE::ARTILLERY:
            unitnameRenderFrame = 3;
            if (playerType == PLAYER_TYPE::PLAYER1)
                unitRenderFrame = { 3, 0 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                unitRenderFrame = { 3, 1 };
            break;
        case UNIT_TYPE::APC:
            unitnameRenderFrame = 4;
            if (playerType == PLAYER_TYPE::PLAYER1)
                unitRenderFrame = { 4, 0 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                unitRenderFrame = { 4, 1 };
            break;
        }

        IMAGE->frameRender("unit_type", getMemDC(), infoPos.x - 150 + 43, infoPos.y + 20, unitRenderFrame.x, unitRenderFrame.y);
        IMAGE->frameRender("unit_name", getMemDC(), infoPos.x - 150 + 25, infoPos.y - 21, unitnameRenderFrame, 0);

        
        IMAGE->frameRender("info_icon", getMemDC(), infoPos.x - 150 + 20, infoPos.y + 90, 0, 0);
        if (unitHP > 9)
            IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 60, infoPos.y + 95, 1, 0);
        IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 88, infoPos.y + 95, static_cast<int>(floor(unitHP)) % 10, 0);

        IMAGE->frameRender("info_icon", getMemDC(), infoPos.x - 150 + 20, infoPos.y + 130, 1, 0);
        if (fuel > 9)
            IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 60, infoPos.y + 135, fuel / 10, 0);
        IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 88, infoPos.y + 135, fuel % 10, 0);

        IMAGE->frameRender("info_icon", getMemDC(), infoPos.x - 150 + 20, infoPos.y + 170, 4, 0);
        if (ammo > 9)
            IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 60, infoPos.y + 175, ammo / 10, 0);
        IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 88, infoPos.y + 175, ammo % 10, 0);
    }
    else
    {
        IMAGE->alphaRender("black_info1", getMemDC(), infoPos.x, infoPos.y, 100);
    }
    bool isBuildingOnCursor = gameMgr->getMap()->getTile()[gameMgr->getCursor()->getCursorIdx()]->getBuildtype() != BUILDING_TYPE::NONE;
    if (isBuildingOnCursor)
    {
        BUILDING_TYPE buildingType = gameMgr->getMap()->getTile()[cursorIdx]->getBuildtype();
        playerType = gameMgr->getMap()->getTile()[cursorIdx]->getPlayerType();
        switch (buildingType)
        {
        case BUILDING_TYPE::CITY:
            tileNameRenderFrame = 7;
            if (playerType == PLAYER_TYPE::PLAYER1)
                tileRenderFrame = { 0, 1 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                tileRenderFrame = { 1, 1 };
            else if (playerType == PLAYER_TYPE::NONE)
                tileRenderFrame = { 5, 1 };
            break;
        case BUILDING_TYPE::HEADQUATERS:
            tileNameRenderFrame = 9;
            if (playerType == PLAYER_TYPE::PLAYER1)
                tileRenderFrame = { 0, 3 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                tileRenderFrame = { 1, 3 };
            else if (playerType == PLAYER_TYPE::NONE)
                tileRenderFrame = { 5, 3 };
            break;
        case BUILDING_TYPE::FACTORY:
            tileNameRenderFrame = 8;
            if (playerType == PLAYER_TYPE::PLAYER1)
                tileRenderFrame = { 0, 2 };
            else if (playerType == PLAYER_TYPE::PLAYER2)
                tileRenderFrame = { 1, 2 };
            else if (playerType == PLAYER_TYPE::NONE)
                tileRenderFrame = { 5, 2 };
            break;
        }

        for (int idx = 0; idx < gameMgr->getBuildingMgr()->getVecBuilding().size(); idx++)
        {
            if (gameMgr->getBuildingMgr()->getVecBuilding()[idx]->getTileIdx() == cursorIdx)
            {
                capturePoint = gameMgr->getBuildingMgr()->getVecBuilding()[idx]->getCapturePoint();
                break;
            }
        }
        IMAGE->frameRender("info_icon", getMemDC(), infoPos.x + 20, infoPos.y + 130, 3, 0);
        if (capturePoint > 9)
            IMAGE->frameRender("number", getMemDC(), infoPos.x + 60, infoPos.y + 135, capturePoint / 10, 0);
        IMAGE->frameRender("number", getMemDC(), infoPos.x + 88, infoPos.y + 135, capturePoint % 10, 0);
    }
    else
    {
        switch (gameMgr->getMap()->getTile()[gameMgr->getCursor()->getCursorIdx()]->getTileType())
        {
        case ENVIRONMENT_TYPE::PLAIN:
            tileNameRenderFrame = 0;
            tileRenderFrame = { 0, 0 };
            break;
        case ENVIRONMENT_TYPE::WOOD:
            tileNameRenderFrame = 1;
            tileRenderFrame = { 1, 0 };
            break;
        case ENVIRONMENT_TYPE::MOUNTAIN:
            tileNameRenderFrame = 2;
            tileRenderFrame = { 2, 0 };
            break;
        case ENVIRONMENT_TYPE::BRIDGE:
            tileNameRenderFrame = 6;
            tileRenderFrame = { 6, 0 };
            break;
        case ENVIRONMENT_TYPE::RIVER:
        case ENVIRONMENT_TYPE::RIVER_LINE:
        case ENVIRONMENT_TYPE::RIVER_CURVE:
        case ENVIRONMENT_TYPE::RIVER_3WAYS:
        case ENVIRONMENT_TYPE::RIVER_4WAYS:
            tileNameRenderFrame = 4;
            tileRenderFrame = { 4, 0 };
            break;
        case ENVIRONMENT_TYPE::ROAD:
        case ENVIRONMENT_TYPE::ROAD_LINE:
        case ENVIRONMENT_TYPE::ROAD_CURVE:
        case ENVIRONMENT_TYPE::ROAD_3WAYS:
        case ENVIRONMENT_TYPE::ROAD_4WAYS:
            tileNameRenderFrame = 5;
            tileRenderFrame = { 5, 0 };
            break;
        case ENVIRONMENT_TYPE::SEA:
        case ENVIRONMENT_TYPE::SEA_2WAYS:
        case ENVIRONMENT_TYPE::SEA_3WAYS:
        case ENVIRONMENT_TYPE::SEA_4WAYS:
        case ENVIRONMENT_TYPE::SEA_5WAYS:
        case ENVIRONMENT_TYPE::SEA_6WAYS:
        case ENVIRONMENT_TYPE::SEA_7WAYS:
        case ENVIRONMENT_TYPE::SEA_8WAYS:
        case ENVIRONMENT_TYPE::SEA_VERTICAL00:
        case ENVIRONMENT_TYPE::SEA_VERTICAL01:
        case ENVIRONMENT_TYPE::SEA_VERTICAL02:
        case ENVIRONMENT_TYPE::SEA_HORIZONTAL00:
        case ENVIRONMENT_TYPE::SEA_HORIZONTAL01:
        case ENVIRONMENT_TYPE::SEA_HORIZONTAL02:
        case ENVIRONMENT_TYPE::SEA_NOWAYS:
            tileNameRenderFrame = 3;
            tileRenderFrame = { 3, 0 };
            break;
        }
    }
    IMAGE->frameRender("tileTool_frame", getMemDC(), infoPos.x + 43, infoPos.y + 21, tileRenderFrame.x, tileRenderFrame.y);    
    IMAGE->frameRender("tile_name", getMemDC(), infoPos.x + 25, infoPos.y - 20, tileNameRenderFrame, 0);

    IMAGE->frameRender("info_icon", getMemDC(), infoPos.x + 20, infoPos.y + 90, 2, 0);
    IMAGE->frameRender("number", getMemDC(), infoPos.x + 60, infoPos.y + 95, defense, 0);

    if (gameMgr->isAttackMode() && gameMgr->isUnitOnCursor())
    {
        IMAGE->render("damageUI", getMemDC(), infoPos.x - 150 + 30, infoPos.y - 95);
        if (gameMgr->predictDamaged() > 9)
            IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 43, infoPos.y - 60, gameMgr->predictDamaged() / 10, 0);
        IMAGE->frameRender("number", getMemDC(), infoPos.x - 150 + 43 + 25, infoPos.y - 60, gameMgr->predictDamaged() % 10, 0);
    }
}