#include "stdafx.h"
#include "BlockItem.h"

BlockItem::BlockItem(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData)
	:GameItemBase(itemData)
{
	//ブロックの名前を作成する。
	auto& tkmPath = GetItemData()->tkmPath;
	int indexSlash = tkmPath.find_last_of("/\\");
	int indexTkm = tkmPath.rfind(".tkm");
	int pathSize = tkmPath.size();
	m_blockName = tkmPath.substr(static_cast<int>(indexSlash + 1), static_cast<int>((pathSize - indexSlash) - (pathSize - indexTkm) - 1));

	m_placeParams = params;
	m_placeParams.BlockName = m_blockName.c_str();
	m_placeCollectData = std::move(placeCollectData);
}
