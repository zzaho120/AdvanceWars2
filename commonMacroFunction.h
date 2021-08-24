#pragma once
//===============================================
//commonMacroFunction(�ʿ��� �κ��� �����������)
//===============================================

//����Ʈ
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT�����(�»�� ����)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}
//RECT�����(�߽������� ����)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}

//�簢�� �׸���
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

//�� �׸���
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
