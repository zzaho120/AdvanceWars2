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
	sprintf_s(strBlock, "현재위치  X: %d번 타일, Y: %d번 타일", tileX, tileY);
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
	int tileIndex[2] = { 0, };//검사용 타일
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

	//땅크가 지금 밟고  있는 타일 번호를 알아오자
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//땅크가 타일 어디에 있는지 확인이 가능하므로
	//땅크 방향에 따라서 그 앞의 타일 번호를 계산한다.
	//인덱스 번호가 2개인 이유는 렉트의 레프트, 탑 위치로 땅크의 위치를 구하고
	//렉트의 레프트, 탑이 타일 번호에 걸쳐져 있을수도, 딱 맞게 있을수도 있기 때문에
	//걸쳐져 있을경우 걸친 그 밑의 타일의 값(ex : 오른쪽일 경우 땅크 위치 밑에 있는 값 앞에 있는 타일)을 가져온다.
	//그래서 정확하게 걸치지 않았을때 통과 할수 있도록.....

	switch (_direction)
	{
	case TANKDIRECTION::TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;//땅크가 밟고 있는 녀석
		tileIndex[1] = tileX + (tileY+1) * TILEX;//땅크가 밟고 있는 왼쪽
		break;
	case TANKDIRECTION::TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX)+1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX)+1;//땅크가 밟고 있는 오른쪽
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

		//해당 타일의 속성이 움직이지 못하는 곳이면
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVABLE) == ATTR_UNMOVABLE) &&
			IntersectRect(&rc, &_tankMap->getMap()[tileIndex[i]].rcTile, &rcCollision))
		{
			switch (_direction)
			
			{
			case TANKDIRECTION::TANKDIRECTION_LEFT:
				
				_rc.left = _tankMap->getMap()[tileIndex[i]].rcTile.right;//왼쪽 타일의 라이트의 위치를 탱크의 레프트의 위치로 고정
				_rc.right = _rc.left + _image->getFrameWidth();			//탱크의 크기만큼
				_x = _rc.left + (_rc.right - _rc.left) / 2;				//탱크 X의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로)
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
		int tileIndex;//검사할 타일
		int tileX, tileY;//총알 날아가고 있는 타일 x,y

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
