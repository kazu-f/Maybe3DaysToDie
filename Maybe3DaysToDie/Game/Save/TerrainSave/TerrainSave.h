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
	/// �e���C�����[���h���Z�b�g
	/// </summary>
	/// <param name="terrain">�e���C�����[���h</param>
	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

private:
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
};