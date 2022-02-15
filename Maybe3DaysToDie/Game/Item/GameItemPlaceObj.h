#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemPlaceObj : public GameItemBase
{
public:
	GameItemPlaceObj(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, AccessTag type);
	~GameItemPlaceObj() {}

private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	std::string m_objName;
	AccessTag m_placeType = AccessTag::NonAccess;

};

