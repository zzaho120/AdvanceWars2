#pragma once
#include "singleton.h"
class CCommand;
class CCommandHistory : public Singleton<CCommandHistory>
{
private:
	vector<CCommand*> cmdHistory;
	vector<CCommand*>::iterator iterHistory;
public:
	CCommandHistory();
	~CCommandHistory();

	HRESULT init();

	void add(CCommand* cmd);
	void undo();
};