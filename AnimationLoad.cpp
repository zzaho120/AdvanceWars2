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

	ANIMATION->addAnimation("river_vertical", "river", 0, 7, 10, false, true);
	ANIMATION->addAnimation("river_horizontal", "river", 8, 15, 10, false, true);
	ANIMATION->addAnimation("river_curve01", "river", 16, 23, 10, false, true);
	ANIMATION->addAnimation("river_curve02", "river", 24, 31, 10, false, true);
	ANIMATION->addAnimation("river_curve03", "river", 32, 39, 10, false, true);
	ANIMATION->addAnimation("river_curve04", "river", 40, 47, 10, false, true);

	//============================ CURSOR =============================
	//============================ CURSOR =============================
	
	ANIMATION->addAnimation("cursor_ani", "cursor", 0, 4, 10, false, true);
}
