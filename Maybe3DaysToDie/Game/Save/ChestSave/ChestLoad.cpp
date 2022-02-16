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
	int size = 0;
	fread(&size, sizeof(int), 1, fp);
	fclose(fp);

	FILE* fp2;
	fp2 = fopen(m_dataFile->GetSaveDataFilePath(), "rb");
	if (fp2 == NULL)
	{
		//セーブデータがありません
		return false;
	}

	//ChestDataFile::WorldChestData hoge;
	//while (fread(&hoge, sizeof(ChestDataFile::WorldChestData), 1, fp2) == 1) {
	//	m_dataFile->GetAllData().push_back(hoge);
	//}

	//m_dataFile->GetAllData().resize(size);

	//fread(&m_dataFile->GetAllData(), sizeof(ChestDataFile::WorldChestData), size, fp2);
	//取得できた

	fclose(fp2);
	return true;
}