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
	CObject(const CObject& copy);
	CObject(const CObject* copy);
	CObject(Vec2 _pos, Vec2 _size, image* _img = nullptr, animation* _ani = nullptr);
	~CObject();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	CObject& operator=(const CObject& ref);
	CObject* operator=(const CObject* ref);

	Vec2 getPos() { return pos; }
	void setPos(Vec2 _pos) { pos = _pos; }

	Vec2 getSize() { return size; }
	Vec2 setSize(Vec2 _size) { size = _size; }

	image* getImg() { return img; }
};