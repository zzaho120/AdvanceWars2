#pragma once
#include"Object.h"
class CEnvironment : public CObject
{
private:
	int tileIdx;
public:
	CEnvironment();
	~CEnvironment();

	HRESULT init();
	void release();
	void update();
	void render();
};

