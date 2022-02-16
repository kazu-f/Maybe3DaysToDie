#include "stdafx.h"
#include "TerrainManager.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Enemy/StandardZombie/StandardZombie.h"
#include "Enemy/EnemyGenerator.h"
#include "SaveDataFile.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemTerrain.h"

namespace nsTerrain {
	bool TerrainManager::Start()
	{
		PopurerTerrainMap();		//地形データを生成。
		
		m_naviMeshManager = NewGO<NaviMeshManager>(0);

		for (int chunkX = 0; chunkX < TERRAIN_WORLD_CHUNKSIZE; chunkX++)
		{
			for (int chunkY = 0; chunkY < TERRAIN_WORLD_CHUNKSIZE; chunkY++)
			{
				//地形を生成する。
				m_terrainWorlds[chunkX][chunkY] = NewGO<TerrainWorld>(0);
				m_terrainWorlds[chunkX][chunkY]->SetTerrainChunkData(&m_terrainChunkData[chunkX][chunkY]);
				m_terrainWorlds[chunkX][chunkY]->SetTerrainPosition(
					{
						static_cast<float>(chunkX * ChunkWidth * OBJECT_UNIT),
						0.0f,
						static_cast<float>(chunkY * ChunkWidth * OBJECT_UNIT)
					}
				);
				m_terrainWorlds[chunkX][chunkY]->SetNavimeshMnager(m_naviMeshManager);
			}
		}

		return true;
	}
	void TerrainManager::Update()
	{
		if (m_terrainWorlds[0][0]->IsInited()
			&& !m_isInitNVM)
		{
			//NVMデータを作成。
			//m_NVMGenerator.CreateNVM(m_terrainWorlds[0][0]->GetTerrainRender(), true);
			////敵キャラを作成。
			//m_enemyGenerator.Create<StandardZombie>(&m_NVMGenerator);

			m_isInitNVM = true;
		}
	}
	void TerrainManager::OnDestroy()
	{
		for (int chunkX = 0; chunkX < TERRAIN_WORLD_CHUNKSIZE; chunkX++)
		{
			for (int chunkY = 0; chunkY < TERRAIN_WORLD_CHUNKSIZE; chunkY++)
			{
				DeleteGO(m_terrainWorlds[chunkX][chunkY]);
			}
		}
	}
	void TerrainManager::PopurerTerrainMap()
	{
		//地形を生成する。
		for (int chunkX = 0; chunkX < MAX_CHUNK_SIDE; chunkX++)
		{
			for (int chunkY = 0; chunkY < MAX_CHUNK_SIDE; chunkY++)
			{
				//チャンク毎に地形を計算していく。
				ChunkTerrainGenerate(chunkX, chunkY);
			}
		}
	}
	void nsTerrain::TerrainManager::LoadTerrainData(SaveDataFile* saveDataFile)
	{
		//地形を生成する。
		for (int chunkX = 0; chunkX < MAX_CHUNK_SIDE; chunkX++)
		{
			for (int chunkY = 0; chunkY < MAX_CHUNK_SIDE; chunkY++)
			{
				LoadTerrainInChunk(chunkX, chunkY, saveDataFile);
			}
		}
	}
	void nsTerrain::TerrainManager::SaveTerrainData(SaveDataFile* saveDataFile)
	{
		//地形を生成する。
		for (int chunkX = 0; chunkX < MAX_CHUNK_SIDE; chunkX++)
		{
			for (int chunkY = 0; chunkY < MAX_CHUNK_SIDE; chunkY++)
			{
				SaveTerrainInChunk(chunkX, chunkY, saveDataFile);
			}
		}
	}
	void TerrainManager::ChunkTerrainGenerate(int chunkX, int chunkY)
	{
		auto* itemDataFile = ItemDataFile::GetInstance();
		GameItemTerrain* geneTerrains[3] = { nullptr };
		geneTerrains[0] = itemDataFile->GetTerrainDataTypeID(0);
		geneTerrains[1] = itemDataFile->GetTerrainDataTypeID(1);
		geneTerrains[2] = itemDataFile->GetTerrainDataTypeID(2);
		float geneMap[3] = { 0.2f,0.4f,1.0f };

		for (int x = 0; x < ChunkWidth + 1; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth + 1; z++)
				{
					const auto& terrain = m_terrains[x + ChunkWidth * chunkX][y][z + ChunkWidth * chunkY].get();
					float noise = m_perlinNoise.CalculationNoise(
						(static_cast<double>(x + (ChunkWidth * chunkX)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001),
						(static_cast<double>(z + (ChunkWidth * chunkY)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001)
						//,(static_cast<double>(y) / static_cast<double>(height) * 1.5 + 0.001)
					);

					noise = max(0.0f, min(1.0f, noise));

					float thisHeight = (static_cast<float>(ChunkHeight - GroundSurface) * noise);
					thisHeight += static_cast<float>(GroundSurface);

					float point = 0;
					int terrainID = 0;
					for (terrainID = 0; terrainID < 3; terrainID++)
					{
						if (geneMap[terrainID] < noise) continue;
						break;
					}

					//この場所の高さに対してブロックが届いていない。
					if (y >= thisHeight - nsMarching::TERRAIN_SURFACE)
					{
						point = 0.0f;
					}
					//この場所の上にもブロックがある。
					else if (y < thisHeight + nsMarching::TERRAIN_SURFACE)
					{
						point = 1.0f;
					}
					//この場所のブロックの影響値。
					else
					{
						point = 0.5f;
					}

					terrain->SetVoxel(point);
					if (point > 0.0f) {
						terrain->SetTerrainID(terrainID);
						ObjectParams params;
						params.BlockID = geneTerrains[terrainID]->GetObjParams().BlockID;
						params.Durable = geneTerrains[terrainID]->GetObjParams().Durable;
						params.AptitudeTool = geneTerrains[terrainID]->GetObjParams().AptitudeTool;

						terrain->SetParams(params);
					}

					Vector3 pos;
					pos.x = static_cast<float>((x + ChunkWidth * chunkX)) * OBJECT_UNIT;
					pos.y = static_cast<float>(y) * OBJECT_UNIT;
					pos.z = static_cast<float>((z + ChunkWidth * chunkY)) * OBJECT_UNIT;
					terrain->SetPosition(pos);

					m_terrainChunkData[chunkX][chunkY].SetTerrainData(terrain, x, y, z);
				}
			}
		}
	}

	void nsTerrain::TerrainManager::LoadTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile)
	{
		auto* itemDataFile = ItemDataFile::GetInstance();		
		for (int x = 0; x < ChunkWidth + 1; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth + 1; z++)
				{
					const auto& terrain = m_terrains[x + ChunkWidth * chunkX][y][z + ChunkWidth * chunkY].get();

					auto& objData = saveDataFile->m_ChunkData[chunkX][chunkY].ObjData[x][y][z];
					ObjectParams params;
					params.BlockID = objData.ObjId;

					if (params.BlockID == -1) continue;

					auto* terrainData = itemDataFile->GetTerrainData(params.BlockID);

					if (terrainData == nullptr) continue;

					params.Durable = terrainData->GetObjParams().Durable;

					terrain->SetParams(params);
					terrain->SetCurrentDurable(objData.ObjDurable);

					terrain->SetTerrainID(terrainData->GetItemData()->itemTypeID);

					terrain->CalcVoxel();

					Vector3 pos;
					pos.x = static_cast<float>((x + ChunkWidth * chunkX)) * OBJECT_UNIT;
					pos.y = static_cast<float>(y) * OBJECT_UNIT;
					pos.z = static_cast<float>((z + ChunkWidth * chunkY)) * OBJECT_UNIT;
					terrain->SetPosition(pos);

					m_terrainChunkData[chunkX][chunkY].SetTerrainData(terrain, x, y, z);
				}
			}
		}
	}
	void nsTerrain::TerrainManager::SaveTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile)
	{
		for (int x = 0; x < ChunkWidth + 1; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth + 1; z++)
				{
					auto& terrain = m_terrains[x + ChunkWidth * chunkX][y][z + ChunkWidth * chunkY];
					auto& objData = saveDataFile->m_ChunkData[chunkX][chunkY].ObjData[x][y][z];

					if (terrain->IsTerrainEnabled())
					{
						objData.ObjDurable = terrain->GetParam().Durable;
						objData.ObjId = terrain->GetParam().BlockID;
					}
				}
			}
		}
	}
}