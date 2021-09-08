#include "framework.h"
#include"GameManager.h"
#include "GameResult.h"

CGameResult::CGameResult() :
    bgAlpha(0),
    resultIdx(0),
    vitoryPlayer(200, 260),
    vitoryInfo(310, 300),
    losePlayer(200, 540),
    loseInfo(310, 580)
{
}


CGameResult::~CGameResult()
{
}

HRESULT CGameResult::init()
{
    SOUND->stop("player1bg");
    SOUND->stop("player2bg");
    SOUND->play("gameover", 0.5F);
    return S_OK;
}

HRESULT CGameResult::init(CGameManager* mgr)
{
    gameMgr = mgr;
    return S_OK;
}

void CGameResult::release()
{
}

void CGameResult::update()
{
    pageMove();
    settingData();
    inputKey();
}

void CGameResult::render()
{
    IMAGE->alphaRender("result", getMemDC(), 0, 0, bgAlpha);

    IMAGE->alphaFrameRender("result_player", getMemDC(), vitoryPlayer.x, vitoryPlayer.y, winner, 0, bgAlpha);
    IMAGE->alphaFrameRender("result_player", getMemDC(), losePlayer.x, losePlayer.y, loser, 0, bgAlpha);

    if(resultIdx > 0)
        IMAGE->alphaFrameRender("result_arrow", getMemDC(), 0, WINSIZEY / 2 + 30, 0, 0, bgAlpha);
    if(resultIdx < 3)
        IMAGE->alphaFrameRender("result_arrow", getMemDC(), 950, WINSIZEY / 2 + 30, 1, 0, bgAlpha);

    IMAGE->alphaFrameRender("result_info", getMemDC(), 80, WINSIZEY / 2 + 20, resultIdx, 0, bgAlpha);
    if (vitory > 99999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x, vitoryInfo.y, vitory / 100000 % 10, 0, bgAlpha);
    if (vitory > 9999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x + 40, vitoryInfo.y, vitory / 10000 % 10, 0, bgAlpha);
    if (vitory > 999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x + 80, vitoryInfo.y, vitory / 1000 % 10, 0, bgAlpha);
    if (vitory > 99)
        IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x + 120, vitoryInfo.y, vitory / 100 % 10, 0, bgAlpha);
    if (vitory > 9)
        IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x + 160, vitoryInfo.y, vitory / 10 % 10, 0, bgAlpha);
    IMAGE->alphaFrameRender("result_number", getMemDC(), vitoryInfo.x + 200, vitoryInfo.y, vitory % 10, 0, bgAlpha);

    if (lose > 99999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x, loseInfo.y, lose / 100000 % 10, 0, bgAlpha);
    if (lose > 9999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x + 40, loseInfo.y, lose / 10000 % 10, 0, bgAlpha);
    if (lose > 999)
        IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x + 80, loseInfo.y, lose / 1000 % 10, 0, bgAlpha);
    if (lose > 99)
        IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x + 120, loseInfo.y, lose / 100 % 10, 0, bgAlpha);
    if (lose > 9)
        IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x + 160, loseInfo.y, lose / 10 % 10, 0, bgAlpha);
    IMAGE->alphaFrameRender("result_number", getMemDC(), loseInfo.x + 200, loseInfo.y, lose % 10, 0, bgAlpha);


}

void CGameResult::pageMove()
{
    if (bgAlpha > 200 && resultIdx > 0 && InputManager->isOnceKeyDown(VK_LEFT))
        resultIdx--;
    if (bgAlpha > 200 && resultIdx < 3 && InputManager->isOnceKeyDown(VK_RIGHT))
        resultIdx++;
}

void CGameResult::settingData()
{
    switch (resultIdx)
    {
    case 0:
        if (gameMgr->getKO(0))
        {
            winner = 1;
            loser = 0;
            vitory = gameMgr->getGameData()->getUnitGenerate().y;
            lose = gameMgr->getGameData()->getUnitGenerate().x;
        }
        else
        {
            winner = 0;
            loser = 1;
            vitory = gameMgr->getGameData()->getUnitGenerate().x;
            lose = gameMgr->getGameData()->getUnitGenerate().y;
        }
        break;
    case 1:
        if (gameMgr->getKO(0))
        {
            winner = 1;
            loser = 0;
            vitory = gameMgr->getGameData()->getUnitDeath().y;
            lose = gameMgr->getGameData()->getUnitDeath().x;
        }
        else
        {
            winner = 0;
            loser = 1;
            vitory = gameMgr->getGameData()->getUnitDeath().x;
            lose = gameMgr->getGameData()->getUnitDeath().y;
        }
        break;

    case 2:
        if (gameMgr->getKO(0))
        {
            winner = 1;
            loser = 0;
            vitory = gameMgr->getGameData()->getMoneyIncome().y;
            lose = gameMgr->getGameData()->getMoneyIncome().x;
        }
        else
        {
            winner = 0;
            loser = 1;
            vitory = gameMgr->getGameData()->getMoneyIncome().x;
            lose = gameMgr->getGameData()->getMoneyIncome().y;
        }
        break;

    case 3:
        if (gameMgr->getKO(0))
        {
            winner = 1;
            loser = 0;
            vitory = gameMgr->getGameData()->getMoneySpending().y;
            lose = gameMgr->getGameData()->getMoneySpending().x;
        }
        else
        {
            winner = 0;
            loser = 1;
            vitory = gameMgr->getGameData()->getMoneySpending().x;
            lose = gameMgr->getGameData()->getMoneySpending().y;
        }
        break;
    }
}

void CGameResult::inputKey()
{
    if (gameMgr->getGameover() && bgAlpha < 255)
        bgAlpha += 3;
    else if (bgAlpha > 254 && InputManager->isOnceKeyDown('Z'))
    {
        SOUND->stop("gameover");
        SCENE->changeScene("mainMenuScene");
    }
}
