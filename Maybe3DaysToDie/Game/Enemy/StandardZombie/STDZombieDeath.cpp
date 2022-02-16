#include "stdafx.h"
#include "STDZombieDeath.h"
#include "StandardZombie.h"
#include "Enemy/EnemyGenerator.h"

void STDZombieDeath::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Death, 0.5f);
	m_enemy->DeleteCollision();
}

void STDZombieDeath::Update()
{
	m_deleteTimer += GameTime().GetFrameDeltaTime();

	if (m_deleteTimer > DELETE_TIME)
	{
		m_enemy->GetEnemyGenerator()->UnRegistEnemy(dynamic_cast<IEnemy*>(m_enemy));
		m_enemy->GetEnemyGenerator()->AddDeadEnemyCount();
		m_deleteTimer = 0.0f;
	}
}

void STDZombieDeath::Leave()
{
}
