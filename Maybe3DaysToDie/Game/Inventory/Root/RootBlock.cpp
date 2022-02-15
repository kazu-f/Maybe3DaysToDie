#include "stdafx.h"
#include "RootBlock.h"
#include "Item/ItemDataFile.h"
#include <random>

RootBlock::RootBlock()
{
	//初期化
	Init();
}
RootBlock::~RootBlock()
{
	OnDestroy();
}

void RootBlock::OnDestroy()
{
	////メモリ開放
	//for (auto& x : m_item)
	//{
	//	for (auto& item : x)
	//	{
	//		delete item;
	//	}
	//}
}

void RootBlock::Init()
{
	////メモリ確保
	//for (auto& x : m_item)
	//{
	//	for (auto& item : x)
	//	{
	//		//アイテムをnew
	//		SItemDataPtr ItemData;
	//		item = new GameItemBase(ItemData);
	//	}
	//}
}

std::vector<Item>& RootBlock::Root(int id)
{
	//データファイルを取得
	const auto& DataFile = ItemDataFile::GetInstance();
	m_item.clear();
	//ルートテーブルのリストを取得
	const RootInsideItemDataList& rootList = GetTable(id);
	//ランダムの初期化
	std::random_device rd;
	std::default_random_engine eng(rd());
	//ランダム生成
	for (int kinds = 0; kinds < rootList.size(); kinds++)
	{
		if (rootList[kinds].insideID == -1)
		{
			return m_item;
		}
		//確率なので0～100に範囲を指定
		std::uniform_int_distribution<int> distr(0, 100);
		//ランダム生成
		int probility = distr(eng);
		if (probility > rootList[kinds].insideProbility)
		{
			//入っていない
			continue;
		}
		//入っているので個数を取得
		//範囲を指定
		std::uniform_int_distribution<int> distr2(rootList[kinds].minNum, rootList[kinds].maxNum);
		//アイテム生成
		Item item;
		//アイテムのデータを取得する
		item.item = DataFile->GetItemDataBase(rootList[kinds].insideID);
		//スタック数をランダム生成
		item.stack = distr2(eng);

		//アイテムの配列に追加
		m_item.push_back(item);
	}

	return m_item;
}

const RootInsideItemDataList& RootBlock::GetTable(int id)
{
	//データファイルをまずは取得する
	const auto& DataFile = ItemDataFile::GetInstance();
	auto* rootBlock = DataFile->GetPlaceData(id);
	return rootBlock->GetRootInsideItemData();
}
