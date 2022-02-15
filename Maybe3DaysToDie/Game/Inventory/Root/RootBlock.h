#pragma once
#include "Item/GameItemBase.h"
#include "RootTable.h"
#include "Inventory/Inventory.h"
#include "Item/GameItemPlaceObj.h"

struct Item {
	GameItemBase* item = nullptr;
	int stack = 0;
};

class RootBlock
{
public:
	RootBlock();
	~RootBlock();

	/// <summary>
	/// ÉãÅ[ÉgÇ∑ÇÈ
	/// </summary>
	std::vector<Item>& Root(int id);

private:
	void OnDestroy();
	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Init();

	const RootInsideItemDataList& GetTable(int i);

private:
	std::vector<Item> m_item;
};