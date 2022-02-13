#include "stdafx.h"
#include "RootBlock.h"

RootBlock::RootBlock()
{
	//������
	Init();
}
RootBlock::~RootBlock()
{
	OnDestroy();
}

void RootBlock::OnDestroy()
{
	//�������J��
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
	//�������m��
	for (auto& x : m_item)
	{
		for (auto& item : x)
		{
			//�A�C�e����new
			SItemDataPtr ItemData;
			item = new GameItemBase(ItemData);
		}
	}
}
void RootBlock::Root()
{

}