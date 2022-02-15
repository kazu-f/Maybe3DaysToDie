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

class ChestSave
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

	/// <summary>
	/// �`�F�X�g�̃f�[�^��ǉ�
	/// </summary>
	/// <param name="key">�L�[</param>
	/// <param name="data">�`�F�X�g�̃f�[�^</param>
	void AddChestData(const ChunkAndPos& key, const ChestData& data)
	{
		m_WorldChestData.insert(std::make_pair(key, data));
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
			if (CheckID(key, chest.first))
			{
				//ID�����v����
				return &chest.second;
			}
		}
		return nullptr;
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
	std::map<ChunkAndPos, ChestData>m_WorldChestData;
};