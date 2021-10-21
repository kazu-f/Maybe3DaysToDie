#include "stdafx.h"
#include "STDZombieWandering.h"
#include "StandardZombie.h"
#include "Enemy/IEnemy.h"

void STDZombieWandering::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Run, 0.5f);
}

void STDZombieWandering::Update()
{
	if (m_movePathList.size() == 0) {
		//探査パス0。処理は行わない。
		return;
	}
}

void STDZombieWandering::Leave()
{
}
