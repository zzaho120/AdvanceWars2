#pragma once
class CGameData
{
private:
	float turn;
	Vec2 unitGenerate;
	Vec2 unitDeath;
	Vec2 moneyIncome;
	Vec2 moneySpending;

public:
	CGameData() :
		turn(1), unitDeath(0),
		unitGenerate(0), moneyIncome(0),
		moneySpending(0)
	{ }
	~CGameData() { }

	int getTurn() { return turn; }
	Vec2 getUnitGenerate() { return unitGenerate; }
	Vec2 getUnitDeath() { return unitDeath; }
	Vec2 getMoneyIncome() { return moneyIncome; }
	Vec2 getMoneySpending() { return moneyIncome; }

	void setTurn(int curTurn) { turn = curTurn; }
	void setUnitGenerate(Vec2 generate) { unitGenerate = generate; }
	void setUnitDeath(Vec2 death) { unitDeath = death; }
	void setMoneyIncome(Vec2 money) { moneyIncome = money; }
	void setMoneySpending(Vec2 money) { moneySpending = money; }

	void plusTurn() { turn += 0.5; }
	void plusGenerate(PLAYER_TYPE type);
	void plusDeath(PLAYER_TYPE type);
	void plusIncome(PLAYER_TYPE type, int income);
	void plusSpending(PLAYER_TYPE type, int spending);
};

