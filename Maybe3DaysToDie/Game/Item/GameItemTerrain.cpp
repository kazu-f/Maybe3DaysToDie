#include "stdafx.h"
#include "GameItemTerrain.h"
#include "ItemBar/ItemBar.h"
#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"

GameItemTerrain::GameItemTerrain(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& collectData, std::string& texture)
	:GameItemBase(itemData)
{
	m_terrainParams = params;
	m_terrainCollectData = collectData;
	m_textureFilePath = texture;
}

void GameItemTerrain::SelectItemAction(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->SetParams(m_terrainParams);
}

void GameItemTerrain::UseItemAction1(ItemBar* itemBar)
{
}

void GameItemTerrain::UseItemAction2(ItemBar* itemBar)
{
	auto* placeObj = itemBar->GetPlacementObject();
	placeObj->PlaceObject();
}
