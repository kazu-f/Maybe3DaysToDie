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
	void SelectItemAction(ItemBar* itemBar);	//このアイテムが選択されたときの処理。
	void UseItemAction1(ItemBar* itemBar);		//左クリックのアクション。
	void UseItemAction2(ItemBar* itemBar);	//右クリックのアクション。

private:
	ObjectParams m_blockParams;
	ObjectCollectItemData m_placeCollectData;
	std::string m_blockName;
	int m_blockHash = 0;
};