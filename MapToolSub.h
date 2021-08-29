#pragma once
#include"gameNode.h"

class CMapToolSub : public gameNode
{
private:
	tagSampleTile sampleTile[SAMPLE_TILE_X * SAMPLE_TILE_Y];
public:
	CMapToolSub();
	~CMapToolSub();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapToolSetup();
	void setMap();
};