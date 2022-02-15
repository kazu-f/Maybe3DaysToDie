#pragma once
#include "Item/GameItemBase.h"

class SaveDataFile
{
public:
	struct ObjectData {
		unsigned char ObjId = -1;		//使用しているブロックの種類
		unsigned short ObjDurable = 0;		//ブロックの耐久値
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
		GameItemBase* item;		//アイテム
		int stack = 0;		//個数
	};

	struct ChestData {
		ItemData itemData[Inventory_X][Inventory_Y];		//枠分
	};

	struct ChunkAndPos {
		int ID[5] = { 0,0,0,0,0 };		//前2つがチャンク後ろ2つが素のチャンク内の位置
	};

	struct WorldChestData {
		ChunkAndPos id;
		ChestData data;
	};
	/// <summary>
	/// チェストのデータを追加
	/// </summary>
	/// <param name="data">チェストのデータ</param>
	void AddChestData(const WorldChestData& data)
	{
		m_WorldChestData.push_back(data);
	}

	/// <summary>
	/// チェストを取得
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns>チェストのデータ</returns>
	const ChestData* GetChestData(const ChunkAndPos& key)
	{
		for (const auto& chest : m_WorldChestData)
		{
			//IDをチェック
			if (CheckID(key, chest.id))
			{
				//IDが合致した
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