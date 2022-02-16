#pragma once
#include "Inventory/Inventory.h"
#include "Inventory/Root/RootBlock.h"

class Chest
{
public:
	Chest() {}
	~Chest() {}

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Root(int ObjectID);

private:
	void AddItem(InventoryItemData& data);
private:
	InventoryItemData m_itemData[Inventory_X][Inventory_Y];
	RootBlock m_Root;
};