#pragma once
class GameItemBase;
class GameItemTool;
class GameItemPlaceObj;
class BlockItem;
class GameItemTerrain;
class GameItemFoods;
class GameItemMaterial;
namespace nsTerrain {
	class TerrainMaterial;
}
class Tool;

/// <summary>
/// jsonファイルからツールデータを読み込むクラス。
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;

public:		//シングルトン。
	static void CreateInstance()
	{
		m_instance = new ItemDataFile();
	}

	static void Release()
	{
		if(m_instance != nullptr) delete m_instance;
	}

	static ItemDataFile* GetInstance()
	{
		return m_instance;
	}

private:
	static ItemDataFile* m_instance;

private:
	ItemDataFile();
	~ItemDataFile();

public:
	//アイテムのデータを読み込む処理。
	void InitItemData(const char* filePath);
	//アイテムデータを基底クラスで取得する。
	GameItemBase* GetItemDataBase(int id)
	{
		return m_itemArray[id];
	}
	/// <summary>
	/// アイテムのデータを取得する。
	/// </summary>
	/// <param name="id">アイテムのID</param>
	/// <returns>型変換が上手くいけば取得できる。</returns>
	template<class T>T* GetItemData(int id)
	{
		T* p = dynamic_cast<T*>(m_itemArray[id]);
		if (p == nullptr) {
			ENGINE_MESSAGE_BOX(
				"アイテムデータの型変換に失敗しました。",
				"\n型の情報を基底クラスの変数から確認してください。")
		}
		return p;
	}
	/// <summary>
	/// ツールデータを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	GameItemTool* GetToolData(int id)
	{
		GameItemTool* tool = nullptr;

		auto it = m_toolMap.find(id);
		if (it != m_toolMap.end())
		{
			tool = it->second;
		}

		return tool;
	}
	/// <summary>
	/// ブロックデータを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	GameItemPlaceObj* GetPlaceData(int id)
	{
		GameItemPlaceObj* place = nullptr;

		auto it = m_placeMap.find(id);
		if (it != m_placeMap.end())
		{
			place = it->second;
		}

		return place;

	}
	/// <summary>
	/// ブロックデータを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	BlockItem* GetBlockData(int id)
	{
		BlockItem* block = nullptr;

		auto it = m_blockMap.find(id);
		if (it != m_blockMap.end())
		{
			block = it->second;
		}

		return block;

	}
	/// <summary>
	/// 地形データを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	GameItemTerrain* GetTerrainData(int id)
	{
		GameItemTerrain* terrain = nullptr;

		auto it = m_terrainMap.find(id);
		if (it != m_terrainMap.end())
		{
			terrain = it->second;
		}

		return terrain;

	}
	/// <summary>
	/// 地形データを取得する。
	/// </summary>
	/// <param name="id">地形ID</param>
	/// <returns></returns>
	GameItemTerrain* GetTerrainDataTypeID(int id)
	{
		GameItemTerrain* terrain = nullptr;

		auto it = m_terrainMap.begin();
		std::advance(it, id);

		terrain = it->second;

		return terrain;

	}
	/// <summary>
	/// 食料等のデータを取得できるようにした。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	GameItemFoods* GetFoodData(int id)
	{
		GameItemFoods* food = nullptr;

		auto it = m_foodMap.find(id);
		if (it != m_foodMap.end())
		{
			food = it->second;
		}

		return food;
	}
	/// <summary>
	/// 素材データを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns></returns>
	GameItemMaterial* GetMaterialData(int id)
	{
		GameItemMaterial* material = nullptr;

		auto it = m_materialMap.find(id);
		if (it != m_materialMap.end())
		{
			material = it->second;
		}

		return material;
	}

	nsTerrain::TerrainMaterial* GetTerrainMaterials()
	{
		return m_terrainMaterials.get();
	}

	Tool* GetHandTool()
	{
		return m_handTool.get();
	}

	GameItemBase* GetNullGameItem()
	{
		return m_nullGameItem;
	}
private:
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
	std::map<int, GameItemTool*> m_toolMap;
	std::map<int, GameItemPlaceObj*> m_placeMap;
	std::map<int, BlockItem*> m_blockMap;
	std::map<int, GameItemTerrain*> m_terrainMap;
	std::map<int, GameItemFoods*> m_foodMap;
	std::map<int, GameItemMaterial*> m_materialMap;
	std::unique_ptr<nsTerrain::TerrainMaterial> m_terrainMaterials;
	std::unique_ptr<Tool> m_handTool;
	GameItemBase* m_nullGameItem;

	int m_arraySize = 0;
};

