#include "stdafx.h"
#include "IEnemy.h"
#include "IEnemyState.h"
#include "EnemyGenerator.h"
#include "GameScene.h"

IEnemy::IEnemy()
{
}

void IEnemy::OnDestroy()
{
	m_generatorPtr->UnRegistEnemy(this);
	DeleteGO(m_modelRender);
}

//void IEnemy::InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[], int animSize, bool isRandMove)
//{
//	//モデル初期化。
//	InitActor(initData, tag, animClipDatas);
//	//エージェント初期化。
//	m_agent.Init(m_modelRender, mesh, isRandMove);
//}

void IEnemy::InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[], int animSize)
{
	m_modelRender = NewGO<prefab::ModelRender>(0, tag);
	m_modelRender->Init(initData, animClipDatas, animSize);

	FootIK::FootIKParam param;
	param.footBoneName_0 = L"mixamorig:LeftToe_End";
	param.footBoneName_1 = L"mixamorig:RightToe_End";
	param.rootBoneName = L"mixamorig:Hips";
	param.footCapsuleColliderRadius_0 = 1.0f;
	param.footCapsuleColliderRadius_1 = 1.0f;
	param.footCapsuleColliderHeight_0 = 1.0f;
	param.footCapsuleColliderHeight_1 = 1.0f;
	m_footIK.Enable(&m_modelRender->GetSkeleton(), param);
}




