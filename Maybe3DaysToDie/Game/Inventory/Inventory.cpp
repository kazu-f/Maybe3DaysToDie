#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"
#include <windowsx.h>
#include "Item/ItemDataFile.h"
#include "Item/GameItemFoods.h"
#include "Item/BlockItem.h"
#include "Item/GameItemBase.h"

namespace {
	const float ItemOneBoxSize = 75.0f;
	const int InventoryPrio = 2;
}

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(InventoryPrio);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_H, FRAME_BUFFER_H);
	m_Inbentory->SetActiveFlag(false);


	for (int i = 0; i < Inventory_X; i++) {
		for (int j = 0; j < Inventory_Y; j++) {
			Vector2 SlotPos = {
				((i * 93.0f) - 287.0f),
				((j * -86.0f) + 152.0f)
			};
			m_ItemSlot[i][j].inventoryPos = SlotPos;
			if (m_ItemSlot[i][j].m_itemBase != nullptr) {
				continue;
			}
			ItemDataFile* it = ItemDataFile::GetInstance();
			if ((i * j % 2) == 1) {
				auto& BlockDataOne = m_ItemSlot[i][j].m_itemBase;
				BlockDataOne = it->GetBlockData(10);
				m_ItemSlot[i][j].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 1);
				m_ItemSlot[i][j].m_IconRender->Init(
					it->GetItemDataBase(10)->GetItemData()->iconPath.c_str(),
					ItemOneBoxSize, ItemOneBoxSize
				);
				m_ItemSlot[i][j].Id = 10;
				m_ItemSlot[i][j].m_IconRender->SetPosition(m_ItemSlot[i][j].inventoryPos);
				m_ItemSlot[i][j].m_IconRender->SetActiveFlag(false);
			}
			else {
				auto& EatDataTwo = m_ItemSlot[i][j];
				EatDataTwo.m_itemBase = it->GetFoodData(13);
				EatDataTwo.m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 1);
				EatDataTwo.m_IconRender->Init(
					it->GetItemDataBase(13)->GetItemData()->iconPath.c_str(),
					ItemOneBoxSize, ItemOneBoxSize
				);
				EatDataTwo.Id = 13;
				EatDataTwo.m_IconRender->SetPosition(m_ItemSlot[i][j].inventoryPos);
				EatDataTwo.m_IconRender->SetActiveFlag(false);
			}
		}
	}
	return true;
}

void Inventory::Update()
{
	//Tabを押していたら
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		//インベントリを開閉する
		SwhichInventoryState();
	}
	//タブを押し続けていないか？
	TriggerTab();
	if (!m_IsShow) {
		return;
	}
	Vector2 MausePos = MauseInfo::GetInstance()->GetMausePos();
	MauseInfo::State MauseState = MauseInfo::GetInstance()->GetMauseState();
	// いろいろと計算
	GetWindowRect(g_hWnd, &m_MainRt);
	float sx = (m_MainRt.right - m_MainRt.left); // ウインドウの横幅
	float sy = (m_MainRt.bottom - m_MainRt.top); // ウインドウの高さ
	float SpriteSizeX = ((sx) / FRAME_BUFFER_W);
	float SpriteSizeY = ((sy) / FRAME_BUFFER_H);
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);     // タイトルバーの高さ
	float diffX = 1000.0f;
	float diffY = 1000.0f;
	if (MauseState ==
		MauseInfo::State::MauseLClick &&
		m_PickUpItem.m_itemBase == nullptr) {
		for (int i = 0; i < Inventory_X; i++) {
			for (int j = 0; j < Inventory_Y; j++)
			{
				diffX = fabsf(MausePos.x - ((m_ItemSlot[i][j].inventoryPos.x + sx / 2) * SpriteSizeX + m_MainRt.left));
				diffY = fabsf(MausePos.y - -((m_ItemSlot[i][j].inventoryPos.y - sy / 2) * SpriteSizeY + m_MainRt.top - cyCaption));

				if (diffX < 43.0f &&
					diffY < 43.0f) {
					if (m_ItemSlot[i][j].m_itemBase != nullptr) {
						m_PickUpItem.m_itemBase = m_ItemSlot[i][j].m_itemBase;
						m_PickUpItem.Id = m_ItemSlot[i][j].Id;
						m_ItemSlot[i][j].m_itemBase = nullptr;
						DeleteGO(m_ItemSlot[i][j].m_IconRender);
						m_PickSlot[0] = i;
						m_PickSlot[1] = j;
					}
				}
			}
		}
	}
	if (m_PickUpItem.m_itemBase != nullptr) {
		if (!m_InitialPick) {
			ItemDataFile* it = ItemDataFile::GetInstance();
			m_PickUpItem.m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 2);
			m_PickUpItem.m_IconRender->Init(
				it->GetItemDataBase(m_PickUpItem.Id)->GetItemData()->iconPath.c_str(),
				ItemOneBoxSize, ItemOneBoxSize);
			m_InitialPick = true;
		}
		Vector2 MauseOnItemPos = {
			(MausePos.x - sx / 2) * SpriteSizeX + m_MainRt.left,
			-(MausePos.y - sy / 2) * SpriteSizeY + m_MainRt.top + cyCaption
		};
		m_PickUpItem.m_IconRender->SetPosition(MauseOnItemPos);
		if (MauseState != MauseInfo::State::MauseLClick) {
			for (int i = 0; i < Inventory_X; i++) {
				for (int j = 0; j < Inventory_Y; j++)
				{
					diffX = fabsf(MausePos.x - ((m_ItemSlot[i][j].inventoryPos.x + sx / 2) * SpriteSizeX + m_MainRt.left));
					diffY = fabsf(MausePos.y - -((m_ItemSlot[i][j].inventoryPos.y - sy / 2) * SpriteSizeY + m_MainRt.top - cyCaption));

					if (diffX < 43.0f &&
						diffY < 43.0f) {
						if (m_ItemSlot[i][j].m_itemBase == nullptr) {
							m_ItemSlot[i][j].m_itemBase = m_PickUpItem.m_itemBase;
							ItemDataFile* it = ItemDataFile::GetInstance();
							m_ItemSlot[i][j].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 2);
							m_ItemSlot[i][j].m_IconRender->Init(
								it->GetItemDataBase(m_PickUpItem.Id)->GetItemData()->iconPath.c_str(),
								ItemOneBoxSize, ItemOneBoxSize);
							m_ItemSlot[i][j].Id = m_PickUpItem.Id;
							Vector2 SlotPos = {
								((i * 93.0f) - 287.0f),
								((j * -86.0f) + 152.0f)
							};
							m_ItemSlot[i][j].m_IconRender->SetPosition(SlotPos);
						}
						else {
							m_ItemSlot[m_PickSlot[0]][m_PickSlot[1]].m_itemBase = m_ItemSlot[i][j].m_itemBase;
							ItemDataFile* it = ItemDataFile::GetInstance();
							m_ItemSlot[m_PickSlot[0]][m_PickSlot[1]].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 2);
							m_ItemSlot[m_PickSlot[0]][m_PickSlot[1]].m_IconRender->Init(
								it->GetItemDataBase(m_ItemSlot[i][j].Id)->GetItemData()->iconPath.c_str(),
								ItemOneBoxSize, ItemOneBoxSize);
							m_ItemSlot[m_PickSlot[0]][m_PickSlot[1]].Id = m_ItemSlot[i][j].Id;
							Vector2 SlotPos = {
								((m_PickSlot[0] * 93.0f) - 287.0f),
								((m_PickSlot[1] * -86.0f) + 152.0f)
							};
							m_ItemSlot[m_PickSlot[0]][m_PickSlot[1]].m_IconRender->SetPosition(SlotPos);
							DeleteGO(m_ItemSlot[i][j].m_IconRender);
							m_ItemSlot[i][j].m_itemBase = nullptr;

							m_ItemSlot[i][j].m_itemBase = m_PickUpItem.m_itemBase;
							m_ItemSlot[i][j].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 2);
							m_ItemSlot[i][j].m_IconRender->Init(
								it->GetItemDataBase(m_PickUpItem.Id)->GetItemData()->iconPath.c_str(),
								ItemOneBoxSize, ItemOneBoxSize);
							m_ItemSlot[i][j].Id = m_PickUpItem.Id;
							SlotPos = {
								((i * 93.0f) - 287.0f),
								((j * -86.0f) + 152.0f)
							};
							m_ItemSlot[i][j].m_IconRender->SetPosition(SlotPos);
						}
						m_PickUpItem.m_itemBase = nullptr;
						DeleteGO(m_PickUpItem.m_IconRender);
						m_InitialPick = false;
					}
				}
			}
		}
	}
}

void Inventory::OnDestroy()
{
	//画面を削除
	DeleteGO(m_Inbentory);
}

void Inventory::SwhichInventoryState()
{
	if (!m_IsShow) {
		if (m_player->OpenInventory()) {
			m_Inbentory->SetActiveFlag(true);
			for (int i = 0; i < Inventory_X; i++) {
				for (int j = 0; j < Inventory_Y; j++) {
					m_ItemSlot[i][j].m_IconRender->SetActiveFlag(true);
				}
			}
			m_IsShow = true;
			while (true) {
				int returnNo = ShowCursor(true);
				if (returnNo >= 0) {
					break;
				}
			}
		}
	}
	else {
		m_player->CloseInventory();
		m_IsShow = false;
		while (true) {
			int returnNo = ShowCursor(false);
			m_Inbentory->SetActiveFlag(false);
			for (int i = 0; i < Inventory_X; i++) {
				for (int j = 0; j < Inventory_Y; j++) {
					m_ItemSlot[i][j].m_IconRender->SetActiveFlag(false);
				}
			}
			if (returnNo < 0) {
				break;
			}
		}
	}
}

void Inventory::TriggerTab()
{
	if (GetAsyncKeyState(VK_TAB)) {
		if (!m_IsTriggerTab)
			m_IsTriggerTab = true;
	}
	else {
		m_IsTriggerTab = false;
	}
}

void Inventory::SetItemSlot(InventoryItemData GameItem, const int x, const int y) {
	if (m_ItemSlot[x][y].m_itemBase != nullptr) {
		m_ItemSlot[x][y].m_itemBase = nullptr;
	}
	if (m_ItemSlot[x][y].m_IconRender != nullptr) {
		DeleteGO(m_ItemSlot[x][y].m_IconRender);
	}
	m_ItemSlot[x][y].m_itemBase = GameItem.m_itemBase;
	m_ItemSlot[x][y].Id = GameItem.Id;
	m_ItemSlot[x][y].itemCount = GameItem.itemCount;
	ItemDataFile* it = ItemDataFile::GetInstance();
	m_ItemSlot[x][y].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio + 1);
	m_ItemSlot[x][y].m_IconRender->Init(
			it->GetItemDataBase(m_ItemSlot[x][y].Id)->GetItemData()->iconPath.c_str(),
			ItemOneBoxSize, ItemOneBoxSize);
	Vector2 SlotPos = {
		( x *  93.0f ) - 287.0f,
		( y * -86.0f ) + 152.0f
	};
	m_ItemSlot[x][y].m_IconRender->SetActiveFlag(false);
	m_ItemSlot[x][y].m_IconRender->SetPosition(SlotPos);
}
