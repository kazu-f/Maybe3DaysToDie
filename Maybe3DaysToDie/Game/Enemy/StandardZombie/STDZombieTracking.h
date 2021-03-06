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
	const float SUCCESS_TIME = 0.5f;
	const float FAILED_TIME = 2.0f;
	float m_serchTime = SUCCESS_TIME;
};

