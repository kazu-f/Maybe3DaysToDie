#pragma once
#include "Inventory/Inventory.h"

class Chest
{
public:
	Chest() {}
	~Chest() {}

private:
	InventoryItemData m_itemData[Inventory_X][Inventory_Y];
};

