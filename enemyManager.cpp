#include "framework.h"
#include "enemyManager.h"
#include"rocket.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    this->setMinion();

    _bullet = new bullet;
    _bullet->init("bullet", 10, 600);

    return S_OK;
}

void enemyManager::release()
{
    SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
    _viMinion = _vMinion.begin();
    for (_viMinion; _viMinion!=_vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->update();
    }
    //�Ѿ�
    _bullet->update();
    collision();
    this->minionBulletFire();
}
void enemyManager::render()
{
    _viMinion = _vMinion.begin();
    for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->render();
    }
    _bullet->render();
}

void enemyManager::setMinion()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 6;j++)
        {
            enemy* ufo;
            ufo = new minion;
            ufo->init("ufo", PointMake(100 + j * 150, 100 + i * 200));
            _vMinion.push_back(ufo);
        }
    }
}

void enemyManager::minionBulletFire()
{
    _viMinion = _vMinion.begin();
    for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
    {
        if ((*_viMinion)->bulletCountFire())
        {
            //������
            /*RECT rc = (*_viMinion)->getRect();
            _bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI_2, 5.0f);*/


            //�÷��̾� ���� ������
            RECT rc = (*_viMinion)->getRect();
            _bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
                UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
                    rc.bottom + (rc.top - rc.bottom) / 2,
                    _rocket->getRocketImage()->getX() + _rocket->getRocketImage()->getWidth() / 2,
                    _rocket->getRocketImage()->getY()), 5.0f);
        }
    }
}

void enemyManager::removeMinion(int arrNum)
{
    _vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::collision()
{
    for (int i = 0; i < _bullet->getVBullet().size(); i++)
    {
        RECT rc;

        if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_rocket->getRocketImage()->getBoundingBox()))
        {
            _bullet->removeMissile(i);
            _rocket->hitDamage(10);
        }
    }
}
