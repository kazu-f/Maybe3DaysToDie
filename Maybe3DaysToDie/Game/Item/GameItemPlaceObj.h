#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemPlaceObj : public GameItemBase
{
public:
	GameItemPlaceObj(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, int type);
	~GameItemPlaceObj() {}

private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	int m_placeType = -1;

};

