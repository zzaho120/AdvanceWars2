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
	IMAGE->addFrameImage("number", "images/UI/number.bmp", 30 * 11, 30, 11, 1);

	IMAGE->addFrameImage("unit_hp", "images/UI/unit_hp.bmp", 80, 8, 10, 1);
	IMAGE->addFrameImage("unit_status_mark", "images/UI/unit_status_mark.bmp", 25 * 3, 25 * 5, 3, 5);
	IMAGE->addFrameImage("unit_warnings", "images/UI/unit_warnings.bmp", 16, 8, 2, 1);

	IMAGE->addFrameImage("move_arrow", "images/UI/move_arrow.bmp", 112, 32, 6, 2);
	IMAGE->addFrameImage("supply_message", "images/UI/supply_message.bmp", 128, 32, 2, 1);

	IMAGE->addImage("black", "images/UI/bgblack.bmp", WINSIZEX, WINSIZEY);
	IMAGE->addImage("black_info1", "images/UI/bgblack.bmp", 150, 200);
	IMAGE->addImage("black_info2", "images/UI/bgblack.bmp", 300, 200);
	IMAGE->addImage("tileTool", "images/tile/maptool_tile.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 4);
	IMAGE->addFrameImage("tileTool_frame", "images/tile/maptool_tile.bmp", TILE_SIZE_X * 8, TILE_SIZE_Y * 4, 8, 4);

	IMAGE->addImage("factory_arrow", "images/UI/factory_arrow.bmp", 70, 40);
	IMAGE->addImage("factory_panel_red", "images/UI/factory_panel_red.bmp", 600, 600);
	IMAGE->addImage("factory_panel_blue", "images/UI/factory_panel_blue.bmp", 600, 600);

	IMAGE->addImage("option_panel_red", "images/UI/option_panel_red.bmp", 300, 400);
	IMAGE->addImage("option_panel_blue", "images/UI/option_panel_blue.bmp", 300, 400);

	IMAGE->addImage("infoUI_gold_red", "images/UI/infoUI_gold_red.bmp", 250, 100);
	IMAGE->addImage("infoUI_gold_blue", "images/UI/infoUI_gold_blue.bmp", 250, 100);

	IMAGE->addImage("action_panel_red", "images/UI/action_panel_red.bmp", 250, 360);
	IMAGE->addImage("action_panel_blue", "images/UI/action_panel_blue.bmp", 250, 360);

	IMAGE->addImage("action_failed", "images/UI/action_failed.bmp", 70, 70);
	IMAGE->addImage("action_capture", "images/UI/action_capture.bmp", 210, 75);
	IMAGE->addImage("action_fire", "images/UI/action_fire.bmp", 210, 75);
	IMAGE->addImage("action_supply", "images/UI/action_supply.bmp", 210, 75);
	IMAGE->addImage("action_wait", "images/UI/action_wait.bmp", 210, 75);

	IMAGE->addFrameImage("tile_name", "images/UI/tile_name.bmp", 100 * 10, TILE_SIZE_Y, 10, 1);
	IMAGE->addFrameImage("unit_name", "images/UI/unit_name.bmp", 100 * 5, TILE_SIZE_Y, 5, 1);
	IMAGE->addFrameImage("unit_type", "images/UI/unit_type.bmp", TILE_SIZE_X * 5, TILE_SIZE_Y * 2, 5, 2);
	IMAGE->addFrameImage("info_icon", "images/UI/info_icon.bmp", 40 * 4, 40, 4, 1);

	//============================ EFFECT ============================
	//============================ EFFECT ============================

	EFFECT->addEffect("ground_destroy", "images/effect/ground_destroy.bmp", 288, 32, 32, 32, 1, 0.3f, 100);
}
