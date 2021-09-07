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

	// �� Ŭ���� ����� �����ͷ� ������ ������ �Ŵ����� �߰�
	void initObject();

	// �÷��̾� �� ��ü �޼���
	void changePlayerMsg();

	// ���� ���� ���� �޼���
	void generateUnitMsg(UNIT_TYPE type);
	
	// ���� ���� ���� �޼���
	void selectUnitMsg();
	void selectUnitCancelMsg();

	// ���� �̵� ���� �޼��� �� �Լ�
	void moveUnitSettingMsg();
	void moveUndoMsg();
	void completeMoveUnitMsg();
	bool isUnitArrive();

	// UI ���� �޼��� �� �Լ�
	void viewFactoryMsg();
	void viewOptionMsg();
	void viewActionMsg();
	void closeUIMsg();
	
	// ���� ���� ���� �޽��� �� �Լ�
	void captureBuildingMsg();

	// ���� ���� �޽��� �� �Լ�
	void attackUnitSettingMsg();
	void attackUnitMsg();
	bool isAvailableAttack();
	bool isAttackMode();
	bool isUnitOnCursor();
	int predictDamaged();

	// ���� ���� ���� �޽��� �� �Լ�
	void destroyUnitMsg(CUnit* unit);

	// ���� ���� �޽��� �� �Լ�
	bool isAvailableSupply();
	void supplyUnitMsg();

	// ���� �����Ÿ� ��� ���� �޽��� �� �Լ�
	void viewUnitRangeMsg();
	void cancelUnitRangeMsg();

	// �� ���� �� ���� ���� �޽��� �� �Լ�
	void incomeMoneyMsg();
	void unitRepairMsg();

	// ���� ���� �б��� üũ �Լ�
	void isGameEnd();

	// Ŀ�ǵ� ����
	void commandExcute();

	CMap* getMap() { return map; }
	CPlayer* getCurPlayer() { return curPlayer; }
	CCursor* getCursor() { return cursor; }
	CUnitManager* getUnitMgr() { return unitMgr; }
	CBuildingManager* getBuildingMgr() { return buildingMgr; }
	CGameData* getGameData() { return gameData; }
};