#include "stdafx.h"
#include "STDZombieMove.h"
#include "Enemy/IEnemyState.h"
#include "Enemy/IEnemy.h"
#include "StandardZombie.h"

void STDZombieMove::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Run, 0.5f);
}

void STDZombieMove::Leave()
{

}

void STDZombieMove::Update()
{
	//フットステップの移動量を追加。
	Vector3 fotStep = m_enemy->GetModelRender()->GetFootstepMove();
	Vector3 myPos = m_enemy->GetPos();
	myPos += fotStep;
	//適応。
	m_enemy->SetPos(myPos);
	m_enemy->GetModelRender()->SetPosition(myPos);


}
