#include "framework.h"
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