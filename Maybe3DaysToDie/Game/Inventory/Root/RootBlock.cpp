#include "stdafx.h"
#include "RootBlock.h"
#include "Item/ItemDataFile.h"
#include <random>

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
	////�������J��
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
	////�������m��
	//for (auto& x : m_item)
	//{
	//	for (auto& item : x)
	//	{
	//		//�A�C�e����new
	//		SItemDataPtr ItemData;
	//		item = new GameItemBase(ItemData);
	//	}
	//}
}

std::vector<Item>& RootBlock::Root(int id)
{
	//�f�[�^�t�@�C�����擾
	const auto& DataFile = ItemDataFile::GetInstance();
	m_item.clear();
	//���[�g�e�[�u���̃��X�g���擾
	const RootInsideItemDataList& rootList = GetTable(id);
	//�����_���̏�����
	std::random_device rd;
	std::default_random_engine eng(rd());
	//�����_������
	for (int kinds = 0; kinds < rootList.size(); kinds++)
	{
		if (rootList[kinds].insideID == -1)
		{
			return m_item;
		}
		//�m���Ȃ̂�0�`100�ɔ͈͂��w��
		std::uniform_int_distribution<int> distr(0, 100);
		//�����_������
		int probility = distr(eng);
		if (probility > rootList[kinds].insideProbility)
		{
			//�����Ă��Ȃ�
			continue;
		}
		//�����Ă���̂Ō����擾
		//�͈͂��w��
		std::uniform_int_distribution<int> distr2(rootList[kinds].minNum, rootList[kinds].maxNum);
		//�A�C�e������
		Item item;
		//�A�C�e���̃f�[�^���擾����
		item.item = DataFile->GetItemDataBase(rootList[kinds].insideID);
		//�X�^�b�N���������_������
		item.stack = distr2(eng);

		//�A�C�e���̔z��ɒǉ�
		m_item.push_back(item);
	}

	return m_item;
}

const RootInsideItemDataList& RootBlock::GetTable(int id)
{
	//�f�[�^�t�@�C�����܂��͎擾����
	const auto& DataFile = ItemDataFile::GetInstance();
	auto* rootBlock = DataFile->GetPlaceData(id);
	return rootBlock->GetRootInsideItemData();
}
