#include "stdafx.h"
#include "RootBlock.h"

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
	//メモリ開放
	for (auto& x : m_item)
	{
		for (auto& item : x)
		{
			delete item;
		}
	}
}

void RootBlock::Init()
{
	//メモリ確保
	for (auto& x : m_item)
	{
		for (auto& item : x)
		{
			//アイテムをnew
			SItemDataPtr ItemData;
			item = new GameItemBase(ItemData);
		}
	}
}
void RootBlock::Root()
{

}