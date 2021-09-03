#include "framework.h"
#include "AnimationLoad.h"

CAnimationLoad::CAnimationLoad()
{
}

CAnimationLoad::~CAnimationLoad()
{
}

void CAnimationLoad::resourceLoad()
{
	//============================ CURSOR =============================
	//============================ CURSOR =============================
	
	ANIMATION->addAnimation("cursor_ani", "cursor", 0, 4, 10, false, true);

	//============================== CITY =============================
	//============================== CITY =============================

	ANIMATION->addAnimation("city_red", "city", 0, 1, 1, false, true);
	ANIMATION->addAnimation("city_blue", "city", 2, 3, 1, false, true);

	//============================ FACTORY ============================
	//============================ FACTORY ============================

	ANIMATION->addAnimation("factory_red", "factory", 0, 1, 1, false, true);
	ANIMATION->addAnimation("factory_blue", "factory", 2, 3, 1, false, true);


	//============================== HQ ===============================
	//============================== HQ ===============================

	ANIMATION->addAnimation("HQ_red", "HQ", 0, 1, 1, false, true);
	ANIMATION->addAnimation("HQ_blue", "HQ", 2, 3, 1, false, true);

	//============================ INFANTRY ===========================
	//============================ INFANTRY ===========================

	ANIMATION->addAnimation("infry_idle_red_on", "infantry_idle", 0, 2, 3, false, true);
	ANIMATION->addAnimation("infry_idle_red_off", "infantry_idle", 3, 5, 3, false, true);

	ANIMATION->addAnimation("infry_idle_blue_on", "infantry_idle", 6, 8, 3, false, true);
	ANIMATION->addAnimation("infry_idle_blue_off", "infantry_idle", 9, 11, 3, false, true);

	ANIMATION->addAnimation("infry_move_left_red", "infantry_move", 0, 2, 8, false, true);
	ANIMATION->addAnimation("infry_move_down_red", "infantry_move", 3, 5, 3, false, true);
	ANIMATION->addAnimation("infry_move_up_red", "infantry_move", 6, 8, 3, false, true);

	ANIMATION->addAnimation("infry_move_left_blue", "infantry_move", 9, 11, 8, false, true);

	//============================== MECH =============================
	//============================== MECH =============================
	ANIMATION->addAnimation("mech_idle_red_on", "mech_idle", 0, 2, 3, false, true);
	ANIMATION->addAnimation("mech_idle_red_off", "mech_idle", 3, 5, 3, false, true);

	ANIMATION->addAnimation("mech_idle_blue_on", "mech_idle", 6, 8, 3, false, true);
	ANIMATION->addAnimation("mech_idle_blue_off", "mech_idle", 9, 11, 3, false, true);

	ANIMATION->addAnimation("mech_move_left_red", "mech_move", 0, 2, 8, false, true);
	ANIMATION->addAnimation("mech_move_down_red", "mech_move", 3, 5, 3, false, true);
	ANIMATION->addAnimation("mech_move_up_red", "mech_move", 6, 8, 3, false, true);

	ANIMATION->addAnimation("mech_move_left_blue", "mech_move", 9, 11, 8, false, true);

	//============================== TANK =============================
	//============================== TANK =============================
	ANIMATION->addAnimation("tank_idle_red_on", "tank_idle", 0, 2, 3, false, true);
	ANIMATION->addAnimation("tank_idle_red_off", "tank_idle", 3, 5, 3, false, true);

	ANIMATION->addAnimation("tank_idle_blue_on", "tank_idle", 6, 8, 3, false, true);
	ANIMATION->addAnimation("tank_idle_blue_off", "tank_idle", 9, 11, 3, false, true);

	ANIMATION->addAnimation("tank_move_left_red", "tank_move", 0, 2, 8, false, true);
	ANIMATION->addAnimation("tank_move_down_red", "tank_move", 3, 5, 3, false, true);
	ANIMATION->addAnimation("tank_move_up_red", "tank_move", 6, 8, 3, false, true);

	ANIMATION->addAnimation("tank_move_left_blue", "tank_move", 9, 11, 8, false, true);

	//=========================== ARTILLERY ===========================
	//=========================== ARTILLERY ===========================
	ANIMATION->addAnimation("artil_idle_red_on", "artillery_idle", 0, 2, 3, false, true);
	ANIMATION->addAnimation("artil_idle_red_off", "artillery_idle", 3, 5, 3, false, true);

	ANIMATION->addAnimation("artil_idle_blue_on", "artillery_idle", 6, 8, 3, false, true);
	ANIMATION->addAnimation("artil_idle_blue_off", "artillery_idle", 9, 11, 3, false, true);

	ANIMATION->addAnimation("artil_move_left_red", "artillery_move", 0, 2, 8, false, true);
	ANIMATION->addAnimation("artil_move_down_red", "artillery_move", 3, 5, 3, false, true);
	ANIMATION->addAnimation("artil_move_up_red", "artillery_move", 6, 8, 3, false, true);

	ANIMATION->addAnimation("artil_move_left_blue", "artillery_move", 9, 11, 8, false, true);
	//=============================== APC =============================
	//=============================== APC =============================
	ANIMATION->addAnimation("APC_idle_red_on", "APC_idle", 0, 2, 3, false, true);
	ANIMATION->addAnimation("APC_idle_red_off", "APC_idle", 3, 5, 3, false, true);

	ANIMATION->addAnimation("APC_idle_blue_on", "APC_idle", 6, 8, 3, false, true);
	ANIMATION->addAnimation("APC_idle_blue_off", "APC_idle", 9, 11, 3, false, true);

	ANIMATION->addAnimation("APC_move_left_red", "APC_move", 0, 2, 8, false, true);
	ANIMATION->addAnimation("APC_move_down_red", "APC_move", 3, 5, 3, false, true);
	ANIMATION->addAnimation("APC_move_up_red", "APC_move", 6, 8, 3, false, true);

	ANIMATION->addAnimation("APC_move_left_blue", "APC_move", 9, 11, 8, false, true);

	//============================== SEA ==============================
	//============================== SEA ==============================

	ANIMATION->addAnimation("sea_3ways_curve00", "flow_sea", 0, 3, 5, false, true);
	ANIMATION->addAnimation("sea_5ways_top", "flow_sea", 4, 7, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_curve01", "flow_sea", 8, 11, 5, false, true);
	ANIMATION->addAnimation("sea_5ways_left", "flow_sea", 12, 15, 5, false, true);
	ANIMATION->addAnimation("sea_8ways", "flow_sea", 16, 19, 5, false, true);
	ANIMATION->addAnimation("sea_5ways_right", "flow_sea", 20, 23, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_curve02", "flow_sea", 24, 27, 5, false, true);
	ANIMATION->addAnimation("sea_5ways_bottom", "flow_sea", 28, 31, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_curve03", "flow_sea", 32, 35, 5, false, true);
	
	ANIMATION->addAnimation("sea_2ways_curve00", "flow_sea", 36, 39, 5, false, true);
	ANIMATION->addAnimation("sea_2ways_curve01", "flow_sea", 40, 43, 5, false, true);
	ANIMATION->addAnimation("sea_2ways_curve02", "flow_sea", 44, 47, 5, false, true);
	ANIMATION->addAnimation("sea_2ways_curve03", "flow_sea", 48, 51, 5, false, true);
	
	ANIMATION->addAnimation("sea_3ways_top", "flow_sea", 52, 55, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_top00", "flow_sea", 56, 59, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_top01", "flow_sea", 60, 63, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_left", "flow_sea", 64, 67, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_left00", "flow_sea", 68, 71, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_left01", "flow_sea", 72, 75, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_right", "flow_sea", 76, 79, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_right00", "flow_sea", 80, 83, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_right01", "flow_sea", 84, 87, 5, false, true);
	ANIMATION->addAnimation("sea_3ways_bottom", "flow_sea", 88, 91, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_bottom00", "flow_sea", 92, 95, 5, false, true);
	ANIMATION->addAnimation("sea_4ways_bottom01", "flow_sea", 96, 99, 5, false, true);
	
	ANIMATION->addAnimation("sea_6ways00", "flow_sea", 100, 103, 5, false, true);
	ANIMATION->addAnimation("sea_6ways01", "flow_sea", 104, 107, 5, false, true);
	ANIMATION->addAnimation("sea_6ways02", "flow_sea", 108, 111, 5, false, true);
	ANIMATION->addAnimation("sea_6ways03", "flow_sea", 112, 115, 5, false, true);
	ANIMATION->addAnimation("sea_6ways04", "flow_sea", 116, 119, 5, false, true);
	ANIMATION->addAnimation("sea_6ways05", "flow_sea", 120, 123, 5, false, true);

	ANIMATION->addAnimation("sea_5ways00", "flow_sea", 124, 127, 5, false, true);
	ANIMATION->addAnimation("sea_5ways01", "flow_sea", 128, 131, 5, false, true);
	ANIMATION->addAnimation("sea_5ways02", "flow_sea", 132, 135, 5, false, true);
	ANIMATION->addAnimation("sea_5ways03", "flow_sea", 136, 139, 5, false, true);
	ANIMATION->addAnimation("sea_4ways00", "flow_sea", 140, 143, 5, false, true);

	ANIMATION->addAnimation("sea_horizontal00", "flow_sea", 144, 147, 5, false, true);
	ANIMATION->addAnimation("sea_horizontal01", "flow_sea", 148, 151, 5, false, true);
	ANIMATION->addAnimation("sea_horizontal02", "flow_sea", 152, 155, 5, false, true);

	ANIMATION->addAnimation("sea_vertical00", "flow_sea", 156, 159, 5, false, true);
	ANIMATION->addAnimation("sea_vertical01", "flow_sea", 160, 163, 5, false, true);
	ANIMATION->addAnimation("sea_vertical02", "flow_sea", 164, 167, 5, false, true);
	ANIMATION->addAnimation("sea_noway", "flow_sea", 168, 171, 5, false, true);

	ANIMATION->addAnimation("sea_7ways00", "flow_sea", 172, 175, 5, false, true);
	ANIMATION->addAnimation("sea_7ways01", "flow_sea", 176, 179, 5, false, true);
	ANIMATION->addAnimation("sea_7ways02", "flow_sea", 180, 183, 5, false, true);
	ANIMATION->addAnimation("sea_7ways03", "flow_sea", 184, 187, 5, false, true);


	//============================= RIVER =============================
	//============================= RIVER =============================

	ANIMATION->addAnimation("river_line00", "flow_river", 0, 7, 10, false, true);
	ANIMATION->addAnimation("river_line01", "flow_river", 8, 15, 10, false, true);
	ANIMATION->addAnimation("river_curve00", "flow_river", 16, 23, 10, false, true);
	ANIMATION->addAnimation("river_curve01", "flow_river", 24, 31, 10, false, true);
	ANIMATION->addAnimation("river_curve02", "flow_river", 32, 39, 10, false, true);
	ANIMATION->addAnimation("river_curve03", "flow_river", 40, 47, 10, false, true);
	ANIMATION->addAnimation("river_3ways00", "flow_river", 48, 55, 10, false, true);
	ANIMATION->addAnimation("river_3ways01", "flow_river", 56, 63, 10, false, true);
	ANIMATION->addAnimation("river_3ways02", "flow_river", 64, 71, 10, false, true);
	ANIMATION->addAnimation("river_3ways03", "flow_river", 72, 79, 10, false, true);
	ANIMATION->addAnimation("river_4ways", "flow_river", 80, 87, 10, false, true);

	
}
