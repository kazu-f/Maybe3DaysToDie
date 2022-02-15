#include "stdafx.h"
#include "RootTable.h"
#include "Item/ItemDataFile.h"

RootTable::RootTable()
{
	//�e�[�u���̏�����
	Init();
}

void RootTable::Init()
{
	//�f�[�^�t�@�C�����܂��͎擾����
	const auto& DataFile = ItemDataFile::GetInstance();
	for (int id = 0; id < DataFile->GetPlaceArraySize(); id++)
	{
		auto* rootBlock = DataFile->GetPlaceObjTypeID(id);
		if (rootBlock != nullptr)
		{
			//���[�g�u���b�N�̎�
			//�A�C�e���̏�������
			RootInsideItemDataList itemList;
			itemList = rootBlock->GetRootInsideItemData();
			m_table.insert(std::make_pair(id, itemList));
		}
	}
}