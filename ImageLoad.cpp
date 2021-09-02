#include "framework.h"
#include "ImageLoad.h"

CImageLoad::CImageLoad()
{ }

CImageLoad::~CImageLoad()
{ }

void CImageLoad::resourceLoad()
{
	//=========================== BUILDING ===========================
	//=========================== BUILDING ===========================

	IMAGE->addFrameImage("city", "images/building/city.bmp", TILE_SIZE_X * 2, TILE_SIZE_Y * 2 * 6, 2, 6);
	IMAGE->addFrameImage("factory", "images/building/factory.bmp", TILE_SIZE_X * 2, TILE_SIZE_Y * 6, 2, 6);
	IMAGE->addFrameImage("HQ", "images/building/HQ.bmp", TILE_SIZE_X * 2, TILE_SIZE_Y * 2 * 6, 2, 6);

	//============================== TILE ============================
	//============================== TILE ============================

	IMAGE->addFrameImage("pipe", "images/tile/pipe.bmp", 80, 32, 6, 2);
	IMAGE->addFrameImage("road", "images/tile/road.bmp", TILE_SIZE_X * 5, TILE_SIZE_Y * 3, 5, 3);
	IMAGE->addFrameImage("flow_river", "images/tile/flow_river.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 11, 8, 11);
	IMAGE->addFrameImage("sea", "images/tile/sea.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 3, 8, 3);
	IMAGE->addFrameImage("flow_sea", "images/tile/flow_sea.bmp", TILE_SIZE_X * 4, TILE_SIZE_Y * 47, 4, 47);
	IMAGE->addFrameImage("single_environment", "images/tile/single_environment.bmp", 64 * 5, 64, 5, 1);
	IMAGE->addFrameImage("wood", "images/tile/wood.bmp", TILE_SIZE_X * 4, TILE_SIZE_Y * 3, 4, 3);
	IMAGE->addImage("move_range", "images/tile/moveRange.bmp", TILE_SIZE_X, TILE_SIZE_Y);

	//============================= UNIT =============================
	//============================= UNIT =============================

	IMAGE->addFrameImage("infantry_idle", "images/unit/infantry_idle.bmp", TILE_SIZE_X * 6, TILE_SIZE_Y * 5, 6, 5);
	IMAGE->addFrameImage("infantry_move", "images/unit/infantry_move.bmp", (TILE_SIZE_X + 24) * 3, (TILE_SIZE_Y + 32) * 15, 3, 15);

	IMAGE->addFrameImage("mech_idle", "images/unit/mech_idle.bmp", TILE_SIZE_X * 6, TILE_SIZE_Y * 5, 6, 5);
	IMAGE->addFrameImage("mech_move", "images/unit/mech_move.bmp", (TILE_SIZE_X + 24) * 3, (TILE_SIZE_Y + 32) * 15, 3, 15);

	IMAGE->addFrameImage("tank_idle", "images/unit/tank_idle.bmp", TILE_SIZE_X * 6, TILE_SIZE_Y * 5, 6, 5);
	IMAGE->addFrameImage("tank_move", "images/unit/tank_move.bmp", (TILE_SIZE_X + 24) * 3, (TILE_SIZE_Y + 32) * 15, 3, 15);

	IMAGE->addFrameImage("artillery_idle", "images/unit/artillery_idle.bmp", TILE_SIZE_X * 6, TILE_SIZE_Y * 5, 6, 5);
	IMAGE->addFrameImage("artillery_move", "images/unit/artillery_move.bmp", (TILE_SIZE_X + 24) * 3, (TILE_SIZE_Y + 32) * 15, 3, 15);

	IMAGE->addFrameImage("APC_idle", "images/unit/APC_idle.bmp", TILE_SIZE_X * 6, TILE_SIZE_Y * 5, 6, 5);
	IMAGE->addFrameImage("APC_move", "images/unit/APC_move.bmp", (TILE_SIZE_X + 24) * 3, (TILE_SIZE_Y + 32) * 15, 3, 15);

	//=============================== UI =============================
	//=============================== UI =============================

	IMAGE->addFrameImage("cursor", "images/UI/cursor.bmp", 64 * 5, 64, 5, 1);
	IMAGE->addFrameImage("number", "images/UI/number.bmp", 80, 8, 10, 1);

	IMAGE->addFrameImage("unit_hp", "images/UI/unit_hp.bmp", 80, 8, 10, 1);
	IMAGE->addFrameImage("unit_name", "images/UI/unit_name.bmp", 160, 16, 5, 1);
	IMAGE->addFrameImage("unit_status_mark", "images/UI/unit_status_mark.bmp", 24, 40, 3, 5);
	IMAGE->addFrameImage("unit_warnings", "images/UI/unit_warnings.bmp", 16, 8, 2, 1);

	IMAGE->addFrameImage("move_arrow", "images/UI/move_arrow.bmp", 112, 32, 6, 2);
	IMAGE->addFrameImage("supply_message", "images/UI/supply_message.bmp", 128, 32, 2, 1);

	IMAGE->addImage("black", "images/UI/bgblack.bmp", WINSIZEX, WINSIZEY);
	IMAGE->addImage("tileTool", "images/tile/maptool_tile.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 4);

	IMAGE->addImage("factory_arrow", "images/UI/factory_arrow.bmp", 200, 100);
	IMAGE->addImage("factory_panel_red", "images/UI/factory_panel_red.bmp", 400, 500);
	IMAGE->addImage("factory_panel_blue", "images/UI/factory_panel_blue.bmp", 400, 500);
	//============================ EFFECT ============================
	//============================ EFFECT ============================

	EFFECT->addEffect("ground_destroy", "images/effect/ground_destroy.bmp", 288, 32, 32, 32, 1, 0.3f, 100);
}
