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
	for (int i = 0; i < static_cast<int>(RootType::Num); i++)
	{
		//アイテムの情報を入れる
		std::vector<RootItem> item;
	}
}