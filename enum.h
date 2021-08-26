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
	ROAD_4WAYS
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
	BOTTOM
};

enum class ROTATE_TYPE
{
	NONE,
	DEG0,
	DEG90,
	DEG180,
	DEG270
};