#include "framework.h"
#include "rocket.h"
#include"enemyManager.h"
rocket::rocket()
{
}

rocket::~rocket()
{
}

HRESULT rocket::init()
{

	_player = IMAGE->addImage("rocket", "images/rocket.bmp", WINSIZEX / 2, WINSIZEY - 200, 52, 64, true, RGB(255, 0, 255));

	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _player->getWidth(), _player->getHeight());


	_missile = new missile;
	_missile->init(10, 1000);
	_nuclear = new nuclear;
	_nuclear->init(30, 1000);


	_maxHp = _currentHp = 100;
	_hpBar = new progressBar;
	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void rocket::release()
{
	SAFE_DELETE(_missile);
	SAFE_DELETE(_nuclear);
	SAFE_DELETE(_hpBar);
}

void rocket::update()
{
	/*if (InputManager->isStayKeyDown(VK_LEFT))
	{
		OffsetRect(&rc, -5, 0);
	}
	if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		OffsetRect(&rc, 5, 0);
	}
	if (InputManager->isStayKeyDown(VK_DOWN))
	{
		OffsetRect(&rc, 0, 5);
	}
	if (InputManager->isStayKeyDown(VK_UP))
	{
		OffsetRect(&rc, 0, -5);
	}*/


	if (InputManager->isStayKeyDown(VK_LEFT) && _player->getX() > 0)
	{
		_player->setX(_player->getX() - 5);
	}
	if (InputManager->isStayKeyDown(VK_RIGHT) && _player->getX()+_player->getWidth()<WINSIZEX)
	{
		_player->setX(_player->getX() + 5);
	}
	if (InputManager->isStayKeyDown(VK_UP) && _player->getY() > 0)
	{
		_player->setY(_player->getY() - 5);
	}
	if (InputManager->isStayKeyDown(VK_DOWN) && _player->getY() + _player->getHeight()<WINSIZEY)
	{
		_player->setY(_player->getY() +5);
	}


	if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		//_missile->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
		_missile->fire(_player->getX() + _player->getWidth() / 2, _player->getY() - 50);
	}
	if (InputManager->isOnceKeyDown('Z'))
	{
		//_nuclear->fire(rc.right - (rc.right - rc.left) / 2, rc.top - 50);
		_nuclear->fire(_player->getX() + _player->getWidth() / 2, _player->getY() - 50);
	}
	_missile->update();
	_nuclear->update();

	collision();


	_hpBar->setX(_player->getX());
	_hpBar->setY(_player->getY()-15);
	_hpBar->setGauge(_currentHp, _maxHp);
	_hpBar->update();


	if (InputManager->isOnceKeyDown('S'))
	{
		char  temp[64];
		vector<string>vStr;

		vStr.push_back(_itoa(_currentHp, temp, 10));
		vStr.push_back(_itoa(_maxHp, temp, 10));
		vStr.push_back(_itoa(_player->getX(), temp, 10));
		vStr.push_back(_itoa(_player->getY(), temp, 10));

		TXT->txtSave("save/rocketData.txt", vStr);

	}
	if (InputManager->isOnceKeyDown('L'))
	{
		vector<string> vStr(TXT->txtLoad("save/rocketData.txt"));

		_currentHp = stoi(vStr[0]);
		_maxHp = stoi(vStr[1]);
		_player->setX(stoi(vStr[2]));
		_player->setY(stoi(vStr[3]));




	}

}

void rocket::render()
{
	_player->render(getMemDC(), _player->getX(),  _player->getY());
	_missile->render();
	_nuclear->render();

	_hpBar->render();

}

void rocket::removeMissile(int arrNum)
{
	_nuclear->removeNuclear(arrNum);
}

void rocket::collision()
{
	for (int i = 0; i < _nuclear->getVBullet().size(); i++)
	{
		for (int j = 0;j <_em->getVMinion().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_nuclear->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_nuclear->removeNuclear(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void rocket::hitDamage(float damage)
{
	_currentHp -= damage;
}
