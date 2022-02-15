#pragma once
#include "Item/GameItemBase.h"
#include "RootTable.h"

class RootBlock
{
public:
	RootBlock();
	~RootBlock();

	/// <summary>
	/// ルートする
	/// </summary>
	void Root();

	/// <summary>
	/// アイテムをインベントリから取得
	/// </summary>
	/// <param name="x">インベントリのX</param>
	/// <param name="y">インベントリのY</param>
	/// <returns>アイテム</returns>
	GameItemBase* GetItem(int x, int y)
	{
		return m_item[x][y];
	}

private:
	void OnDestroy();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

private:
	GameItemBase* m_item[Inventory_X][Inventory_Y] = { nullptr };
	RootTable m_rootTable;
};