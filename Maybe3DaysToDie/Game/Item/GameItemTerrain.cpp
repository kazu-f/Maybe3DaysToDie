#include "stdafx.h"
#include "GameItemTerrain.h"

GameItemTerrain::GameItemTerrain(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& collectData, std::string& texture)
	:GameItemBase(itemData)
{
	m_terrainParams = params;
	m_terrainCollectData = collectData;
	m_textureFilePath = texture;
}

void GameItemTerrain::SelectItemAction(ItemBar* itemBar)
{
}

void GameItemTerrain::UseItemAction1(ItemBar* itemBar)
{
}
