#include "stdafx.h"
#include "STDZombieAttack.h"
#include "StandardZombie.h"

void STDZombieAttack::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Attack, 0.5f);
}

void STDZombieAttack::Update()
{
}

void STDZombieAttack::Leave()
{
}
