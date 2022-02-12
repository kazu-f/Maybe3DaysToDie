#include "stdafx.h"
#include "Stage.h"
#include "Enemy/EnemyGenerator.h"
#include "Enemy/StandardZombie/StandardZombie.h"
#include "NaviMeshManager.h"
#include "Load/TerrainLoad/LoadingByChunk.h"

Stage::Stage()
{
	if (m_Load.Load())
	{
		//�Z�[�u�f�[�^��ǂݍ��߂�
		return;
	}
	//�����Œn�ʂ����
	NewGround();
}


bool Stage::Start()
{
	m_Terrain->PopurerTerrainMap();
	//�����ǂݍ���
	m_Map.SetSaveDataFile(m_SaveDataFile);
	m_Map.SetChunkID(1, 1);
	m_Map.Init("Assets/level/Building_0.tkl");

	m_enemyGenerator.SetStage(this);

	m_LoadingByChunk->SetTerrainManager(m_Terrain);

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
	////���f�����폜
	//DeleteGO(m_Model);
}

void Stage::NewGround()
{
	m_Terrain = NewGO<nsTerrain::TerrainManager>(0,"Terrain");
	m_SkyCube = NewGO<prefab::CSky>(0);
	m_LoadingByChunk = NewGO<LoadingByChunk>(0, "LoadingByChunk");
}