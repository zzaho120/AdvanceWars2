#pragma once
#include"image.h"

static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _mapBuffer = IMAGE->addImage("mapBuffer", MAP_SIZE_X, MAP_SIZE_Y);
static image* _tileBuffer = IMAGE->addImage("tileBuffer", MAP_SIZE_X, MAP_SIZE_Y);
class gameNode
{
private:
	HDC _hdc;
	bool  _managerInit;
	RECT _rc;
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	image* getBackBuffer() const { return _backBuffer; }
	image* getMapBuffer() const { return _mapBuffer; }
	image* getTileBuffer() const { return _tileBuffer; }

	HDC getHDC() const { return _hdc; }
	HDC getMemDC() const { return _backBuffer->getMemDC(); }
	HDC getMapDC() const { return _mapBuffer->getMemDC(); }
	HDC getTileDC() const { return _tileBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	RECT getClientRC() { return _rc; }
};