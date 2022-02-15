#pragma once

#include "Item/GameItemBase.h"

struct InventoryItemData {
	GameItemBase* m_itemBase = nullptr;
	int itemCount = 0;
	Vector2 inventoryPos = Vector2::Zero;
};
class Player;
class Inventory :public IGameObject
{
public:
	void SetPlayer(Player* pp) {
		m_player = pp;
	} 
	/// <summary>
	/// �A�C�e�����X���b�g�̂ǂ��ɃZ�b�g����H
	/// </summary>
	/// <param name="Item">�A�C�e��</param>
	/// <param name="x">�����W</param>
	/// <param name="y">�����W</param>
	void SetItemSlot(GameItemBase* Item,const int x, const int y) {
		m_ItemSlot[x][y]->m_itemBase = Item;
	}
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;
	/// <summary>
	/// �C���x���g���̏�ԂɑJ�ڂ��邩�̔��������
	/// </summary>
	void SwhichInventoryState();
	/// <summary>
	/// Tab�̃g���K�[��������
	/// </summary>
	void TriggerTab();
	prefab::CSpriteRender* m_Inbentory = nullptr;
	bool m_IsShow = false;
	bool m_IsTriggerTab = false;
	Player* m_player = nullptr;
	const Vector2 SlotMax = { 7,6 };
	InventoryItemData* m_ItemSlot[7][6] = { nullptr };
	InventoryItemData* m_PickUpItem = nullptr;
	RECT m_MainRt;				//�E�B���h�E���
	RECT m_DeskRt;				//�f�X�N�g�b�v���
};