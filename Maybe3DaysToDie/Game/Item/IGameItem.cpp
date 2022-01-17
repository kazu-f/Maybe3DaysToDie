#include "stdafx.h"
#include "IGameItem.h"

namespace {
	const float ItemOneBoxSize = 75.0f;
}

IGameItem::IGameItem(std::string& itemName, std::string& tkmPath, std::string& iconPath)
{
	m_itemName = itemName;

	if (tkmPath.size() > 0) {
		m_itemModel = NewGO<prefab::ModelRender>(10);
		//モデル読み込み。
		ModelInitData modelData;
		modelData.m_tkmFilePath = tkmPath.c_str();
		m_itemModel->Init(modelData);
	}

	if (iconPath.size() > 0) {
		m_itemIcon = NewGO<prefab::CSpriteRender>(10);
		//ファイルパスをpngからddsに変換。
		std::string ddsFilePath = iconPath;
		int pos = static_cast<int>(ddsFilePath.find(".png"));
		ddsFilePath.replace(pos, 4, ".dds");

		//アイテム用のアイコンを読み込む。
		m_itemIcon->Init(ddsFilePath.c_str(), ItemOneBoxSize, ItemOneBoxSize);
	}
}
