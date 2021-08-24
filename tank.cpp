#include "framework.h"
#include "tank.h"

tank::tank()
{
}

tank::~tank()
{
}

HRESULT tank::init(const char* imageName)
{

	_direction = TANKDIRECTION::TANKDIRECTION_UP;

	_image = IMAGE->findImage(imageName);

	_speed = 100.0f;

	_bullet = new bullet;
	_bullet->init("bullet", 10, 650);

	return S_OK;
}

void tank::release()
{
	SAFE_DELETE(_bullet);
}

void tank::update()
{
	if (InputManager->isStayKeyDown(VK_LEFT))
	{
		 tankMove();
		_direction = TANKDIRECTION::TANKDIRECTION_LEFT;
	}
	if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		tankMove();
		_direction = TANKDIRECTION::TANKDIRECTION_RIGHT;
	}
	if (InputManager->isStayKeyDown(VK_UP))
	{
		tankMove();
		_direction = TANKDIRECTION::TANKDIRECTION_UP;
	}
	if (InputManager->isStayKeyDown(VK_DOWN))
	{
		tankMove();
		_direction = TANKDIRECTION::TANKDIRECTION_DOWN;
	}

	if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		fire();
	}
	_bullet->update();
	bulletCollision();
}

void tank::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, 0, _frameY);
	_bullet->render();


	char strBlock[128];
	sprintf_s(strBlock, "������ġ  X: %d�� Ÿ��, Y: %d�� Ÿ��", tileX, tileY);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), 300, 10, strBlock, strlen(strBlock));

}

void tank::setTankPosition(RECT rc)
{
	_rc = rc;
	_x = rc.left + (_rc.right - _rc.left) / 2;
	_y = rc.top + (_rc.bottom - _rc.top) / 2;
}

void tank::tankMove()
{
	RECT rcCollision;
	int tileIndex[2] = { 0, };//�˻�� Ÿ��
	rcCollision = _rc;


	float elpasedTime = TIME->getElapsedTime();
	float moveSpeed = elpasedTime * _speed;


	switch (_direction)
	{
	case TANKDIRECTION::TANKDIRECTION_LEFT:
		_frameY = 2;
		_x -= moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION::TANKDIRECTION_RIGHT:
		_frameY = 1;
		_x += moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION::TANKDIRECTION_UP:
		_frameY =3;
		_y-= moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION::TANKDIRECTION_DOWN:
		_frameY = 0;
		_y += moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	//��ũ�� ���� ���  �ִ� Ÿ�� ��ȣ�� �˾ƿ���
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//��ũ�� Ÿ�� ��� �ִ��� Ȯ���� �����ϹǷ�
	//��ũ ���⿡ ���� �� ���� Ÿ�� ��ȣ�� ����Ѵ�.
	//�ε��� ��ȣ�� 2���� ������ ��Ʈ�� ����Ʈ, ž ��ġ�� ��ũ�� ��ġ�� ���ϰ�
	//��Ʈ�� ����Ʈ, ž�� Ÿ�� ��ȣ�� ������ ��������, �� �°� �������� �ֱ� ������
	//������ ������� ��ģ �� ���� Ÿ���� ��(ex : �������� ��� ��ũ ��ġ �ؿ� �ִ� �� �տ� �ִ� Ÿ��)�� �����´�.
	//�׷��� ��Ȯ�ϰ� ��ġ�� �ʾ����� ��� �Ҽ� �ֵ���.....

	switch (_direction)
	{
	case TANKDIRECTION::TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;//��ũ�� ��� �ִ� �༮
		tileIndex[1] = tileX + (tileY+1) * TILEX;//��ũ�� ��� �ִ� ����
		break;
	case TANKDIRECTION::TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX)+1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX)+1;//��ũ�� ��� �ִ� ������
		break;
	case TANKDIRECTION::TANKDIRECTION_UP:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX +1 +tileY * TILEX;
		break;
	case TANKDIRECTION::TANKDIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEX)+TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX)+TILEX;
		break;
	}

	for (size_t i = 0; i < 2; i++)
	{
		RECT rc;

		//�ش� Ÿ���� �Ӽ��� �������� ���ϴ� ���̸�
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVABLE) == ATTR_UNMOVABLE) &&
			IntersectRect(&rc, &_tankMap->getMap()[tileIndex[i]].rcTile, &rcCollision))
		{
			switch (_direction)
			
			{
			case TANKDIRECTION::TANKDIRECTION_LEFT:
				
				_rc.left = _tankMap->getMap()[tileIndex[i]].rcTile.right;//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.right = _rc.left + _image->getFrameWidth();			//��ũ�� ũ�⸸ŭ
				_x = _rc.left + (_rc.right - _rc.left) / 2;				//��ũ X�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)
				break;
			case TANKDIRECTION::TANKDIRECTION_RIGHT:
				_rc.right = _tankMap->getMap()[tileIndex[i]].rcTile.left;
				_rc.left = _rc.right - _image->getFrameWidth();			
				_x = _rc.left + (_rc.right - _rc.left) / 2;				
				break;
			case TANKDIRECTION::TANKDIRECTION_UP:
				_rc.top = _tankMap->getMap()[tileIndex[i]].rcTile.bottom;
				_rc.bottom = _rc.top + _image->getFrameHeight();
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			case TANKDIRECTION::TANKDIRECTION_DOWN:
				_rc.bottom = _tankMap->getMap()[tileIndex[i]].rcTile.top;
				_rc.top = _rc.bottom- _image->getFrameHeight();
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			}
			return;
		}

	}//end of for

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_rc = rcCollision;
}

void tank::fire()
{
	switch (_direction)
	{
	case TANKDIRECTION::TANKDIRECTION_LEFT:

		_bullet->fire(_x, _y, PI, 5.0f);
		break;
	case TANKDIRECTION::TANKDIRECTION_RIGHT:
		_bullet->fire(_x, _y, 0, 5.0f);
		break;
	case TANKDIRECTION::TANKDIRECTION_UP:
		_bullet->fire(_x, _y, PI/2, 5.0f);
		break;
	case TANKDIRECTION::TANKDIRECTION_DOWN:
		_bullet->fire(_x, _y, PI/2*3, 5.0f);
		break;
	}
}

void tank::bulletCollision()
{
	RECT rc;


	for (size_t i = 0; i < _bullet->getVBullet().size(); i++)
	{
		if (_bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2 < 0
			|| _bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2 > WINSIZEX
			|| _bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2 < 0
			|| _bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2 > WINSIZEY)
		{
			_bullet->removeMissile(i);
			return;
		}
		int tileIndex;//�˻��� Ÿ��
		int tileX, tileY;//�Ѿ� ���ư��� �ִ� Ÿ�� x,y

		if (_bullet->getVBullet()[i].angle == PI)
		{
			tileX = (_bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2) / TILESIZE;
			tileY = (_bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2) / TILESIZE;
			tileIndex = tileX + tileY * TILEX;
		}
		else if (_bullet->getVBullet()[i].angle == 0)
		{
			tileX = (_bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2) / TILESIZE;
			tileY = (_bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2) / TILESIZE;
			tileIndex = tileX + tileY * TILEX;
		}
		else if (_bullet->getVBullet()[i].angle == PI/2)
		{
			tileX = (_bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2) / TILESIZE;
			tileY = (_bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2) / TILESIZE;
			tileIndex = tileX + tileY * TILEX;
		}
		else if (_bullet->getVBullet()[i].angle == PI / 2*3)
		{
			tileX = (_bullet->getVBullet()[i].rc.left + IMAGE->findImage("bullet")->getWidth() / 2) / TILESIZE;
			tileY = (_bullet->getVBullet()[i].rc.top + IMAGE->findImage("bullet")->getHeight() / 2) / TILESIZE;
			tileIndex = tileX + tileY * TILEX;
		}
		if (_tankMap->getMap()[tileIndex].obj == OBJECT::OBJ_BLOCK
			|| _tankMap->getMap()[tileIndex].obj == OBJECT::OBJ_BLOCKS
			|| _tankMap->getMap()[tileIndex].obj == OBJECT::OBJ_BLOCK3)
		{
			_tankMap->attackBlock(tileIndex);
			_bullet->removeMissile(i);
		}
	}
}
