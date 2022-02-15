#pragma once
#include "MiniEngine/physics/CollisionAttr.h"
#include "Item/GameItemBase.h"

class Tool;
class SaveDataFile;
//todo �v���C���[������ĂԂ悤�ɂȂ�����IGameObject���p�����Ȃ��悤��
class DestroyObject:public IGameObject
{
public:
	DestroyObject();
	~DestroyObject();

	std::vector<GameItemBase*>& AddObjectDamage();

	void Update();

	void SetTool(Tool* tool)
	{
		m_tool = tool;
	}

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}

private:
	Tool* m_tool = nullptr;
	SaveDataFile* m_SaveData = nullptr;
	std::vector<GameItemBase*>	m_Item;
};