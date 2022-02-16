#include "stdafx.h"
#include "Chest.h"

void Chest::Root(int ObjectID)
{
	auto& item_vector = m_Root.Root(ObjectID);
	for (auto& item : item_vector)
	{
		InventoryItemData data;
		data.m_itemBase = item.item;
		data.itemCount = item.stack;
		AddItem(data);
	}
}

void Chest::AddItem(InventoryItemData& data)
{
	for (int x = 0; x < Inventory_X; x++)
	{
		for (int y = 0; y < Inventory_Y; y++)
		{
			if (m_itemData[x][y].m_itemBase == nullptr)
			{
				m_itemData[x][y] = data;
				return;
			}
		}
	}
}