#include "stdafx.h"
#include "TerrainLoad.h"

TerrainLoad::TerrainLoad()
{

}

TerrainLoad::~TerrainLoad()
{

}

bool TerrainLoad::Load()
{
	if (m_SaveDataFile == nullptr)
	{
		//セーブデータファイルクラスが参照できませんでした。
		return false;
	}
	FILE* fp;
	fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "rb");
	if (fp == NULL)
	{
		//セーブデータがありません
		return false;
	}

	fread(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
	//取得できた
	return true;
}