#pragma once
#include "SaveDataFile.h"

class ChestLoad
{
public:
	ChestLoad() {}
	~ChestLoad() {}

	/// <summary>
	/// ロード
	/// </summary>
	bool Load();

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

