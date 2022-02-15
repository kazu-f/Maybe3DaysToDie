#pragma once

struct RootItem
{
	int ItemID = -1;		//アイテムのID
	int Priority = -1;		//アイテムの優先度
	int AcquireNum = -1;		//獲得個数
};

//struct Table {
//	std::vector<RootItem> m_Table;
//	char TableID = -1;
//};

enum class RootType {
	CardBoard,		//段ボール
	ShelfBlock,		//棚
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
	/// テーブルの初期化
	/// </summary>
	void Init();

private:
	std::map<char, std::vector<RootItem>> m_table;
};