#pragma once
#include"ImageLoad.h"
#include"AnimationLoad.h"
#include"SoundLoad.h"
class CResourceLoadFacade
{
private:
	CImageLoad imgLoad;
	CAnimationLoad aniLoad;
	CSoundLoad soundLoad;
public:
	CResourceLoadFacade();
	~CResourceLoadFacade();

	void resourceLoad();
};