#pragma once
#include "TerrainManager/TerrainWorld.h"
#include "SaveDataFile.h"

class TerrainSave
{
public:
	TerrainSave() {}
	~TerrainSave() {}

	void Save();

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	/// <param name="file">セーブデータファイル</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

private:
	SaveDataFile* m_SaveDataFile = nullptr;
};