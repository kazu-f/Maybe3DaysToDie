#include "stdafx.h"
#include "BlockItem.h"
#include "ItemBar/ItemBar.h"
#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"

BlockItem::BlockItem(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData)
	:GameItemBase(itemData)
{
	//ブロックの名前を作成する。
	auto& tkmPath = GetItemData()->tkmPath;
	int indexSlash = tkmPath.find_last_of("/\\");
	int indexTkm = tkmPath.rfind(".tkm");
	int pathSize = tkmPath.size();
	m_blockName = tkmPath.substr(static_cast<size_t>(indexSlash + 1), static_cast<size_t>((pathSize - indexSlash) - (pathSize - indexTkm) - 1));

	m_blockParams = params;
	m_blockParams.BlockName = m_blockName.c_str();
	m_placeCollectData = std::move(placeCollectData);
	m_blockHash = Util::MakeHash(m_blockName.c_str());
}

void BlockItem::SelectItemAction(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->SetParams(m_blockParams);
}

void BlockItem::UseItemAction1(ItemBar* itemBar)
{
}

void BlockItem::UseItemAction2(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->PlaceObject();
}
