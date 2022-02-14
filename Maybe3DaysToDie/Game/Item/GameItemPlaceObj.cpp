#include "stdafx.h"
#include "GameItemPlaceObj.h"

GameItemPlaceObj::GameItemPlaceObj(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, int type)
	:GameItemBase(itemData)
{
	m_placeParams = params;
	m_placeCollectData = std::move(placeCollectData);
	m_placeType = type;
}
