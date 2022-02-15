#include "stdafx.h"
#include "STDZombieDeath.h"
#include "StandardZombie.h"

void STDZombieDeath::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Death, 0.5f);
}

void STDZombieDeath::Update()
{

}

void STDZombieDeath::Leave()
{
}
