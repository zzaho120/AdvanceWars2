#pragma once
#include"gameNode.h"
#include"loading.h"
class loadiingTest : public gameNode
{
private:
	loading* _loading;
public:
	loadiingTest();
	~loadiingTest();

	HRESULT init();
	void release();
	void update();
	void render();


	void totalLoading();

};

