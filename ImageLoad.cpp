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

	IMAGE->addFrameImage("city", "images/building/city.bmp", 32, 192, 2, 6);
	IMAGE->addFrameImage("factory", "images/building/factory.bmp", 32, 96, 2, 6);
	IMAGE->addFrameImage("HQ", "images/building/HQ.bmp", 32, 192, 2, 6);

	//============================== TILE ============================
	//============================== TILE ============================

	IMAGE->addFrameImage("maptool_tile", "images/tile/maptool_tile.bmp", 128, 16, 7, 1);
	IMAGE->addFrameImage("pipe", "images/tile/pipe.bmp", 80, 32, 6, 2);
	IMAGE->addFrameImage("road", "images/tile/road.bmp", TILE_SIZE_X * 5, TILE_SIZE_Y * 3, 5, 3);
	IMAGE->addFrameImage("river", "images/tile/river.bmp", 128 * 4, 96 * 4, 8, 6);
	IMAGE->addFrameImage("sea", "images/tile/sea.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 3, 8, 3);
	IMAGE->addFrameImage("single_environment", "images/tile/single_environment.bmp", 64 * 5, 64, 5, 1);
	IMAGE->addFrameImage("wood", "images/tile/wood.bmp", TILE_SIZE_X * 4, TILE_SIZE_Y * 3, 4, 3);


	//============================= UNIT =============================
	//============================= UNIT =============================

	IMAGE->addFrameImage("infantry_idle", "images/unit/infantry_idle.bmp", 96, 80, 6, 5);
	IMAGE->addFrameImage("infantry_move", "images/unit/infantry_move.bmp", 72, 360, 3, 15);

	IMAGE->addFrameImage("mech_idle", "images/unit/mech_idle.bmp", 96, 80, 6, 5);
	IMAGE->addFrameImage("mech_move", "images/unit/mech_move.bmp", 72, 360, 3, 15);

	IMAGE->addFrameImage("tank_idle", "images/unit/tank_idle.bmp", 96, 80, 6, 5);
	IMAGE->addFrameImage("tank_move", "images/unit/tank_move.bmp", 72, 360, 3, 15);

	IMAGE->addFrameImage("artillery_idle", "images/unit/artillery_idle.bmp", 96, 80, 6, 5);
	IMAGE->addFrameImage("artillery_move", "images/unit/artillery_move.bmp", 72, 360, 3, 15);

	IMAGE->addFrameImage("APC_idle", "images/unit/APC_idle.bmp", 96, 80, 6, 5);
	IMAGE->addFrameImage("APC_move", "images/unit/APC_move.bmp", 72, 360, 3, 15);

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

	//============================ EFFECT ============================
	//============================ EFFECT ============================

	EFFECT->addEffect("ground_destroy", "images/effect/ground_destroy.bmp", 288, 32, 32, 32, 1, 0.3f, 100);
}
