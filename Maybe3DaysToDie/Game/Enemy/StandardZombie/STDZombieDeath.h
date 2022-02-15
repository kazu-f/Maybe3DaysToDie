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
	float m_deathTimer = 0.0f;
};

