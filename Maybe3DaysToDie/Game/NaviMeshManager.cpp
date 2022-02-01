#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"
#include "Load/TerrainLoad/LoadingByChunk.h"

NaviMeshManager::~NaviMeshManager()
{
}

bool NaviMeshManager::Start()
{
	//よくないがFindあるんだし使うよなぁ！？
	m_playerPtr = FindGO<Player>("player");
	m_terrainManager = FindGO<nsTerrain::TerrainManager>("Terrain");
	m_loadingByChunk = FindGO<LoadingByChunk>("LoadingByChunk");

	//最初のNVM初期化処理及び、チャンクの初期化処理を呼び出す。
	return true;
}

void NaviMeshManager::Update()
{
	//NVMを更新するのはコリジョンがある範囲のみ。


	for (int x = 0; x < LoadingChunkCols; x++)
	{
		for (int y = 0; y < LoadingChunkCols; y++)
		{
			if ( m_loadingByChunk->IsNvmDirty(x, y) || m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm() )
			{
				//更新が必要なチャンクは更新する。
				m_terrainManager->GetTerrainWorld(x, y)->CreateNVM();
				m_terrainManager->GetTerrainWorld(x, y)->ResetUpdateNvmFlag();
				m_loadingByChunk->NvmDirtyFlagDown(x, y);
			}
		}
	}

	//if (IsNvmDirty)
	//{
	//	//地形の更新がない。
	//	return;
	//}


}

void NaviMeshManager::CalcPlayerGrid()
{
	if (m_playerPtr == nullptr)
	{
		//移動しているオブジェクトがないため更新は必要ない。
		return;
	}

	//playerの位置。
	Vector3 playerPos = m_playerPtr->GetPosition();

	//プレイヤーの位置をグリッド化。
	m_playerGrid[0] = static_cast<int>(std::floor((playerPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[1] = static_cast<int>(std::floor((playerPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[0]), 1);
	m_playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[1]), 1);
}