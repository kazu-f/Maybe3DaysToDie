#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class BlockItem :public GameItemBase
{
public:
	BlockItem(SItemDataPtr& itemData,const ObjectParams& params, ObjectCollectItemData& placeCollectData);
	~BlockItem() {}

private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	std::string m_blockName;
};