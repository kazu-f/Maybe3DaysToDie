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
	const float ATTACK_HIT_TIME = 1.8f;	//�U�����q�b�g����^�C�~���O
	bool m_isAttack = true;				//�U���\���B
	float m_attackTimer = 0.0f;
	Quaternion m_rot;
	float m_angle = 0.0f;
};

