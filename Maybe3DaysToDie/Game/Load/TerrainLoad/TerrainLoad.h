#pragma once
#include "SaveDataFile.h"

class TerrainLoad
{
public:
	TerrainLoad();
	~TerrainLoad();

	void Load();

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