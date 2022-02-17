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
	const Vector2 ItemBarPos = { -262.5f,-285.0f };
	const float ItemBarWidthSize = 525.0f;
}

bool ItemBar::Start()
{
	m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
	m_ItemIcon->Init("Assets/sprite/ItemUI/HotBar.dds", ItemBarWidthSize, ItemOneBoxSize);
	m_ItemIcon->SetPosition(ItemBarPos);
	m_ItemIcon->SetPivot({ 0.0f,0.5f });

	for (int i = 0; i < SelectNum; i++) {
		m_SelectPos[i] = { ItemBarPos.x + (ItemOneBoxSize * i) ,ItemBarPos.y };
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

	for (int i = 0; i < Inventory_X; i++) {
		m_Player->GetInventory()->SetItemSlot(m_itemInventory[i], i, 0);
	}
	return true;
}
void ItemBar::Update()
{
	for (int i = 0; i < Inventory_X; i++) {
		m_itemInventory[i] = m_Player->GetInventory()->GetItem(i, 0);
	}
	if (m_Player->GetState() != Player::State::Menu) {
		if (MauseInfo::GetInstance()->GetMauseState() ==
			MauseInfo::State::MauseLClick)
		{
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

		if (MauseInfo::GetInstance()->GetMauseState() ==
			MauseInfo::State::MauseRClick) {
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

		MouseWheelUpdate();

		ItemSlotKey('1', 0);
		ItemSlotKey('2', 1);
		ItemSlotKey('3', 2);
		ItemSlotKey('4', 3);
		ItemSlotKey('5', 4);
		ItemSlotKey('6', 5);
		ItemSlotKey('7', 6);
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
	//for (auto& i : item)
	//{
	//	m_Player->GetInventory()->SetItemSlot(i.item, 1, 1);
	//}
}

void ItemBar::MouseWheelUpdate()
{
	int oldNum = m_SelectNum;
	auto MouseInstance = MauseInfo::GetInstance();
	if (MouseInstance->GetMauseState() == MauseInfo::State::MauseWheelUp) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = SelectNum - 1;
		}
		MouseInstance->SetMauseState(MauseInfo::State::None);
	}

	if (MouseInstance->GetMauseState() == MauseInfo::State::MauseWheelDown)
	{
		m_SelectNum++;
		if (m_SelectNum > SelectNum - 1) {
			m_SelectNum = 0;
		}
		MouseInstance->SetMauseState(MauseInfo::State::None);
	}

	if (oldNum != m_SelectNum)
	{
		m_itemInventory[m_SelectNum].m_itemBase->ResetUseItemSelect(this);
		m_itemInventory[m_SelectNum].m_itemBase->SelectItemAction(this);
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
	for (int j = 0; i < SelectNum; j++)
	{
		m_itemInventory[i].m_itemBase = datas->GetNullGameItem();
		i++;
	}
	m_itemInventory[1].m_itemBase = datas->GetPlaceObjTypeID(0);
	m_itemInventory[0].m_itemBase->ResetUseItemSelect(this);
	m_itemInventory[0].m_itemBase->SelectItemAction(this);
}
