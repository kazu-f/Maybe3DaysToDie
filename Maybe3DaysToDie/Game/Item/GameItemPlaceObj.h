#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

struct SRootInsideItemData {
	int insideID = -1;
	int insideProbility = 0;
	int maxNum = 0;
	int minNum = 0;
};

using RootInsideItemDataList = std::vector<SRootInsideItemData>;

class GameItemPlaceObj : public GameItemBase
{
public:
	GameItemPlaceObj(
		SItemDataPtr& itemData,
		const ObjectParams& params,
		ObjectCollectItemData& placeCollectData,
		RootInsideItemDataList& insideDataList,
		AccessTag type);
	~GameItemPlaceObj() {}

	int GetBlockHash()
	{
		return m_objHash;
	}
	const ObjectParams& GetObjParams()
	{
		return m_placeParams;
	}

	const AccessTag& GetAccessTag()
	{
		return m_placeType;
	}

	const ObjectCollectItemData& GetCollectItemData()
	{
		return m_placeCollectData;
	}
private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	RootInsideItemDataList m_rootItemDataList;
	std::string m_objName;
	AccessTag m_placeType = AccessTag::NonAccess;
	int m_objHash = 0;
};

