#pragma once
#include "Item/GameItemPlaceObj.h"

//struct Table {
//	std::vector<RootItem> m_Table;
//	char TableID = -1;
//};

enum class RootType {
	CardBoard,		//�i�{�[��
	ShelfBlock,		//�I
	Num
};
class RootTable
{
public:
	RootTable();
	~RootTable() {}

	std::vector<SRootInsideItemData>* GetRootTable(int i)
	{
		const auto& it = m_table.find(i);
		if (it != m_table.end())
		{
			return &it->second;
		}
		return nullptr;
	}

private:
	/// <summary>
	/// �e�[�u���̏�����
	/// </summary>
	void Init();

private:
	std::map<int, std::vector<SRootInsideItemData>> m_table;
};