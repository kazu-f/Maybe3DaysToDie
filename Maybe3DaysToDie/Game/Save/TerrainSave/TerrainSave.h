#pragma once
#include "TerrainManager/TerrainWorld.h"
#include "SaveDataFile.h"

class TerrainSave:public ISave
{
public:
	TerrainSave() {}
	~TerrainSave() {}

	void Save();
	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}
private:
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
};