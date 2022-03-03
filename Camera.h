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
	CCamera(const CCamera& copy);
	CCamera(const CCamera* copy);
	~CCamera();

	HRESULT init();
	void release();
	void update();
	void render();

	CCamera& operator=(const CCamera& ref);
	CCamera* operator=(const CCamera* ref);

	Vec2 getCam1() { return cam1; }
	Vec2 getCam2() { return cam2; }

	Vec2 getCamSize() { return cam_size; }

	void setTargetVec2(Vec2 pos) { target = pos; }
};

