#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"
#include <windowsx.h>
#include "Item/ItemDataFile.h"
#include "Item/GameItemFoods.h"
#include "Item/BlockItem.h"

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
				((i *  93.0f ) - 287.0f),
				((j * -86.0f ) + 152.0f)
			};

			m_ItemSlot[i][j].inventoryPos = SlotPos;
			ItemDataFile* it = ItemDataFile::GetInstance();
			int SlotNum = i + j;
			auto& BlockDataOne = m_ItemSlot[i][j].m_itemBase;
			BlockDataOne = it->GetBlockData(10);
			m_ItemSlot[i][j].m_IconRender = NewGO<prefab::CSpriteRender>(InventoryPrio+1);
			m_ItemSlot[i][j].m_IconRender->Init(
				it->GetItemDataBase(10)->GetItemData()->iconPath.c_str(),
				ItemOneBoxSize, ItemOneBoxSize
			);
			m_ItemSlot[i][j].m_IconRender->SetPosition(m_ItemSlot[i][j].inventoryPos);
			m_ItemSlot[i][j].m_IconRender->SetActiveFlag(false);
			/*
		}
		else {
			auto& EatDataTwo = m_ItemSlot[i][j];
			EatDataTwo.m_itemBase = it->GetFoodData(13);
			EatDataTwo.m_itemBase->SetItemIconEnable(true);
			EatDataTwo.m_itemBase->SetIconPosition(SlotPos);
		}*/
		}
	}

	return true;
}

void Inventory::Update()
{
	//Tab�������Ă�����
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		//�C���x���g�����J����
		SwhichInventoryState();
	}
	Vector2 MausePos = MauseInfo::GetInstance()->GetMausePos();
	MauseInfo::State MauseState = MauseInfo::GetInstance()->GetMauseState();
	// ���낢��ƌv�Z
	GetWindowRect(g_hWnd, &m_MainRt);
	float sx = (m_MainRt.right - m_MainRt.left); // �E�C���h�E�̉���
	float sy = (m_MainRt.bottom - m_MainRt.top); // �E�C���h�E�̍���
	float SpriteSizeX = ((sx) / FRAME_BUFFER_W);
	float SpriteSizeY = ((sy) / FRAME_BUFFER_H);
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);     // �^�C�g���o�[�̍���
	float diffX = fabsf(MausePos.x - (( m_ItemSlot[0][0].inventoryPos.x + sx / 2 ) * SpriteSizeX + m_MainRt.left));
	float diffY = fabsf(MausePos.y - -(( m_ItemSlot[0][0].inventoryPos.y - sy / 2) * SpriteSizeY + m_MainRt.top + cyCaption));
	if (MauseState ==
		MauseInfo::State::MauseLClick) {
		if (diffX < 43.0f &&
			diffY < 43.0f) {
			int a;
			a = 0;
			//m_PickUpItem.m_itemBase = m_ItemSlot[0][0].m_itemBase;
		}
	}
	//if (m_PickUpItem.m_itemBase != nullptr) {
	//	m_PickUpItem.inventoryPos = MausePos;
	//	if (MauseState != MauseInfo::State::MauseLClick) {
	//		if (diffX < 116.0f &&
	//			diffY < 109.0f) {
	//			m_ItemSlot[0][0] = m_PickUpItem;
	//		}
	//	}
	//}

	//�^�u�����������Ă��Ȃ����H
	TriggerTab();
}

void Inventory::OnDestroy()
{
	//��ʂ��폜
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

void Inventory::SetItemSlot(GameItemBase* GameItem, const int x, const int y) {
	m_ItemSlot[x][y].m_itemBase = GameItem;
}
