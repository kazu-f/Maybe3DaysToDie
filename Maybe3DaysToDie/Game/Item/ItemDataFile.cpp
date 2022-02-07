#include "stdafx.h"
#include "ItemDataFile.h"

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
	namespace Items {
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
	namespace Tools {
		const char* damage = "damage";					//ダメージ。
		const char* durable = "durable";				//耐久値。
		const char* useStamina = "useStamina";			//使用スタミナ。
		const char* toolTypeTag = "tool";				//ツールタイプ。
	}
}

ItemDataFile::ItemDataFile()
{
}

ItemDataFile::~ItemDataFile()
{
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
		itemData->itemID = _item[Items::itemID];
		itemData->itemType = _item[Items::itemType];
		itemData->itemName = _item[Items::itemName];
		itemData->tkmPath = _item[Items::itemTkm];
		itemData->iconPath = _item[Items::itemIcon];

		//クラフト素材データリストを構築。
		int craftMaterialNum = _item[Items::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[Items::itemMaterials][i][Items::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[Items::itemMaterials][i][Items::CraftMaterials::materialNum];
		}
		//クラフト可能先データリストを構築。
		int craftableNum = _item[Items::itemCraftables][Items::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[Items::itemCraftables][Items::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//アイテムのタイプ別にデータを構築。
		switch (itemData->itemType)
		{
		case EnItemType::enItem_Tool: {
			ToolInfo info;
			info.AttackPower = _item[Tools::damage];
			info.Durable = _item[Tools::durable];
			info.UseStamina = _item[Tools::useStamina];
			info.tool = _item[Tools::toolTypeTag];

			GameItemTool* gameItemTool = new GameItemTool(itemData, info);
			m_itemArray.push_back(gameItemTool);
		}
			break;
			
		case EnItemType::enItem_Place:
			break;
			
		case EnItemType::enItem_Food:
			break;
			
		case EnItemType::enItem_Material:
			break;

		default:
			break;
		}


	}


}
