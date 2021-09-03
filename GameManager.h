#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "Player.h"
#include "UIManager.h"

class CGameManager : public gameNode
{
private:
	CMap* map;
	CCamera* cam;
	CCursor* cursor;

	CPlayer* playerArr[2];
	CPlayer* curPlayer;

	CUnitManager* unitMgr;
	CBuildingManager* buildingMgr;
	CUIManager* uiMgr;

	CCommand* command;

public:
	CGameManager();
	~CGameManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 맵 클래스 기반의 데이터로 빌딩과 유닛을 매니저에 추가
	void initObject();

	// 플레이어 턴 교체 메세지
	void changePlayerMsg();

	// 유닛 생성 관련 메세지
	void generateUnitMsg(UNIT_TYPE type);
	
	// 유닛 선택 관련 메세지
	void selectUnitMsg();
	void selectUnitCancelMsg();

	// 유닛 이동 관련 메세지 및 함수
	void moveUnitSettingMsg();
	void moveUndoMsg();
	void completeMoveUnitMsg();
	bool isUnitArrive();

	// 유닛 생산 관련 메세지 및 함수
	void viewFactoryMsg();
	void viewOptionMsg();
	void closeUIMsg();
	
	void incomeMoneyMsg();

	void commandExcute();

	CMap* getMap() { return map; }
	CPlayer* getCurPlayer() { return curPlayer; }
	CCursor* getCursor() { return cursor; }
};