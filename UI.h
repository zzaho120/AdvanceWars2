#pragma once
#include "gameNode.h"

class CUI : public gameNode
{
protected:
	bool isActive;
	UI_TYPE uiType;
public:
	CUI() : isActive(false), uiType(UI_TYPE::NONE)
	{ };
	CUI(UI_TYPE type) : isActive(false), uiType(type)
	{ };
	~CUI() { };

	virtual HRESULT init() { return S_OK; }
	virtual void release() { }
	virtual void update() { }
	virtual void render() { }

	virtual void enter() { }
	virtual void exit() { }

	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }

	UI_TYPE getUIType() { return uiType; }
};