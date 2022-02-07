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

	//�A�C�e���̊�{�f�[�^�Ɋւ��閼�O��ԁB
	namespace Items {
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
	namespace Tools {
		const char* damage = "damage";					//�_���[�W�B
		const char* durable = "durable";				//�ϋv�l�B
		const char* useStamina = "useStamina";			//�g�p�X�^�~�i�B
		const char* toolTypeTag = "tool";				//�c�[���^�C�v�B
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
		itemData->itemID = _item[Items::itemID];
		itemData->itemType = _item[Items::itemType];
		itemData->itemName = _item[Items::itemName];
		itemData->tkmPath = _item[Items::itemTkm];
		itemData->iconPath = _item[Items::itemIcon];

		//�N���t�g�f�ރf�[�^���X�g���\�z�B
		int craftMaterialNum = _item[Items::CraftMaterials::itemMaterialDataNum];
		itemData->craftMaterialDatas.resize(craftMaterialNum);
		for (int i = 0; i < craftMaterialNum; i++)
		{
			itemData->craftMaterialDatas[i].itemID = _item[Items::itemMaterials][i][Items::CraftMaterials::materialID];
			itemData->craftMaterialDatas[i].itemNum = _item[Items::itemMaterials][i][Items::CraftMaterials::materialNum];
		}
		//�N���t�g�\��f�[�^���X�g���\�z�B
		int craftableNum = _item[Items::itemCraftables][Items::Craftable::craftableNum];
		itemData->craftableItemIDs.resize(craftableNum);
		int No = 0;
		for (auto id : _item[Items::itemCraftables][Items::Craftable::craftableIDs])
		{
			itemData->craftableItemIDs[No] = id;
			No++;
		}

		//�A�C�e���̃^�C�v�ʂɃf�[�^���\�z�B
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
