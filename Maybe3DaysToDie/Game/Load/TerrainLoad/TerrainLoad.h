#pragma once
#include "SaveDataFile.h"

class TerrainLoad
{
public:
	TerrainLoad();
	~TerrainLoad();

	void Load();
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}
private:
	SaveDataFile* m_SaveDataFile = nullptr;
};