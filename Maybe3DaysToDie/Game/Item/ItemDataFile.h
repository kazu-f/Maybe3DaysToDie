#pragma once
#include "Item/GameItemTool.h"

/// <summary>
/// jsonファイルからツールデータを読み込むクラス。
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;
public:
	ItemDataFile();
	~ItemDataFile();

	void InitItemData(const char* filePath);

private:
	typedef std::vector<GameItemTool*> ToolArray;
	ToolArray m_toolArray;
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
};

