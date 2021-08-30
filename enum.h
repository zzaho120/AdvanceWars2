#pragma once

enum class ENVIRONMENT_TYPE
{
	NONE,
	PLAIN,
	WOOD,
	MOUNTAIN,
	RIVER,
	SEA,
	ROAD,
	BRIDGE,

	RIVER_LINE,
	RIVER_CURVE,
	RIVER_3WAYS,
	RIVER_4WAYS,

	ROAD_LINE,
	ROAD_CURVE,
	ROAD_3WAYS,
	ROAD_4WAYS,

	SEA_2WAYS,
	SEA_3WAYS,
	SEA_4WAYS,
	SEA_5WAYS,
	SEA_6WAYS,
	SEA_7WAYS,
	SEA_8WAYS,

	SEA_VERTICAL00,
	SEA_VERTICAL01,
	SEA_VERTICAL02,

	SEA_HORIZONTAL00,
	SEA_HORIZONTAL01,
	SEA_HORIZONTAL02,
	SEA_NOWAYS
};
enum class BUILDING_TYPE
{
	NONE,
	CITY,
	HEADQUATERS,
	FACTORY
};

enum class PLAYER_TYPE
{
	NONE,
	PLAYER1,
	PLAYER2
};

enum class UNIT_TYPE
{
	NONE,
	INFANTRY,
	MECH,
	TANK,
	ARTILLERY,
	APC
};

enum class UNIT_MATCH
{
	NONE,
	INFANTRY,
	VEHICLE
};
enum class RECT_EDGE
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

enum class CTRL
{
	CTRL_DRAW,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_EXIT,
	CTRL_EDIT,
	CTRL_LIST,
	CTRL_REMOVE
};

// 강, 도로와 같은 방향성을 가진 스프라이트인지 체크
enum class DIRECTION_SPRITE
{
	NO,
	YES
};

// 강, 도로와 같은 방향성을 가진 스프라이트의 방향을 체크
enum class DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,

	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

enum class ROTATE_TYPE
{
	NONE,
	DEG0,
	DEG45,
	DEG90,
	DEG135,
	DEG180,
	DEG225,
	DEG270,
	DEG315,
	DEG360
};