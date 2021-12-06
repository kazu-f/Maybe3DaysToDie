#pragma once
#include "SaveDataFile.h"

class TerrainLoad
{
public:
	TerrainLoad();
	~TerrainLoad();

	void Load();

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