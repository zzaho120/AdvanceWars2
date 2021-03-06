#include "framework.h"
#include "Camera.h"

CCamera::CCamera()
{
    cam_size = { CAMERA_SIZE_X, CAMERA_SIZE_Y };
}

CCamera::CCamera(const CCamera& copy)
{
    CObject(ref);
    cam1 = copy.cam1;
    cam2 = copy.cam2;

    cam_size = copy.cam_size;
    target = copy.target;
}

CCamera::CCamera(const CCamera* copy)
{
    CObject(ref);
    cam1 = copy->cam1;
    cam2 = copy->cam2;

    cam_size = copy->cam_size;
    target = copy->target;
}

CCamera::~CCamera()
{
}

HRESULT CCamera::init()
{
    cam_size = { CAMERA_SIZE_X, CAMERA_SIZE_Y };
    return S_OK;
}

void CCamera::release()
{
}

void CCamera::update()
{
    cam1 = { target.x - CAMERA_MOVE_X - cam_size.x / 2, target.y - CAMERA_MOVE_Y - cam_size.y / 2 };
    cam2 = { cam1.x + cam_size.x, cam1.y + cam_size.y };

    if (cam1.x < 0)
    {
        cam1.x = 0;
        cam2.x = cam_size.x;
    }
    if (cam1.y < 0)
    {
        cam1.y = 0;
        cam2.y = cam_size.y;
    }
    if (cam2.x > MAP_SIZE_X)
    {
        cam2.x = MAP_SIZE_X;
        cam1.x = cam2.x - cam_size.x;
    }
    if (cam2.y > MAP_SIZE_Y)
    {
        cam2.y = MAP_SIZE_Y;
        cam1.y = cam2.y - cam_size.y;
    }
}

void CCamera::render()
{
}

CCamera& CCamera::operator=(const CCamera& ref)
{
    CObject::operator=(ref);
    cam1 = ref.cam1;
    cam2 = ref.cam2;

    cam_size = ref.cam_size;
    target = ref.target;
    return *this;
}

CCamera* CCamera::operator=(const CCamera* ref)
{
    CObject::operator=(ref);
    cam1 = ref->cam1;
    cam2 = ref->cam2;

    cam_size = ref->cam_size;
    target = ref->target;
    return this;
}