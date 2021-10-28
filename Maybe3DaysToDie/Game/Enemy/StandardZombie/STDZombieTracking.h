#pragma once

#include "Enemy/IEnemy.h"

class STDZombieTracking : public IEnemyState
{
public:
	STDZombieTracking(IEnemy* enemy) :
		IEnemyState::IEnemyState(enemy)
	{
	}
public:
	void Enter() override final;
	void Update() override final;
	void Leave() override final;
private:
};

