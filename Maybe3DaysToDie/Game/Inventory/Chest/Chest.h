#pragma once
#include "Inventory/Inventory.h"

class Chest
{
public:
	Chest() {}
	~Chest() {}

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �A�C�e�����X���b�g�̂ǂ��ɃZ�b�g����H
	/// </summary>
	/// <param name="Item">�A�C�e��</param>
	/// <param name="x">�����W</param>
	/// <param name="y">�����W</param>
	void SetItem(GameItemBase* Item, const int x, const int y);
private:
	InventoryItemData m_itemData[Inventory_X][Inventory_Y];
};