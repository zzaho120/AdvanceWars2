#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Camera.h"
#include "Cursor.h"
#include "Player.h"

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

	CCommand* command;
public:
	CGameManager();
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

	// ���� ���� ���� �޼��� �� �Լ�
	void viewFactoryMsg();
	
	void commandExcute();
};