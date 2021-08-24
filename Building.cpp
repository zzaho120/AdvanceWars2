#include "framework.h"
#include "Building.h"

CBuilding::CBuilding() :
	CObject(),
	isHeadQuater(false),
	isFactory(false),
	tileIdx(0),
	income(0),
	def(0),
	playerType(PLAYER_TYPE::NONE)
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
