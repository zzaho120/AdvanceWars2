// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//==========================================
//				 매크로 설정
//==========================================
#define WINNAME			(LPTSTR)(TEXT("20210823~20210910_개인프로젝트_어드밴스워즈2"))
#define WINSTARTX		100
#define WINSTARTY		100
#define WINSIZEX		1024
#define WINSIZEY		768
#define	WINSTYLE		WS_CAPTION | WS_SYSMENU

//==========================================
//					STL
//==========================================
#include<vector>
#include<map>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<cmath>
//==========================================
//				 내가만든 헤더파일
//==========================================
#include"enum.h"
#include"vector2.h"
#include"commonMacroFunction.h"
#include"globalValue.h"
#include"Input.h"
#include"imageManager.h"
#include"timeManager.h"
#include"sceneManager.h"
#include"soundManager.h"
#include"animationManager.h"
#include"effectManager.h"
#include"randomFunction.h"
#include"utils.h"
#include"SubWindow.h"
#include"UnitFactory.h"
#include"BuildingFactory.h"
#include"Astar.h"
#include"CommandHistory.h"
#include"MapDataManager.h"
//======================================
//##			매니저들			  ##
//======================================
#define InputManager	Input::getSingleton()
#define RND				RandomFunction::getSingleton()
#define IMAGE			imageManager::getSingleton()
#define TIME			timeManager::getSingleton()
#define SCENE			SceneManager::getSingleton()
#define SOUND			soundManager::getSingleton()
#define ANIMATION		animationManager::getSingleton()
#define EFFECT			effectManager::getSingleton()
#define SUBWIN			CSubWindow::getSingleton()
#define UNITFACTORY		CUnitFactory::getSingleton()
#define BUILDINGFACTORY	CBuildingFactory::getSingleton()
#define ASTAR			CAstar::getSingleton()
#define HISTORY			CCommandHistory::getSingleton()
#define MAPDATA			CMapDataManager::getSingleton()
//==========================================
//			메인게임 릴리즈에서 사용
//==========================================
#define SAFE_DELETE(p) {if(p) {delete(p);(p) = nullptr;}}
//========================================================
//		전역변수 아이들(인스턴스,윈도우 핸들, 마우스 좌표)
//========================================================

extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;

