#include "stdafx.h"
#include "IEnemy.h"
#include "IEnemyState.h"
#include "MiniEngine/NaviMesh/NaviMesh.h"
#include "EnemyGenerator.h"

IEnemy::IEnemy()
{
}

IEnemy::~IEnemy()
{
	//関連解除。
	EnemyGenerator::GetEnemyGenerator()->UnRegistEnemy(this);
	DeleteGO(m_modelRender);
	DeleteGO(this);
}

void IEnemy::InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[], int animSize, bool isRandMove)
{
	//モデル初期化。
	InitActor(initData, tag, animClipDatas);
	//エージェント初期化。
	m_agent.Init(m_modelRender, mesh, isRandMove);
}

void IEnemy::InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[], int animSize)
{
	m_modelRender = NewGO<prefab::ModelRender>(0, tag);
	m_modelRender->Init(initData, animClipDatas, animSize);
}




