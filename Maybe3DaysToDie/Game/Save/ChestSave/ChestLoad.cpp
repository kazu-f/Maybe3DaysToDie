#include "stdafx.h"
#include "ChestLoad.h"

bool ChestLoad::Load()
{
	if (m_dataFile == nullptr)
	{
		//セーブデータファイルクラスが参照できませんでした。
		return false;
	}
	FILE* fp;
	fp = fopen(m_dataFile->GetSaveDataFilePath_Num(), "rb");
	if (fp == NULL)
	{
		//セーブデータがありません
		return false;
	}

	FILE* fp2;
	fp2 = fopen(m_dataFile->GetSaveDataFilePath(), "rb");
	if (fp2 == NULL)
	{
		//セーブデータがありません
		return false;
	}

	int size = 0;
	fread(&size, sizeof(int), 1, fp);
	m_dataFile->GetAllData().resize(size);
	fclose(fp);

	fread(&m_dataFile->GetAllData(), sizeof(ChestDataFile::WorldChestData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp2);
	//取得できた
	fclose(fp2);
	return true;
}