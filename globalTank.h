#pragma once
#define TILESIZE  32		//오른쪽화면 타일 사이즈
#define TILEX     20		//왼쪽화면타일 사이즈 X
#define TILEY     20		//왼쪽화면타일 사이즈 Y

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면  오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 9


//비트연산을 하기  위해
#define ATTR_UNMOVABLE 0x00000001
#define ATTR_POSITION 0x00000002

enum class TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};
//오브젝트(ex : 지형 위쪽에  배치, 움직이거나 부서지거나하는 변화를 줄수있는 물체)
enum class OBJECT
{
	OBJ_BLOCK,
	OBJ_BLOCK3,
	OBJ_BLOCKS,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_NONE
};
//위치 좌표
enum class POS
{
	POS_TANK1,
	POS_TANK2
};
//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT  rcTile;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

};
//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile[SAMPLETILEX* SAMPLETILEY];
	int terrainFrameX;
	int terrainFrameY;
};
//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

struct tagOBJAttribute
{
	int strength;
};