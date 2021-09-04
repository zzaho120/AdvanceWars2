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

    int curMoney = gameMgr->getCurPlayer()->getMoney();
    if(curMoney > 99999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 50, panelPos.y + 10, curMoney % 1000000 / 100000, 0); // 100000의 자리
    if(curMoney > 9999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 80, panelPos.y + 10, curMoney % 100000 / 10000, 0); // 10000의 자리
    if (curMoney > 999)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 110, panelPos.y + 10, curMoney % 10000 / 1000, 0); // 1000의 자리
    if (curMoney > 99)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 140, panelPos.y + 10, curMoney % 1000 / 100, 0); // 100의 자리
    if (curMoney > 9)
        IMAGE->frameRender("number", getMemDC(), panelPos.x + 170, panelPos.y + 10, curMoney % 100 / 10, 0); // 10의 자리
    IMAGE->frameRender("number", getMemDC(), panelPos.x + 200, panelPos.y + 10, curMoney % 10, 0); // 1의 자리
}

void CInfoUI::enter()
{
    curPlayerType = gameMgr->getCurPlayer()->getPlayerType();
}

void CInfoUI::exit()
{
    curPlayerType = PLAYER_TYPE::NONE;
}
