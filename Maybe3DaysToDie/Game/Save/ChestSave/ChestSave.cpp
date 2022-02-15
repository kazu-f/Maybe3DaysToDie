#include "stdafx.h"
#include "ChestSave.h"
#include <direct.h>

void ChestSave::Save()
{
	if (m_dataFile == nullptr)
	{
		//セーブデータファイルクラスが参照できませんでした。
		return;
	}
	FILE* fp;
	fp = fopen(m_dataFile->GetSaveDataFilePath_Num(), "wb");
	if (fp == NULL)
	{
		if (_mkdir("SaveData") != 0)
		{
			//ディレクトリが作成できなかった
			return;
		}
		fp = fopen(m_dataFile->GetSaveDataFilePath_Num(), "wb");
	}
	int size = m_dataFile->GetAllData().size();
	fwrite(&size, sizeof(int), 1, fp);
	fclose(fp);

	FILE* fp2;
	fp2 = fopen(m_dataFile->GetSaveDataFilePath(), "wb");
	if (fp2 == NULL)
	{
		if (_mkdir("SaveData") != 0)
		{
			//ディレクトリが作成できなかった
			return;
		}
		fp2 = fopen(m_dataFile->GetSaveDataFilePath(), "wb");
	}
	fwrite(&m_dataFile->GetAllData(), sizeof(ChestDataFile::WorldChestData), m_dataFile->GetAllData().size(), fp2);
	fclose(fp2);
}