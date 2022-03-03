#pragma once
#include"singleton.h"
#include"image.h"
class imageManager : public Singleton<imageManager>
{
private:
	//������ ���� �̹��� ���
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;

	mapImageList _mImageList;
public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, const int width, const int height);
	image* addImage(string strKey, const char* fileName, const int width, const int height, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, const float x, const float y, const int const width, const int height, bool trans, COLORREF transColor);


	//Ű������ ������ �̹��� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));

	//�̹����� ã�ƶ�
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	bool deleteImage(string strKey);

	//�̹��� ��ü����
	bool deleteAll();

	//����
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, const int destX, const int destY);
	void render(string strKey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight);
	void alphaRender(string strKey, HDC hdc, const int destX, const int destY, BYTE alpha);

	//������
	void frameRender(string strKey, HDC hdc, const int destX, const int destY);
	void frameRender(string strKey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);
	void alphaFrameRender(string strKey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha);
	
	//����
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

};

