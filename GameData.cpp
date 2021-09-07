#include "framework.h"
#include "GameData.h"

void CGameData::plusGenerate(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE::PLAYER1:
		unitGenerate.x += 1;
		break;
	case PLAYER_TYPE::PLAYER2:
		unitGenerate.y += 1;
		break;
	}
}

void CGameData::plusDeath(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE::PLAYER1:
		unitDeath.x += 1;
		break;
	case PLAYER_TYPE::PLAYER2:
		unitDeath.y += 1;
		break;
	}
}

void CGameData::plusIncome(PLAYER_TYPE type, int income)
{
	switch (type)
	{
	case PLAYER_TYPE::PLAYER1:
		moneyIncome.x += income;
		break;
	case PLAYER_TYPE::PLAYER2:
		moneyIncome.y += income;
		break;
	}
}

void CGameData::plusSpending(PLAYER_TYPE type, int spending)
{
	switch (type)
	{
	case PLAYER_TYPE::PLAYER1:
		moneySpending.x += spending;
		break;
	case PLAYER_TYPE::PLAYER2:
		moneySpending.y += spending;
		break;
	}
}
