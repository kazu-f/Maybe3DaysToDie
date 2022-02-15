#pragma once

#include "Enemy/IEnemy.h"

class STDZombieDeath : public IEnemyState
{
public:
	STDZombieDeath(IEnemy* enemy) :
		IEnemyState::IEnemyState(enemy)
	{
	}
public:
	void Enter() override final;
	void Update() override final;
	void Leave() override final;

private:
	const float DELETE_TIME = 5.0f;
	float m_deleteTimer = 0.0f;
};

