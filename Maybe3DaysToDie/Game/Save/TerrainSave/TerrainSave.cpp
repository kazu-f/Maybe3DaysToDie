#include "stdafx.h"
#include "TerrainSave.h"
#include "SaveDataFile.h"
#include <direct.h>

void TerrainSave::Save()
{
	if (m_TerrainWorld == nullptr)
	{
		return;
	}
	FILE* fp;
	fp = fopen(SaveDataFilePath_Terrain, "wb");
	if (fp == NULL)
	{
		if (_mkdir("SaveData") != 0)
		{
			//ディレクトリが作成できなかった
			return;
		}
		fp = fopen(SaveDataFilePath_Terrain, "wb");
	}

	for (int chunk_x = 0; chunk_x < MAX_CHUNK_SIDE; chunk_x++)
	{
		for (int chunk_y = 0; chunk_y < MAX_CHUNK_SIDE; chunk_y++)
		{
			//チャンクごとの位置を記憶
			m_ChunkData[chunk_x][chunk_y].ChunkID[0] = chunk_x;
			m_ChunkData[chunk_x][chunk_y].ChunkID[1] = chunk_y;
			for (int terrain_x = 0; terrain_x < ChunkWidth; terrain_x++)
			{
				for (int terrain_y = 0; terrain_y < ChunkHeight; terrain_y++)
				{
					for (int terrain_z = 0; terrain_z < ChunkWidth; terrain_z++)
					{
						//テライン単位の位置を記憶
						int terrainID[3] = { 0 };
						terrainID[0] = terrain_x;
						terrainID[1] = terrain_y;
						terrainID[2] = terrain_z;
						auto& TerrainParam = m_TerrainWorld->GetTerrain(terrainID).GetParam();
						//ブロックのIDを記憶
						m_ChunkData[chunk_x][chunk_y].TerrainID[terrainID[0]][terrainID[1]][terrainID[2]] = TerrainParam.BlockID;
						//ブロックの耐久値を記憶
						m_ChunkData[chunk_x][chunk_y].TerrainDurable[terrainID[0]][terrainID[1]][terrainID[2]] = TerrainParam.Durable;
						//オブジェクトのタイプを記憶
						m_ChunkData[chunk_x][chunk_y].TerrainType = TerrainParam.Type;
					}
				}
			}
		}
	}
	fwrite(&m_ChunkData, sizeof(ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
	fclose(fp);
}