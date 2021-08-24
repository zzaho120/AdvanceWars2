#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"progressBar.h"


class enemyManager;//Ŭ���� ���漱��
class rocket : public gameNode
{
private:
	image* _player;

	missile* _missile;
	nuclear* _nuclear;
	RECT rc;


	//����
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

	//�̻��� ����
	void removeMissile(int arrNum);

	//�浹�Լ�
	void collision();

	//�Ǳ�� �Լ�
	void hitDamage(float damage);

	//��Ŭ����  ��������
	nuclear* getMissile() { return _nuclear; }
	//�����̹��� ��������
	image* getRocketImage() { return _player; }


	void setEnemyMemoryLink(enemyManager* em) { _em = em; }


};

