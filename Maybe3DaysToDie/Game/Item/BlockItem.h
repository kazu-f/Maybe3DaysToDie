#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class BlockItem :public GameItemBase
{
public:
	BlockItem(SItemDataPtr& itemData,const ObjectParams& params, ObjectCollectItemData& placeCollectData,int type);
	~BlockItem() {}

private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	int m_placeType = -1;
};