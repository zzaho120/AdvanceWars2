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
        setMap();
}

void CMapToolSub::render(HDC hdc)
{
    TCHAR currentSelect[64];
    wsprintf(currentSelect, "tile : {%d,%d}",
        SUBWIN->GetTileFrame().x, SUBWIN->GetTileFrame().y);
    TextOut(hdc, 10, 250, currentSelect, strlen(currentSelect));

    /*for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            Rectangle(hdc, sampleTile[i * SAMPLE_TILE_X + j].rcTile.left,
                sampleTile[i * SAMPLE_TILE_X + j].rcTile.top,
                sampleTile[i * SAMPLE_TILE_X + j].rcTile.right,
                sampleTile[i * SAMPLE_TILE_X + j].rcTile.bottom);
        }
    }*/
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