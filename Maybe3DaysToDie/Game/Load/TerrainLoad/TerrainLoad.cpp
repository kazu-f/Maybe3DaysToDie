#include "stdafx.h"
#include "TerrainLoad.h"

TerrainLoad::TerrainLoad()
{

}

TerrainLoad::~TerrainLoad()
{

}

void TerrainLoad::Load()
{
	if (m_SaveDataFile == nullptr)
	{
		//セーブデータファイルクラスが参照できませんでした。
		return;
	}
	FILE* fp;
	fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "rb");
	if (fp == NULL)
	{
		//セーブデータがありません
		return;
	}

	fread(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
}