#pragma once
#include "SaveDataFile.h"

class AccessObject
{
public:
	AccessObject() {}
	~AccessObject() {}


	void Access();

	void SwitchAction(AccessTag tag);

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}
private:
	DestructibleObject* m_hitObj = nullptr;
	SaveDataFile* m_SaveData = nullptr;
};

