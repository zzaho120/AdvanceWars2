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

	//============================ CURSOR =============================
	//============================ CURSOR =============================
	
	ANIMATION->addAnimation("cursor_ani", "cursor", 0, 4, 10, false, true);
}
