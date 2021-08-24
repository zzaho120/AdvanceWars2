#pragma once
#include"gameNode.h"
class enemy : public gameNode
{
private:

	image* _image;
	RECT _rc;
	
	
	int _currentFrameX;
	int _currentFrameY;
	int _count;


	int _fireCount;
	int _rndfireCount;
public:

	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void  update();
	void render();


	virtual void draw();
	virtual void  animation();


	bool bulletCountFire();

	RECT getRect() { return _rc; }




};

