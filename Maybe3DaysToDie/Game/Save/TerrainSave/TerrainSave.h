#pragma once
#include "TerrainManager/TerrainWorld.h"
#include "SaveDataFile.h"

class TerrainSave
{
public:
	TerrainSave() {}
	~TerrainSave() {}

	void Save();
	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

private:
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
};