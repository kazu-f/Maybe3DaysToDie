#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemTerrain : public GameItemBase
{
public:
	GameItemTerrain(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& collectData, std::string& texture);
	~GameItemTerrain() {}
private:
	void SelectItemAction(ItemBar* itemBar);	//���̃A�C�e�����I�����ꂽ�Ƃ��̏����B
	void UseItemAction1(ItemBar* itemBar);		//���N���b�N�̃A�N�V�����B
	void UseItemAction2(ItemBar* itemBar);	//�E�N���b�N�̃A�N�V�����B

	const ObjectCollectItemData& GetCollectItemData()
	{
		return m_terrainCollectData;
	}
private:
	ObjectParams m_terrainParams;
	ObjectCollectItemData m_terrainCollectData;
	std::string m_textureFilePath;
};

