#pragma once

#include "Item/GameItemBase.h"

struct InventoryItemData {
	GameItemBase* m_itemBase = nullptr;
	int itemCount = 0;
	int Id = 0;
	Vector2 inventoryPos = Vector2::Zero;
	prefab::CSpriteRender* m_IconRender = nullptr;
};
class Player;
class Inventory :public IGameObject
{
public:
	void SetPlayer(Player* pp) {
		m_player = pp;
	} 
	/// <summary>
	/// アイテムをスロットのどこにセットする？
	/// </summary>
	/// <param name="Item">アイテム</param>
	/// <param name="x">ｘ座標</param>
	/// <param name="y">ｙ座標</param>
	void SetItemSlot(GameItemBase* Item, const int x, const int y);
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;
	/// <summary>
	/// インベントリの状態に遷移するかの判定をする
	/// </summary>
	void SwhichInventoryState();
	/// <summary>
	/// Tabのトリガー判定を取る
	/// </summary>
	void TriggerTab();

	prefab::CSpriteRender* m_Inbentory = nullptr;
	bool m_IsShow = false;
	bool m_IsTriggerTab = false;
	Player* m_player = nullptr;
	InventoryItemData m_ItemSlot[Inventory_X][Inventory_Y];
	InventoryItemData m_PickUpItem;
	RECT m_MainRt;				//ウィンドウ画面
	RECT m_DeskRt;				//デスクトップ画面
};