#pragma once

#include "Enemy/IEnemy.h"

class STDZombieAttack : public IEnemyState
{
public:
	STDZombieAttack(IEnemy* enemy) :
		IEnemyState::IEnemyState(enemy)
	{
	}
public:
	void Enter() override final;
	void Update() override final;
	void Leave() override final;
private:
};

