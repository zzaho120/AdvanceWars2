#pragma once
#include"Object.h"
class CTile : public CObject
{
private:
	ENVIRONMENT_TYPE tileType;
	BUILDING_TYPE buildingType;
public:
	CTile();
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();
};