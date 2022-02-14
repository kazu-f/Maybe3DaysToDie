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
/// json�t�@�C������c�[���f�[�^��ǂݍ��ރN���X�B
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;

public:		//�V���O���g���B
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
	//�A�C�e���̃f�[�^��ǂݍ��ޏ����B
	void InitItemData(const char* filePath);
	//�A�C�e���f�[�^�����N���X�Ŏ擾����B
	GameItemBase* GetItemDataBase(int id)
	{
		return m_itemArray[id];
	}
	/// <summary>
	/// �A�C�e���̃f�[�^���擾����B
	/// </summary>
	/// <param name="id">�A�C�e����ID</param>
	/// <returns>�^�ϊ�����肭�����Ύ擾�ł���B</returns>
	template<class T>T* GetItemData(int id)
	{
		T* p = dynamic_cast<T*>(m_itemArray[id]);
		if (p == nullptr) {
			ENGINE_MESSAGE_BOX(
				"�A�C�e���f�[�^�̌^�ϊ��Ɏ��s���܂����B",
				"\n�^�̏������N���X�̕ϐ�����m�F���Ă��������B")
		}
		return p;
	}
	/// <summary>
	/// �c�[���f�[�^���擾����B
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
	/// �u���b�N�f�[�^���擾����B
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
	/// �u���b�N�f�[�^���擾����B
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
	/// �n�`�f�[�^���擾����B
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
	/// �n�`�f�[�^���擾����B
	/// </summary>
	/// <param name="id">�n�`ID</param>
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
	/// �H�����̃f�[�^���擾�ł���悤�ɂ����B
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
	/// �f�ރf�[�^���擾����B
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

