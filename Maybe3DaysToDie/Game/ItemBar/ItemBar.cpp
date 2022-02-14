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
	return true;
}
void ItemBar::Update()
{
	if (m_Player->GetState() != Player::State::Menu) {
		if (GetAsyncKeyState(MK_LBUTTON)) {
			m_InstallTime += GameTime().GetFrameDeltaTime();
			if (m_InstallTime > 0.2f) {
				m_PlacementObject->PlaceObject();
				m_InstallTime = 0.0f;
			}
		}
		else {
			m_InstallTime = 0.2f;
		}

		if (GetAsyncKeyState(MK_RBUTTON)) {
			m_DeleteTime += GameTime().GetFrameDeltaTime();
			if (m_DeleteTime > 0.2f) {
				m_DestroyObject->AddObjectDamage();
				m_DeleteTime = 0.0f;
			}
		}
		else {
			m_DeleteTime = 0.2f;
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

void ItemBar::ItemSlotKey(int vKey, int slot)
{
	if (GetAsyncKeyState(vKey)) {
		if (m_SelectNum != slot) {
			m_SelectNum = slot;

			//パラメータ
			ObjectParams param;
			param.BlockID = m_SelectNum;
			param.Durable = 500;
			m_PlacementObject->SetParams(param);
		}
	}
}
