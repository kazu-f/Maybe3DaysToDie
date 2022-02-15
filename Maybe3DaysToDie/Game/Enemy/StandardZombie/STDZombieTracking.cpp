#include "stdafx.h"
#include "STDZombieTracking.h"
#include "StandardZombie.h"
#include "Player/Player.h"

void STDZombieTracking::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Run, 0.5f);
	m_enemy->GetAgent().ResetNodeList();
}

void STDZombieTracking::Update()
{
	Vector3 pPos = m_enemy->GetPlayer()->GetPosition();
	m_enemy->GetAgent().MoveForFootStep(m_enemy->GetModelRender(), m_enemy->GetPos(), pPos);

	Quaternion qRot;
	qRot.SetRotation(Vector3::AxisY, atan2f(m_enemy->GetAgent().GetWayPoint().x, m_enemy->GetAgent().GetWayPoint().z));
	m_enemy->GetRot().Slerp(0.1f, m_enemy->GetRot(), qRot);
	m_enemy->SetPos(m_enemy->GetAgent().GetAgentPos());
}

void STDZombieTracking::Leave()
{
}
