#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemTerrain : public GameItemBase
{
public:
	GameItemTerrain(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& collectData, std::string& texture);
	~GameItemTerrain() {}

private:
	ObjectParams m_terrainParams;
	ObjectCollectItemData m_terrainCollectData;
	std::string m_textureFilePath;
};

