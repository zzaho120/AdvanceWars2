#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "Player.h"
#include "UIManager.h"
#include "GameData.h"

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

	CGameData* gameData;

	CCommand* command;

	bool isGameover;
	bool isKO[2];
public:
	CGameManager();
	CGameManager(const char* fileName);
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

	// UI 관련 메세지 및 함수
	void viewFactoryMsg();
	void viewOptionMsg();
	void viewActionMsg();
	void closeUIMsg();
	
	// 빌딩 점령 관련 메시지 및 함수
	void captureBuildingMsg();

	// 공격 관련 메시지 및 함수
	void attackUnitSettingMsg();
	void attackUnitMsg();
	bool isAvailableAttack();
	bool isAttackMode();
	bool isUnitOnCursor();
	int predictDamaged();

	// 유닛 삭제 관련 메시지 및 함수
	void destroyUnitMsg(CUnit* unit);

	// 보급 관련 메시지 및 함수
	bool isAvailableSupply();
	void supplyUnitMsg();

	// 유닛 사정거리 출력 관련 메시지 및 함수
	void viewUnitRangeMsg();
	void cancelUnitRangeMsg();

	// 턴 시작 시 수행 관련 메시지 및 함수
	void incomeMoneyMsg();
	void unitRepairMsg();

	// 게임 종료 분기점 체크 함수
	void isGameEnd();

	// 커맨드 실행
	void commandExcute();

	CMap* getMap() { return map; }
	CPlayer* getCurPlayer() { return curPlayer; }
	CCursor* getCursor() { return cursor; }
	CUnitManager* getUnitMgr() { return unitMgr; }
	CBuildingManager* getBuildingMgr() { return buildingMgr; }
	CGameData* getGameData() { return gameData; }
};