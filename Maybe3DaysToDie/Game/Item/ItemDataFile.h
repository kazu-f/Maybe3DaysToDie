#pragma once
class GameItemBase;

/// <summary>
/// json�t�@�C������c�[���f�[�^��ǂݍ��ރN���X�B
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

