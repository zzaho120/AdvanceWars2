#include "framework.h"
#include "FactoryUI.h"

CFactoryUI::CFactoryUI() :
    CUI(UI_TYPE::FACTORY_UI), cursorIdx(0), curPlayerType(PLAYER_TYPE::NONE),
    gameMgr(nullptr)
{
}

CFactoryUI::CFactoryUI(CGameManager* mgr) :
    CUI(UI_TYPE::FACTORY_UI), cursorIdx(0), curPlayerType(PLAYER_TYPE::NONE),
    gameMgr(mgr)
{
}

CFactoryUI::~CFactoryUI()
{
}

HRESULT CFactoryUI::init()
{
    return S_OK;
}

void CFactoryUI::release()
{
}

void CFactoryUI::update()
{
    if (isActive && curPlayerType != PLAYER_TYPE::NONE)
    {
        cursorMove();
        unitGenerate();
        closeFactoryUI();
    }
}

void CFactoryUI::render()
{
    if (isActive)
    {
        switch (curPlayerType)
        {
        case PLAYER_TYPE::PLAYER1:
            IMAGE->render("factory_panel_red", getMapDC(), 100, 100);
            break;
        case PLAYER_TYPE::PLAYER2:
            IMAGE->render("factory_panel_blue", getMapDC(), 100, 100);
            break;
        default:
            break;
        }
        IMAGE->render("factory_arrow", getMapDC(), 100, 100 + cursorIdx * 100);
    }
}

void CFactoryUI::enter()
{
    curPlayerType = gameMgr->getCurPlayer()->getPlayerType();
    cursorIdx = 0;
    isActive = true;
}

void CFactoryUI::exit()
{
    curPlayerType = PLAYER_TYPE::NONE;
    cursorIdx = 0;
    isActive = false;
}

void CFactoryUI::cursorMove()
{
    if (InputManager->isOnceKeyDown(VK_UP) && cursorIdx > 0) cursorIdx--;
    else if (InputManager->isOnceKeyDown(VK_DOWN) && cursorIdx < UNIT_MAX_NUM) cursorIdx++;
}

void CFactoryUI::unitGenerate()
{
    if (InputManager->isOnceKeyDown('Z'))
    {
        gameMgr->generateUnitMsg(static_cast<UNIT_TYPE>(cursorIdx + 1));
        exit();
    }
}

void CFactoryUI::closeFactoryUI()
{
    if (InputManager->isOnceKeyDown('X'))
    {
        exit();
    }
}
