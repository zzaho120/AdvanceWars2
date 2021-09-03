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
    goldInfoPos({ 750, 50 }),
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
        IMAGE->render("infoUI_gold_red", getMemDC(), goldInfoPos.x, goldInfoPos.y);
        break;
    case PLAYER_TYPE::PLAYER2:
        IMAGE->render("infoUI_gold_blue", getMemDC(), goldInfoPos.x, goldInfoPos.y);
        break;
    }

    int curMoney = gameMgr->getCurPlayer()->getMoney();
    if(curMoney > 99999)
        IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 50, goldInfoPos.y + 10, curMoney % 1000000 / 100000, 0); // 100000�� �ڸ�
    if(curMoney > 9999)
        IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 80, goldInfoPos.y + 10, curMoney % 100000 / 10000, 0); // 10000�� �ڸ�
    if (curMoney > 999)
        IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 110, goldInfoPos.y + 10, curMoney % 10000 / 1000, 0); // 1000�� �ڸ�
    if (curMoney > 99)
        IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 140, goldInfoPos.y + 10, curMoney % 1000 / 100, 0); // 100�� �ڸ�
    if (curMoney > 9)
        IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 170, goldInfoPos.y + 10, curMoney % 100 / 10, 0); // 10�� �ڸ�
    IMAGE->frameRender("number", getMemDC(), goldInfoPos.x + 200, goldInfoPos.y + 10, curMoney % 10, 0); // 1�� �ڸ�
}

void CInfoUI::enter()
{
    curPlayerType = gameMgr->getCurPlayer()->getPlayerType();
}

void CInfoUI::exit()
{
    curPlayerType = PLAYER_TYPE::NONE;
}