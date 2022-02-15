#pragma once
#include "SaveDataFile.h"

class ChestSave
{
public:
	ChestSave() {}
	~ChestSave() {}

	/// <summary>
	/// セーブ
	/// </summary>
	void Save();

	/// <summary>
	/// データファイルをセット
	/// </summary>
	void SetDataFile(ChestDataFile* file)
	{
		m_dataFile = file;
	}

private:
	ChestDataFile* m_dataFile = nullptr;
};

