#pragma once
#include "Item/GameItemBase.h"
#include "RootTable.h"

class RootBlock
{
public:
	RootBlock();
	~RootBlock();

	/// <summary>
	/// ���[�g����
	/// </summary>
	void Root();

	/// <summary>
	/// �A�C�e�����C���x���g������擾
	/// </summary>
	/// <param name="x">�C���x���g����X</param>
	/// <param name="y">�C���x���g����Y</param>
	/// <returns>�A�C�e��</returns>
	GameItemBase* GetItem(int x, int y)
	{
		return m_item[x][y];
	}

private:
	void OnDestroy();
	/// <summary>
	/// ������
	/// </summary>
	void Init();

private:
	GameItemBase* m_item[Inventory_X][Inventory_Y] = { nullptr };
	RootTable m_rootTable;
};