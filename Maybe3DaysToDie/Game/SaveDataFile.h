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

class ChestSave
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

	/// <summary>
	/// チェストのデータを追加
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="data">チェストのデータ</param>
	void AddChestData(const ChunkAndPos& key, const ChestData& data)
	{
		m_WorldChestData.insert(std::make_pair(key, data));
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
			if (CheckID(key, chest.first))
			{
				//IDが合致した
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