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
//	//���f���������B
//	InitActor(initData, tag, animClipDatas);
//	//�G�[�W�F���g�������B
//	m_agent.Init(m_modelRender, mesh, isRandMove);
//}

void IEnemy::InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[], int animSize)
{
	m_modelRender = NewGO<prefab::ModelRender>(0, tag);
	m_modelRender->Init(initData, animClipDatas, animSize);
}




