#include "stdafx.h"
#include "StandardZombie.h"
#include "Enemy/IEnemy.h"
#include "Enemy/IEnemyState.h"
#include "STDZombieTracking.h"
#include "Enemy/EnemyGenerator.h"

bool StandardZombie::Start()
{
	//StatusInit
	m_parameters.Attack = 20;
	m_parameters.AttackRange = 150.0f;
	m_parameters.Deffence = 5;
	m_parameters.EXP = 500.0f;
	m_parameters.MoveSpeed = 2.0f;
	m_parameters.SearchRange = 20000.0f;

	//modelInitData.
	ModelInitData modelInitData;
	//modelData
	modelInitData.m_tkmFilePath = "Assets/modelData/Enemy/StandardZombie/StandardZombie.tkm";
	
	//animInitData.
	AnimClipInitData animData[EnAnimationState_Num];
	//animDataInit.
	animData[EnAnimationState_Idle].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Scream.tka";
	animData[EnAnimationState_Idle].isLoop = true;
	animData[EnAnimationState_Run].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Run.tka";
	animData[EnAnimationState_Run].isLoop = true;

	//エージェントとアクター一緒に初期化。
	InitActor(modelInitData, "StandardZombie", animData, sizeof(animData) / sizeof(animData[0]));

	//scaleFix.
	this->GetModelRender()->SetScale(m_scale);

	//StateInit.
	m_trackingState = new STDZombieTracking(this);
	
	//DefaultAnimPlay.
	this->GetModelRender()->PlayAnimation(EnAnimationState_Run, 0.0f);



	return true;
}

void StandardZombie::Update()
{
	ChangeState(m_trackingState);
	GetCurrentState()->Update();
}

void StandardZombie::PostUpdate()
{
	//IK更新。
	GetIK().ApplyIK();
}

IEnemy::EnemyParams& StandardZombie::GetEnemyParameters()
{
	return m_parameters;
}
