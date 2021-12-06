#pragma once
#include "SaveDataFile.h"

class LoadingByChunk:public IGameObject
{
private:
	enum class LoadingRange
	{
		Short = 1,
		Middle = 1 << 1,
		Far = 1 << 2,
	};

public:
	LoadingByChunk();
	~LoadingByChunk();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

	bool Start();

	void Update();
private:
	SaveDataFile* m_SaveDataFile = nullptr;
	LoadingRange m_LoadingRange = LoadingRange::Short;
};