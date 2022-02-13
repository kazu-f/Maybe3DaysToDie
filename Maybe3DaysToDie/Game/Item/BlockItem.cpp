#include "stdafx.h"
#include "BlockItem.h"

BlockItem::BlockItem(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, int type)
	:GameItemBase(itemData)
{
	m_placeParams = params;
	m_placeCollectData = std::move(placeCollectData);
	m_placeType = type;
}
