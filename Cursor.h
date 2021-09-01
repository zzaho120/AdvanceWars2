#pragma once
#include "Object.h"
class CCursor : public CObject
{
private:
	int tileIdx;
public:
	CCursor();
	CCursor(Vec2 pos, int tileIndex);
	~CCursor();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
};