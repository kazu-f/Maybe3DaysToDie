#include "stdafx.h"
#include "STDZombieTracking.h"
#include "StandardZombie.h"
#include "Player/Player.h"

void STDZombieTracking::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Run, 0.5f);
}

void STDZombieTracking::Update()
{
	Vector3 pPos = m_enemy->GetPlayer()->GetPosition();
	m_enemy->GetAgent().MoveForFootStep(m_enemy->GetModelRender(), m_enemy->GetPos(), pPos);
	m_enemy->GetAgent().GetAgentPositionAndRotation(m_enemy->GetPos(), m_enemy->GetRot());
	m_enemy->GetModelRender()->SetPosition(m_enemy->GetPos());
	m_enemy->GetModelRender()->SetRotation(m_enemy->GetRot());
}

void STDZombieTracking::Leave()
{
}
