#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemPlaceObj : public GameItemBase
{
public:
	GameItemPlaceObj(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& placeCollectData, AccessTag type);
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
private:
	ObjectParams m_placeParams;
	ObjectCollectItemData m_placeCollectData;
	std::string m_objName;
	AccessTag m_placeType = AccessTag::NonAccess;
	int m_objHash = 0;
};

