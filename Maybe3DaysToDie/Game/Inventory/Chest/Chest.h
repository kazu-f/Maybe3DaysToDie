#pragma once
#include "Inventory/Inventory.h"

class Chest
{
public:
	Chest() {}
	~Chest() {}

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// アイテムをスロットのどこにセットする？
	/// </summary>
	/// <param name="Item">アイテム</param>
	/// <param name="x">ｘ座標</param>
	/// <param name="y">ｙ座標</param>
	void SetItem(GameItemBase* Item, const int x, const int y);
private:
	InventoryItemData m_itemData[Inventory_X][Inventory_Y];
};