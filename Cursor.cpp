#include "framework.h"
#include "Cursor.h"

CCursor::CCursor() :
	CObject(), tileIdx(0), gameMgr(nullptr)
{
	ANIMATION->start("cursor_ani");
}

CCursor::CCursor(Vec2 pos, int tileIndex) :
	CObject(pos, TILE_SIZE, IMAGE->findImage("cursor"), ANIMATION->findAnimation("cursor_ani")),
	tileIdx(tileIndex), gameMgr(nullptr)
{
	ANIMATION->start("cursor_ani");
}


CCursor::~CCursor()
{
}

HRESULT CCursor::init()
{
	ANIMATION->start("cursor_ani");
    return S_OK;
}

HRESULT CCursor::init(CGameManager* mgr)
{
	gameMgr = mgr;
	ANIMATION->start("cursor_ani");
	return S_OK;
}

void CCursor::release()
{
}

void CCursor::update()
{
	cursorMove();
}

void CCursor::render()
{
	img->aniRender(getMapDC(), pos.x - 32, pos.y - 32, ani);
}

void CCursor::cursorMove()
{
	// 버튼에 의한 커맨드 패턴으로 바꿀지 고민 중
	if (InputManager->isOnceKeyDown(VK_LEFT))
	{
		pos.x -= TILE_SIZE_X;
		tileIdx -= 1;
	}
	else if (InputManager->isOnceKeyDown(VK_RIGHT))
	{
		pos.x += TILE_SIZE_X;
		tileIdx += 1;
	}
	else if (InputManager->isOnceKeyDown(VK_UP))
	{
		pos.y -= TILE_SIZE_Y;
		tileIdx -= 30;
	}
	else if (InputManager->isOnceKeyDown(VK_DOWN))
	{
		pos.y += TILE_SIZE_Y;
		tileIdx += 30;
	}
}
