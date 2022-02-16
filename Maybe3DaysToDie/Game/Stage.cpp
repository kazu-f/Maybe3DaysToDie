#include "stdafx.h"
#include "Stage.h"
#include "Enemy/EnemyGenerator.h"
#include "Enemy/StandardZombie/StandardZombie.h"
#include "NaviMeshManager.h"
#include "Load/TerrainLoad/LoadingByChunk.h"

Stage::Stage()
{
	//ここで地面を作る
	NewGround();

}

Stage::~Stage()
{
}
bool Stage::Start()
{
	m_enemyGenerator = NewGO<EnemyGenerator>(0);
	m_enemyGenerator->SetStage(this);
	//地形生成
	//todo　もしもSaveDataFileから計算するようになったらif文の下に置く
	m_Load.SetSaveDataFile(m_SaveDataFile);
	if (m_Load.Load())
	{
		//セーブデータを読み込めた
		m_Terrain->LoadTerrainData(m_SaveDataFile);
		m_LoadingByChunk->UpdateMoveChunk();
		return true;
	}
	m_Terrain->PopurerTerrainMap();
	m_LoadingByChunk->UpdateMoveChunk();

	//建物読み込み
	m_Map.SetSaveDataFile(m_SaveDataFile);
	m_Map.SetTerrainManager(m_Terrain);
	m_Map.SetChunkID(1, 1);
	m_Map.Init("Assets/level/Building_0.tkl");

	return true;
}

void Stage::Update()
{

	if (GetAsyncKeyState('U')) {
		//StandardZombie* sz = dynamic_cast<StandardZombie*>(m_enemyGenerator.Create<StandardZombie>());
		//sz->SetPos({ 300.0f, 0.0f, 300.0f });
	}
	if (GetAsyncKeyState('K')) {
		m_enemyGenerator->ReleaseEnemy();
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
	m_LoadingByChunk = NewGO<LoadingByChunk>(0, "LoadingByChunk");
	m_LoadingByChunk->SetTerrainManager(m_Terrain);
}