#pragma once
#include"gameNode.h"
#include"tankMap.h"
#include"bullet.h"

enum class  TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
public:
	tank();
	~tank();

	int _frameY;
	float _speed;
	float _x, _y;
	int tileX, tileY;//��ũ�� ��� �ִ� Ÿ�� ��ȣ

	TANKDIRECTION _direction;
	tankMap* _tankMap;
	bullet* _bullet;
	image* _image;
	RECT _rc;



	HRESULT init(const char* imageName);
	void release();
	void update();
	void render();

	void setTankPosition(RECT rc);
	void tankMove();
	void fire();
	void bulletCollision();

	void setTankMapMemoryAdress(tankMap* tm) { _tankMap = tm; }


};

