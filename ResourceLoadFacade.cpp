#include "framework.h"
#include "ResourceLoadFacade.h"

CResourceLoadFacade::CResourceLoadFacade()
{
}

CResourceLoadFacade::~CResourceLoadFacade()
{
}

void CResourceLoadFacade::resourceLoad()
{
	imgLoad.resourceLoad();
	aniLoad.resourceLoad();
	soundLoad.resourceLoad();
}
