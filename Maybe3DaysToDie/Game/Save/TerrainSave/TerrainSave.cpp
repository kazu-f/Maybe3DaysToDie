#include "stdafx.h"
#include "TerrainSave.h"
#include <direct.h>

void TerrainSave::Save()
{
	if (m_SaveDataFile == nullptr)
	{
		//セーブデータファイルクラスが参照できませんでした。
		return;
	}
	if (m_TerrainWorld == nullptr)
	{
		return;
	}
	FILE* fp;
	fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "wb");
	if (fp == NULL)
	{
		if (_mkdir("SaveData") != 0)
		{
			//ディレクトリが作成できなかった
			return;
		}
		fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "wb");
	}

	for (int chunk_x = 0; chunk_x < MAX_CHUNK_SIDE; chunk_x++)
	{
		for (int chunk_y = 0; chunk_y < MAX_CHUNK_SIDE; chunk_y++)
		{
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
						m_SaveDataFile->m_ChunkData[chunk_x][chunk_y].ObjData[terrainID[0]][terrainID[1]][terrainID[2]].ObjId = TerrainParam.BlockID;
						//ブロックの耐久値を記憶
						m_SaveDataFile->m_ChunkData[chunk_x][chunk_y].ObjData[terrainID[0]][terrainID[1]][terrainID[2]].ObjDurable = TerrainParam.Durable;
					}
				}
			}
		}
	}
	fwrite(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
	fclose(fp);
}