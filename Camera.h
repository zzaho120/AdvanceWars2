#pragma once
#include "Object.h"
class CCamera : public CObject
{
private:
	Vec2 cam1;
	Vec2 cam2;
	Vec2 cam_size;
	Vec2 target;
public:
	CCamera();
	~CCamera();

	HRESULT init();
	void release();
	void update();
	void render();

	Vec2 getCam1() { return cam1; }
	Vec2 getCam2() { return cam2; }

	Vec2 getCamSize() { return cam_size; }

	void setTargetVec2(Vec2 pos) { target = pos; }
};

