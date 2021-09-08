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
            IMAGE->render("factory_panel_red", getMemDC(), 50, 120);
            switch (cursorIdx)
            {
            case 0:
                IMAGE->render("infry_red", getMemDC(), 655, 170);
                break;

            case 1:
                IMAGE->render("mech_red", getMemDC(), 655, 170);
                break;

            case 2:
                IMAGE->render("tank_red", getMemDC(), 655, 170);
                break;

            case 3:
                IMAGE->render("artil_red", getMemDC(), 655, 170);
                break;

            case 4:
                IMAGE->render("APC_red", getMemDC(), 655, 170);
                break;
            }
            break;
        case PLAYER_TYPE::PLAYER2:
            IMAGE->render("factory_panel_blue", getMemDC(), 50, 120);
            switch (cursorIdx)
            {
            case 0:
                IMAGE->render("infry_blue", getMemDC(), 655, 170);
                break;

            case 1:
                IMAGE->render("mech_blue", getMemDC(), 655, 170);
                break;

            case 2:
                IMAGE->render("tank_blue", getMemDC(), 655, 170);
                break;

            case 3:
                IMAGE->render("artil_blue", getMemDC(), 655, 170);
                break;

            case 4:
                IMAGE->render("APC_blue", getMemDC(), 655, 170);
                break;
            }
            break;
        default:
            break;
        }
        IMAGE->render("factory_arrow", getMemDC(), 30, 180 + cursorIdx * 90);
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
    if (InputManager->isOnceKeyDown(VK_UP) && cursorIdx > 0)
    {
        if (SOUND->isPlaySound("move_menu"))
            SOUND->stop("move_menu");
        if (!SOUND->isPlaySound("move_menu"))
            SOUND->play("move_menu", 0.4F);
        cursorIdx--;
    }
    else if (InputManager->isOnceKeyDown(VK_DOWN) && cursorIdx < UNIT_MAX_NUM)
    {
        if (SOUND->isPlaySound("move_menu"))
            SOUND->stop("move_menu");
        if (!SOUND->isPlaySound("move_menu"))
            SOUND->play("move_menu", 0.4F);
        cursorIdx++;
    }
}

void CFactoryUI::unitGenerate()
{
    if (InputManager->isOnceKeyDown('Z'))
    {
        int cost = 0;
        switch (static_cast<UNIT_TYPE>(cursorIdx + 1))
        {
        case UNIT_TYPE::INFANTRY:
            cost = 1000;
            break;
        case UNIT_TYPE::MECH:
            cost = 3000;
            break;
        case UNIT_TYPE::TANK:
            cost = 7000;
            break;
        case UNIT_TYPE::ARTILLERY:
            cost = 6000;
            break;
        case UNIT_TYPE::APC:
            cost = 5000;
            break;
        }

        if (cost <= gameMgr->getCurPlayer()->getMoney())
        {
            if (SOUND->isPlaySound("select"))
                SOUND->stop("select");
            if (!SOUND->isPlaySound("select"))
                SOUND->play("select", 0.4F);

            gameMgr->generateUnitMsg(static_cast<UNIT_TYPE>(cursorIdx + 1));
            gameMgr->closeUIMsg();
            exit();
        }
        else
        {
            if (SOUND->isPlaySound("unavailable"))
                SOUND->stop("unavailable");
            if (!SOUND->isPlaySound("unavailable"))
                SOUND->play("unavailable", 0.4F);
        }
    }
}

void CFactoryUI::closeFactoryUI()
{
    if (InputManager->isOnceKeyDown('X'))
    {
        gameMgr->closeUIMsg();
        exit();
    }
}
