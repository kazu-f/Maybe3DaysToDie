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
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

private:
	SaveDataFile* m_SaveDataFile = nullptr;
};