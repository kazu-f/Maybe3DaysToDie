#pragma once

struct RootItem
{
	int ItemID = -1;		//�A�C�e����ID
	int Priority = -1;		//�A�C�e���̗D��x
	int AcquireNum = -1;		//�l����
};

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

	std::vector<RootItem>* GetRootTable(int i)
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
	std::map<char, std::vector<RootItem>> m_table;
};