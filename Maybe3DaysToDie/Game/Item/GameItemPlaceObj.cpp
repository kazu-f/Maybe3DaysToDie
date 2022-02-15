#include "stdafx.h"
#include "GameItemPlaceObj.h"

GameItemPlaceObj::GameItemPlaceObj(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, AccessTag type)
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
	m_placeType = type;
}
