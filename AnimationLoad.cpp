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


	//============================== SEA ==============================
	//============================== SEA ==============================

	ANIMATION->addAnimation("sea_curve00", "flow_sea", 0, 3, 10, false, true);
	ANIMATION->addAnimation("sea_top", "flow_sea", 4, 7, 10, false, true);
	ANIMATION->addAnimation("sea_curve01", "flow_sea", 8, 11, 10, false, true);
	ANIMATION->addAnimation("sea_left", "flow_sea", 12, 15, 10, false, true);
	ANIMATION->addAnimation("sea_4ways", "flow_sea", 16, 19, 10, false, true);
	ANIMATION->addAnimation("sea_right", "flow_sea", 20, 23, 10, false, true);
	ANIMATION->addAnimation("sea_curve02", "flow_sea", 24, 27, 10, false, true);
	ANIMATION->addAnimation("sea_bottom", "flow_sea", 28, 31, 10, false, true);
	ANIMATION->addAnimation("sea_curve03", "flow_sea", 32, 35, 10, false, true);
	ANIMATION->addAnimation("sea_curve03", "flow_sea", 32, 35, 10, false, true);
	ANIMATION->addAnimation("sea_horizontal00", "flow_sea", 36, 39, 10, false, true);
	ANIMATION->addAnimation("sea_horizontal01", "flow_sea", 40, 43, 10, false, true);
	ANIMATION->addAnimation("sea_horizontal02", "flow_sea", 44, 47, 10, false, true);
	ANIMATION->addAnimation("sea_vertical00", "flow_sea", 48, 51, 10, false, true);
	ANIMATION->addAnimation("sea_vertical01", "flow_sea", 52, 55, 10, false, true);
	ANIMATION->addAnimation("sea_vertical02", "flow_sea", 56, 59, 10, false, true);
	ANIMATION->addAnimation("sea_noway", "flow_sea", 60, 63, 10, false, true);


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
