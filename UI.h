#pragma once
#include "Object.h"
class CUI : public CObject
{
private:

public:
	CUI();
	~CUI();

	HRESULT init();
	void release();
	void update();
	void render();
};