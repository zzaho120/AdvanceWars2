#include "framework.h"
#include "UIManager.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

HRESULT CUIManager::init()
{
    return S_OK;
}

void CUIManager::release()
{
}

void CUIManager::update()
{
    for (iterUI = vecUI.begin(); iterUI != vecUI.end(); iterUI++)
    {
        (*iterUI)->update();
    }
}

void CUIManager::render()
{
    for (iterUI = vecUI.begin(); iterUI != vecUI.end(); iterUI++)
    {
        (*iterUI)->render();
    }
}

void CUIManager::addUI(CUI* ui)
{
    vecUI.push_back(ui);
}
