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
	AddFontResourceA("font/家具稠8.ttf");
	HFONT hFont, oldFont;
	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("家具稠8"));
	oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
}
