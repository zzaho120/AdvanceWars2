#pragma once
#include"Object.h"
class CTile : public CObject
{
private:
	ENVIRONMENT_TYPE tileType;
	BUILDING_TYPE buildingType;
	UNIT_TYPE unitType;
public:
	CTile();
	CTile(Vec2 _pos, Vec2 _size, image* _img = nullptr, animation* _ani = nullptr);
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileRenderSet();
};