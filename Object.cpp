#include "framework.h"
#include "Object.h"

CObject::CObject() :
	pos({ WINSIZEX / 2, WINSIZEY / 2 }),
	size({ 10, 10 }),
	img(nullptr),
	ani(nullptr)
{
}

CObject::~CObject()
{
	SAFE_DELETE(img);
	SAFE_DELETE(ani);
}

HRESULT CObject::init()
{
	return S_OK;
}

void CObject::release()
{
}

void CObject::update()
{
}

void CObject::render()
{
}
