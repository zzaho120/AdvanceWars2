#include "framework.h"
#include "Unit.h"
#include "Building.h"

CBuilding::CBuilding() :
	CObject(),
	isHQ(false),
	isFactory(false),
	tileIdx(0),
	playerType(PLAYER_TYPE::NONE),
	capturePoint(0)
{ }

CBuilding::CBuilding(PLAYER_TYPE type, Vec2 pos, bool factory, bool HQ, int idx) : 
	CObject(pos, { TILE_SIZE_X, TILE_NUM_Y }), playerType(type), isFactory(factory), 
	isHQ(HQ), tileIdx(idx), capturePoint(20)
{ }

CBuilding::~CBuilding()
{
}

HRESULT CBuilding::init()
{
	return S_OK;
}

void CBuilding::release()
{
}

void CBuilding::update()
{
}

void CBuilding::render()
{
}

void CBuilding::capture(CUnit* unit)
{
	if (capturePoint > 0)
	{
		capturePoint -= unit->getHP();
		if (capturePoint <= 0)
		{
			playerType = unit->getPlayerType();
			unCapture();

			if (SOUND->isPlaySound("capture_finish"))
				SOUND->stop("capture_finish");
			if (!SOUND->isPlaySound("capture_finish"))
				SOUND->play("capture_finish", 0.4F);
		}
		else
		{
			if (SOUND->isPlaySound("capturing"))
				SOUND->stop("capturing");
			if (!SOUND->isPlaySound("capturing"))
				SOUND->play("capturing", 0.4F);
		}
	}
}

void CBuilding::unCapture()
{
	capturePoint = 20;
}
