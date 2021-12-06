#include "stdafx.h"
#include "SaveDataFile.h"
#include "TerrainLoad.h"

TerrainLoad::TerrainLoad()
{

}

TerrainLoad::~TerrainLoad()
{

}

void TerrainLoad::Load()
{
	FILE* fp;
	fp = fopen(SaveDataFilePath_Terrain, "rb");
	if (fp == NULL)
	{
		//セーブデータがありません
		return;
	}

	fread(&m_ChunkData, sizeof(ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);

	for (int chunk_x = 0; chunk_x < MAX_CHUNK_SIDE; chunk_x++)
	{
		for (int chunk_y = 0; chunk_y < MAX_CHUNK_SIDE; chunk_y++)
		{
			//チャンクごとに取り出す

		}
	}
}