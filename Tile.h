#pragma once
#include"Object.h"
class CTile : public CObject
{
private:
	ENVIRONMENT_TYPE tileType;
	BUILDING_TYPE buildingType;
	UNIT_TYPE unitType;
	PLAYER_TYPE playerType;
	DIRECTION_SPRITE directionType;
	ROTATE_TYPE rotateType;
public:
	CTile();
	CTile(Vec2 _pos, Vec2 _size, image* _img = nullptr, animation* _ani = nullptr);
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileRender();

	CTile& operator=(const CTile& ref);
	CTile* operator=(const CTile* ref);

	ENVIRONMENT_TYPE getTileType() { return tileType; }
	BUILDING_TYPE getBuildtype() { return buildingType; }
	UNIT_TYPE getUnitType() { return unitType; }
	PLAYER_TYPE getPlayerType() { return playerType; }
	DIRECTION_SPRITE getDirection() { return directionType; }
	ROTATE_TYPE getRotateType() { return rotateType; }

	void setTileType(ENVIRONMENT_TYPE type) { tileType = type; }
	void setBuildingType(BUILDING_TYPE type) { buildingType = type; }
	void setUnitType(UNIT_TYPE type) { unitType = type; }
	void setPlayerType(PLAYER_TYPE type) { playerType = type; }
	void setDirectionType(DIRECTION_SPRITE type) { directionType = type; }
	void setRotateType(ROTATE_TYPE type) { rotateType = type; }
};