#pragma once
#include "GameItemBase.h"

struct SPlaceObjCollectData
{
	int collectID = -1;		//採取アイテムのID。
	int collectNum = 1;		//採取できる量。
};

using PlaceObjectCollectItemData = std::vector<SPlaceObjCollectData>;

class BlockItem :public GameItemBase
{
public:
	BlockItem(SItemDataPtr& itemData,const ObjectParams& params, PlaceObjectCollectItemData& placeCollectData,int type);
	~BlockItem() {}

private:
	ObjectParams m_placeParams;
	PlaceObjectCollectItemData m_placeCollectData;
	int m_placeType = -1;
};