#pragma once
#include "SaveDataFile.h"

class AccessObject
{
public:
	AccessObject();
	~AccessObject();

private:
	/// <summary>
	/// ������
	/// </summary>
	void Init();

	void OnDestroy();

public:
	/// <summary>
	/// �I�u�W�F�N�g�ɃA�N�Z�X����
	/// </summary>
	void Access();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}

	/// <summary>
	/// �A�N�Z�X�����ǂ������擾
	/// </summary>
	/// <returns>�A�N�Z�X���̎���true</returns>
	bool IsAccess()
	{
		return IsSpriteActive;
	}

	/// <summary>
	/// �A�N�Z�X���I������B
	/// �{�b�N�X�����Ƃ��ȂǂɎg�p
	/// </summary>
	void EndAccess()
	{
		SetAccessFlag(false);
	}

private:
	void SwitchAction(AccessTag tag);

	void SwitchSpriteActive()
	{
		IsSpriteActive = !IsSpriteActive;
		m_BoxSprite->SetActiveFlag(IsSpriteActive);
	}
	
	void SetAccessFlag(bool flag)
	{
		if (IsSpriteActive == flag)
		{
			//�t���O�ɕύX�Ȃ��Ƃ�return
			return;
		}
		IsSpriteActive = flag;
		m_BoxSprite->SetActiveFlag(flag);
	}
private:
	DestructibleObject* m_hitObj = nullptr;
	SaveDataFile* m_SaveData = nullptr;
	prefab::CSpriteRender* m_BoxSprite = nullptr;
	bool IsSpriteActive = false;
};

