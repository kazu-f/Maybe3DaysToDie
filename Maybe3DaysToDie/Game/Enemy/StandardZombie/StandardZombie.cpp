#include "stdafx.h"
#include "StandardZombie.h"
#include "Enemy/IEnemy.h"
#include "Enemy/IEnemyState.h"
#include "STDZombieTracking.h"
#include "STDZombieAttack.h"
#include "STDZombieWandering.h"
#include "STDZombieDeath.h"
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
	m_parameters.SearchRange = 600.0f;

	//modelInitData.
	ModelInitData modelInitData;
	//modelData
	modelInitData.m_tkmFilePath = "Assets/modelData/Enemy/StandardZombie/StandardZombie.tkm";
	
	//animInitData.
	AnimClipInitData animData[EnAnimationState_Num];
	//animDataInit.
	animData[EnAnimationState_Idle].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Scream.tka";
	animData[EnAnimationState_Idle].isLoop = true;
	animData[EnAnimationState_Walk].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Walk.tka";
	animData[EnAnimationState_Walk].isLoop = true;
	animData[EnAnimationState_Run].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Run.tka";
	animData[EnAnimationState_Run].isLoop = true;
	animData[EnAnimationState_Attack].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Attack.tka";
	animData[EnAnimationState_Attack].isLoop = true;
	animData[EnAnimationState_Death].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Death.tka";
	animData[EnAnimationState_Death].isLoop = false;

	//�G�[�W�F���g�ƃA�N�^�[�ꏏ�ɏ������B
	InitActor(modelInitData, "StandardZombie", animData, sizeof(animData) / sizeof(animData[0]));

	//scaleFix.
	this->GetModelRender()->SetScale(m_scale);

	//StateInit.
	m_trackingState = new STDZombieTracking(this);
	m_attackState = new STDZombieAttack(this);
	m_wanderingState = new STDZombieWandering(this);
	m_deathState = new STDZombieDeath(this);
	
	//DefaultAnimPlay.
	this->GetModelRender()->PlayAnimation(EnAnimationState_Run, 0.0f);

	//�R���C�_�[�������B
	m_capsuleCollider.Create(m_parameters.Radius, m_parameters.Hight);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_capsuleCollider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.GetBody()->setUserPointer(this);
	m_rigidBody.GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Character);

	return true;
}

void StandardZombie::Update()
{
	if (m_parameters.Hp <= 0)
	{
		//���S�B
		ChangeState(m_deathState);
	}
	else
	{
		//�U��or�ړ�
		Vector3 P2E = m_playerPtr->GetPosition() - m_pos;
		float P2ELen = P2E.Length();
		if (P2ELen < m_parameters.AttackRange)
		{
			//�U���͈͓��B
			ChangeState(m_attackState);
		}
		else if (P2ELen < m_parameters.SearchRange)
		{
			//�U���͈͊O�B
			ChangeState(m_trackingState);
		}
		else
		{
			ChangeState(m_wanderingState);
		}
	}

	//���s�ړ����擾�B
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_modelRender->GetPosition().x, m_modelRender->GetPosition().y + m_parameters.Hight / 2, m_modelRender->GetPosition().z));

	m_currentState->Update();
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

void StandardZombie::HitDamage(int attack)
{
	int Damage = attack - m_parameters.Deffence;
	m_parameters.Hp = max(m_parameters.Hp - Damage, 0);
}
