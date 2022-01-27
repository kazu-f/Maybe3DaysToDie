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
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}
private:
	DestructibleObject* m_hitObj = nullptr;
	SaveDataFile* m_SaveData = nullptr;
};

