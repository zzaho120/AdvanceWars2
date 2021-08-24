#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"progressBar.h"


class enemyManager;//클래스 전방선언
class rocket : public gameNode
{
private:
	image* _player;

	missile* _missile;
	nuclear* _nuclear;
	RECT rc;


	//피통
	progressBar* _hpBar;
	float _maxHp;
	float _currentHp;

	enemyManager* _em;
public:
	rocket();
	~rocket();
	
	HRESULT init();
	void release();
	void update();
	void render();

	//미사일 삭제
	void removeMissile(int arrNum);

	//충돌함수
	void collision();

	//피깎는 함수
	void hitDamage(float damage);

	//뉴클리어  가져오기
	nuclear* getMissile() { return _nuclear; }
	//로켓이미지 가져오기
	image* getRocketImage() { return _player; }


	void setEnemyMemoryLink(enemyManager* em) { _em = em; }


};

