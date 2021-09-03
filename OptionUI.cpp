#include "framework.h"
#include"GameManager.h"
#include "OptionUI.h"

COptionUI::COptionUI() :
    CUI(UI_TYPE::OPTION_UI), cursorIdx(0), 
    curPlayerType(PLAYER_TYPE::NONE),
    gameMgr(nullptr)
{
}

COptionUI::COptionUI(CGameManager* mgr) :
    CUI(UI_TYPE::OPTION_UI), cursorIdx(0), 
    curPlayerType(PLAYER_TYPE::NONE),
    gameMgr(mgr)
{
}

COptionUI::~COptionUI()
{
}

HRESULT COptionUI::init()
{
    return S_OK;
}

void COptionUI::release()
{
}

void COptionUI::update()
{
    if (isActive && curPlayerType != PLAYER_TYPE::NONE)
    {
        cursorMove();
        turnOver();
        closeOptionUI();
    }
}

void COptionUI::render()
{
    if (isActive)
    {
        switch (curPlayerType)
        {
        case PLAYER_TYPE::PLAYER1:
            IMAGE->render("option_panel_red", getMemDC(), 50, 80);
            break;
        case PLAYER_TYPE::PLAYER2:
            IMAGE->render("option_panel_blue", getMemDC(), 50, 80);
            break;
        default:
            break;
        }
        IMAGE->render("factory_arrow", getMemDC(), 20, 120 + cursorIdx * 90);
    }
}

void COptionUI::enter()
{
    curPlayerType = gameMgr->getCurPlayer()->getPlayerType();
    cursorIdx = 0;
    isActive = true;
}

void COptionUI::exit()
{
    curPlayerType = PLAYER_TYPE::NONE;
    cursorIdx = 0;
    isActive = false;
}

void COptionUI::cursorMove()
{
    if (InputManager->isOnceKeyDown(VK_UP) && cursorIdx > 0) cursorIdx--;
    else if (InputManager->isOnceKeyDown(VK_DOWN) && cursorIdx < 3) cursorIdx++;
}

void COptionUI::turnOver()
{
    if (InputManager->isOnceKeyDown('Z'))
    {
        switch (cursorIdx)
        {
        case 0:
            gameMgr->changePlayerMsg();
            exit();
            break;
        }
    }
}

void COptionUI::closeOptionUI()
{
    if (InputManager->isOnceKeyDown('X'))
    {
        gameMgr->closeUIMsg();
        exit();
    }
}
