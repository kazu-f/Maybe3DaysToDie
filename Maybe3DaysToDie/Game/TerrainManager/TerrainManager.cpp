#include "stdafx.h"
#include "TerrainManager.h"
#include "DestructibleObject/Terrain/Terrain.h"

namespace nsTerrain {
	bool TerrainManager::Start()
	{
		PopurerTerrainMap();		//地形データを生成。

		for (int chunkX = 0; chunkX < LoadingChunkCols; chunkX++)
		{
			for (int chunkY = 0; chunkY < LoadingChunkCols; chunkY++)
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
			}
		}

		return true;
	}
	void TerrainManager::Update()
	{
	}
	void TerrainManager::OnDestroy()
	{
		for (int chunkX = 0; chunkX < LoadingChunkCols; chunkX++)
		{
			for (int chunkY = 0; chunkY < LoadingChunkCols; chunkY++)
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
	void TerrainManager::ChunkTerrainGenerate(int chunkX, int chunkY)
	{
		for (int x = 0; x < ChunkWidth; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth; z++)
				{
					auto* terrain = m_terrainChunkData[chunkX][chunkY].GetTerrainData(x, y, z);
					if (terrain != nullptr)
					{
						float noise = m_perlinNoise.CalculationNoise(
							(static_cast<double>(x + (ChunkWidth * chunkX)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001),
							(static_cast<double>(z + (ChunkWidth * chunkY)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001)
							//,(static_cast<double>(y) / static_cast<double>(height) * 1.5 + 0.001)
						);

						noise = max(0.0f, min(1.0f, noise));

						float thisHeight = (static_cast<float>(ChunkHeight) * noise);

						float point = 0;

						////この場所の高さに対してブロックが届いていない。
						//if (y <= thisHeight - nsMarching::TERRAIN_SURFACE)
						//	point = 0.0f;
						////この場所の上にもブロックがある。
						//else if (y > thisHeight + nsMarching::TERRAIN_SURFACE)
						//	point = 1.0f;
						////この場所のブロックの影響値計算。(上方向。)
						//else if (y > thisHeight)
						//	point = (float)y - thisHeight;
						////この場所のブロックの影響値計算。(下方向。)
						//else
						//	point = thisHeight - (float)y;

						//この場所の高さに対してブロックが届いていない。
						if (y >= thisHeight - nsMarching::TERRAIN_SURFACE)
							point = 0.0f;
						//この場所の上にもブロックがある。
						else if (y < thisHeight + nsMarching::TERRAIN_SURFACE)
							point = 1.0f;
						//この場所のブロックの影響値。
						else
							point = 0.5f;

						if (y == 0)
						{
							point = 1.0f;
						}

						terrain->SetVoxel(point);

						Vector3 pos;
						pos.x = static_cast<float>((x + ChunkWidth * chunkX)) * OBJECT_UNIT;
						pos.y = static_cast<float>(y) * OBJECT_UNIT;
						pos.z = static_cast<float>((z + ChunkWidth * chunkY)) * OBJECT_UNIT;
						terrain->SetPosition(pos);
					}
				}
			}
		}
	}
}