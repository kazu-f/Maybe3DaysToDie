#pragma once
#include "SaveDataFile.h"

class ChestSave
{
public:
	ChestSave() {}
	~ChestSave() {}

	/// <summary>
	/// �Z�[�u
	/// </summary>
	void Save();

	/// <summary>
	/// �f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetDataFile(ChestDataFile* file)
	{
		m_dataFile = file;
	}

private:
	ChestDataFile* m_dataFile = nullptr;
};

