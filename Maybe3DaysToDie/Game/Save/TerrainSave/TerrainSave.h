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
	/// テラインワールドをセット
	/// </summary>
	/// <param name="terrain">テラインワールド</param>
	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	/// <param name="file">セーブデータファイル</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

private:
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
};