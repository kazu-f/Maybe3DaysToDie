#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "TerrainManager/TerrainManager.h"

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

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		for (int y = 0; y < LoadingChunkCols; y++)
		{
			bool LoadingChunkUpdateFlag = m_loadingByChunk->IsNvmDirty(x, y);

			if ( !LoadingChunkUpdateFlag && !m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm() )
			{
				//更新必要なし。
				continue;
			}

			//更新が必要なチャンクは更新する。
			m_terrainManager->GetTerrainWorld(x, y)->ResetNvm();

			if (LoadingChunkUpdateFlag)
			{
				//ブロックが設置or破壊されたので、セルの追加、削除処理を行う。
				std::vector<NVMGenerator::Cell> AddCellList;
				
				//設置されたブロックの座標を検索。
				for (int i = 0; i < BlockKinds; i++)
				{
					for (const auto& placementObject : m_loadingByChunk->GetChunkBlock(x, y)->GetInstancingData(i))
					{
						//ブロック上面の４点を計算。
						Vector3 UpperSufaceVertexs[4];
						UpperSufaceVertexs[VERTEX_BackLeft] =
						{ placementObject.pos.x - 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z + 50.0f };
						UpperSufaceVertexs[VERTEX_BackRight] =
						{ placementObject.pos.x + 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z + 50.0f };
						UpperSufaceVertexs[VERTEX_FrontLeft] =
						{ placementObject.pos.x - 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z - 50.0f };
						UpperSufaceVertexs[VERTEX_FrontRight] =
						{ placementObject.pos.x + 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z - 50.0f };

						//セルを生成していく。
						NVMGenerator::Cell cell[2];
						//左側セル。
						cell[0].pos[0] = UpperSufaceVertexs[VERTEX_BackLeft];
						cell[0].pos[1] = UpperSufaceVertexs[VERTEX_BackRight];
						cell[0].pos[2] = UpperSufaceVertexs[VERTEX_FrontLeft];
						//右側セル。
						cell[1].pos[0] = UpperSufaceVertexs[VERTEX_FrontRight];
						cell[1].pos[1] = UpperSufaceVertexs[VERTEX_FrontLeft];
						cell[1].pos[2] = UpperSufaceVertexs[VERTEX_BackRight];

						AddCellList.push_back(cell[0]);
						AddCellList.push_back(cell[1]);
					}
				}

				for (auto& AddCell : AddCellList)
				{
					m_terrainManager->GetTerrainWorld(x, y)->AddCell(&AddCell);
				}

			}
			m_terrainManager->GetTerrainWorld(x, y)->CreateNVM();
			m_terrainManager->GetTerrainWorld(x, y)->ResetUpdateNvmFlag();
			m_loadingByChunk->NvmDirtyFlagDown(x, y);
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