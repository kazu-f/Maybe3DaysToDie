#include "stdafx.h"
#include "StandardZombie.h"
#include "IEnemy.h"

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
	AnimClipInitData animData[1];
	//animDataInit.
	animData[0].tkaFilePath = "Assets/modelData/Enemy/StandardZombie/Scream.tka";
	animData[0].isLoop = true;

	//エージェントとアクター一緒に初期化。
	InitActor(modelInitData, "StandardZombie", animData, sizeof(animData) / sizeof(animData[0]));

	//scaleFix.
	this->GetModelRender()->SetScale(m_scale);
	
	//DefaultAnimPlay.
	this->GetModelRender()->PlayAnimation(0, 0.5f);

	return true;
}

void StandardZombie::Update()
{

}

IEnemy::EnemyParams& StandardZombie::GetEnemyParameters()
{
	return m_parameters;
}
