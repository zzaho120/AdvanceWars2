#pragma once
#include"singleton.h"
class CMapDataManager : public Singleton<CMapDataManager> 
{
private:
	vector<CMap*> vecMap;

	CMap* curMap;
public:
	CMapDataManager();
	~CMapDataManager();

	HRESULT init();
	void release();
	void render();

	vector<CMap*> getVecMap() { return vecMap; }
	CMap* getCurMap() { return curMap; }

	void setCurMap(int idx) { curMap = vecMap[idx]; }
};

