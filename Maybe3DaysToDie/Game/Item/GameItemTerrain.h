#pragma once
#include "GameItemBase.h"
#include "CollectData.h"

class GameItemTerrain : public GameItemBase
{
public:
	GameItemTerrain(SItemDataPtr& itemData, const ObjectParams& params, ObjectCollectItemData& collectData, std::string& texture);
	~GameItemTerrain() {}
private:
	void SelectItemAction(ItemBar* itemBar);	//このアイテムが選択されたときの処理。
	void UseItemAction1(ItemBar* itemBar);		//左クリックのアクション。
	void UseItemAction2(ItemBar* itemBar);	//右クリックのアクション。

	const ObjectCollectItemData& GetCollectItemData()
	{
		return m_terrainCollectData;
	}
private:
	ObjectParams m_terrainParams;
	ObjectCollectItemData m_terrainCollectData;
	std::string m_textureFilePath;
};

