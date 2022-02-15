#include "stdafx.h"
#include "RootTable.h"
#include "Item/ItemDataFile.h"

RootTable::RootTable()
{
	//テーブルの初期化
	Init();
}

void RootTable::Init()
{
	//データファイルをまずは取得する
	const auto& DataFile = ItemDataFile::GetInstance();
	for (int id = 0; id < DataFile->GetPlaceArraySize(); id++)
	{
		auto* rootBlock = DataFile->GetPlaceObjTypeID(id);
		if (rootBlock != nullptr)
		{
			//ルートブロックの時
			//アイテムの情報を入れる
			RootInsideItemDataList itemList;
			itemList = rootBlock->GetRootInsideItemData();
			m_table.insert(std::make_pair(id, itemList));
		}
	}
}