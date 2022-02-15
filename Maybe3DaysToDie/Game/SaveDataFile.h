#pragma once
#include "Item/GameItemBase.h"

class SaveDataFile
{
public:
	struct ObjectData {
		unsigned char ObjId = -1;		//�g�p���Ă���u���b�N�̎��
		unsigned short ObjDurable = 0;		//�u���b�N�̑ϋv�l
		Quaternion Rotate = Quaternion::Identity;
	};

	struct  ChunkData
	{
		ObjectData ObjData[ChunkWidth][ChunkHeight][ChunkWidth];
	};
	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
};

class ChestDataFile
{
public:
	struct ItemData {
		GameItemBase* item;		//�A�C�e��
		int stack = 0;		//��
	};

	struct ChestData {
		ItemData itemData[Inventory_X][Inventory_Y];		//�g��
	};

	struct ChunkAndPos {
		int ID[5] = { 0,0,0,0,0 };		//�O2���`�����N���2���f�̃`�����N���̈ʒu
	};

	struct WorldChestData {
		ChunkAndPos id;
		ChestData data;
	};
	/// <summary>
	/// �`�F�X�g�̃f�[�^��ǉ�
	/// </summary>
	/// <param name="data">�`�F�X�g�̃f�[�^</param>
	void AddChestData(const WorldChestData& data)
	{
		m_WorldChestData.push_back(data);
	}

	/// <summary>
	/// �`�F�X�g���擾
	/// </summary>
	/// <param name="key">�L�[</param>
	/// <returns>�`�F�X�g�̃f�[�^</returns>
	const ChestData* GetChestData(const ChunkAndPos& key)
	{
		for (const auto& chest : m_WorldChestData)
		{
			//ID���`�F�b�N
			if (CheckID(key, chest.id))
			{
				//ID�����v����
				return &chest.data;
			}
		}
		return nullptr;
	}

	const char* GetSaveDataFilePath_Num()
	{
		return SaveDataFilePath_ChestNum;
	}
	const char* GetSaveDataFilePath()
	{
		return SaveDataFilePath_Chest;
	}

	std::vector<WorldChestData>& GetAllData()
	{
		return m_WorldChestData;
	}
private:
	bool CheckID(const ChunkAndPos& id1, const ChunkAndPos& id2)
	{
		for (int i = 0; i < 5; i++)
		{
			if (id1.ID[i] != id2.ID[i])
			{
				return false;
			}
		}
		return true;
	}

private:
	std::vector<WorldChestData>m_WorldChestData;
	const char* SaveDataFilePath_Chest = "SaveData/ChestData.dat";
	const char* SaveDataFilePath_ChestNum = "SaveData/ChestNum.dat";
};