#include "stdafx.h"
#include "Stage.h"
#include "Enemy/EnemyGenerator.h"
#include "Enemy/StandardZombie/StandardZombie.h"

Stage::Stage()
{
	//ここで地面を作る
	NewGround();
}


bool Stage::Start()
{
	//メインカメラの描画距離をロードしているチャンクに合わせる
	MainCamera().SetFar(OBJECT_UNIT * ChunkWidth * LoadingChunks / 2);
	m_SkyCube->SetScale(ChunkWidth * LoadingChunks);
	return true;
}

void Stage::Update()
{

	if (GetAsyncKeyState('U')) {
		m_enemyGenerator.Create<StandardZombie>();
	}
	if (GetAsyncKeyState('K')) {
		m_enemyGenerator.ReleaseEnemy();
	}
}

void Stage::OnDestroy()
{
	if (m_Terrain != nullptr)
	{
		DeleteGO(m_Terrain);
		m_Terrain = nullptr;
	}
	//m_stage.OnDestroy();
	////モデルを削除
	//DeleteGO(m_Model);
}

void Stage::NewGround()
{
	m_Terrain = NewGO<nsTerrain::TerrainManager>(0,"Terrain");
	m_SkyCube = NewGO<prefab::CSky>(0);
	//m_stage.CreateStage();
	//m_Model = NewGO<prefab::ModelRender>(0);
	//ModelInitData InitModelUnity;
	//InitModelUnity.m_tkmFilePath = "Assets/modelData/testbg/bg.tkm";
	//m_Model->Init(InitModelUnity);
	//m_pos.x += 50.0f;
	//m_pos.z += 50.0f;
	//m_Model->SetPosition(m_pos);
	//m_Model->SetShadowReceiverFlag(true);
}