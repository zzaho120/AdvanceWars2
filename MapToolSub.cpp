#include "framework.h"
#include "MapToolSub.h"

CMapToolSub::CMapToolSub()
{
    mapToolSetup();
}

CMapToolSub::~CMapToolSub()
{
}

HRESULT CMapToolSub::init()
{
    return S_OK;
}

void CMapToolSub::release()
{
}

void CMapToolSub::update()
{
    if (SUBWIN->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON))
    {
        setMap();
        tileStringSetting();
    }
}

void CMapToolSub::render(HDC hdc)
{
    TextOut(hdc, 10, 250, tileName, strlen(tileName));

    IMAGE->render("tileTool", hdc, 0, 280);
}

void CMapToolSub::mapToolSetup()
{
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            sampleTile[i * SAMPLE_TILE_X + j].frame.x = j;
            sampleTile[i * SAMPLE_TILE_X + j].frame.y = i;

            sampleTile[i * SAMPLE_TILE_X + j].rcTile =
                RectMake(
                    TILE_SIZE_X * j, 280 + TILE_SIZE_Y * i,
                    TILE_SIZE_X, TILE_SIZE_Y);
        }
    }
}

void CMapToolSub::setMap()
{
    for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
    {
        if (PtInRect(&sampleTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetTileFrame(PointMake(sampleTile[i].frame.x, sampleTile[i].frame.y));
        }
    }
}

void CMapToolSub::tileStringSetting()
{
    if (SUBWIN->GetTileFrame().y == 0)
    {
        switch (SUBWIN->GetTileFrame().x)
        {
        case 0:
            strcpy(tileName, "현재 타일 : plain");
            break;
        case 1:
            strcpy(tileName, "현재 타일 : wood");
            break;
        case 2:
            strcpy(tileName, "현재 타일 : mountain");
            break;
        case 3:
            strcpy(tileName, "현재 타일 : sea");
            break;
        case 4:
            strcpy(tileName, "현재 타일 : river");
            break;
        case 5:
            strcpy(tileName, "현재 타일 : road");
            break;
        case 6:
            strcpy(tileName, "현재 타일 : bridge");
            break;
        }
    }
    else if (SUBWIN->GetTileFrame().y == 1)
    {
        switch (SUBWIN->GetTileFrame().x)
        {
        case 0:
            strcpy(tileName, "현재 타일 : city_1p");
            break;
        case 1:
            strcpy(tileName, "현재 타일 : city_2p");
            break;
        case 2:
        case 3:
        case 4:
            strcpy(tileName, "현재 타일 : 사용불가");
            break;
        case 5:
            strcpy(tileName, "현재 타일 : city_none");
            break;
        }
    }
    else if (SUBWIN->GetTileFrame().y == 2)
    {
        switch (SUBWIN->GetTileFrame().x)
        {
        case 0:
            strcpy(tileName, "현재 타일 : factory_1p");
            break;
        case 1:
            strcpy(tileName, "현재 타일 : factory_2p");
            break;
        case 2:
        case 3:
        case 4:
            strcpy(tileName, "현재 타일 : 사용불가");
            break;
        case 5:
            strcpy(tileName, "현재 타일 : factory_none");
            break;
        }
    }
    else if (SUBWIN->GetTileFrame().y == 3)
    {
        switch (SUBWIN->GetTileFrame().x)
        {
        case 0:
            strcpy(tileName, "현재 타일 : HQ_1p");
            break;
        case 1:
            strcpy(tileName, "현재 타일 : HQ_2p");
            break;
        }
    }
}
