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
		//�T���p�X0�B�����͍s��Ȃ��B
		return;
	}
}

void STDZombieWandering::Leave()
{
}
