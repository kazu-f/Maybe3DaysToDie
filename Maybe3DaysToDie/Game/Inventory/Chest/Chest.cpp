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
		data.Id = item.itemID;
		AddItem(data);
	}
}

void Chest::AddItem(InventoryItemData& data)
{
	for (int x = 0; x < Inventory_X; x++)
	{
		for (int y = 0; y < Inventory_Y; y++)
		{
			auto& m_data = m_itemData[x][y];
			if (m_data.m_itemBase == nullptr)
			{
				//まだアイテムがないのでセット
				m_itemData[x][y] = data;
				return;
			}
			else if(m_data.Id == data.Id)
			{
				//アイテム被りなのでスタック
				m_data.itemCount += data.itemCount;
				return;
			}
		}
	}
}