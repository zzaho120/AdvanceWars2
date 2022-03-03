#pragma once
#include"gameNode.h"
#include"ImageLoad.h"
#include"AnimationLoad.h"
#include"SoundLoad.h"
class CResourceLoadFacade : public gameNode
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