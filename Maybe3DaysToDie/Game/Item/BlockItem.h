#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class BlockItem :public GameItemBase
{
public:
	BlockItem(SItemDataPtr& itemData,const ObjectParams& params, ObjectCollectItemData& placeCollectData);
	~BlockItem() {}
	int GetBlockHash()
	{
		return m_blockHash;
	}

	const ObjectParams& GetObjParams()
	{
		return m_blockParams;
	}
private:
	void SelectItemAction(ItemBar* itemBar);	//���̃A�C�e�����I�����ꂽ�Ƃ��̏����B
	void UseItemAction1(ItemBar* itemBar);		//���N���b�N�̃A�N�V�����B
	void UseItemAction2(ItemBar* itemBar);	//�E�N���b�N�̃A�N�V�����B

private:
	ObjectParams m_blockParams;
	ObjectCollectItemData m_placeCollectData;
	std::string m_blockName;
	int m_blockHash = 0;
};