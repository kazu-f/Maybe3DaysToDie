#include "stdafx.h"
#include "GameItemBase.h"
#include "ItemDataFile.h"
#include "ItemBar/ItemBar.h"
#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"

namespace {
	const float ItemOneBoxSize = 75.0f;
}

GameItemBase::GameItemBase(SItemDataPtr& itemData)
{
	//ユニークポインタを受け渡す。
	m_itemData = std::move(itemData);

	//if (m_itemData->tkmPath.size() > 0) {
	//	m_itemModel = NewGO<prefab::ModelRender>(10);
	//	//モデル読み込み。
	//	ModelInitData modelData;
	//	modelData.m_tkmFilePath = m_itemData->tkmPath.c_str();
	//	m_itemModel->Init(modelData);
	//	m_itemModel->SetActiveFlag(false);
	//}

	std::string ddsFilePath = m_itemData->iconPath;
	int pos = static_cast<int>(ddsFilePath.find(".png"));
	ddsFilePath.replace(pos, 4, ".dds");
	m_itemData->iconPath = ddsFilePath;
}

GameItemBase::~GameItemBase()
{
	if (m_itemModel != nullptr && !m_itemModel->IsDead())
	{
		DeleteGO(m_itemModel);
	}
}

void GameItemBase::SelectItemAction(ItemBar* itemBar)
{
	SetToolHand(itemBar);
}

void GameItemBase::UseItemAction1(ItemBar* itemBar)
{
	auto* destroy = itemBar->GetDestroyObject();
	itemBar->SetInventory(destroy->AddObjectDamage());
}

void GameItemBase::ResetUseItemSelect(ItemBar* itemBar)
{
	SetToolHand(itemBar);
	SetPlaceNone(itemBar);
}

void GameItemBase::SetToolHand(ItemBar* itemBar)
{
	auto* destroy = itemBar->GetDestroyObject();
	auto* hand = ItemDataFile::GetInstance()->GetHandTool();
	destroy->SetTool(hand);
}

void GameItemBase::SetPlaceNone(ItemBar* itemBar)
{
	auto* place = itemBar->GetPlacementObject();
	ObjectParams param;
	place->SetParams(param);
}
