#include "stdafx.h"
#include "STDZombieMove.h"
#include "Enemy/IEnemyState.h"
#include "Enemy/IEnemy.h"
#include "StandardZombie.h"

void STDZombieMove::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Walk, 0.5f);
}

void STDZombieMove::Leave()
{

}

void STDZombieMove::Update()
{

}
