#pragma once
#include "Item/GameItemBase.h"
#include "Inventory/Inventory.h"
#include "Item/GameItemPlaceObj.h"
#include "DestroyObject/DestroyObject.h"

class RootBlock
{
public:
	RootBlock();
	~RootBlock();

	/// <summary>
	/// ルートする
	/// </summary>
	std::vector<Item>& Root(int id);

private:
	void OnDestroy();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	const RootInsideItemDataList& GetTable(int i);

private:
	std::vector<Item> m_item;
};