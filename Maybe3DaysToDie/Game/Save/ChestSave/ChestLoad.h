#pragma once
#include "SaveDataFile.h"

class ChestLoad
{
public:
	ChestLoad() {}
	~ChestLoad() {}

	/// <summary>
	/// ���[�h
	/// </summary>
	bool Load();

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

