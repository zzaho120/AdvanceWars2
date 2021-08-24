#pragma once
#include "gameNode.h"

class CObject : public gameNode
{
protected:
	Vec2 pos;
	Vec2 size;

	image* img;
	animation* ani;
public:
	CObject();
	~CObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

