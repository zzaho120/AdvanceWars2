#pragma once
//===============================================
//commonMacroFunction(필요한 부분은 직접만들어써라)
//===============================================

//포인트
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT만들기(좌상단 기준)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}

//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc,RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void ElllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color)
{
	*brush = CreateSolidBrush(color);
	*brush = (HBRUSH)SelectObject(hdc,*brush);
}

inline int RectEdge(Vec2 pos, Vec2 size, RECT_EDGE edge)
{
	switch (edge)
	{
	case RECT_EDGE::LEFT:
		return pos.x - size.x / 2;
		break;
	case RECT_EDGE::RIGHT:
		return pos.x + size.x / 2;
		break;
	case RECT_EDGE::TOP:
		return pos.y - size.y / 2;
		break;
	case RECT_EDGE::BOTTOM:
		return pos.y + size.y / 2;
		break;
	}
}

//RECT 중점
inline int RectCenterX(RECT& rc)
{
	return (rc.left + rc.right) / 2;
}

inline int RectCenterY(RECT& rc)
{
	return (rc.top + rc.bottom) / 2;
}

//RECT 높이/너비
inline int RectWidth(RECT& rc)
{
	return rc.right - rc.left;
}

inline int RectHeight(RECT& rc)
{
	return rc.bottom - rc.top;
}

inline Vec2 getLeftTopVec2(Vec2 pos, Vec2 size)
{
	return Vec2{ pos.x - size.x / 2, pos.y - size.y / 2 };
}
