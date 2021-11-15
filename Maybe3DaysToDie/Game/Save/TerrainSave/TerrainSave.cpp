#include "stdafx.h"
#include "TerrainSave.h"

void TerrainSave::Save()
{
	for (int x = 0; x < MAX_CHUNK_SIDE; x++)
	{
		for (int y = 0; y < MAX_CHUNK_SIDE; y++)
		{
			//�`�����N���Ƃ̈ʒu���L��
			m_ChunkData[x][y].ChunkID[0] = x;
			m_ChunkData[x][y].ChunkID[1] = y;
			for (int terrain_x = 0; terrain_x < ChunkWidth; terrain_x++)
			{
				for (int terrain_y = 0; terrain_x < ChunkHeight; terrain_y++)
				{
					for (int terrain_z = 0; terrain_z < ChunkWidth; terrain_z++)
					{
						//�e���C���P�ʂ̈ʒu���L��
						int terrainID[3] = { 0 };
						terrainID[0] = terrain_x;
						terrainID[1] = terrain_y;
						terrainID[2] = terrain_z;
						auto& terrain = m_TerrainWorld->GetTerrain(terrainID);
						m_ChunkData[x][y].TerrainID[terrainID[0]][terrainID[1]][terrainID[2]] = terrain.GetParam().BlockID;
					}
				}
			}
		}
	}
}