#include "stdafx.h"
#include "ItemDataFile.h"
#include "Item/GameItemBase.h"
#include "Item/GameItemTool.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"
#include "Item/GameItemFoods.h"
#include "Item/GameItemMaterial.h"
#include "TerrainManager/TerrainRender/TerrainMaterial.h"

ItemDataFile* ItemDataFile::m_instance = nullptr;

namespace {

	const char* InitFilePath = "Assets/Data/json/Item_v2.json";		//読み込むファイルのファイルパス。
	enum EnItemType
	{
		enItem_None = -1,
		enItem_Tool,
		enItem_Place,
		enItem_Terrain,
		enItem_Food,
		enItem_Material,
		ItemTypeNum
	};

	//アイテムの基本データに関する名前空間。
	namespace nsItemsData {
		const char* itemType = "itemType";		//アイテムの種類を分けるための変数。
		const char* itemID = "itemID";			//アイテムのID。
		const char* itemTypeID = "itemTypeID";			//アイテムのID。
		const char* itemName = "name";			//アイテムの名前。
		const char* itemStuck = "stackNum";		//アイテムのスタック数。
		const char* itemTkm = "tkmFile";		//アイテムのモデルファイルパス。
		const char* itemIcon = "iconData";		//アイテムのアイコンファイルパス。
		const char* itemMaterials = "itemMaterialData";				//アイテムをクラフトするための素材データ配列。
		//クラフト素材についての名前空間。
		namespace CraftMaterials{
			const char* itemMaterialDataNum = "itemMaterialDataNum";//アイテムをクラフトするための素材データ配列のサイズ。
			const char* materialID = "craftMaterialID";				//クラフト素材のID。
			const char* materialNum = "craftItemNum";				//クラフト素材の必要数。
		}
		const char* itemCraftables = "craftableItemIDs";			//クラフト可能先アイテム構造体。
		//クラフト可能先アイテムについての名前空間。
		namespace Craftable {
			const char* craftableIDs = "craftableIDs";				//クラフト可能先のアイテムIDのリスト。
			const char* craftableNum = "craftableItemNum";			//クラフト可能先アイテムのIDのリストのサイズ。
		}
	}

	//ツールデータに関する名前空間。
	namespace nsToolsData {
		const char* damage = "damage";					//ダメージ。
		const char* durable = "durable";				//耐久値。
		const char* useStamina = "useStamina";			//使用スタミナ。
		const char* toolTypeTag = "tool";				//ツールタイプ。
	}
	
	//設置物データに関する名前空間。
	namespace nsTerrainData {

		const char* durable = "durable";				//耐久値。
		const char* tool = "tool";						//特攻ツール。
		const char* texture = "texture";				//地形のテクスチャ。
		const char* collectItems = "collectItems";		//設置物から採取できるアイテムデータリスト。
		namespace Collect {
			const char* collectItemDataNum = "collectItemDataNum";		//採取物データの数。
			const char* corectItemID = "corectItemID";	//採取できるアイテムのID。
			const char* corectionNum = "corectionNum";	//採取できる量。
		}
	}
	//設置物データに関する名前空間。
	namespace nsPlaceObjsData {

		//設置物のタイプ。
		enum EnPlaceTypes
		{
			enType_Terrain,
			enType_Block,
			enType_Object,
			enPlaceTypeNum
		};
		const char* durable = "durable";				//耐久値。
		const char* tool = "tool";						//特攻ツール。
		const char* Type = "Type";						//設置物のタイプ。
		const char* collectItems = "collectItems";		//設置物から採取できるアイテムデータリスト。
		namespace Collect {
			const char* collectItemDataNum = "collectItemDataNum";		//採取物データの数。
			const char* corectItemID = "corectItemID";	//採取できるアイテムのID。
			const char* corectionNum = "corectionNum";	//採取できる量。
		}
	}
	
	//食料等のデータに関する名前空間。
	namespace nsFoodsData {
		const char* hp = "HP";
		const char* water = "water";
		const char* food = "food";
		const char* stamina = "stamina";
	}

	//素材アイテムに関する名前空間。
	namespace nsMaterialsData
	{
		const char* MaterialType = "MaterialType";		//素材タイプ？
	}
}

ItemDataFile::ItemDataFile()
{
	//シングルトン。
	assert(m_instance == nullptr);
	m_terrainMaterials = std::make_unique<nsTerrain::TerrainMaterial>();
	InitItemData(InitFilePath);
}

ItemDataFile::~ItemDataFile()
{
	m_instance = nullptr;
}

void ItemDataFile::InitItemData(const char* filePath)
{
	std::ifstream ifs;
	ifs.open(filePath);
	if (!ifs) {
		ENGINE_MESSAGE_BOX(
			"Itemデータファイルのオープンに失敗しました。\n"
			"%s", filePath
		);
		return;
	}

	//jsonファイルに読み込んでいく。
	json jItem;
	ifs >> jItem;
	ifs.close();			//ファイルは閉じておく。

	//ツールの種類ごとに読み込む。
	for (auto _item : jItem)
	{
		//アイテムの基本データの読み込み。
		SItemDataPtr itemData = std::make_unique<SItemData>();
		itemData->itemID = _item[nsItemsData::itemID];
		itemData->itemTypeID = _item[nsItemsData::itemTypeID];
		itemData->itemType = _item[nsItemsData::itemType];
		itemData->itemName = _item[nsItemsData::itemName];
		itemData->tkmPath = _item[nsItemsData::itemTkm];
		itemData->iconPath = _item[nsItemsData::itemIcon];

		//クラフト素材データリストを構築。
		int craftMaterialNum = _item[nsItemsData::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[nsItemsData::itemMaterials][i][nsItemsData::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[nsItemsData::itemMaterials][i][nsItemsData::CraftMaterials::materialNum];
		}
		//クラフト可能先データリストを構築。
		int craftableNum = _item[nsItemsData::itemCraftables][nsItemsData::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[nsItemsData::itemCraftables][nsItemsData::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//アイテムのタイプ別にデータを構築。
		switch (itemData->itemType)
		{
		case EnItemType::enItem_Tool: {
			ToolInfo info;
			info.AttackPower = _item[nsToolsData::damage];
			info.Durable = _item[nsToolsData::durable];
			info.UseStamina = _item[nsToolsData::useStamina];
			info.tool = _item[nsToolsData::toolTypeTag];

			GameItemTool* gameItemTool = new GameItemTool(itemData, info);
			m_itemArray.push_back(gameItemTool);
			m_toolMap.insert(std::make_pair(gameItemTool->GetIdemData()->itemID, gameItemTool));
		}
			break;
			
		case EnItemType::enItem_Place: {
			//設置物の耐久値と特攻ツール。
			ObjectParams params;
			params.Durable = _item[nsPlaceObjsData::durable];
			params.AptitudeTool = _item[nsPlaceObjsData::tool];

			int placeType = _item[nsPlaceObjsData::Type];
			//設置物から採取できるアイテムのデータ。
			ObjectCollectItemData collectItemData;
			int num = _item[nsPlaceObjsData::Collect::collectItemDataNum];
			collectItemData.resize(num);
			for (int i = 0; i < num; i++)
			{
				collectItemData[i].collectID = _item[nsPlaceObjsData::collectItems][i][nsPlaceObjsData::Collect::corectItemID];
				collectItemData[i].collectNum = _item[nsPlaceObjsData::collectItems][i][nsPlaceObjsData::Collect::corectionNum];
			}

			BlockItem* blockItem = new BlockItem(itemData, params, collectItemData, placeType);
			m_itemArray.push_back(blockItem);
			m_blockMap.insert(std::make_pair(blockItem->GetIdemData()->itemID, blockItem));
		}
		case EnItemType::enItem_Terrain: {
			//設置物の耐久値と特攻ツール。
			ObjectParams params;
			params.Durable = _item[nsTerrainData::durable];
			params.AptitudeTool = _item[nsTerrainData::tool];
			std::string texture = _item[nsTerrainData::texture];

			//設置物から採取できるアイテムのデータ。
			ObjectCollectItemData collectItemData;
			int num = _item[nsTerrainData::Collect::collectItemDataNum];
			collectItemData.resize(num);
			for (int i = 0; i < num; i++)
			{
				collectItemData[i].collectID = _item[nsTerrainData::collectItems][i][nsTerrainData::Collect::corectItemID];
				collectItemData[i].collectNum = _item[nsTerrainData::collectItems][i][nsTerrainData::Collect::corectionNum];
			}
			m_terrainMaterials->RegistTexturePath(texture);

			GameItemTerrain* terrainItem = new GameItemTerrain(itemData, params, collectItemData, texture);
			m_itemArray.push_back(terrainItem);
			m_terrainMap.insert(std::make_pair(terrainItem->GetIdemData()->itemID, terrainItem));
		}
			break;
			
		case EnItemType::enItem_Food: {
			//食料等のパラメータ。
			SFoodParams params;
			params.hp = _item[nsFoodsData::hp];
			params.water = _item[nsFoodsData::water];
			params.food = _item[nsFoodsData::food];
			params.stamina = _item[nsFoodsData::stamina];

			GameItemFoods* foodItem = new GameItemFoods(itemData, params);
			m_itemArray.push_back(foodItem);
			m_foodMap.insert(std::make_pair(foodItem->GetIdemData()->itemID, foodItem));
		}
			break;
			
		case EnItemType::enItem_Material: {
			//素材タイプ？
			int type = _item[nsMaterialsData::MaterialType];

			GameItemMaterial* materialItem = new GameItemMaterial(itemData, type);
			m_itemArray.push_back(materialItem);
			m_materialMap.insert(std::make_pair(materialItem->GetIdemData()->itemID, materialItem));
		}
			break;

		default:
			break;
		}


	}

	m_arraySize = m_itemArray.size();
	m_terrainMaterials->InitTexture();
}
