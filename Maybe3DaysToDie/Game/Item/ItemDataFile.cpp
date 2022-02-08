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

	//�A�C�e���̊�{�f�[�^�Ɋւ��閼�O��ԁB
	namespace nsItems {
		const char* itemType = "itemType";		//�A�C�e���̎�ނ𕪂��邽�߂̕ϐ��B
		const char* itemID = "itemID";			//�A�C�e����ID�B
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
	namespace nsTools {
		const char* damage = "damage";					//�_���[�W�B
		const char* durable = "durable";				//�ϋv�l�B
		const char* useStamina = "useStamina";			//�g�p�X�^�~�i�B
		const char* toolTypeTag = "tool";				//�c�[���^�C�v�B
	}
	
	//�ݒu���f�[�^�Ɋւ��閼�O��ԁB
	namespace nsPlaceObjs {

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
	namespace nsFoods {
		const char* hp = "HP";
		const char* water = "water";
		const char* food = "food";
		const char* stamina = "stamina";
	}

	//�f�ރA�C�e���Ɋւ��閼�O��ԁB
	namespace nsMaterials
	{
		const char* MaterialType = "MaterialType";		//�f�ރ^�C�v�H
	}
}

ItemDataFile::ItemDataFile()
{
	//�V���O���g���B
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
		itemData->itemID = _item[nsItems::itemID];
		itemData->itemType = _item[nsItems::itemType];
		itemData->itemName = _item[nsItems::itemName];
		itemData->tkmPath = _item[nsItems::itemTkm];
		itemData->iconPath = _item[nsItems::itemIcon];

		//�N���t�g�f�ރf�[�^���X�g���\�z�B
		int craftMaterialNum = _item[nsItems::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[nsItems::itemMaterials][i][nsItems::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[nsItems::itemMaterials][i][nsItems::CraftMaterials::materialNum];
		}
		//�N���t�g�\��f�[�^���X�g���\�z�B
		int craftableNum = _item[nsItems::itemCraftables][nsItems::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[nsItems::itemCraftables][nsItems::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//�A�C�e���̃^�C�v�ʂɃf�[�^���\�z�B
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
			//�ݒu���̑ϋv�l�Ɠ��U�c�[���B
			ObjectParams params;
			params.Durable = _item[nsPlaceObjs::durable];
			params.AptitudeTool = _item[nsPlaceObjs::tool];

			int placeType = _item[nsPlaceObjs::Type];
			//�ݒu������̎�ł���A�C�e���̃f�[�^�B
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
			//�H�����̃p�����[�^�B
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
			//�f�ރ^�C�v�H
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
