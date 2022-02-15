#include "stdafx.h"
#include "ItemBar.h"
#include <Windows.h>

#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"
#include "Tool/Tool.h"
#include "SaveDataFile.h"
#include "Save/TerrainSave/TerrainSave.h"
#include "Save/TerrainSave/TerrainLoad.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "Stage.h"
#include "Player/Player.h"
#include "Player/state/IPlayerState.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemBase.h"
#include "Item/GameItemTool.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"
#include "Item/GameItemFoods.h"
#include "Item/GameItemMaterial.h"
#include "Inventory/Inventory.h"
#include "DestroyObject/DestroyObject.h"

namespace {
	const Vector2 ItemBarPos = { -300.0f,-285.0f };
	const float ItemBarWidthSize = 600.0f;
}

bool ItemBar::Start()
{
	m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
	m_ItemIcon->Init("Assets/sprite/ItemUI/HotBar.dds", ItemBarWidthSize, ItemOneBoxSize);
	m_ItemIcon->SetPosition(ItemBarPos);
	m_ItemIcon->SetPivot({ 0.0f,0.5f });

	for (int i = 0; i < SelectNum; i++) {
		m_SelectPos[i] = { -300.0f + (75.0f * i) ,ItemBarPos.y };
	}

	m_SelectItemIcon = NewGO<prefab::CSpriteRender>(1);
	m_SelectItemIcon->Init("Assets/sprite/ItemUI/SelectBar.dds", ItemOneBoxSize, ItemOneBoxSize);
	m_SelectItemIcon->SetPosition(m_SelectPos[0]);
	m_SelectItemIcon->SetPivot({ 0.0f,0.5 });

	m_DestroyObject->SetTool(m_Tool);

	m_LoadingByChunk->SetTerrainManager(m_Stage->GetTerrainWorld());
	//セーブデータファイルをセット
	m_LoadingByChunk->SetSaveDataFile(m_SaveDataFile);
	m_PlacementObject->SetLoadingChunk(m_LoadingByChunk);
	m_PlacementObject->SetSaveData(m_SaveDataFile);
	m_DestroyObject->SetSaveData(m_SaveDataFile);
	SetItemDatas();
	return true;
}
void ItemBar::Update()
{
	if (m_Player->GetState() != Player::State::Menu) {
		if (GetAsyncKeyState(MK_LBUTTON)) {
			m_InstallTime += GameTime().GetFrameDeltaTime();
			if (m_InstallTime > 0.2f) {

				//m_PlacementObject->PlaceObject();
				m_InstallTime = 0.0f;

				m_itemInventory[m_SelectNum].m_itemBase->UseItemAction1(this);
			}
		}
		else {
			m_InstallTime = 0.2f;
		}

		if (GetAsyncKeyState(MK_RBUTTON)) {
			m_DeleteTime += GameTime().GetFrameDeltaTime();
			if (m_DeleteTime > 0.2f) {
				m_itemInventory[m_SelectNum].m_itemBase->UseItemAction2(this);

				//m_DestroyObject->AddObjectDamage();
				m_DeleteTime = 0.0f;
			}
		}
		else {
			m_DeleteTime = 0.2f;
		}

		auto MouseState = MauseInfo::GetInstance()->GetMauseState();
		if (MouseState == MauseInfo::State::MauseWheelUp) {
			m_SelectNum = m_SelectNum--;
			if (m_SelectNum < 0) {
				m_SelectNum = SelectNum - 1;
			}
		}

		if (MouseState == MauseInfo::State::MauseWheelDown)
		{
			m_SelectNum++;
			if (m_SelectNum > SelectNum - 1) {
				m_SelectNum = 0;
			}
		}
		ItemSlotKey('1', 0);
		ItemSlotKey('2', 1);
		ItemSlotKey('3', 2);
		ItemSlotKey('4', 3);
		ItemSlotKey('5', 4);
		ItemSlotKey('6', 5);
		ItemSlotKey('7', 6);
		ItemSlotKey('8', 7);
	}
	m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);
}

void ItemBar::OnDestroy()
{
	DeleteGO(m_ItemIcon);
	DeleteGO(m_SelectItemIcon);
}

void ItemBar::SetInventory(std::vector<Item>& item)
{
	for (auto& i : item)
	{
		m_Player->GetInventory()->SetItemSlot(i.item, 1, 1);
	}
}

void ItemBar::ItemSlotKey(int vKey, int slot)
{
	if (GetAsyncKeyState(vKey)) {
		if (m_SelectNum != slot) {
			m_SelectNum = slot;

			m_itemInventory[m_SelectNum].m_itemBase->ResetUseItemSelect(this);
			m_itemInventory[m_SelectNum].m_itemBase->SelectItemAction(this);

			/// 			////パラメータ
			//ObjectParams param;
			//param.BlockID = m_SelectNum;
			//param.Durable = 500;
			//m_PlacementObject->SetParams(param);
		}
	}
}

void ItemBar::SetItemDatas()
{
	auto* datas = ItemDataFile::GetInstance();
	int i = 0;
	for (; i < 3; i++)
	{
		m_itemInventory[i].m_itemBase = datas->GetBlockDataTypeID(i);
	}
	for (int j = 0; i < 6; j++)
	{
		m_itemInventory[i].m_itemBase = datas->GetTerrainDataTypeID(j);
		i++;
	}
	for (int j = 0; i < 8; j++)
	{
		m_itemInventory[i].m_itemBase = datas->GetNullGameItem();
		i++;
	}
}
