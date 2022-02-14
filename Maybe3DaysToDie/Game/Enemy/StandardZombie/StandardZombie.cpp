#include "stdafx.h"
#include "StandardZombie.h"
#include "Enemy/IEnemy.h"
#include "Enemy/IEnemyState.h"
#include "STDZombieTracking.h"
#include "STDZombieAttack.h"
#include "Enemy/EnemyGenerator.h"
#include "Player/Player.h"

bool StandardZombie::Start()
{
	__super::Start();

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
	animData[EnAnimationState_Attack].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Attack.tka";
	animData[EnAnimationState_Attack].isLoop = true;

	//�G�[�W�F���g�ƃA�N�^�[�ꏏ�ɏ������B
	InitActor(modelInitData, "StandardZombie", animData, sizeof(animData) / sizeof(animData[0]));

	//scaleFix.
	this->GetModelRender()->SetScale(m_scale);

	//StateInit.
	m_trackingState = new STDZombieTracking(this);
	m_attackState = new STDZombieAttack(this);
	
	//DefaultAnimPlay.
	this->GetModelRender()->PlayAnimation(EnAnimationState_Run, 0.0f);

	m_CharaCon.Init(m_parameters.Radius, m_parameters.Hight, GetPos());
	m_CharaCon.GetBody()->GetBody()->setUserPointer(this); 
	return true;
}

void StandardZombie::Update()
{
	//�U��or�ړ�
	Vector3 P2E = m_playerPtr->GetPosition() - m_pos;
	float P2ELen = P2E.Length();
	if (P2ELen < m_parameters.AttackRange)
	{
		//�U���͈͓��B
		ChangeState(m_attackState);
	}
	else
	{
		//�U���͈͊O�B
		ChangeState(m_trackingState);
	}

	GetCurrentState()->Update();
}

void StandardZombie::PostUpdate()
{
	//IK�X�V�B
	//GetIK().ApplyIK();
}

IEnemy::EnemyParams& StandardZombie::GetEnemyParameters()
{
	return m_parameters;
}
