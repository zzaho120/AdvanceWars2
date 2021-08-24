#pragma once
#include"gameNode.h"
#include"Astar.h"
class mainGame : public gameNode
{
private:
	
	Astar* _astar;


public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);


	
	
};

