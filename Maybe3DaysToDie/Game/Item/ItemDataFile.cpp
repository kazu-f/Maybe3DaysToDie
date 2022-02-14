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

	const char* InitFilePath = "Assets/Data/json/Item_v2.json";		//�ǂݍ��ރt�@�C���̃t�@�C���p�X�B
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

	//�A�C�e���̊�{�f�[�^�Ɋւ��閼�O��ԁB
	namespace nsItemsData {
		const char* itemType = "itemType";		//�A�C�e���̎�ނ𕪂��邽�߂̕ϐ��B
		const char* itemID = "itemID";			//�A�C�e����ID�B
		const char* itemTypeID = "itemTypeID";			//�A�C�e����ID�B
		const char* itemName = "name";			//�A�C�e���̖��O�B
		const char* itemStuck = "stackNum";		//�A�C�e���̃X�^�b�N���B
		const char* itemTkm = "tkmFile";		//�A�C�e���̃��f���t�@�C���p�X�B
		const char* itemIcon = "iconData";		//�A�C�e���̃A�C�R���t�@�C���p�X�B
		const char* itemMaterials = "itemMaterialData";				//�A�C�e�����N���t�g���邽�߂̑f�ރf�[�^�z��B
		//�N���t�g�f�ނɂ��Ă̖��O��ԁB
		namespace CraftMaterials{
			const char* itemMaterialDataNum = "itemMaterialDataNum";//�A�C�e�����N���t�g���邽�߂̑f�ރf�[�^�z��̃T�C�Y�B
			const char* materialID = "craftMaterialID";				//�N���t�g�f�ނ�ID�B
			const char* materialNum = "craftItemNum";				//�N���t�g�f�ނ̕K�v���B
		}
		const char* itemCraftables = "craftableItemIDs";			//�N���t�g�\��A�C�e���\���́B
		//�N���t�g�\��A�C�e���ɂ��Ă̖��O��ԁB
		namespace Craftable {
			const char* craftableIDs = "craftableIDs";				//�N���t�g�\��̃A�C�e��ID�̃��X�g�B
			const char* craftableNum = "craftableItemNum";			//�N���t�g�\��A�C�e����ID�̃��X�g�̃T�C�Y�B
		}
	}

	//�c�[���f�[�^�Ɋւ��閼�O��ԁB
	namespace nsToolsData {
		const char* damage = "damage";					//�_���[�W�B
		const char* durable = "durable";				//�ϋv�l�B
		const char* useStamina = "useStamina";			//�g�p�X�^�~�i�B
		const char* toolTypeTag = "tool";				//�c�[���^�C�v�B
	}
	
	//�ݒu���f�[�^�Ɋւ��閼�O��ԁB
	namespace nsTerrainData {

		const char* durable = "durable";				//�ϋv�l�B
		const char* tool = "tool";						//���U�c�[���B
		const char* texture = "texture";				//�n�`�̃e�N�X�`���B
		const char* collectItems = "collectItems";		//�ݒu������̎�ł���A�C�e���f�[�^���X�g�B
		namespace Collect {
			const char* collectItemDataNum = "collectItemDataNum";		//�̎敨�f�[�^�̐��B
			const char* corectItemID = "corectItemID";	//�̎�ł���A�C�e����ID�B
			const char* corectionNum = "corectionNum";	//�̎�ł���ʁB
		}
	}
	//�ݒu���f�[�^�Ɋւ��閼�O��ԁB
	namespace nsPlaceObjsData {

		//�ݒu���̃^�C�v�B
		enum EnPlaceTypes
		{
			enType_Terrain,
			enType_Block,
			enType_Object,
			enPlaceTypeNum
		};
		const char* durable = "durable";				//�ϋv�l�B
		const char* tool = "tool";						//���U�c�[���B
		const char* Type = "Type";						//�ݒu���̃^�C�v�B
		const char* collectItems = "collectItems";		//�ݒu������̎�ł���A�C�e���f�[�^���X�g�B
		namespace Collect {
			const char* collectItemDataNum = "collectItemDataNum";		//�̎敨�f�[�^�̐��B
			const char* corectItemID = "corectItemID";	//�̎�ł���A�C�e����ID�B
			const char* corectionNum = "corectionNum";	//�̎�ł���ʁB
		}
	}
	
	//�H�����̃f�[�^�Ɋւ��閼�O��ԁB
	namespace nsFoodsData {
		const char* hp = "HP";
		const char* water = "water";
		const char* food = "food";
		const char* stamina = "stamina";
	}

	//�f�ރA�C�e���Ɋւ��閼�O��ԁB
	namespace nsMaterialsData
	{
		const char* MaterialType = "MaterialType";		//�f�ރ^�C�v�H
	}
}

ItemDataFile::ItemDataFile()
{
	//�V���O���g���B
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
			"Item�f�[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B\n"
			"%s", filePath
		);
		return;
	}

	//json�t�@�C���ɓǂݍ���ł����B
	json jItem;
	ifs >> jItem;
	ifs.close();			//�t�@�C���͕��Ă����B

	//�c�[���̎�ނ��Ƃɓǂݍ��ށB
	for (auto _item : jItem)
	{
		//�A�C�e���̊�{�f�[�^�̓ǂݍ��݁B
		SItemDataPtr itemData = std::make_unique<SItemData>();
		itemData->itemID = _item[nsItemsData::itemID];
		itemData->itemTypeID = _item[nsItemsData::itemTypeID];
		itemData->itemType = _item[nsItemsData::itemType];
		itemData->itemName = _item[nsItemsData::itemName];
		itemData->tkmPath = _item[nsItemsData::itemTkm];
		itemData->iconPath = _item[nsItemsData::itemIcon];

		//�N���t�g�f�ރf�[�^���X�g���\�z�B
		int craftMaterialNum = _item[nsItemsData::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[nsItemsData::itemMaterials][i][nsItemsData::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[nsItemsData::itemMaterials][i][nsItemsData::CraftMaterials::materialNum];
		}
		//�N���t�g�\��f�[�^���X�g���\�z�B
		int craftableNum = _item[nsItemsData::itemCraftables][nsItemsData::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[nsItemsData::itemCraftables][nsItemsData::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//�A�C�e���̃^�C�v�ʂɃf�[�^���\�z�B
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
			//�ݒu���̑ϋv�l�Ɠ��U�c�[���B
			ObjectParams params;
			params.Durable = _item[nsPlaceObjsData::durable];
			params.AptitudeTool = _item[nsPlaceObjsData::tool];

			int placeType = _item[nsPlaceObjsData::Type];
			//�ݒu������̎�ł���A�C�e���̃f�[�^�B
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
			//�ݒu���̑ϋv�l�Ɠ��U�c�[���B
			ObjectParams params;
			params.Durable = _item[nsTerrainData::durable];
			params.AptitudeTool = _item[nsTerrainData::tool];
			std::string texture = _item[nsTerrainData::texture];

			//�ݒu������̎�ł���A�C�e���̃f�[�^�B
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
			//�H�����̃p�����[�^�B
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
			//�f�ރ^�C�v�H
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
