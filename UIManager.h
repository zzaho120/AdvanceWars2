#pragma once
#include "UI.h"

class CUIManager : public gameNode
{
private:
	vector<CUI*> vecUI;
	vector<CUI*>::iterator iterUI;
public:
	CUIManager();
	~CUIManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addUI(CUI* ui);
	void enterUI(int idx) { vecUI[idx]->enter(); }

	vector<CUI*> getVecUI() { return vecUI; }
};

