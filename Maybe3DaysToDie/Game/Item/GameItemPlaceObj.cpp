#include "stdafx.h"
#include "GameItemPlaceObj.h"
#include "ItemBar/ItemBar.h"
#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"

GameItemPlaceObj::GameItemPlaceObj(
	SItemDataPtr& itemData, 
	const ObjectParams& params, 
	ObjectCollectItemData& placeCollectData,
	RootInsideItemDataList& insideDataList,
	AccessTag type
)
	:GameItemBase(itemData)
{
	//ブロックの名前を作成する。
	auto& tkmPath = GetItemData()->tkmPath;
	int indexSlash = tkmPath.find_last_of("/\\");
	int indexTkm = tkmPath.rfind(".tkm");
	int pathSize = tkmPath.size();
	m_objName = tkmPath.substr(static_cast<int>(indexSlash + 1), static_cast<int>((pathSize - indexSlash) - (pathSize - indexTkm) - 1));

	m_placeParams = params;
	m_placeCollectData = std::move(placeCollectData);
	m_rootItemDataList = std::move(insideDataList);
	m_placeType = type;
	m_objHash = Util::MakeHash(m_objName.c_str());
}

void GameItemPlaceObj::SelectItemAction(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->SetParams(m_placeParams);
}

void GameItemPlaceObj::UseItemAction1(ItemBar* itemBar)
{
}

void GameItemPlaceObj::UseItemAction2(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->PlaceObject();
}
