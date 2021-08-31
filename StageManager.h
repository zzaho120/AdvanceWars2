#pragma once
#include"singleton.h"

class CMap;
class CStageManager : public Singleton<CStageManager>
{
private:
	CMap* curMap;
public:
	CStageManager();
	~CStageManager();

	CMap* getCurMap() { return curMap; }

	void setCurMap(CMap* map) { curMap = map; }
};