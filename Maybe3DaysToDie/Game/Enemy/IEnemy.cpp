#include "stdafx.h"
#include "IEnemy.h"
#include "MiniEngine/NaviMesh/NaviMesh.h"

IEnemy::~IEnemy()
{
}

void IEnemy::InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[], int animSize)
{
	m_modelRender = NewGO<prefab::ModelRender>(0, tag);
	m_modelRender->Init(initData, animClipDatas, animSize);
}

void IEnemy::InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[], bool isRandMove)
{
	//モデル初期化。
	InitActor(initData, tag ,animClipDatas);
	//エージェント初期化。
	m_agent.Init(m_modelRender, mesh, isRandMove);
}


