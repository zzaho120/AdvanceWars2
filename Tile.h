#pragma once
#include"Object.h"
class CTile : public CObject
{
private:
	ENVIRONMENT_TYPE tileType;
	BUILDING_TYPE buildingType;
	UNIT_TYPE unitType;
	PLAYER_TYPE playerType;
public:
	CTile();
	CTile(Vec2 _pos, Vec2 _size, image* _img = nullptr, animation* _ani = nullptr);
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileRenderSet();

	BUILDING_TYPE getBuildtype() { return buildingType; }

	void setTileType(ENVIRONMENT_TYPE type) { tileType = type; }
	void setBuildingType(BUILDING_TYPE type) { buildingType = type; }
	void setPlayerType(PLAYER_TYPE type) { playerType = type; }
};