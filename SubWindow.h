#pragma once
#include"singleton.h"

class CMapTool;
class TestMonsterScene;


class CSubWindow :public Singleton<CSubWindow>
{
private:
	HWND hWnd;
	static POINT ptMouse;

	image* backBuffer;
	gameNode* currentScene;

	HWND btnDraw;
	HWND btnInit;

	HWND btnSave;
	HWND btnLoad;

	HWND btnExit;
	HWND editStr;

	HWND listFile;
	HWND btnRemoveFile;

	POINT tileFrame;

	int clickIndex;
	int fileCnt;

	bool isActive;

	CMapTool* map;
	TestMonsterScene* test;
public:
	CSubWindow();
	~CSubWindow();

	void init();
	void release();
	void update();
	void render();

	void SetScene(gameNode* scene);

	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetHwnd() { return hWnd; }

	static POINT GetMousePos() { return ptMouse; }

	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }

	void SetTileFrame(POINT frame) { tileFrame = frame; }
	POINT GetTileFrame() { return tileFrame; }

	void SetFrameIndex(int index) { clickIndex = index; }
	int GetFrameIndex() { return clickIndex; }

	void SetMapLink(CMapTool* _map) { map = _map; }
	void SetTestLink(TestMonsterScene* _test) { test = _test; }

	CMapTool* getMap() { return map; }
	TestMonsterScene* getTest() { return test; }

	HWND getListHandle() { return listFile; }

	void CreateSubWindow();

	void FileListSet();

	void subWindowClose();
};