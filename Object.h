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
	CObject(Vec2 _pos, Vec2 _size, image* _img = nullptr, animation* _ani = nullptr);
	~CObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Vec2 getPos() { return pos; }
	Vec2 getSize() { return size; }
	image* getImg() { return img; }
};