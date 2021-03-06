#include "stdafx.h"
#include "STDZombieAttack.h"
#include "StandardZombie.h"
#include "Player/Player.h"

void STDZombieAttack::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Attack, 0.5f);
	m_isAttack = true;
}

void STDZombieAttack::Update()
{
	//Playerの方に向ける。
	Vector3 e2p = m_enemy->GetPlayer()->GetPosition() - m_enemy->GetPos();
	e2p.Normalize();

	//攻撃が当たるタイミングを調節する。
	if(ATTACK_HIT_TIME < m_enemy->GetModelRender()->GetAnimation().GetCurrentAnimTime() && m_isAttack)
	{
		m_isAttack = false;
		m_enemy->GetPlayer()->HitDamage(m_enemy->GetEnemyParameters().Attack);
	}
	else if (m_enemy->GetModelRender()->GetAnimation().GetCurrentAnimTime() < ATTACK_HIT_TIME)
	{
		m_isAttack = true;
	}
}

void STDZombieAttack::Leave()
{
}
