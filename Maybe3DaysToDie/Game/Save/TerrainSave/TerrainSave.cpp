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

	fwrite(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
	fclose(fp);
}