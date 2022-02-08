#include "stdafx.h"
#include "ItemDataFile.h"
#include "Item/GameItemBase.h"
#include "Item/GameItemTool.h"
#include "Item/BlockItem.h"
#include "Item/GameItemFoods.h"
#include "Item/GameItemMaterial.h"

ItemDataFile* ItemDataFile::m_instance = nullptr;

namespace {
	enum EnItemType
	{
		enItem_None = -1,
		enItem_Tool,
		enItem_Place,
		enItem_Food,
		enItem_Material,
		ItemTypeNum
	};

	//アイテムの基本データに関する名前空間。
	namespace nsItems {
		const char* itemType = "itemType";		//アイテムの種類を分けるための変数。
		const char* itemID = "itemID";			//アイテムのID。
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
	namespace nsTools {
		const char* damage = "damage";					//ダメージ。
		const char* durable = "durable";				//耐久値。
		const char* useStamina = "useStamina";			//使用スタミナ。
		const char* toolTypeTag = "tool";				//ツールタイプ。
	}
	
	//設置物データに関する名前空間。
	namespace nsPlaceObjs {

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
	namespace nsFoods {
		const char* hp = "HP";
		const char* water = "water";
		const char* food = "food";
		const char* stamina = "stamina";
	}

	//素材アイテムに関する名前空間。
	namespace nsMaterials
	{
		const char* MaterialType = "MaterialType";		//素材タイプ？
	}
}

ItemDataFile::ItemDataFile()
{
	//シングルトン。
	assert(m_instance == nullptr);	
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
		itemData->itemID = _item[nsItems::itemID];
		itemData->itemType = _item[nsItems::itemType];
		itemData->itemName = _item[nsItems::itemName];
		itemData->tkmPath = _item[nsItems::itemTkm];
		itemData->iconPath = _item[nsItems::itemIcon];

		//クラフト素材データリストを構築。
		int craftMaterialNum = _item[nsItems::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[nsItems::itemMaterials][i][nsItems::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[nsItems::itemMaterials][i][nsItems::CraftMaterials::materialNum];
		}
		//クラフト可能先データリストを構築。
		int craftableNum = _item[nsItems::itemCraftables][nsItems::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[nsItems::itemCraftables][nsItems::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//アイテムのタイプ別にデータを構築。
		switch (itemData->itemType)
		{
		case EnItemType::enItem_Tool: {
			ToolInfo info;
			info.AttackPower = _item[nsTools::damage];
			info.Durable = _item[nsTools::durable];
			info.UseStamina = _item[nsTools::useStamina];
			info.tool = _item[nsTools::toolTypeTag];

			GameItemTool* gameItemTool = new GameItemTool(itemData, info);
			m_itemArray.push_back(gameItemTool);
		}
			break;
			
		case EnItemType::enItem_Place: {
			//設置物の耐久値と特攻ツール。
			ObjectParams params;
			params.Durable = _item[nsPlaceObjs::durable];
			params.AptitudeTool = _item[nsPlaceObjs::tool];

			int placeType = _item[nsPlaceObjs::Type];
			//設置物から採取できるアイテムのデータ。
			PlaceObjectCollectItemData collectItemData;
			int num = _item[nsPlaceObjs::Collect::collectItemDataNum];
			collectItemData.resize(num);
			for (int i = 0; i < num; i++)
			{
				collectItemData[i].collectID = _item[nsPlaceObjs::collectItems][i][nsPlaceObjs::Collect::corectItemID];
				collectItemData[i].collectNum = _item[nsPlaceObjs::collectItems][i][nsPlaceObjs::Collect::corectionNum];
			}

			BlockItem* blockItem = new BlockItem(itemData, params, collectItemData, placeType);
			m_itemArray.push_back(blockItem);
		}
			break;
			
		case EnItemType::enItem_Food: {
			//食料等のパラメータ。
			SFoodParams params;
			params.hp = _item[nsFoods::hp];
			params.water = _item[nsFoods::water];
			params.food = _item[nsFoods::food];
			params.stamina = _item[nsFoods::stamina];

			GameItemFoods* foodItem = new GameItemFoods(itemData, params);
			m_itemArray.push_back(foodItem);
		}
			break;
			
		case EnItemType::enItem_Material: {
			//素材タイプ？
			int type = _item[nsMaterials::MaterialType];

			GameItemMaterial* materialItem = new GameItemMaterial(itemData, type);
			m_itemArray.push_back(materialItem);
		}
			break;

		default:
			break;
		}


	}

	m_arraySize = m_itemArray.size();
}
