#include "framework.h"
#include "tankMap.h"

tankMap::tankMap()
{
}

tankMap::~tankMap()
{
}

HRESULT tankMap::init()
{
    IMAGE->addFrameImage("mapTiles", "images/mapTiles.bmp", 0, 0, 640, 288, 20, 9, true, RGB(255, 0, 255));

    load();
    return S_OK;
}

void tankMap::release()
{
}

void tankMap::update()
{
}

void tankMap::render()
{
    //지형
    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        IMAGE->frameRender("mapTiles", getMemDC(),
            _map[i].rcTile.left, _map[i].rcTile.top,
            _map[i].terrainFrameX, _map[i].terrainFrameY);
    }
    //오브젝트
    for (size_t i = 0; i < TILEX * TILEY; i++)
    {

        if (_map[i].obj == OBJECT::OBJ_NONE)continue;

        IMAGE->frameRender("mapTiles", getMemDC(),
            _map[i].rcTile.left, _map[i].rcTile.top,
            _map[i].objFrameX, _map[i].objFrameY);
    }
}

void tankMap::load()
{
    HANDLE file;
    DWORD read;

    file = CreateFile("tileMap.map",
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ReadFile(file, _map, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
    ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);


    //땅크 위치에 해당하는 타일 이미지를 걸러낸다.

    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        _OBJattribute[i].strength = 0;

        if (_map[i].obj == OBJECT::OBJ_TANK1 || _map[i].obj == OBJECT::OBJ_TANK2)
        {
            _map[i].obj = OBJECT::OBJ_NONE;
        }
    }
    //속성정의를 하자
    memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);

    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        if (_map[i].terrain == TERRAIN::TR_WATER)
        {
            _attribute[i] |= ATTR_UNMOVABLE;
        }
        if (_map[i].obj == OBJECT::OBJ_BLOCK)
        {
            _attribute[i] |= ATTR_UNMOVABLE;
            _OBJattribute[i].strength = 1;
        }
        if (_map[i].obj == OBJECT::OBJ_BLOCK3)
        {
            _attribute[i] |= ATTR_UNMOVABLE;
            _OBJattribute[i].strength = 3;
        }
        if (_map[i].obj == OBJECT::OBJ_BLOCKS)
        {
            _attribute[i] |= ATTR_UNMOVABLE;
        }
    }
}
void tankMap::attackBlock(int tileN)
{
    if (_map[tileN].obj == OBJECT::OBJ_BLOCKS)return;

    _OBJattribute[tileN].strength--;

    if (_OBJattribute[tileN].strength <= 0)
    {
        _OBJattribute[tileN].strength = 0;
        _attribute[tileN] = 0;
        _map[tileN].obj = OBJECT::OBJ_NONE;
    }
}
