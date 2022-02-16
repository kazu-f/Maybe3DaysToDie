#pragma once
#include "MiniEngine/physics/CollisionAttr.h"
#include "Item/GameItemBase.h"

class Tool;
class SaveDataFile;

struct Item {
	GameItemBase* item = nullptr;
	int stack = 0;
	int itemID = -1;
};

//todo �v���C���[������ĂԂ悤�ɂȂ�����IGameObject���p�����Ȃ��悤��
class DestroyObject:public IGameObject
{
public:
	DestroyObject();
	~DestroyObject();

	std::vector<Item>& AddObjectDamage();

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
	std::vector<Item> m_Item;
};