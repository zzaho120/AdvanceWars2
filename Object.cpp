#include "framework.h"
#include "Object.h"

CObject::CObject() :
	pos({ WINSIZEX / 2, WINSIZEY / 2 }),
	size({ 10, 10 }),
	img(nullptr),
	ani(nullptr)
{ }

CObject::CObject(const CObject& copy)
{
	pos = copy.pos;
	size = copy.size;

	img = copy.img;
	ani = copy.ani;
}

CObject::CObject(const CObject* copy)
{
	pos = copy->pos;
	size = copy->size;

	img = copy->img;
	ani = copy->ani;
}

CObject::CObject(Vec2 _pos, Vec2 _size, image* _img, animation* _ani) :
	pos(_pos), size(_size), 
	img(_img), ani(_ani)
{
}

CObject::~CObject()
{
	//if(img != nullptr)
	//	SAFE_DELETE(img);
	//if(ani != nullptr)
	//	SAFE_DELETE(ani);
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

CObject& CObject::operator=(const CObject& ref)
{
	pos = ref.pos;
	size = ref.size;

	img = ref.img;
	ani = ref.ani;
	return *this;
}

CObject* CObject::operator=(const CObject* ref)
{
	pos = ref->pos;
	size = ref->size;

	img = ref->img;
	ani = ref->ani;
	return this;
}
