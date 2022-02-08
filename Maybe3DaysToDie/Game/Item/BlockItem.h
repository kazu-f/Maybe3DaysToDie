#pragma once
#include "GameItemBase.h"

struct SPlaceObjCollectData
{
	int collectID = -1;		//�̎�A�C�e����ID�B
	int collectNum = 1;		//�̎�ł���ʁB
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