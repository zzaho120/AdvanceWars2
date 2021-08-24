#pragma once
#include"ImageLoad.h"
#include"AnimationLoad.h"

class CResourceLoadFacade
{
private:
	CImageLoad imgLoad;
	CAnimationLoad aniLoad;
public:
	CResourceLoadFacade();
	~CResourceLoadFacade();

	void resourceLoad();
};