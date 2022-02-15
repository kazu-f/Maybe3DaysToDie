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
	const float ATTACK_HIT_TIME = 1.8f;	//攻撃がヒットするタイミング
	bool m_isAttack = true;				//攻撃可能か。
	float m_attackTimer = 0.0f;
	Quaternion m_rot;
	float m_angle = 0.0f;
};

