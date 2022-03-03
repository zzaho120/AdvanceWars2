#include "framework.h"
#include "Command.h"
#include "CommandHistory.h"

CCommandHistory::CCommandHistory()
{
	
}

CCommandHistory::~CCommandHistory()
{
}

HRESULT CCommandHistory::init()
{
	iterHistory = cmdHistory.begin();
	return S_OK;
}

void CCommandHistory::add(CCommand* cmd)
{
	cmdHistory.push_back(cmd);
}

void CCommandHistory::undo()
{
	cmdHistory.pop_back();
}
