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
	for (int i = 0; i < static_cast<int>(RootType::Num); i++)
	{
		//�A�C�e���̏�������
		std::vector<RootItem> item;
	}
}