#pragma once
class CCommand
{
private:

public:
	virtual ~CCommand() { };
	virtual void excute() = 0;
	virtual void undo() = 0;
};