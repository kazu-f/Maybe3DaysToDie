#pragma once
class GameItemBase;

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
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
};

