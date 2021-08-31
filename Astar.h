#pragma once
#include"singleton.h"

#define TILE_X 20	//가로타일
#define TILE_Y 20	//세로타일
#define WIDTH  35	//타일 가로길이
#define HEIGHT 35	//타일 세로길이
#define BIGNUM 5000 


struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;		//지나갈수 있냐	
	bool listOn;		//openList에 추가되었는지 여부
	int i, j;
	int F, G, H;
	char str[128];
	aStarTile* parent;	//부모 타일 주소
	TILE_TYPE type;		//타일속성
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
	int _lastIndex;	//나중에 추가된 클로즈 리스트의 인덱스

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

	void tileInitializing();//배치후 속성에 맞게 초기화
	void addOpenList();	//오픈리스트 추가
	void caculateH();		//오픈리스트내 타일 H값 계산
	void caculateF();		//오픈리스트내 타일 F값 계산
	void addCloseList();	//가장 작은 F선택후 클로즈 리스트에 추가
	void checkArrive();	//도착했는지 여부 체크
	void setStartEnd(int startIdx, int endIdx);

	stack<int> getRoadList() { return roadList; }
	aStarTile* getAstarTile() { return _tile; }

	void eraseRoadList() { if(!roadList.empty()) roadList.pop(); }
};