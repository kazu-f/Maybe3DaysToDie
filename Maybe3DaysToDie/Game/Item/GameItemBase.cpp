#include "stdafx.h"
#include "GameItemBase.h"
#include "ItemBar.h"

namespace {
	const float ItemOneBoxSize = 75.0f;
}

GameItemBase::GameItemBase(SItemDataPtr& itemData)
{
	//ユニークポインタを受け渡す。
	m_itemData = std::move(itemData);

	if (m_itemData->tkmPath.size() > 0) {
		m_itemModel = NewGO<prefab::ModelRender>(10);
		//モデル読み込み。
		ModelInitData modelData;
		modelData.m_tkmFilePath = m_itemData->tkmPath.c_str();
		m_itemModel->Init(modelData);
		m_itemModel->SetActiveFlag(false);
	}

	if (m_itemData->iconPath.size() > 0) {
		m_itemIcon = NewGO<prefab::CSpriteRender>(10);
		//ファイルパスをpngからddsに変換。
		std::string ddsFilePath = m_itemData->iconPath;
		int pos = static_cast<int>(ddsFilePath.find(".png"));
		ddsFilePath.replace(pos, 4, ".dds");

		//アイテム用のアイコンを読み込む。
		m_itemIcon->Init(ddsFilePath.c_str(), ItemOneBoxSize, ItemOneBoxSize);
		m_itemIcon->SetActiveFlag(false);
	}
}

GameItemBase::~GameItemBase()
{
	if (m_itemModel != nullptr && !m_itemModel->IsDead())
	{
		DeleteGO(m_itemModel);
	}
	if (m_itemIcon != nullptr && !m_itemIcon->IsDead())
	{
		DeleteGO(m_itemIcon);
	}
}

void GameItemBase::UseItemAction1(ItemBar* itemBar)
{

}
