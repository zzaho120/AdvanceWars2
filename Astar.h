#pragma once
#include"singleton.h"

#define TILE_X 20	//����Ÿ��
#define TILE_Y 20	//����Ÿ��
#define WIDTH  35	//Ÿ�� ���α���
#define HEIGHT 35	//Ÿ�� ���α���
#define BIGNUM 5000 


struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;		//�������� �ֳ�	
	bool listOn;		//openList�� �߰��Ǿ����� ����
	int i, j;
	int F, G, H;
	char str[128];
	aStarTile* parent;	//�θ� Ÿ�� �ּ�
	TILE_TYPE type;		//Ÿ�ϼӼ�
	int tileIdx;
	Vec2 pos;
};

class CAstar : public Singleton<CAstar>
{
private:

	aStarTile _tile[TILE_NUM_X * TILE_NUM_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;
	stack<int> roadList;

	ASTAR_STATE _astarState;
	TILE_TYPE _selectType;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex;	//���߿� �߰��� Ŭ���� ����Ʈ�� �ε���

	int Ci;
	int Cj;
	int Cg;

	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;

	bool isArrive;
public:
	CAstar();
	~CAstar();

	HRESULT init();
	void release();
	void update();

	void tileInitializing();//��ġ�� �Ӽ��� �°� �ʱ�ȭ
	void addOpenList();	//���¸���Ʈ �߰�
	void caculateH();		//���¸���Ʈ�� Ÿ�� H�� ���
	void caculateF();		//���¸���Ʈ�� Ÿ�� F�� ���
	void addCloseList();	//���� ���� F������ Ŭ���� ����Ʈ�� �߰�
	void checkArrive();	//�����ߴ��� ���� üũ
	void setStartEnd(int startIdx, int endIdx);

	stack<int> getRoadList() { return roadList; }
	aStarTile* getAstarTile() { return _tile; }

	void eraseRoadList() { if(!roadList.empty()) roadList.pop(); }
};